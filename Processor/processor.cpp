#include "processor.h"

Processor::Processor(int id) {
    this->id = id;
    this->Cache = {};
    this->requests_num = std::vector<int>(memory_cells_num, 0);

    for (int i = 0; i < cache_lines_num; i++) {
        this->Cache.push_back(CacheLine(i, 'I'));
    }
}

void Processor::readLine(short read_address) {
    requests_num[read_address]++; // подсчет обращения для политики замещения

    // поиск ячейки в кэше
    bool read_hit = 0;
    for (int i = 0; i < cache_lines_num; i++) {
        if (Cache[i].getAddress() == read_address){
            // Смогли считать с кэша нужную ячейку
            char state = Cache[i].getState();
            if (state == 'M' or state == 'E' or
                state == 'S' or state == 'F') {
                // Добавить сообщение в лог: "Данные ячейки read_address переданы в процессор"
                qDebug() << QString("Read Hit, данные ячейки a%1 переданы в процессор").arg(read_address);
                read_hit = true; // обозначаем, что у нас Read Hit
            }
            break; // в кэше точно больше не будет нужной строки -> выходим
        }
    }

    if (!read_hit) {
        // строка в состоянии Invalid (Read Miss) -> считываем с шины
    }

}


void Processor::writeLine(short write_address) {
    requests_num[write_address]++; // подсчет обращения для политики замещения

    // поиск ячейки в кэше
    bool write_hit = 0;
    for (int i = 0; i < cache_lines_num; i++) {
        if (Cache[i].getAddress() == write_address){
            // Смогли найти в кэше нужную ячейку
            char state = Cache[i].getState();
            switch (state) {
            case 'M':
                Cache[i].incrementData();
                write_hit = 1;
                qDebug() << QString("Данные ячейки a%1 перезаписаны с %2 на %3").arg(write_address)
                            .arg(+Cache[i].getData()-1).arg(+Cache[i].getData());
                break;

            case 'E':
                Cache[i].incrementData();
                Cache[i].updateState('M');
                write_hit = 1;
                qDebug() << QString("Данные ячейки a%1 перезаписаны с %2 на %3").arg(write_address)
                            .arg(+Cache[i].getData()-1).arg(+Cache[i].getData());
                break;

            case 'S':
            case 'F':
                Cache[i].incrementData();
                Cache[i].updateState('M');
                write_hit = 1;
                // добавить Write Invalidate на шину
                qDebug() << QString("Данные ячейки a%1 перезаписаны с %2 на %3,"
                                    " на шину отправлен Invalidate").arg(write_address)
                                    .arg(+Cache[i].getData()-1).arg(+Cache[i].getData());
                break;
            }

            break; // в кэше точно больше не будет нужной строки -> выходим
        }
    }

    if (!write_hit) {
        // строка в состоянии Invalid (Write Miss) -> RWITM (считываем с намерением изменить)
    }

}
