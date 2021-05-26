#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * @brief Helper function used to split strings.
 * 
 * @param stringp 
 * @param delim 
 * @return char* 
 */
char* Utils_StrSplit(char **stringp, const char *delim);

/**
 * @brief Helper function used to copy strings.
 * 
 * @param str 
 * @return char* 
 */
char* Utils_StrCopy(const char* str);

/**
 * @brief Returns min(x, y).
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int Utils_MinNumber(int x, int y);

/**
 * @brief Safely copies a string with varying length to a string with fixed length (ensures that we don't copy unalloacted memory).
 * 
 * @param from 
 * @param to 
 * @param length 
 */
void Utils_StrCopyToFixedLen(char* from, char* to, int length);

#endif