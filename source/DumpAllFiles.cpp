#include <iostream>
#include <string>

#include "ZipFile.h"
#include "ZipFileIterator.hpp"

bool IsXmlFile(const std::string Filename)
{
    if (Filename.find(".xml") != std::string::npos)
        return true;
    return false;
};

void DumpFile(std::ostream& out, ZipArchiveEntry::Ptr& Entry)
{
    auto Stream = Entry->GetDecompressionStream();
    out << Stream->rdbuf() << std::endl;
};

void DumpAllFiles(const std::string ModelFile)
{
    ZipFileIterator M(ModelFile);
    for (auto File : M)
    {
        std::cout << "File: " << File->GetFullName() << std::endl;
        if (IsXmlFile(File->GetFullName()))
        {
            DumpFile(std::cout, File);
        }
    }
}
