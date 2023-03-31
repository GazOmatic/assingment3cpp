#include <unordered_set>
class ConnectedComponent
{
    int pixelCount;
    int id;
    std::unordered_set<std::pair<int, int>> pixels;
    public:
    ConnectedComponent();
};