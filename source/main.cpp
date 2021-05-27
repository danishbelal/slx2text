#include <filesystem>
#include <iostream>
#include <string>

#include "icecream.hpp"

#include "SlxUtils.hpp"
#include "ZipUtils.hpp"

#include "ConfigReader.hpp"

int main(int argc, char** argv)
{
    int SoftErrorOccurred = 0;
    if (argc < 2)
    {
        std::cerr << "Usage: " << '\n'
                  << argv[0] << " <file>" << std::endl;
        return -1;
    }
    auto ModelFilename = argv[1];
    ZipArchive::Ptr Model = ZipFile::Open(ModelFilename);
    if (Model == nullptr)
    {
        std::cerr << "Cannot open " << ModelFilename << std::endl;
        return -1;
    }

    std::set<std::string> ShowIds;
    try
    {
        ShowIds = GetIdsToShow();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    try
    {
        IC(InferVersion(Model));
        auto TargetSet = FindRelTargets(Model);

        for (auto Id : ShowIds)
        {
            auto Target = FindRelTargetById(TargetSet, Id);
            auto File = Model->GetEntry(Target);
            if (File == nullptr)
            {
                std::cerr << "Failed to open " << Target << std::endl;
                SoftErrorOccurred = -1;
                //continue;
                return SoftErrorOccurred;
            }
            DumpXmlFile(std::cout, File);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return SoftErrorOccurred;
}