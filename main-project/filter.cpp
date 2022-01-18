#include "filter.h"
#include <cstring>
#include <iostream>

protocol** filter(protocol* array[], int size, bool (*check)(protocol* element), int& result_size)
{
	protocol** result = new protocol * [size];
	result_size = 0;
	for (int i = 0; i < size; i++)
	{
		if (check(array[i]))
		{
			result[result_size++] = array[i];
		}
	}
	return result;
}

bool check_results_by_skype(protocol* element)
{
	return strcmp(element->path, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe") == 0;
}

bool check_results_by_time(protocol* element)
{
	int param = 8;
	int cmp = element->start.hour;

	return cmp >= param;
}
