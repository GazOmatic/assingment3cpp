#include <unordered_set>
class ConnectedComponent
{

public:
    int pixelCount;
    int id;
    std::unordered_set<std::pair<int, int>> pixels;

    ConnectedComponent();
};