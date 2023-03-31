#include <set>
class ConnectedComponent
{
public:
    int pixelCount;
    int id;
    std::set<std::pair<int, int>> pixels;

    ConnectedComponent() : pixelCount(0), id(0) {}

    ConnectedComponent &operator+=(const ConnectedComponent &rhs)
    {
        this->pixelCount += rhs.pixelCount;
        this->pixels.insert(rhs.pixels.begin(), rhs.pixels.end());
        return *this;
    }
    ConnectedComponent operator+(const ConnectedComponent &rhs) const
    {
        ConnectedComponent result = *this;
        result += rhs;
        return result;
    }
};
std::set<std::pair<int, int>> operator+(std::set<std::pair<int, int>> &lhs, std::set<std::pair<int, int>> &rhs)
{
    std::set<std::pair<int, int>> out;
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