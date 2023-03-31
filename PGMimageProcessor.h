#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "ConnectedComponent.cpp"
#define print(x) std::cout << x << std::endl;

namespace WRBGAR002
{
    class PGMimageProcessor
    {

        unsigned char *image;
        int width, height;

    public:
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
    };
}