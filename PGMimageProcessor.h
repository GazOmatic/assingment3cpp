#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string.h>
#include "ConnectedComponent.cpp"
#define print(x) std::cout << x << std::endl;

struct image // Place to hold image
{
    unsigned char *pixels;
    int width, height;
    size_t pixelCount;
    image() : pixels(nullptr), width(0), height(0) {}
    image(int width, int height)
    {
        this->width = width;
        this->height = height;
        size_t size = width * height * sizeof(unsigned char);
        pixelCount = width * height;
        pixels = (unsigned char *)malloc(size);
    }
    image(const image &rhs)
    {
        width = rhs.width;
        height = rhs.height;
        pixelCount = width * height;
        size_t size = width * height * sizeof(unsigned char);
        pixels = (unsigned char *)malloc(size);
        memcpy(pixels, rhs.pixels, size);
    }

    image &operator=(const image &rhs)
    {
        if (this != &rhs)
        {
            free(pixels);
            width = rhs.width;
            height = rhs.height;
            pixelCount = width * height;
            size_t size = width * height * sizeof(unsigned char);
            pixels = (unsigned char *)malloc(size);
            memcpy(pixels, rhs.pixels, size);
        }
        return *this;
    }
    ~image()
    {
        free(pixels);
    }
    operator unsigned char *() const
    {
        return pixels;
    }
    unsigned char &operator()(int x, int y)
    {
        return pixels[y * width + x];
    }
    unsigned char &operator()(std::pair<int, int> loc)
    {
        return pixels[loc.second * width + loc.first];
    }
};

namespace WRBGAR002
{
    class PGMimageProcessor
    {

    public:
        image inputImage;
        std::vector<ConnectedComponent> components;

        PGMimageProcessor();                                        // Default
        PGMimageProcessor(const std::string filename);              // Custom
        PGMimageProcessor(const PGMimageProcessor &rhs);            // Copy
        PGMimageProcessor(PGMimageProcessor &&rhs);                 // Move
        PGMimageProcessor &operator=(const PGMimageProcessor &rhs); // Copy Assing
        PGMimageProcessor operator=(PGMimageProcessor &&rhs);       // Move assign
        ~PGMimageProcessor();                                       // Destructor
        int extractComponents(unsigned char threshold, int minValidSize);
        int filterComponentBySize(int minSize, int maxSize);
        bool writeComponents(const std::string &outFileName);
        int getComponentCount(void) const;
        int getLargestSize(void) const;
        int getSmallestSize(void) const;
        void printComponentData(const ConnectedComponent &theComponent) const;
        void save_image(const char *filename, const image &img);
        ConnectedComponent search(int startx, int starty);
        
    };
}