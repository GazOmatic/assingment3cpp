#include "PGMimageProcessor.cpp"

int main(int argc, char const *argv[])
{
    // Default values
    int min = 3;
    int max = INT32_MAX;
    int thresh = 128;
    std::string outfilename = "out.pgm";
    bool minMax = false;
    std::string filename = "";

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
        if (arg.find('.') != -1)
        {
            filename = arg;
        }
    }
    if (filename == "")
    {
        print("No input file provided..");
        return 0;
    }

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
