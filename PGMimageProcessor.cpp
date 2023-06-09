#include "PGMimageProcessor.h"
#include <iostream>
#include <queue>
#include <algorithm>

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
    file.close();
}
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &rhs)
{
    this->inputImage = rhs.inputImage;
    this->components = rhs.components;
}
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&rhs)
{
    this->inputImage = std::move(inputImage);
    this->components = std::move(components);
}
PGMimageProcessor &PGMimageProcessor::operator=(const PGMimageProcessor &rhs)
{
    if (this != &rhs)
    {
        inputImage = rhs.inputImage;
        components = rhs.components;
    }
    return *this;
}
PGMimageProcessor PGMimageProcessor::operator=(PGMimageProcessor &&rhs)
{
    if (this != &rhs)
    {
        inputImage = std::move(rhs.inputImage);
        components = std::move(rhs.components);
    }
    return *this;
}
PGMimageProcessor::~PGMimageProcessor()
{
    // The PGMimageprocessor uses the image struct which manages its own memory
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
    // save_image("thresh2.pgm",inputImage);

    ConnectedComponent a;

    for (int x = 0; x < inputImage.width; ++x)
    {
        for (int y = 0; y < inputImage.height; ++y)
        {
            // log(inputImage(x,y));
            // print(inputImage(x,y));
            if (inputImage(x, y) == 255)
            {
                a = search(x, y);
                if (a.pixelCount > minValidSize)
                {
                    components.push_back(a);
                }
            }
        }
    }
    print("Found " << components.size() << " components.");
    std::sort(components.begin(),components.end());
    return components.size();
}
int PGMimageProcessor::filterComponentBySize(int minSize, int maxSize)
{
    auto lamb = [&](const ConnectedComponent &comp)
    {
        return (comp.pixelCount < minSize || comp.pixelCount > maxSize) ? true : false;
    };

    auto newEnd = std::remove_if(components.begin(), components.end(), lamb);

    components.erase(newEnd, components.end());

    return components.size();
}

bool PGMimageProcessor::writeComponents(const std::string &outFileName)
{
    ConnectedComponent out;
    // Add all of the connected components together.
    for (auto c : components)
    {
        out += c;
    }
    // Once added iterate through all of the pixels and add it to the original input image
    for (auto p : out.pixels)
    {
        inputImage(p.first, p.second) = 255;
    }
    save_image(outFileName.c_str(), inputImage);
    return true;
}

int PGMimageProcessor::getComponentCount(void) const
{
    return components.size();
}
int PGMimageProcessor::getLargestSize(void) const
{
    // int max = 0;
    // for (auto c : components)
    // {
    //     if (c.pixelCount > max)
    //     {
    //         max = c.pixelCount;
    //     }
    // }
    // Already sorted
    return components.back().pixelCount;
}
int PGMimageProcessor::getSmallestSize(void) const
{
    // int min = INT32_MAX;
    // for (auto c : components)
    // {
    //     if (c.pixelCount < min)
    //     {
    //         min = c.pixelCount;
    //     }
    // }
    return components.front().pixelCount;
}

void PGMimageProcessor::printComponentData(const ConnectedComponent &theComponent) const
{
    print(theComponent.id << "\t" << theComponent.pixelCount);
}
void PGMimageProcessor::printData(void)
{
    print("ID\tPixelCount");
    for (auto c : components)
    {
        printComponentData(c);
    }
}
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
        if (out.pixels.count(current) > 0)
        {
            continue;
        }

        // Check if the pixel is a valid pixel in the image
        if (current.first < 0 || current.first >= inputImage.width || current.second < 0 || current.second >= inputImage.height)
        {
            continue;
        }

        // Check if the pixel is part of the connected component
        if (inputImage(current.first, current.second) == 255)
        {
            out.pixels.insert(current);
            out.pixelCount++;
            inputImage(current) = 0; // Make current pixel black

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