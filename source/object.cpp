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
    genHitbox(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);
}

Object2D::Object2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
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
    genHitbox(vertices);
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

void Object2D::genHitbox(std::vector<double> &vertices)
{
    for (int i = 0; i < vertices.size(); i += 4)
    {
        hitbox.push_back({vertices[i], vertices[i + 1]});
    }
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

bool Object2D::inHitbox(dVector2 point)
{
    int i, j;
    bool in = false;
    for (i = 0, j = hitbox.size() - 1; i < hitbox.size(); j = i++)
    {
        double x = hitbox[i].x * scale.x * 2 + position.x;
        double y = hitbox[i].y * scale.y * 2 + position.y;
        double x2 = hitbox[j].x * scale.x * 2 + position.x;
        double y2 = hitbox[j].y * scale.y * 2 + position.y;

        if ((y > point.y) != (y2 > point.y) && (point.x < (x2 - x) * (point.y - y) / (y2 - y) + x))
            in = !in;
    }
    return in;
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

std::vector<dVector2> Object2D::getHitbox() { return hitbox; }
dVector2 Object2D::getPosition() { return position; }
dVector2 Object2D::getScale() { return scale; }
double Object2D::getRotation() { return rotation; }