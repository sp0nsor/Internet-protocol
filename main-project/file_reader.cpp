#include "file_reader.h"
#include "constants.h"

#include <fstream>
#include <cstring>

times convert(char* str)
{
    times result;
    char* context = NULL;
    char* str_number = strtok_s(str, ":", &context);
    result.hour = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.min = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.sec = atoi(str_number);
    return result;
}

void read(const char* file_name, protocol* array[], int& size)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        size = 0;
        char tmp_buffer[MAX_STRING_SIZE];
        while (!file.eof())
        {
            protocol* item = new protocol;
            file >> tmp_buffer;
            item->start = convert(tmp_buffer);
            file >> tmp_buffer;
            item->end = convert(tmp_buffer);
            file >> item->received;
            file >> item->sent;
            file.read(tmp_buffer, 1); // чтения лишнего символа пробела
            file.getline(item->path, MAX_STRING_SIZE);
            array[size++] = item;
        }
        file.close();
    }
    else
    {
        throw "Ошибка открытия файла";
    }
}