#include "PGMimageProcessor.cpp"

using namespace WRBGAR002;
int main(int argc, char const *argv[])
{
    // Default values
    int min = 3;
    int max = INT32_MAX;
    int thresh = 128;
    std::string outfilename = "out.pgm";
    bool minMax = false;

    if (argc == 1)
    {
        print("-- FindComponents --");
        print("findcomp [options] <inputPGMfile>");
        print("-s <int> <int> (-s min max)");
        print("-t <int>");
        print("-p print out all the component data");
        print("-w <outPGMfile> write out all retained components");
        print("");
        return 0;
    }
    // Handling the args
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-t")
        {
            thresh = std::stoi(argv[++i]);
        }
        if (arg == "-s")
        {
            min = std::stoi(argv[++i]);
            max = std::stoi(argv[++i]);
            minMax = true;
        }
        if (arg == "-w")
        {
            outfilename = argv[++i];
        }
        if (arg == "-p")
        {
        }
    }

    // Taking in filename to open
    std::string filename = argv[argc-1];
    
    PGMimageProcessor h = PGMimageProcessor(filename);

    h.extractComponents(thresh, min);

    if (minMax)
    {
        h.filterComponentBySize(min, max);
    }

    h.writeComponents(outfilename);

    print(h.components.size());
    return 0;
}
