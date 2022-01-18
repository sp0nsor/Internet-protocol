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
    cout << "������������ ������ �8. GIT\n";
    cout << "������� �5. �������� ������ � ��������\n";
    cout << "�����: ����� ��������\n\n";
    protocol* protocols[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", protocols, size);
        cout << "***** �������� ������ � �������� *****\n\n";
        for (int i = 0; i < size; i++)
        {
            /********** ����� ������� ������������� **********/
            cout << "������..........: ";
            // ����� ������� ������ ������ �������������
            cout << setw(2) << setfill('0') << protocols[i]->start.hour << ":";
            cout << setw(2) << setfill('0') << protocols[i]->start.min << ":";
            cout << setw(2) << setfill('0') << protocols[i]->start.sec << endl;
            cout << "�����...........: ";
            // ����� ������� ����� ������ �������������
            cout << setw(2) << setfill('0') << protocols[i]->end.hour << ":";
            cout << setw(2) << setfill('0') << protocols[i]->end.min << ":";
            cout << setw(2) << setfill('0') << protocols[i]->end.sec << endl;

            /********** ����� �������� ������ **********/
            cout << "��������........: ";
            // ����� ������� ���������� ������ � ������
            cout << protocols[i]->received << endl;
            cout << "����������......: ";
            // ����� ������� ������������ ������ � ������
            cout << protocols[i]->sent << endl;
            
            /********** ����� ��������� **********/
            // ����� ������� ���� � ����������� ���������
            cout << "���������.......: ";
            cout << protocols[i]->path << endl;
            cout << '\n';
        }

        bool (*check_function)(protocol*) = NULL; // check_function - ��� ��������� �� �������, ������������ �������� ���� bool,
                                                          // � ����������� � �������� ��������� �������� ���� book_subscription*
        cout << "\n�������� ������ ���������� ��� ��������� ������:\n";
        cout << "1) �������� ������������� ���� �������� ���������� Skype.\n";
        cout << "2) �������� ������������� ���� �������� ����� 8:00:00.\n";
        cout << "3) ������� ��������� ����� ������������� ���� �������� �������� ����������\n";
        cout << "\n������� ����� ���������� ������: ";
        int item;
        cin >> item;
        cout << '\n';
        switch (item)
        {
        case 1:
            check_function = check_results_by_skype; // ����������� � ��������� �� ������� ��������������� �������
            cout << "***** �������� ������������� ���� �������� ���������� Skype *****\n\n";
            break;
        case 2:
            check_function = check_results_by_time; // ����������� � ��������� �� ������� ��������������� �������
            cout << "***** �������� ������������� ���� �������� ����� 8:00:00 *****\n\n";
            break;
        case 3: {
            cout << "***** C�������� ����� ������������� ���� �������� ���������� *****\n\n";

            char* program = new char [MAX_STRING_SIZE];
            cin.ignore();
            cout << "������� �������� ���������: ";
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
            throw "������������ ����� ������";
        }
        if (check_function)
        {
            int new_size;
            protocol** filtered = filter(protocols, size, check_function, new_size);
            for (int i = 0; i < new_size; i++)
            {
                /********** ����� ������� ������������� **********/
                cout << "������..........: ";
                // ����� ������� ������ ������ �������������
                cout << setw(2) << setfill('0') << filtered[i]->start.hour << ":";
                cout << setw(2) << setfill('0') << filtered[i]->start.min << ":";
                cout << setw(2) << setfill('0') << filtered[i]->start.sec << endl;
                cout << "�����...........: ";
                // ����� ������� ����� ������ �������������
                cout << setw(2) << setfill('0') << filtered[i]->end.hour << ":";
                cout << setw(2) << setfill('0') << filtered[i]->end.min << ":";
                cout << setw(2) << setfill('0') << filtered[i]->end.sec << endl;

                /********** ����� �������� ������ **********/
                cout << "��������........: ";
                // ����� ������� ���������� ������ � ������
                cout << filtered[i]->received << endl;
                cout << "����������......: ";
                // ����� ������� ������������ ������ � ������
                cout << filtered[i]->sent << endl;

                /********** ����� ��������� **********/
                // ����� ������� ���� � ����������� ���������
                cout << "���������.......: ";
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