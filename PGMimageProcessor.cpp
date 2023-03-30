#include "PGMimageProcessor.h"
#include <iostream>
#define PGMIP PGMimageProcessor
using namespace WRBGAR002;
class PGMIP
{
    PGMIP()
    {
    }
    PGMIP(const std::string filename)
    {
    }
    PGMIP(const PGMIP &rhs)
    {
    }
    PGMIP(PGMIP &&rhs)
    {
    }
    PGMIP &operator=(const PGMIP &rhs)
    {
    }
    PGMIP operator=(PGMIP &&rhs)
    {
    }
    ~PGMIP()
    {
    }

    int extractComponents(unsigned char threshold, int minValidSize)
    {
    }
    int filterComponentBySize(int minSize, int maxSize) {}

    bool writeComponents(const std::string &outFileName) {}

    int getComponentCount(void) const {}
    int getLargestSize(void) const {}
    int getSmallestSize(void) const {}

    void printComponentData(const ConnectedComponent &theComponent) const {}
};
