#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

#include "protocol.h"
#include "file_reader.h"
#include "constants.h"
#include "filter.h"
#include "processing.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

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

        bool (*check_function)(protocol*) = NULL; // check_function - это указатель на функцию, возвращающую значение типа bool,
                                                          // и принимающую в качестве параметра значение типа book_subscription*
        cout << "\nВыберите способ фильтрации или обработки данных:\n";
        cout << "1) Протокол использования сети Интернет программой Skype.\n";
        cout << "2) Протокол использования сети Интернет после 8:00:00.\n";
        cout << "3) Вывести суммарное время использования сети Интернет заданной программой\n";
        cout << "\nВведите номер выбранного пункта: ";
        int item;
        cin >> item;
        cout << '\n';
        switch (item)
        {
        case 1:
            check_function = check_results_by_skype; // присваиваем в указатель на функцию соответствующую функцию
            cout << "***** Протокол использования сети Интернет программой Skype *****\n\n";
            break;
        case 2:
            check_function = check_results_by_time; // присваиваем в указатель на функцию соответствующую функцию
            cout << "***** Протокол использования сети Интернет после 8:00:00 *****\n\n";
            break;
        case 3: {
            cout << "***** Cуммарное время использования сети Интернет программой *****\n\n";

            char* program = new char [MAX_STRING_SIZE];
            cin.ignore();
            cout << "Введите название программы: ";
            cin.getline(program, MAX_STRING_SIZE, '\n');
            int result = process(protocols, size, program);

            int hour = result / 3600;
            int min = result / 60 - hour * 60;
            int sec = result - hour * 3600 - min * 60;

            cout << setw(2) << setfill('0') << hour << ':';
            cout << setw(2) << setfill('0') << min << ':';
            cout << setw(2) << setfill('0') << sec << '\n';
            break;
        }

        default:
            throw "Некорректный номер пункта";
        }
        if (check_function)
        {
            int new_size;
            protocol** filtered = filter(protocols, size, check_function, new_size);
            for (int i = 0; i < new_size; i++)
            {
                /********** вывод времени использования **********/
                cout << "Начало..........: ";
                // вывод времени начала сессии использования
                cout << setw(2) << setfill('0') << filtered[i]->start.hour << ":";
                cout << setw(2) << setfill('0') << filtered[i]->start.min << ":";
                cout << setw(2) << setfill('0') << filtered[i]->start.sec << endl;
                cout << "Конец...........: ";
                // вывод времени конца сессии использования
                cout << setw(2) << setfill('0') << filtered[i]->end.hour << ":";
                cout << setw(2) << setfill('0') << filtered[i]->end.min << ":";
                cout << setw(2) << setfill('0') << filtered[i]->end.sec << endl;

                /********** вывод передачи данных **********/
                cout << "Получено........: ";
                // вывод размера полученных данных в байтах
                cout << filtered[i]->received << endl;
                cout << "Отправлено......: ";
                // вывод размера отправленных данных в байтах
                cout << filtered[i]->sent << endl;

                /********** вывод программы **********/
                // вывод полного пути к исполняемой программе
                cout << "Программа.......: ";
                cout << filtered[i]->path << endl;
                cout << '\n';
            }
            delete[] filtered;
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