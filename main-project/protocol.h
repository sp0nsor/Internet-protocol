#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "constants.h"

struct times
{
    int hour;
    int min;
    int sec;
};

struct protocol
{
    times start;
    times end;
    unsigned int received;
    unsigned int sent;
    char path[MAX_STRING_SIZE];
};

#endif
#pragma once
