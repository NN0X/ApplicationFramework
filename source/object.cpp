#include "object.h"

// placeholder
#define PI 3.14159265358979323846
// placeholder

void Object::setIndex(int index) { this->index = index; }
int Object::getIndex() { return index; }

void Object::setParent(int parent) { this->parent = parent; }
int Object::getParent() { return parent; }

void Object::addChild(int child) { children.push_back(child); }
void Object::removeChild(int child)
{
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == child)
        {
            children.erase(children.begin() + i);
            break;
        }
    }
}

//-------------------------------------------------------------------
// Object2D

Object2D::Object2D(std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    center = Utility::getCenter2(vertices);

    index = -1;
    parent = -1;
    children = {};

    position = {0, 0};
    scale = {1, 1};
    rotation = 0;

    translationM.identity();
    translationM.translate({position.x, position.y, 0.0});

    rotationM.identity();
    rotationM.rotate(0.0, 0.0, rotation * PI / 180);

    scaleM.identity();
    scaleM.scale({scale.x, scale.y, 1.0});

    projectionM.identity();
    projectionM.orthographic(0, windowSize.x, 0, windowSize.y, -1, 1);

    genVertices(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);
}

Object2D::Object2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    center = Utility::getCenter2(vertices);

    index = -1;
    parent = -1;
    children = {};

    this->position = position;
    this->scale = scale;
    this->rotation = rotation;

    translationM.identity();
    translationM.translate({position.x, position.y, 0.0});

    rotationM.identity();
    rotationM.rotate(0.0, 0.0, rotation * PI / 180);

    scaleM.identity();
    scaleM.scale({scale.x, scale.y, 1.0});

    projectionM.identity();
    projectionM.orthographic(0, windowSize.x, 0, windowSize.y, -1, 1);

    genVertices(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);
}

void Object2D::transformPosition(dVector2 position)
{
    translationM.translate({position.x, position.y, 0.0});
    this->position.x += position.x;
    this->position.y += position.y;
}

void Object2D::transformScale(dVector2 scale)
{
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    scaleM.scale({scale.x, scale.y, 1.0});
}

void Object2D::transformRotation(double rotation)
{
    this->rotation += rotation;
    rotationM.rotate(0.0, 0.0, this->rotation * PI / 180);
}

void Object2D::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "translation"), 1, GL_FALSE, &translationM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotation"), 1, GL_FALSE, &rotationM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "scale"), 1, GL_FALSE, &scaleM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projectionM.m[0][0]);
    glBindVertexArray(attributes);
    glDrawArrays(GL_TRIANGLES, 0, sizeOfVertices);
    glUseProgram(0);
}

void Object2D::genVertices(std::vector<double> &vertices)
{
    sizeOfVertices = vertices.size();

    glGenBuffers(1, &this->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * sizeof(double), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object2D::genTexture(std::string path)
{
    iVector2 size;
    int numCol;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(path.data(), &size.x, &size.y, &numCol, 0);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Object2D::genShader(std::string vertexPath, std::string fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string line;

    std::ifstream vertexFile(vertexPath);
    std::string vertexSource = "";

    while (getline(vertexFile, line))
    {
        vertexSource += line + "\n";
    }

    const char *vertexData = vertexSource.data();

    std::ifstream fragmentFile(fragmentPath);
    std::string fragmentSource = "";

    while (getline(fragmentFile, line))
    {
        fragmentSource += line + "\n";
    }

    const char *fragmentData = fragmentSource.data();

    glShaderSource(vertexShader, 1, &vertexData, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentData, NULL);
    glCompileShader(fragmentShader);

    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Object2D::genAttributes()
{
    glGenVertexArrays(1, &this->attributes);
    glBindVertexArray(this->attributes);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void *)0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void *)(2 * sizeof(double)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Object2D::setPosition(dVector2 position)
{
    translationM.translate({position.x - this->position.x, position.y - this->position.y, 0.0});
    this->position = position;
}

void Object2D::setScale(dVector2 scale)
{
    this->scale = scale;
    scaleM.scale({scale.x, scale.y, 1.0});
}

void Object2D::setRotation(double rotation)
{
    this->rotation = rotation;
    rotationM.rotate(0.0, 0.0, rotation * PI / 180);
}

// -------------------------------------------------------------------
// Object3D

Object3D::Object3D(std::vector<double> &vertices, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    center = Utility::getCenter3(vertices);

    position = {0, 0, 0};
    scale = {1, 1, 1};
    rotation = {0, 0, 0};

    translationM.identity();
    translationM.translate({position.x, position.y, position.z});

    rotationM.identity();
    rotationM.rotate(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);

    scaleM.identity();
    scaleM.scale({scale.x, scale.y, scale.z});

    genVertices(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);
}

Object3D::Object3D(dVector3 position, dVector3 scale, dVector3 rotation, std::vector<double> &vertices, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    center = Utility::getCenter3(vertices);

    this->position = position;
    this->scale = scale;
    this->rotation = rotation;

    translationM.identity();
    translationM.translate({position.x, position.y, position.z});

    rotationM.identity();
    rotationM.rotate(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);

    scaleM.identity();
    scaleM.scale({scale.x, scale.y, scale.z});

    genVertices(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);
}

void Object3D::transformPosition(dVector3 position)
{
    translationM.translate({position.x, position.y, position.z});
    this->position.x += position.x;
    this->position.y += position.y;
    this->position.z += position.z;
}

void Object3D::transformScale(dVector3 scale)
{
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    this->scale.z += scale.z;
    scaleM.scale({scale.x, scale.y, scale.z});
}

void Object3D::transformRotation(dVector3 rotation)
{
    this->rotation.x += rotation.x;
    this->rotation.y += rotation.y;
    this->rotation.z += rotation.z;
    rotationM.rotate(this->rotation.x * PI / 180, this->rotation.y * PI / 180, this->rotation.z * PI / 180);
}

void Object3D::draw(fMatrix4 cameraM)
{
    glUseProgram(shader);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniformMatrix4fv(glGetUniformLocation(shader, "translation"), 1, GL_FALSE, &translationM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotation"), 1, GL_FALSE, &rotationM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "scale"), 1, GL_FALSE, &scaleM.m[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "camera"), 1, GL_FALSE, &cameraM.m[0][0]);
    glBindVertexArray(attributes);
    glDrawArrays(GL_TRIANGLES, 0, sizeOfVertices);
    glUseProgram(0);
}

void Object3D::genVertices(std::vector<double> &vertices)
{
    sizeOfVertices = vertices.size();

    glGenBuffers(1, &this->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * sizeof(double), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object3D::genTexture(std::string path)
{
    iVector2 size;
    int numCol;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(path.data(), &size.x, &size.y, &numCol, 0);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Object3D::genShader(std::string vertexPath, std::string fragmentPath)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string line;

    std::ifstream vertexFile(vertexPath);
    std::string vertexSource = "";

    while (getline(vertexFile, line))
    {
        vertexSource += line + "\n";
    }

    const char *vertexData = vertexSource.data();

    std::ifstream fragmentFile(fragmentPath);
    std::string fragmentSource = "";

    while (getline(fragmentFile, line))
    {
        fragmentSource += line + "\n";
    }

    const char *fragmentData = fragmentSource.data();

    glShaderSource(vertexShader, 1, &vertexData, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentData, NULL);
    glCompileShader(fragmentShader);

    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Object3D::genAttributes()
{
    glGenVertexArrays(1, &this->attributes);
    glBindVertexArray(this->attributes);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void *)0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void *)(3 * sizeof(double)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Object3D::setPosition(dVector3 position)
{
    translationM.translate({position.x - this->position.x, position.y - this->position.y, position.z - this->position.z});
    this->position = position;
}

void Object3D::setScale(dVector3 scale)
{
    this->scale = scale;
    scaleM.scale({scale.x, scale.y, scale.z});
}

void Object3D::setRotation(dVector3 rotation)
{
    this->rotation = rotation;
    rotationM.rotate(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);
}

dVector3 Object3D::getScale() { return scale; }

// -------------------------------------------------------------------
// Camera

Camera::Camera(dVector3 position, dVector3 rotation, double fov, double aspectRatio, double near, double far)
{
    this->position = position;
    this->rotation = rotation;

    projectionM.identity();
    // projectionM.perspective(fov, aspectRatio, near, far);

    viewM.identity();
    viewM.rotate(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);
    viewM.translate({-position.x, -position.y, -position.z});
}

void Camera::transformPosition(dVector3 position)
{
    viewM.translate({-position.x, -position.y, -position.z});
    this->position.x += position.x;
    this->position.y += position.y;
    this->position.z += position.z;
}

void Camera::transformRotation(dVector3 rotation)
{
    this->rotation.x += rotation.x;
    this->rotation.y += rotation.y;
    this->rotation.z += rotation.z;
    viewM.rotate(this->rotation.x * PI / 180, this->rotation.y * PI / 180, this->rotation.z * PI / 180);
}

fMatrix4 Camera::getCameraMatrix() { return Matrix::multiply(projectionM, viewM); }
