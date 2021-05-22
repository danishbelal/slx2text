#include <filesystem>
#include <iostream>
#include <string>

#include "icecream.hpp"

#include "SlxUtils.hpp"
#include "ZipUtils.hpp"

#include <toml++/toml.h>

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

    // Does the config file exist?
    std::filesystem::path ConfigFilePath("slx2text-config.toml");
    if (!std::filesystem::exists(ConfigFilePath))
    {
        std::cerr << "Cannot find config file" << std::endl;
        return -1;
    }

    // Read config
    toml::table Config;
    try
    {
        std::ifstream ConfigFileInputStream(ConfigFilePath);
        Config = toml::parse(ConfigFileInputStream);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // Extract list of relationship ids to be printed
    std::set<std::string> ShowIds;
    try
    {
        toml::array* RelIdList = Config["ids"].as_array();
        for (toml::node& Id : *RelIdList)
        {
            Id.visit([&](auto&& e) {
                if constexpr (toml::is_string<decltype(e)>)
                {
                    auto v = Id.value<std::string>().value();
                    ShowIds.emplace(v);
                }
            });
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        IC(InferVersion(Model));
        auto TargetSet = FindRelTargets(Model);

        for (auto Id : ShowIds)
        {
            auto Target = FindRelTargetById(TargetSet, Id);
            auto File = Model->GetEntry(Target);
            DumpXmlFile(std::cout, File);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}