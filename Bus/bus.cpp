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
            if (processors[i]->getCache()[j].getAddress() == lineAddress)
            {
                processors[i]->getCache()[j].updateState('I');
                break; // больше в этом процессоре таких строк не будет
            }
        }
    }
    emit updateLog(QString("Bus Invalidate to a%1 from processor %2!")
                .arg(lineAddress).arg(id));
    emit updateCacheView();
}

/*
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
}*/

void Bus::BusRead(short lineAddress, int id) {
    emit updateLog(QString("Bus Read to a%1 from processor %2\n")
                .arg(lineAddress).arg(id));

    char data = 0;
    bool read_from_cache = 0;
    // проходим по всем строчкам кэша в системе
    for (int i = 0; i < processors_num; i++) {
        if (i == id) continue; // пропускаем процессор, отправивший сигнал
        for (int j = 0; j < cache_lines_num; j++) {
            if (processors[i]->getCache()[j].getAddress() == lineAddress and
                processors[i]->getCache()[j].getState() != 'I')
            {
                processors[i]->getCache()[j].updateState('S');
                data = processors[i]->getCache()[j].getData();
                read_from_cache = 1;

                emit updateCacheView();
                emit updateLog(QString("Appropriate line in the processor's %1 cache\n").arg(i));
            }
        }
    }
    if (!read_from_cache) {
        data = memory[lineAddress].getData();
        emit updateLog(QString("Read from memory\n"));
        emit updateCacheView();
        // добавить запись data в кэш
        //processors[id]->getCache()[*some line_num from LFU*].updateData(data);
        //processors[id]->getCache()[*some line_num from LFU*].updateState('E');
        return;
    }

    // добавить запись data в кэш
    //processors[id]->getCache()[*some line_num from LFU*].updateData(data);
    //processors[id]->getCache()[*some line_num from LFU*].updateState('F');
    emit updateCacheView();
}

void Bus::BusRWITM(short lineAddress, int id) {
    emit updateLog(QString("Bus RWITM to a%1 from processor %2\n")
                .arg(lineAddress).arg(id));

    char data = 0;
    bool read_from_cache = 0;
    // проходим по всем строчкам кэша в системе
    for (int i = 0; i < processors_num; i++) {
        if (i == id) continue; // пропускаем процессор, отправивший сигнал
        for (int j = 0; j < cache_lines_num; j++) {
            if (processors[i]->getCache()[j].getAddress() == lineAddress and
                processors[i]->getCache()[j].getState() != 'I')
            {
                processors[i]->getCache()[j].updateState('I');
                data = processors[i]->getCache()[j].getData();
                emit updateCacheView();
                read_from_cache = 1;

                emit updateLog(QString("Invalidate line in the processor's %1 cache\n").arg(i));
            }
        }
    }
    if (!read_from_cache) {
        data = memory[lineAddress].getData();
        emit updateLog(QString("Read from memory\n"));
        emit updateCacheView();
        // добавить запись data в кэш
        //processors[id]->getCache()[*some line_num from LFU*].updateData(data);
        //processors[id]->getCache()[*some line_num from LFU*].updateState('E');
        return;
    }

    // добавить запись data в кэш
    //processors[id]->getCache()[*some line_num from LFU*].updateData(data);
    //processors[id]->getCache()[*some line_num from LFU*].updateState('F');
    emit updateCacheView();
}
