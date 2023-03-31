#include "PGMimageProcessor.h"
#include <iostream>
using namespace WRBGAR002;

PGMimageProcessor::PGMimageProcessor()
{
}
PGMimageProcessor::PGMimageProcessor(const std::string filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        {
            // Variable to store the version of the PGM
            std::string version;
            std::getline(file, version);
        }

        while (true)
        {
            // Read in lines until 255 is found
            std::string line;
            std::getline(file, line);
            // If comment line is found then skip the rest of the line
            if (line[0] == '#')
            {
                continue;
            }

            // std::cout << line << std::endl;
            if (line == "255")
            {
                break;
            }
            // I think this is more efficient
            int pos = line.find(' ');
            width = std::stoi(line.substr(0, pos));
            height = std::stoi(line.substr(pos));
        }

        // New method of memory allocation
        size_t size = width * height * sizeof(unsigned char);
        image = (unsigned char *)malloc(size);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                unsigned char *pixel = image + (y * width + x);
                file.read(reinterpret_cast<char *>(&pixel), 1);
            }
        }
    }
}
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &rhs)
{
}
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&rhs)
{
}
PGMimageProcessor &PGMimageProcessor::operator=(const PGMimageProcessor &rhs)
{
}
PGMimageProcessor PGMimageProcessor::operator=(PGMimageProcessor &&rhs)
{
}
PGMimageProcessor::~PGMimageProcessor()
{
    free(this->image);
}

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
}
int PGMimageProcessor::filterComponentBySize(int minSize, int maxSize) {}

bool PGMimageProcessor::writeComponents(const std::string &outFileName) {}

int PGMimageProcessor::getComponentCount(void) const {}
int PGMimageProcessor::getLargestSize(void) const {}
int PGMimageProcessor::getSmallestSize(void) const {}

void PGMimageProcessor::printComponentData(const ConnectedComponent &theComponent) const {}
