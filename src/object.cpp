#include "object.h"

// class Object

Object::Object()
{
    Logger::log("Object created");
}

Object::~Object()
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "' destroyed");
}

void Object::addChild(uInt childID)
{
    childrenIDs.push_back(childID);
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Child '" + std::to_string(childID) + "' added");
}

void Object::removeChild(uInt childID)
{
    for (int i = 0; i < childrenIDs.size(); i++)
    {
        if (childrenIDs[i] == childID)
        {
            childrenIDs.erase(childrenIDs.begin() + i);

            Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Child '" + std::to_string(childID) + "' removed");

            break;
        }
    }
}

std::vector<uInt> Object::getChildren()
{
    return childrenIDs;
}

void Object::clearChildren()
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Clearing children");
    childrenIDs.clear();
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Children cleared");
}

// class Object2D : public Object

Object2D::Object2D()
{
    Logger::log("Object2D created");
}

Object2D::Object2D(uInt id, const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
{
    this->id = id;
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;

    translationMatrix.identity();
    rotationMatrix.identity();
    scaleMatrix.identity();

    translationMatrix.translate({position.x, position.y, 0.0});
    rotationMatrix.rotate(0.0, 0.0, rotation * PI / 180.0);
    scaleMatrix.scale({scale.x, scale.y, 1.0});

    projectionMatrix.identity();
    projectionMatrix.orthographic(0, windowSize.x, 0, windowSize.y, -1, 1);

    genVertices(vertices);
    genHitbox(vertices);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(texturePath);

    Logger::log("Object2D '" + std::to_string(id) + "' created");
}

Object2D::~Object2D()
{
    glDeleteBuffers(1, &vertices);
    glDeleteBuffers(1, &attributes);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shader);

    Logger::log("Object2D '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "' destroyed");
}

void Object2D::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "translation"), 1, GL_FALSE, &translationMatrix.matrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotation"), 1, GL_FALSE, &rotationMatrix.matrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "scale"), 1, GL_FALSE, &scaleMatrix.matrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projectionMatrix.matrix[0][0]);
    glBindVertexArray(attributes);
    glDrawArrays(GL_TRIANGLES, 0, sizeOfVertices);
    glUseProgram(0);
}

void Object2D::transformPosition(const dVector2 &transform)
{
    translationMatrix.translate({transform.x, transform.y, 0.0});
    position.x += transform.x; // change
    position.y += transform.y; // change
}

void Object2D::transformScale(const dVector2 &transform)
{
    scale.x *= transform.x; // change
    scale.y *= transform.y; // change
    scaleMatrix.scale({transform.x, transform.y, 1.0});
}

void Object2D::transformRotation(double transform)
{
    rotation += transform; // change
    rotationMatrix.rotate(0.0, 0.0, transform * PI / 180.0);
}

void Object2D::genVertices(const std::vector<double> &vertices)
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating vertices");

    sizeOfVertices = vertices.size();
    glGenBuffers(1, &this->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * sizeof(double), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Vertices generated");
}

void Object2D::genHitbox(const std::vector<double> &vertices)
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating hitbox");

    for (int i = 0; i < vertices.size(); i += 4)
    {
        hitbox.push_back({vertices[i], vertices[i + 1]});
    }

    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Hitbox generated");
}

void Object2D::genTexture(const std::string &texturePath)
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating texture");

    iVector2 size;
    int numberOfColumns;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath.data(), &size.x, &size.y, &numberOfColumns, 0);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Texture generated");
}

void Object2D::genShader(const std::string &vertexPath, const std::string &fragmentPath)
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating shader");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::ifstream vertexFile(vertexPath);
    std::string vertexSource = "";
    std::string line;
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

    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Shader generated");
}

void Object2D::genAttributes()
{
    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating attributes");

    glGenVertexArrays(1, &attributes);
    glBindVertexArray(attributes);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void *)0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void *)(2 * sizeof(double)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Logger::log("Object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Attributes generated");
}

bool Object2D::inHitbox(const dVector2 &point)
{
    bool in = false;
    int i, j;
    for (i = 0, j = hitbox.size() - 1; i < hitbox.size(); j = i++)
    {
        dVector2 pointA;
        dVector2 pointB;

        pointA.x = (hitbox[i].x * cos(rotation * PI / 180) - hitbox[i].y * sin(rotation * PI / 180)) * scale.x + position.x;
        pointA.y = (hitbox[i].x * sin(rotation * PI / 180) + hitbox[i].y * cos(rotation * PI / 180)) * scale.y + position.y;
        pointB.x = (hitbox[j].x * cos(rotation * PI / 180) - hitbox[j].y * sin(rotation * PI / 180)) * scale.x + position.x;
        pointB.y = (hitbox[j].x * sin(rotation * PI / 180) + hitbox[j].y * cos(rotation * PI / 180)) * scale.y + position.y;

        if ((pointA.y > point.y) != (pointB.y > point.y) && (point.x < (pointB.x - pointA.x) * (point.y - pointA.y) / (pointB.y - pointA.y) + pointA.x))
            in = !in;
    }
    return in;
}

void Object2D::setPosition(const dVector2 &position)
{
    translationMatrix.identity();
    translationMatrix.translate({position.x, position.y, 0.0});
    this->position = position;
}

void Object2D::setScale(const dVector2 &scale)
{
    scaleMatrix.identity();
    scaleMatrix.scale({scale.x, scale.y, 1.0});
    this->scale = scale;
}

void Object2D::setRotation(double rotation)
{
    rotationMatrix.identity();
    rotationMatrix.rotate(0.0, 0.0, rotation * PI / 180.0);
    this->rotation = rotation;
}

dVector2 Object2D::getPosition()
{
    return position;
}

dVector2 Object2D::getScale()
{
    return scale;
}

double Object2D::getRotation()
{
    return rotation;
}

// class Text : public Object2D

Text::Text(uInt id, const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
{
    this->id = id;
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->fontPath = fontPath;

    translationMatrix.identity();
    rotationMatrix.identity();
    scaleMatrix.identity();

    translationMatrix.translate({position.x, position.y, 0.0});
    rotationMatrix.rotate(0.0, 0.0, rotation * PI / 180.0);
    scaleMatrix.scale({scale.x, scale.y, 1.0});

    projectionMatrix.identity();
    projectionMatrix.orthographic(0, windowSize.x, 0, windowSize.y, -1, 1);

    setText(text);
    genAttributes();
    genShader(vertexPath, fragmentPath);
    genTexture(fontPath + ".png");

    Logger::log("Text object '" + std::to_string(id) + "' created");
}

Text::~Text()
{
    glDeleteBuffers(1, &vertices);
    glDeleteBuffers(1, &attributes);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shader);

    Logger::log("Text object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "' destroyed");
}

void Text::genText(const std::string &text)
{
    Logger::log("Text object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Generating text");

    std::vector<double> vertices;

    std::vector<std::string> textVector;
    std::vector<int> characterIndexes;

    std::vector<bool> newLines;

    std::set<std::string> fontCharacters;
    for (std::string character : Utils::loadBinaryStrings(fontPath + ".fc"))
    {
        fontCharacters.insert(character);
    }

    for (char character : text)
    {
        std::string characterString(1, character);
        auto characterMapIndex = fontCharacters.find(characterString);
        if (characterMapIndex != fontCharacters.end())
        {
            textVector.push_back(characterString);
            characterIndexes.push_back(std::distance(fontCharacters.begin(), characterMapIndex));
        }
        else if (character != '\n')
        {
        }
        if (character == '\n')
            newLines.push_back(true);
        else if (newLines.size() < textVector.size())
            newLines.push_back(false);
    }

    if (textVector.size() == 0)
    {
        textVector.push_back(" ");
        characterIndexes.push_back(0);
        newLines.push_back(false);
    }

    std::vector<double> fontVertices = Utils::loadBinaryDoubles(fontPath + ".msh");

    const double characterSize = 1.8;
    int line = 0;
    int prevOffset = 0;
    for (int i = 0; i < textVector.size(); i++)
    {
        if (newLines[i])
        {
            prevOffset = i;
            line++;
        }

        vertices.push_back(1 + i - prevOffset);
        vertices.push_back(1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 2]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 3]);
        vertices.push_back(1 + i - prevOffset);
        vertices.push_back(-1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 6]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 7]);
        vertices.push_back(-1 + i - prevOffset);
        vertices.push_back(1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 10]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 11]);
        vertices.push_back(1 + i - prevOffset);
        vertices.push_back(-1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 14]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 15]);
        vertices.push_back(-1 + i - prevOffset);
        vertices.push_back(-1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 18]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 19]);
        vertices.push_back(-1 + i - prevOffset);
        vertices.push_back(1 - characterSize * line);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 22]);
        vertices.push_back(fontVertices[characterIndexes[i] * 6 * 4 + 23]);
    }

    genVertices(vertices);
    genHitbox(vertices);

    Logger::log("Text object '" + (id == 0 ? "UNKNOWN" : std::to_string(id)) + "': Text generated");
}

void Text::setText(const std::string &text)
{
    this->text = text;
    genText(text);
    genAttributes();
}

std::string Text::getText()
{
    return text;
}

void Text::setFont(const std::string &fontPath)
{
    this->fontPath = fontPath;
    setText(text);
}

std::string Text::getFont()
{
    return fontPath;
}