#ifndef SLX_STUFF_HPP
#define SLX_STUFF_HPP

#include "ZipFile.h"
#include "ZipFileIterator.hpp"
#include "pugixml.hpp"
#include <set>
#include <string>
#include <unordered_map>

/// Determines the Simulink version that was used to create the file.
std::string InferVersion(ZipArchive::Ptr ModelFile);

/// Finds all relationship files in the Zip.
std::set<ZipArchiveEntry::Ptr> FindRelationships(ZipArchive::Ptr ZipFile);

/// Parses the XML File and returns the xml_document
pugi::xml_document ParseXmlFile(ZipArchiveEntry::Ptr File);

/// Finds all relationship files and accumulates their relationships
/// with the corresponding targets.
///
/// The map key is the relationship id.
/// The map value is the relationship target.
std::unordered_map<std::string, std::string> FindRelTargets(ZipArchive::Ptr ZipFile);

/// Searched the (id, target) relationship map for the given Id and returns
/// the corresponding target.
std::string FindRelTargetById(const std::unordered_map<std::string, std::string>& RelTargetIdMap, const std::string Id);

/// Dumps the given XML file to os.  This ensures proper xml formatting, by parsing
/// the document and then dumping the dom.
void DumpXmlFile(std::ostream& os, ZipArchiveEntry::Ptr File);

#endif