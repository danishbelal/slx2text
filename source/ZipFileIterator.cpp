#include "ZipFileIterator.hpp"

ZipFileIterator::ZipFileIterator(const std::string& ZipFile)
    : mZipFile(ZipFile::Open(ZipFile))
{
}

ZipFileIterator::ZipFileIterator(ZipArchive::Ptr ZipFile)
    : mZipFile(ZipFile)
{
}

ZipFileIterator::Iterator::Iterator(std::size_t Idx, ZipArchive::Ptr ZipFile)
    : mCurrentIdx(Idx)
    , mZipFile(ZipFile)
{
}

ZipFileIterator::Iterator::value_type ZipFileIterator::Iterator::operator*() // dont return reference (todo)
{
    return mZipFile->GetEntry(mCurrentIdx);
}

ZipFileIterator::Iterator& ZipFileIterator::Iterator::operator++()
{
    mCurrentIdx++;
    return *this;
}

ZipFileIterator::Iterator ZipFileIterator::Iterator::operator++(int)
{
    auto tmp { *this };
    ++(*this);
    return tmp;
}

bool operator==(const ZipFileIterator::Iterator& a, const ZipFileIterator::Iterator& b)
{
    // todo: check if the ZipFiles are identical as well
    return a.mCurrentIdx == b.mCurrentIdx;
}

bool operator!=(const ZipFileIterator::Iterator& a, const ZipFileIterator::Iterator& b)
{
    return !(a == b);
}

ZipFileIterator::Iterator ZipFileIterator::begin()
{
    return ZipFileIterator::Iterator(0, mZipFile);
}

ZipFileIterator::Iterator ZipFileIterator::end()
{
    auto NumberofFiles = mZipFile->GetEntriesCount();
    return ZipFileIterator::Iterator(NumberofFiles - 1, mZipFile);
}