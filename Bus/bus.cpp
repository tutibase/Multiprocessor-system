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
    emit updateLog(QString("Invalidate по адресу a%1 от CPU %2")
                .arg(lineAddress).arg(id));
    emit updateCacheView();
}


void Bus::BusRead(short lineAddress, int id) {

    short cache_line_num = processors[id]->getLFUcell(lineAddress);

    // отправка в память в случае M или F
    if (processors[id]->getCache()[cache_line_num].getState() == 'F' or
        processors[id]->getCache()[cache_line_num].getState() == 'M')
    {
        emit updateLog(QString("Отправка в память адреса a%1 от CPU %2\nКонец шинного цикла\n")
                       .arg(processors[id]->getCache()[cache_line_num].getAddress()).arg(id));
        emit endBusCycle();
        writeDataToMemory(processors[id]->getCache()[cache_line_num].getAddress(),
                          processors[id]->getCache()[cache_line_num].getData());
    }

    emit updateLog(QString("Чтение адреса a%1 на шине от CPU %2")
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
                emit updateLog(QString("Найден подходящий адрес в кэше CPU %1").arg(i));
            }
        }
    }

    if (!read_from_cache) {
        data = memory[lineAddress].getData();
        emit updateLog(QString("Нет подходящих адресов в кэше CPU, чтение из памяти"));

        // запись data в кэш
        writeDataToCache(id, cache_line_num, lineAddress, data, 'E');
    } else {
        // запись data в кэш
        writeDataToCache(id, cache_line_num, lineAddress, data, 'F');
    }

    emit updateCacheView();
    emit updateLog("Конец шинного цикла\n");
    emit endBusCycle();
}

void Bus::BusRWITM(short lineAddress, int id) {

    short cache_line_num = processors[id]->getLFUcell(lineAddress);
    // отправка в память в случае M или F
    if (processors[id]->getCache()[cache_line_num].getState() == 'F' or
        processors[id]->getCache()[cache_line_num].getState() == 'M')
    {
        emit updateLog(QString("Отправка в память адреса a%1 от CPU %2\nКонец шинного цикла\n")
                       .arg(processors[id]->getCache()[cache_line_num].getAddress()).arg(id));
        emit endBusCycle();
        writeDataToMemory(processors[id]->getCache()[cache_line_num].getAddress(),
                          processors[id]->getCache()[cache_line_num].getData());
    }

    emit updateLog(QString("RWITM адреса a%1 на шине от CPU %2")
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

                emit updateLog(QString("Invalidate адреса a%1 в кэше CPU %2").arg(lineAddress).arg(i));
            }
        }
    }

    if (!read_from_cache) {
        data = memory[lineAddress].getData();
        emit updateLog(QString("Нет подходящих адресов в кэше CPU, чтение из памяти"));
    }

    data++; // считали на запись -> увеличиваем значение
    // запись data в кэш
    writeDataToCache(id, cache_line_num, lineAddress, data, 'M');
    emit updateLog("Конец шинного цикла\n");
    emit endBusCycle();
    emit updateCacheView();
}

void Bus::writeDataToCache(int id, short cache_line_num, short lineAddress, char data, char state) {
    emit updateLog(QString("Запись a%1 в кэш CPU %2").arg(lineAddress).arg(id));
    processors[id]->getCache()[cache_line_num].updateAddress(lineAddress);
    processors[id]->getCache()[cache_line_num].updateData(data);
    processors[id]->getCache()[cache_line_num].updateState(state);
}

void Bus::writeDataToMemory(short lineAddress, char data) {
    memory[lineAddress].updateData(data);
    emit updateMemoryView();
}
