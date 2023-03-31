#include "PGMimageProcessor.cpp"

using namespace WRBGAR002;
int main(int argc, char const *argv[])
{
    PGMimageProcessor h = PGMimageProcessor("chess2.pgm");
    int thresh;
    int min;
    if (argc < 2)
    {
        thresh = 200;
        min = 50;
    }
    else
    {
        thresh = std::stoi(argv[1]);
        min = std::stoi(argv[2]);
    }
    h.extractComponents(thresh, min);
    h.filterComponentBySize(20, 100);

    print(h.components.size());
    return 0;
}
