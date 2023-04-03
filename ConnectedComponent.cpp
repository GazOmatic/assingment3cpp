#include "ConnectedComponent.h"
#define CC ConnectedComponent

int CC::idCount = 0;
CC::CC()
{
    pixelCount = 0;
    id = idCount;
    idCount++;
    setPair pixels;
}
CC::CC(const CC &rhs) : pixelCount(rhs.pixelCount), id(rhs.id), pixels(rhs.pixels) {}

CC &CC::operator=(const CC &rhs)
{
    if (this != &rhs)
    {
        this->pixelCount = rhs.pixelCount;
        this->id = rhs.id;
        this->pixels = rhs.pixels;
    }
    return *this;
}
CC::CC(CC &&rhs) : pixelCount(rhs.pixelCount), id(rhs.id), pixels(std::move(rhs.pixels)) {}

CC &CC::operator=(CC &&rhs)
{
    if (this != &rhs)
    {
        this->pixelCount = rhs.pixelCount;
        this->id = rhs.id;
        this->pixels = std::move(rhs.pixels);
    }
    return *this;
}
CC &CC::operator+=(const CC &rhs)
{
    this->pixelCount += rhs.pixelCount;
    this->pixels.insert(rhs.pixels.begin(), rhs.pixels.end());
    return *this;
}
CC CC::operator+(const CC &rhs) const
{
    CC result = *this;
    result += rhs;
    return result;
}
bool CC::operator<(const CC& rhs) const{
    return pixelCount < rhs.pixelCount;
}

// Easy way to add pairs together
setPair operator+(setPair &lhs, setPair &rhs)
{
    setPair out;
    for (auto x : lhs)
    {
        out.insert(x);
    }
    for (auto x : rhs)
    {
        out.insert(x);
    }
    return out;
}