#include <array.h>

size_t strlen(char* s) {
    size_t i = 0;
    while (s[i]) i++;
    return i;
}