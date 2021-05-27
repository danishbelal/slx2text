#include "ConfigReader.hpp"
#include <filesystem>
#include <iostream>
#include <toml++/toml.h>

std::set<std::string> GetIdsToShow()
{
    std::set<std::string> ShowIds;

    // Does the config file exist?
    std::filesystem::path ConfigFilePath("slx2text-config.toml");
    if (!std::filesystem::exists(ConfigFilePath))
    {
        throw std::runtime_error("Cannot find config file");
    }

    // Read config
    toml::table Config;
    try
    {
        std::ifstream ConfigFileInputStream(ConfigFilePath);
        Config = toml::parse(ConfigFileInputStream);
        toml::array* RelIdList = Config["ids"].as_array();

        // Extract list of relationship ids to be printed
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
        throw std::runtime_error(e.what());
    }
    return ShowIds;
}