#include "recordtable.h"
#include "filesystem.h"
#include "fstream"
#include "qtextstream.h"
#include "QFile"
#include "QDir"
#include "cstring"
#include "map"

RecordTable::RecordTable()
{
    recordTable = new std::multimap<int, std::string>;
    reading();
}

void RecordTable::reading()
{
    QDir dir;
    QString path = dir.absolutePath() + "/resource/recordtable.txt";
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        char* s1= stream.readLine().toLocal8Bit().data();
        std::string s = (strtok(s1, " "));
        int i = atoi(strtok(nullptr, " "));
        recordTable->emplace(i,s);
    }

    file.close();
}

void RecordTable::writing(int i, std::string s)
{
    std::locale log;
    for (std::string::size_type j = 0; j < s.length(); ++j)
        s[j] = std::toupper(s[j], log);

    recordTable->emplace(i,s);

    QDir dir;
    QString path = dir.absolutePath() + "/resource/recordtable.txt";
    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);
    int y = 0;
    for(std::multimap<int, std::string>::reverse_iterator iterator = recordTable->rbegin(); iterator != recordTable->rend(); iterator++)
    {
        if(y == 8) break;
        stream << (*iterator).second.c_str() << " " << (*iterator).first << endl;
        y++;
    }
    file.close();
}

std::multimap<int, std::string>* RecordTable::getRecordTable()
{
    return recordTable;
}

RecordTable::~RecordTable()
{
    delete recordTable;
}

