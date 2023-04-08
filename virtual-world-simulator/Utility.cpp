#include "Utility.h"

int Utility::random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
