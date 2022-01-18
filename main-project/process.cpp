#include "processing.h"
#include <string>
#include <ctype.h>
#include <iostream>

using namespace std;

int delta(times t) {
	return t.hour * 3600 + t.min * 60 + t.sec;
}

int diff(times a, times b)
{
	int x = delta(a);
	int y = delta(b);
	return (x > y ? x - y : y - x);
}

int process(protocol* protocols[], int size, char* program_name)
{
	int time_sum = 0;
	char* cmp = program_name;
	if (strlen(program_name) != 0) {
		for (int i = 0; i < strlen(cmp); i++) {
			cmp[i] = tolower(cmp[i]);
		}

		for (int i = 0; i < size; i++) {
			char* path_lower = protocols[i]->path;
			for (int i = 0; i < strlen(path_lower); i++) {
				path_lower[i] = tolower(path_lower[i]);
			}

			if (strstr(path_lower, cmp) != NULL) {
				time_sum += diff(protocols[i]->end, protocols[i]->start);
			}
		}
	}

	delete cmp;
	return time_sum;
}
