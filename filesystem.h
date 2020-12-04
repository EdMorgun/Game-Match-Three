#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "fstream"

class FileSystem
{
public:
    void virtual reading() = 0;
    void virtual writing(int i, std::string s) = 0;
    virtual ~FileSystem() = default;
};

#endif // FILESYSTEM_H
