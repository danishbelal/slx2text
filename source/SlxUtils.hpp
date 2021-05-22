#ifndef SLX_STUFF_HPP
#define SLX_STUFF_HPP

#include "ZipFile.h"
#include "ZipFileIterator.hpp"
#include "pugixml.hpp"
#include <set>
#include <string>
#include <unordered_map>

std::string InferVersion(ZipArchive::Ptr ModelFile);
std::set<ZipArchiveEntry::Ptr> FindRelationships(ZipArchive::Ptr ZipFile);
pugi::xml_document ParseXmlFile(ZipArchiveEntry::Ptr File);
std::unordered_map<std::string, std::string> FindRelTargets(ZipArchive::Ptr ZipFile);

#endif