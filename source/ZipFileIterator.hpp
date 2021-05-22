#ifndef ZIP_FILE_ITERATOR_HPP
#define ZIP_FILE_ITERATOR_HPP

#include <string>

#include "ZipFile.h"

class ZipFileIterator
{
    ZipArchive::Ptr mZipFile;

public:
    ZipFileIterator(const std::string& ZipFile);
    ZipFileIterator(ZipArchive::Ptr ZipFile);

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = void;
        using value_type = ZipArchiveEntry::Ptr;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(std::size_t Idx, ZipArchive::Ptr ZipFile);
        value_type operator*(); // dont return reference (todo)
        Iterator& operator++();
        Iterator operator++(int);

        friend bool operator==(const Iterator& a, const Iterator& b);
        friend bool operator!=(const Iterator& a, const Iterator& b);

    private:
        std::size_t mCurrentIdx;
        ZipArchive::Ptr mZipFile;
    };

    Iterator begin();
    Iterator end();
};

#endif