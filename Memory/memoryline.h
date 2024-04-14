#ifndef MEMORYLINE_H
#define MEMORYLINE_H
#include <QString>
#include <QDebug>

class MemoryLine {
public:
    MemoryLine(short address);

    void updateData(char data);
    void incrementData();

    char getData() { return data; }
    short getAddress() { return address; }

private:
    char data;
    short address;
};

#endif // MEMORYLINE_H
