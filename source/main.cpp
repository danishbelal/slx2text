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
        auto TargetSet = FindRelTargets(Model);

        auto Target = FindRelTargetById(TargetSet, "blockDiagram");
        auto File = Model->GetEntry(Target);
        DumpXmlFile(std::cout, File);

        IC(TargetSet);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}