#include "timer.h"

int getMilliseconds()
{
    SYSTEMTIME lt;

    GetLocalTime(&lt);

    return lt.wMilliseconds;
}