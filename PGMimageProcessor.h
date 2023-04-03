#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string.h>
#include "ConnectedComponent.cpp"
#include "image.h"
#define print(x) std::cout << x << std::endl;
#define log(x) std::clog << x << std::endl;


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
    void printData(void);
    void save_image(const char *filename, const image &img);
    ConnectedComponent search(int startx, int starty);
};
