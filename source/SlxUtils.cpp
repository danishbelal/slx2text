#include "SlxUtils.hpp"
#include "ZipUtils.hpp"

#include <algorithm>
#include <ranges>

std::string InferVersion(ZipArchive::Ptr ModelFile)
{
    // The Simulink Version is stored in coreProperties.xml
    auto CoreProperties = FindFiles(ModelFile, "coreProperties.xml");
    if (CoreProperties.empty())
    {
        throw std::runtime_error("No CoreProperties found.");
    }
    // Get the first (and only) entry - there should be only one coreProperties.xml
    auto CoreFile = *CoreProperties.begin();

    auto FileStream = CoreFile->GetDecompressionStream();
    pugi::xml_document doc;
    pugi::xml_parse_result Result = doc.load(*FileStream);
    if (Result.status != pugi::status_ok)
    {
        throw std::runtime_error("Failed to parse file.");
    }

    // Find the version node
    auto VersionNode = doc.select_nodes("//cp:version");

    // There should be only one version node.
    if (VersionNode.size() == 1)
    {
        auto Node = VersionNode.first().node();
        std::string ReleaseName = Node.child_value();
        return ReleaseName;
    }
    else
    {
        throw std::runtime_error("ambigous release (or none)");
    }
}

std::set<ZipArchiveEntry::Ptr> FindRelationships(ZipArchive::Ptr ZipFile)
{
    return FindFiles(ZipFile, ".*.rels");
}

// Needs to be unified with DumpXmlFile  (todo)
pugi::xml_document ParseXmlFile(ZipArchiveEntry::Ptr File)
{
    pugi::xml_document doc;

    auto FileStream = File->GetDecompressionStream();
    auto Status = doc.load(*FileStream);
    if (Status.status != pugi::status_ok)
    {
        std::ostringstream os;
        os << "Cannot parse " << File->GetFullName();
        throw std::runtime_error(os.str());
    }

    return doc;
}

std::unordered_map<std::string, std::string> FindRelTargets(ZipArchive::Ptr ZipFile)
{
    std::unordered_map<std::string, std::string> RelTargets;

    // Find all relationship files and store their (id, target) tuple in the map.
    std::ranges::for_each(FindRelationships(ZipFile), [&](ZipArchiveEntry::Ptr File) {
        auto RelDocument = ParseXmlFile(File);
        auto RelXNodes = RelDocument.select_nodes("//Relationship");
        for (auto& XNode : RelXNodes)
        {
            auto Node = XNode.node();
            auto RelId = Node.attribute("Id").value();
            auto RelTarget = Node.attribute("Target").value();
            RelTargets.emplace(RelId, RelTarget);
        }
    });
    return RelTargets;
}

std::string FindRelTargetById(const std::unordered_map<std::string, std::string>& RelTargetIdMap, const std::string Id)
{
    auto Element = RelTargetIdMap.find(Id);
    if (Element != RelTargetIdMap.end())
    {
        auto [Id, Target] = *Element;
        return Target;
    }
    else
    {
        throw std::runtime_error("Cannot find relationship with id " + Id);
    }
}

void DumpXmlFile(std::ostream& os, ZipArchiveEntry::Ptr File)
{
    // Parse the file and then dump the DOM - this ensures proper xml formatting.
    auto Stream = File->GetDecompressionStream();
    pugi::xml_document doc;
    pugi::xml_parse_result Result = doc.load(*Stream);
    if (Result.status != pugi::status_ok)
    {
        throw std::runtime_error("Failed to parse file " + File->GetFullName());
    }

    // Dump to std::ostream
    doc.save(os);
    os << '\n';
}