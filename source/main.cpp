#include <iostream>
#include <string>

#include "icecream.hpp"

void DumpAllFiles(const std::string ModelFile);

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << '\n'
                  << argv[0] << " <file>" << std::endl;
        return -1;
    }
    auto ModelFilename = argv[1];
    DumpAllFiles(ModelFilename);

    //void playground(const std::string ModelFile);
    //playground(ModelFilename);

    return 0;
}