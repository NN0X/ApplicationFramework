#include "utility.h"

std::vector<double> Utility::loadOBJ(std::string path)
{
    std::vector<std::string> data;
    std::string dataline;
    std::ifstream file(path);

    std::vector<dVector3> vertices;
    std::vector<dVector2> textureCoords;

    std::vector<dVector3> verticesIndexed;
    std::vector<dVector2> textureCoordsIndexed;

    std::vector<int> vertexIndices;
    std::vector<int> textureCoordIndices;

    while (file)
    {
        getline(file, dataline);
        data.push_back(dataline);
    }
    file.close();

    dVector3 vertex;
    dVector2 textureCoord;

    std::string split = "";
    std::istringstream iss;
    for (std::string dataline : data)
    {
        if (dataline[0] == 'v' && dataline[1] == 't')
        {
            textureCoord.x = std::stod(dataline.substr(3, dataline.find(' ', 3)));
            textureCoord.y = std::stod(dataline.substr(dataline.find(' ', 3)));
            textureCoords.push_back(textureCoord);
        }
        else if (dataline[0] == 'v')
        {
            vertex.x = std::stod(dataline.substr(2, dataline.find(' ', 2)));
            vertex.y = std::stod(dataline.substr(dataline.find(' ', 2), dataline.find(' ', dataline.find(' ', 2) + 1)));
            vertex.z = std::stod(dataline.substr(dataline.find(' ', dataline.find(' ', 2) + 1)));
            vertices.push_back(vertex);
        }
        else if (dataline[0] == 'f')
        {
            iss = std::istringstream(dataline);
            while (std::getline(iss, split, ' '))
            {
                if (split.find("/") != -1)
                {
                    vertexIndices.push_back(std::stoi(split.substr(0, split.find("/"))) - 1);
                    textureCoordIndices.push_back(std::stoi(split.substr(split.find("/") + 1, split.length() - split.find("/"))) - 1);
                }
            }
        }
    }

    for (int i = 0; i < vertexIndices.size(); i++)
    {
        verticesIndexed.push_back(vertices[vertexIndices[i]]);
    }

    for (int i = 0; i < textureCoordIndices.size(); i++)
    {
        textureCoordsIndexed.push_back(textureCoords[textureCoordIndices[i]]);
    }

    std::vector<double> objData;
    int i = 0;
    for (dVector3 vertex : verticesIndexed)
    {
        objData.push_back(vertex.x);
        objData.push_back(vertex.y);
        objData.push_back(vertex.z);
        objData.push_back(textureCoordsIndexed[i].x);
        objData.push_back(textureCoordsIndexed[i].y);
        i++;
    }

    return objData;
}

dVector2 Utility::getCenter2(const std::vector<double> &vertices)
{
    dVector2 center = {0, 0};

    // point1 i, i+1, data, data
    // point2 i+4, i+5, data, data
    // point3 i+8, i+9, data, data

    int vertexCount = 0;
    for (int i = 0; i < vertices.size(); i += 12)
    {
        center.x += vertices[i] + vertices[i + 4] + vertices[i + 8];
        center.y += vertices[i + 1] + vertices[i + 5] + vertices[i + 9];
        vertexCount++;
    }

    center.x /= vertexCount;
    center.y /= vertexCount;

    return center;
}

dVector3 Utility::getCenter3(const std::vector<double> &vertices)
{
    dVector3 center = {0, 0, 0};

    // point1 i, i+1, i+2, data, data
    // point2 i+5, i+6, i+7, data, data
    // point3 i+10, i+11, i+12, data, data

    int vertexCount = 0;
    for (int i = 0; i < vertices.size(); i += 15)
    {
        center.x += vertices[i] + vertices[i + 5] + vertices[i + 10];
        center.y += vertices[i + 1] + vertices[i + 6] + vertices[i + 11];
        center.z += vertices[i + 2] + vertices[i + 7] + vertices[i + 12];
        vertexCount++;
    }

    center.x /= vertexCount;
    center.y /= vertexCount;
    center.z /= vertexCount;

    return center;
}