/*
 * week4_3_struct_database.c
 * Author: Chamod Chirantha Dilshan
 * Student ID: 233AEB022
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Students will use malloc to allocate space for multiple Student records,
 *   then input, display, and possibly search the data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define struct Student with fields: name, id, grade
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;
    struct Student *students = NULL;

    // Ask user for number of students
    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    // Allocate memory for n Student structs using malloc
    students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read student data in a loop
    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Grade: ");
        scanf("%f", &students[i].grade);
    }

    // Display all student records in formatted output
    printf("\nID     Name        Grade\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %s   %.1f\n", students[i].id, students[i].name, students[i].grade);
    }

    // Optional: Compute average grade
    float average = 0;
    for (int i = 0; i < n; i++) {
        average += students[i].grade;
    }
    average /= n;
    printf("\nAverage grade: %.2f\n", average);

    // Free allocated memory
    free(students);

    return 0;
}
