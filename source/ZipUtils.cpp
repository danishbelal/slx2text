#include "ZipUtils.hpp"
#include "ZipFileIterator.hpp"
#include <filesystem>

template <typename FilterT>
std::set<ZipArchiveEntry::Ptr> FindFilesFilterPath(ZipArchive::Ptr ZipFile, const std::regex FilenameSelector, FilterT Filter)
{
    std::set<ZipArchiveEntry::Ptr> FoundFiles;

    ZipFileIterator AllFiles(ZipFile);
    for (auto File : AllFiles)
    {
        auto FullPath = File->GetFullName();
        if (std::regex_match(Filter(FullPath), FilenameSelector))
        {
            FoundFiles.emplace(File);
        }
    }
    return FoundFiles;
}

std::set<ZipArchiveEntry::Ptr> FindFiles(ZipArchive::Ptr ZipFile, const std::string FilenameSelector)
{
    // Only consider Filename (i.e. ignore preceding path).
    auto Filter = [](const std::string FullPath) -> std::string {
        return std::filesystem::path(FullPath).filename().string();
    };

    // remove possibly preceding path
    std::filesystem::path Path(FilenameSelector);
    auto Selector = Path.filename().string();

    return FindFilesFilterPath(ZipFile, std::regex(Selector), Filter);
}