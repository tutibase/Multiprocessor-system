#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../Memory/cacheline.h"
#include <vector>
#include <QString>
#include <QObject>

const short cache_lines_num = 4;
const short memory_cells_num = 16;
const short processors_num = 4;

class Processor : public QObject {
    Q_OBJECT
public:
    Processor(int id);

    void readLine(short read_address); // запись строки
    void writeLine(short write_address); // чтение строки

    std::vector<CacheLine>& getCache() { return Cache; }
    short getId() { return id; }
    // номер ячейки в кэше, вместо которой можно записать данные адреса
    short getLFUcell(short address);

signals:
    void BusInvalidate(short lineAddress, int id); // сигнал на шину об инвалидации всех ячеек в кэшах с данным адресом
    //void BusShared(short lineAddress); // сигнал на шину о переходе всех ячеек в кэшах с данным адресом в состояние Shared
    void BusRead(short lineAddress, int id); // сигнал на шину о необходимости чтения в кэш процессора ячейки памяти
    void BusRWITM(short lineAddress, int id); // сигнал на шину о необходимости RWITM в кэш процессора ячейки памяти
    void updateLog(QString msg); // отправить сообщение в лог
    void updateCacheView();

private:
    // первая половина ячеек кэша под четные адреса памяти, вторая - нечетные
    std::vector<CacheLine> Cache; // строки кэша процессора
    std::vector<int> requests_num; // количество обращений к каждому адресу для политики замещения
    short id; // номер процессора в системе
};

#endif // PROCESSOR_H
