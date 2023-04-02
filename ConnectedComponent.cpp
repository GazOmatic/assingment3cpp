#include "ConnectedComponent.h"
#define CC ConnectedComponent::ConnectedComponent

CC()
{
    pixelCount = 0;
    id = 0;
    setPair pixels;
}
CC(const ConnectedComponent &rhs) : pixelCount(rhs.pixelCount), id(rhs.id), pixels(rhs.pixels) {}

ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &rhs)
{
    if (this != &rhs)
    {
        this->pixelCount = rhs.pixelCount;
        this->id = rhs.id;
        this->pixels = rhs.pixels;
    }
    return *this;
}
CC(ConnectedComponent &&rhs) : pixelCount(rhs.pixelCount), id(rhs.id), pixels(std::move(rhs.pixels)) {}

ConnectedComponent &ConnectedComponent::operator=(ConnectedComponent &&rhs)
{
    if (this != &rhs)
    {
        this->pixelCount = rhs.pixelCount;
        this->id = rhs.id;
        this->pixels = std::move(rhs.pixels);
    }
    return *this;
}
ConnectedComponent::~ConnectedComponent() {}
ConnectedComponent &ConnectedComponent::operator+=(const ConnectedComponent &rhs)
{
    this->pixelCount += rhs.pixelCount;
    this->pixels.insert(rhs.pixels.begin(), rhs.pixels.end());
    return *this;
}
ConnectedComponent ConnectedComponent::operator+(const ConnectedComponent &rhs) const
{
    ConnectedComponent result = *this;
    result += rhs;
    return result;
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