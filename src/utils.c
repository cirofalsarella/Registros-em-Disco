#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* Utils_StrSplit(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp) *(*stringp)++ = '\0';
        else *stringp = 0;
    }
    return rv;
}

char* Utils_StrCopy(const char* str) {
    int length = strlen(str);

    if (length <= 0) return NULL;

    char* newStr = calloc(length + 1, sizeof(char));
    for (int i = 0; i < length; ++i) {
        newStr[i] = str[i];
    }
    return newStr;
}

int Utils_MinNumber(int x, int y) {
    return x < y ? x : y;
}

void Utils_StrCopyToFixedLen(char* to, char* from, int length) {
    // If we are trying to copy from a "NULO" string, to becomes empty and with trash ('@')
    if (strcmp(from, "NULO") == 0) {
        for (int i = 1; i < length; ++i) {
            to[i] = '@';
        }
        to[0] = 0;
    } else {
        // Else, safely copies a string with varying length to a string with fixed length (ensures that we don't copy unalloacted memory)
        int lenToCopy = Utils_MinNumber(length, strlen(from));
        for (int i = 0; i < lenToCopy; ++i) {
            to[i] = from[i];
        }

        // Fills up trash as '@'
        for (int i = lenToCopy; i < length; ++i) {
            to[i] = '@';
        }

        // Adds \0 if necessary
        if (lenToCopy < length) {
            to[lenToCopy] = '\0';
        }
    }
}

void Utils_StrPrintWithFixedLen(const char* str, int maxLength) {
    int strLen = strlen(str);
    for (int i = 0; i < (strLen < maxLength ? strLen : maxLength); ++i) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int32_t Utils_StrToInt(const char* str) {
    if (strcmp(str, "NULO") == 0 || strlen(str) == 0) {
        return -1;
    } else {
        return atoi(str);
    }
}