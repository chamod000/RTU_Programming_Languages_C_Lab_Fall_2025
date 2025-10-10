/*
 * Lab 3, Task 3
 * Chamod Chirantha Dilshan,233AEB022
 *
 * Implement basic string handling functions.
 * Write your own versions of:
 *   - my_strlen (finds string length)
 *   - my_strcpy (copies string from src to dest)
 *
 * Rules:
 *   - Do not use <string.h> functions for strlen/strcpy.
 *   - Use loops and manual pointer/array access.
 *
 * Example:
 *   char s[] = "hello";
 *   int len = my_strlen(s);   // should return 5
 *
 *   char buffer[100];
 *   my_strcpy(buffer, s);     // buffer now contains "hello"
 */

#include <stdio.h>

// Function prototypes
int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

int main(void) {
    // Test your functions here
    char test[] = "Programming in C";
    char copy[100];

    int len = my_strlen(test);
    printf("Length: %d\n", len);   // 18

    my_strcpy(copy, test);
    printf("Copy: %s\n", copy);    // Programming in C

    return 0;
}

// Implement functions below
int my_strlen(const char *str) {
    if (str == NULL) return 0;
    const char *p = str;
    while (*p) p++;
    return (int)(p - str);
}

void my_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) return;
    while ((*dest++ = *src++) != '\0') {
        /* copy until we hit the terminator */
    }
}

