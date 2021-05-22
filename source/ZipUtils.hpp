#ifndef ZIP_UTILS_HPP
#define ZIP_UTILS_HPP

#include "ZipFile.h"

#include <regex>
#include <set>
#include <string>

std::set<ZipArchiveEntry::Ptr> FindFiles(ZipArchive::Ptr ZipFile, const std::regex FilenameSelector);

template <typename StringT>
std::set<ZipArchiveEntry::Ptr> FindFiles(ZipArchive::Ptr ZipFile, const StringT FilenameSelector)
{
    return FindFiles(ZipFile, std::regex(FilenameSelector));
}

#endif