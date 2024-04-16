#include "utility.h"

void Utility::wait(uInt milliseconds)
{
    Log::log("Waiting " + std::to_string(milliseconds) + " milliseconds");
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Utility::saveBinary(const std::vector<double> &doubles, const std::string &path)
{
    Log::log("Saving binary data to '" + path + "'");

    std::ofstream file(path);

    for (double element : doubles)
    {
        file.write((char *)&element, sizeof(double));
    }

    file.close();

    Log::log("Binary data saved to '" + path + "'");
}

void Utility::saveBinary(const std::vector<std::string> &strings, const std::string &path)
{
    Log::log("Saving binary data to '" + path + "'");

    std::ofstream file(path);

    for (std::string element : strings)
    {
        size_t size = element.size();
        file.write((char *)&size, sizeof(size_t));
        file.write((char *)&element[0], size);
    }

    file.close();

    Log::log("Binary data saved to '" + path + "'");
}

std::vector<double> Utility::loadBinaryDoubles(const std::string &path)
{
    Log::log("Loading binary data from '" + path + "'");

    std::vector<double> data;
    std::ifstream file(path);

    double element;
    while (file.read((char *)&element, sizeof(double)))
    {
        data.push_back(element);
    }

    file.close();

    Log::log("Binary data loaded from '" + path + "'");

    return data;
}

std::vector<std::string> Utility::loadBinaryStrings(const std::string &path)
{
    Log::log("Loading binary data from '" + path + "'");

    std::vector<std::string> data;
    std::ifstream file(path);

    std::string element;
    size_t size;
    while (file.read((char *)&size, sizeof(size_t)))
    {
        element.resize(size);
        file.read((char *)&element[0], size);
        data.push_back(element);
    }

    file.close();

    Log::log("Binary data loaded from '" + path + "'");

    return data;
}

void Utility::genFontFiles()
{
    std::string testChars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    std::vector<double> fontVertices;

    for (int j = 1; j < 7; j++)
    {
        for (int i = 1; i < 17; i++)
        {
            if (i * j == 96)
                break;
            double f1 = 1;
            double f2 = -1;
            double t = 1 / 16.0;
            fontVertices.insert(fontVertices.end(), {
                                                        f1, f1, i * t, 1 - (j - 1) * t,       //
                                                        f1, f2, i * t, 1 - j * t,             //
                                                        f2, f1, (i - 1) * t, 1 - (j - 1) * t, //
                                                        f1, f2, i * t, 1 - j * t,             //
                                                        f2, f2, (i - 1) * t, 1 - j * t,       //
                                                        f2, f1, (i - 1) * t, 1 - (j - 1) * t  //
                                                    });
        }
    }

    Utility::saveBinary(fontVertices, "../resources/fonts/arial/arial.msh"); // msh = mesh

    std::vector<std::string> save;
    for (char c : testChars)
    {
        save.push_back(std::string(1, c));
    }
    Utility::saveBinary(save, "../resources/fonts/arial/arial.fc"); // fc = font characters
}

/*std::vector<double> Utility::loadOBJ(std::string path)
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
}*/