#pragma once
#include <memory>
#include <string.h>
#include <cstdlib>
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
