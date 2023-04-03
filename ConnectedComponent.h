#pragma once
#include <set>

typedef std::set<std::pair<int, int>> setPair;

class ConnectedComponent
{
public:
    static int idCount;
    int pixelCount;
    int id;
    setPair pixels;
    ConnectedComponent();
    ConnectedComponent(const ConnectedComponent &rhs);
    ConnectedComponent &operator=(const ConnectedComponent &rhs);
    ConnectedComponent(ConnectedComponent &&rhs);
    ConnectedComponent &operator=(ConnectedComponent &&rhs);
    ~ConnectedComponent(){};
    ConnectedComponent &operator+=(const ConnectedComponent &rhs);
    ConnectedComponent operator+(const ConnectedComponent &rhs) const;
    bool operator<(const ConnectedComponent &rhs) const;

};