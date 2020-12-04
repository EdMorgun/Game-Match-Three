#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include "filesystem.h"
#include "map"

class RecordTable : public FileSystem
{
public:
    RecordTable();
    void reading() override;
    void writing(int i, std::string s) override;
    std::multimap<int, std::string> *getRecordTable();
    ~RecordTable() override;

private:
    std::multimap<int, std::string> *recordTable;
};

#endif // RECORDTABLE_H
