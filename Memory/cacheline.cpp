#include "cacheline.h"

CacheLine::CacheLine(short address, char state): MemoryLine(address) {
    this->state = state;
}

void CacheLine::updateState(char state){
    this->state = state;
}
