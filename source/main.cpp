#include <iostream>
#include <string>

#include "icecream.hpp"

#include "SlxUtils.hpp"
#include "ZipUtils.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << '\n'
                  << argv[0] << " <file>" << std::endl;
        return -1;
    }
    auto ModelFilename = argv[1];
    ZipArchive::Ptr Model = ZipFile::Open(ModelFilename);

    try
    {
        IC(InferVersion(Model));
        auto Targets = FindRelTargets(Model);

        auto blockDiagram = Targets.find("blockDiagram");
        if (blockDiagram != Targets.end())
        {
            auto [Id, Target] = *blockDiagram;
            auto File = Model->GetEntry(Target);
            std::cout << File->GetDecompressionStream()->rdbuf() << std::endl;
        }

        IC(Targets);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}