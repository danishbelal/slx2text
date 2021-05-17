#include "ZipFileIterator.hpp"
#include "ZipFile.h"
#include "icecream.hpp"
#include "pugixml.hpp"

void CheckError(bool Success, std::string ErrorMsg, std::string SuccessMsg)
{
    if (!Success)
    {
        std::cerr << ErrorMsg << std::endl;
        abort();
    }
    else
    {
        std::cout << SuccessMsg << std::endl;
    }
}

void playground(const std::string ModelFile)
{
    // Modell öffnen.
    ZipArchive::Ptr Model = ZipFile::Open(ModelFile);
    CheckError(Model != nullptr, "Failed to open Model", "Model opened successfully");

    // Alle enthaltenen Dateien auflisten.
    // for (int i = 0; i < Model->GetEntriesCount(); ++i)
    // {
    //     ZipArchiveEntry::Ptr E = Model->GetEntry(i);
    //     if (E == nullptr)
    //         continue;
    //     std::cout << i << ": " << E->GetFullName() << std::endl;
    //     std::istream* Stream = E->GetDecompressionStream();
    //     std::cout << Stream->rdbuf() << std::endl;;
    // }

    // Eintrag öffnen.
    ZipArchiveEntry::Ptr Entry = Model->GetEntry("simulink/blockdiagram.xml");
    CheckError(Entry != nullptr, "Failed to open entry", "Opened entry successfully");

    // Stream erzeugen.
    std::istream* FileStream = Entry->GetDecompressionStream();
    CheckError(FileStream != nullptr, "Failed to create stream", "Successfully opened stream");

    // Load it into pugixml
    pugi::xml_document doc;
    pugi::xml_parse_result Result = doc.load(*FileStream);
    CheckError(Result.status == pugi::status_ok, "Failed to parse document", "Parsed document");

    auto Blocks = doc.select_nodes("//System/Block");
    IC(Blocks.size());
    for (auto& BlockNode : Blocks)
    {
        auto Block = BlockNode.node();
        auto Parent = Block.parent().parent();
        std::cout << "Block: "
                  << Parent.attribute("Name").value() << '/'
                  << Block.attribute("BlockType").value() << " "
                  << Block.attribute("Name").value()
                  << std::endl;
    }
}