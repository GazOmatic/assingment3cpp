#include "PGMimageProcessor.h"
#include <iostream>
#include <queue>
using namespace WRBGAR002;

PGMimageProcessor::PGMimageProcessor()
{
}
PGMimageProcessor::PGMimageProcessor(const std::string filename)
{
    int width, height;
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
        // Create input image and allocate
        image img(width, height);
        inputImage = img;
        unsigned char pixel;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                file.read(reinterpret_cast<char *>(&pixel), 1);
                inputImage[y * width + x] = pixel;
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
}

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    for (size_t i = 0; i < inputImage.pixelCount; ++i)
    {
        if (inputImage[i] > threshold)
        {
            inputImage[i] = 255;
        }
        else
        {
            inputImage[i] = 0;
        }
    }
    print("Image has been thresholded...");

    for (int x = 0; x < inputImage.width; ++x)
    {
        for (int y = 0; y < inputImage.height; ++y)
        {
            if (inputImage(x, y) == 255)
            {
                search(x, y);
                print("Started search")
            }
        }
    }
}
int PGMimageProcessor::filterComponentBySize(int minSize, int maxSize) {}

bool PGMimageProcessor::writeComponents(const std::string &outFileName) {}

int PGMimageProcessor::getComponentCount(void) const {}
int PGMimageProcessor::getLargestSize(void) const {}
int PGMimageProcessor::getSmallestSize(void) const {}

void PGMimageProcessor::printComponentData(const ConnectedComponent &theComponent) const {}
void PGMimageProcessor::save_image(const char *filename, const image &img)
{
    // Open the output file
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open())
    {
        std::cerr << "Error: could not write file " << filename << std::endl;
        return;
    }
    // PGM header
    outfile << "P5" << std::endl;
    outfile << img.width << " " << img.height << std::endl;
    outfile << "255" << std::endl;

    outfile.write((char *)img.pixels, img.width * img.height);

    outfile.close();
}
ConnectedComponent PGMimageProcessor::search(int startx, int starty)
{
    ConnectedComponent out;

    std::queue<std::pair<int, int>> toCheck;
    std::pair<int, int> offsets[] = {std::make_pair(0, 1), std::make_pair(0, -1), std::make_pair(1, 0), std::make_pair(-1, 0)};
    std::pair<int, int> current;
    current.first = startx;
    current.second = starty;
    toCheck.push(current);
    while (!toCheck.empty())
    {
        current = toCheck.front();
        toCheck.pop();

        // Check if the pixel is already in the connected component
        if (out.pixels.count(current) > 0) {
            continue;
        }

        // Check if the pixel is a valid pixel in the image
        if (current.first < 0 || current.first >= inputImage.width || current.second < 0 || current.second >= inputImage.height) {
            continue;
        }

        // Check if the pixel is part of the connected component
        if (inputImage(current.first, current.second) == 255)
        {
            out.pixels.insert(current);
            out.pixelCount++;
            inputImage(current) = 0;

            // Add neighboring pixels to the queue
            for (auto p : offsets)
            {
                std::pair<int, int> neighbor = std::make_pair(current.first + p.first, current.second + p.second);
                toCheck.push(neighbor);
            }
        }
    }

    return out;
}
