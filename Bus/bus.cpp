#include "bus.h"

Bus::Bus() {
    this->processors = {};
    for (int i = 0; i < processors_num; i++) {
        this->processors.push_back(new Processor(i));
    }

    this->memory = {};
    for (int i = 0; i < memory_cells_num; i++) {
        this->memory.push_back(MemoryLine(i));
    }
}

void Bus::BusInvalidate(short lineAddress, int id) {
    // проходим по всем строчкам кэша в системе
    for (int i = 0; i < processors_num; i++) {
        if (i == id) continue; // пропускаем процессор, отправивший сигнал
        for (int j = 0; j < cache_lines_num; j++) {
            if (processors[i]->getCache()[j].getAddress() == lineAddress) {
                processors[i]->getCache()[j].updateState('I');
                break; // больше в этом процессоре таких строк не будет
            }
        }
    }
    qDebug() << QString("Bus Invalidate to a%1 from processor %2!")
                .arg(lineAddress).arg(id);
}

void Bus::BusShared(short lineAddress) {
    // проходим по всем строчкам кэша в системе
    for (int i = 0; i < processors_num; i++) {
        for (int j = 0; j < cache_lines_num; j++) {
            if (processors[i]->getCache()[j].getAddress() == lineAddress) {
                processors[i]->getCache()[j].updateState('S');
                break; // больше в этом процессоре таких строк не будет
            }
        }
    }
    qDebug() << QString("Bus Shared to a%1!").arg(lineAddress);
}
