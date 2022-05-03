#include "time.h"
#include <windows.h>

int getSeconds()
{
    SYSTEMTIME lt;

    GetLocalTime(&lt);

    return lt.wSecond;
}