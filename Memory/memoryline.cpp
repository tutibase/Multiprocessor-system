#include "memoryline.h"

MemoryLine::MemoryLine(short address)
{
    this->address = address;
    this->data = 0;
}

void MemoryLine::updateData(char data){
    this->data = data;
}

void MemoryLine::incrementData() {
    updateData(this->data + 1);
}
