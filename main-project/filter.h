#ifndef FILTER_H
#define FILTER_H

#include "protocol.h"

protocol** filter(protocol* array[], int size, bool (*check)(protocol* element), int& result_size);

bool check_results_by_skype(protocol* element);

bool check_results_by_time(protocol* element);

#endif