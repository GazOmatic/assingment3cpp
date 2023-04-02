#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string.h>
#include "ConnectedComponent.cpp"
#define print(x) std::cout << x << std::endl;
#define log(x) std::clog << x << std::endl;

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
        free(pixels); // Free the allocated memory
    }
    operator unsigned char *() const // When you call image , it returns the pixels
    {
        return pixels;
    }
    unsigned char &operator()(int x, int y) // Easy way to refer to a certain pixel
    {
        return pixels[y * width + x];
    }
    unsigned char &operator()(std::pair<int, int> loc) // Another way to refer to pixels using a pair value
    {
        return pixels[loc.second * width + loc.first];
    }
};

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
