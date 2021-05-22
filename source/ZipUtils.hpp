#ifndef ZIP_UTILS_HPP
#define ZIP_UTILS_HPP

#include "ZipFile.h"

#include <regex>
#include <set>
#include <string>

/// Iterates through all files contained in the ZipFile and attempts to match
/// their filename stem against the regex.  Therefore possibly preceding paths
/// are ignored.  All files which matched the regex are returned in the std::set.
std::set<ZipArchiveEntry::Ptr> FindFiles(ZipArchive::Ptr ZipFile, const std::regex FilenameSelector);

/// A wrapper for FindFiles(ZipArchive::Ptr, const std::regex).  This can be
/// called with any string type which is then converted to an std::regex.
template <typename StringT>
std::set<ZipArchiveEntry::Ptr> FindFiles(ZipArchive::Ptr ZipFile, const StringT FilenameSelector)
{
    return FindFiles(ZipFile, std::regex(FilenameSelector));
}

#endif