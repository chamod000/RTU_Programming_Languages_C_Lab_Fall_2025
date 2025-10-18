/*
 * Name: Chamod Chirantha Dilshan Kodithuwakku Arachchige
 * Student ID: 233AEB022
 * Course: DE0917 (English) 25/26-R
 * Lab 5 – Task 1: Basic text file I/O
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "data.txt";

    /* --- Write --- */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    printf("Writing lines to %s...\n", filename);
    if (fprintf(fp, "Hello, file I/O in C!\n") < 0 ||
        fprintf(fp, "This is another line.\n") < 0) {
        perror("Error writing to file");
        fclose(fp);
        return EXIT_FAILURE;
    }
    if (fclose(fp) == EOF) {
        perror("Error closing file after write");
        return EXIT_FAILURE;
    }

    /* --- Read --- */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    printf("Reading contents:\n");
    char buffer[256];
    while (fgets(buffer, (int)sizeof buffer, fp) != NULL) {
        fputs(buffer, stdout);
    }

    if (ferror(fp)) {
        perror("Error reading file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fclose(fp) == EOF) {
        perror("Error closing file after read");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
