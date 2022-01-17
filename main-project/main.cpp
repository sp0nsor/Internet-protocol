#include <iostream>
#include <iomanip>

using namespace std;

#include "protocol.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
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