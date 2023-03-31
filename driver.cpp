#include "PGMimageProcessor.cpp"

using namespace WRBGAR002;
int main(int argc, char const *argv[])
{
    PGMimageProcessor h = PGMimageProcessor("chess.pgm");
    h.extractComponents(200,100);
    return 0;
}
