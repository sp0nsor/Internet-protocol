#include <iostream>
#include <iomanip>

using namespace std;

#include "protocol.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №5. Протокол работы в Интернет\n";
    cout << "Автор: Роман Кокоткин\n\n";
    protocol* protocols[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", protocols, size);
        cout << "***** Протокол работы в Интернет *****\n\n";
        for (int i = 0; i < size; i++)
        {
            /********** вывод времени использования **********/
            cout << "Начало..........: ";
            // вывод времени начала сессии использования
            cout << setw(2) << setfill('0') << protocols[i]->start.hour << ":";
            cout << setw(2) << setfill('0') << protocols[i]->start.min << ":";
            cout << setw(2) << setfill('0') << protocols[i]->start.sec << endl;
            cout << "Конец...........: ";
            // вывод времени конца сессии использования
            cout << setw(2) << setfill('0') << protocols[i]->end.hour << ":";
            cout << setw(2) << setfill('0') << protocols[i]->end.min << ":";
            cout << setw(2) << setfill('0') << protocols[i]->end.sec << endl;

            /********** вывод передачи данных **********/
            cout << "Получено........: ";
            // вывод размера полученных данных в байтах
            cout << protocols[i]->received << endl;
            cout << "Отправлено......: ";
            // вывод размера отправленных данных в байтах
            cout << protocols[i]->sent << endl;
            
            /********** вывод программы **********/
            // вывод полного пути к исполняемой программе
            cout << "Программа.......: ";
            cout << protocols[i]->path << endl;
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete protocols[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}