#ifndef CACHELINE_H
#define CACHELINE_H
#include "memoryline.h"

class CacheLine : public MemoryLine {
public:
    CacheLine(short address, char state);

    void updateState(char state);
    char getState() { return state; }

private:
    char state; // статус строки в протоколе MERSI – MESIF
};

#endif // CACHELINE_H
