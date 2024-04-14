#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../Memory/cacheline.h"
#include <vector>
#include <QString>

const short cache_lines_num = 4;

class Processor {
public:
    Processor(int id);

    void readLine(short read_address); // запись строки
    void writeLine(short write_address); // чтение строки

    std::vector<CacheLine> getCache() { return Cache; };

private:
    // первая половина ячеек кэша под четные адреса памяти, вторая - нечетные
    std::vector<CacheLine> Cache; // строки кэша процессора
    std::vector<int> requests_num; // количество обращений к каждому адресу для политики замещения
    short id; // номер процессора в системе
};

#endif // PROCESSOR_H
