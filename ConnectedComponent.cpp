#include <set>
class ConnectedComponent
{

public:
    int pixelCount;
    int id;
    std::set<std::pair<int, int>> pixels;

    ConnectedComponent() : pixelCount(0),id(0){}
};