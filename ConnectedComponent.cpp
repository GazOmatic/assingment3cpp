#include <set>
typedef std::set<std::pair<int,int>> setPair;
class ConnectedComponent
{
public:
    int pixelCount;
    int id;
    setPair pixels;

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