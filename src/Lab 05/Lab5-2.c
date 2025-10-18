/*
 * Name: Chamod Chirantha Dilshan Kodithuwakku Arachchige
 * Student ID: 233AEB022
 * Course: DE0917 (English) 25/26-R
 * Lab 5 – Task 2: 
 *

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char  name[64];  /* keep simple for fscanf/fprintf (single-word names safest) */
    int   age;
    double gpa;
} Student;

int save_student(const char *filename, const Student *s) {
    if (filename == NULL || s == NULL) return 0;

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file to save student");
        return 0;
    }
    /* Simple text format: name age gpa (single line) */
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        perror("Error writing student");
        fclose(fp);
        return 0;
    }
    if (fclose(fp) == EOF) {
        perror("Error closing file after save");
        return 0;
    }
    return 1;
}

int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) return 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file to load student");
        return 0;
    }
    /* Read back the same format */
    char nameBuf[64];
    int age;
    double gpa;
    int matched = fscanf(fp, "%63s %d %lf", nameBuf, &age, &gpa);
    if (matched != 3) {
        fprintf(stderr, "Malformed student file: expected 'name age gpa'\n");
        fclose(fp);
        return 0;
    }
    if (fclose(fp) == EOF) {
        perror("Error closing file after load");
        return 0;
    }
    /* Fill output */
    strncpy(out->name, nameBuf, sizeof(out->name));
    out->name[sizeof(out->name)-1] = '\0';
    out->age = age;
    out->gpa = gpa;
    return 1;
}

int main(void) {
    const char *file = "student.txt";
    Student s = { "Alice", 21, 3.75 };

    printf("Saving student to file...\n");
    if (!save_student(file, &s)) {
        fprintf(stderr, "Failed to save student.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    Student loaded;
    if (!load_student(file, &loaded)) {
        fprintf(stderr, "Failed to load student.\n");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return EXIT_SUCCESS;
}
