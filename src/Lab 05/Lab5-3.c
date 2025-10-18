/*
 * Name: Chamod Chirantha Dilshan Kodithuwakku Arachchige
 * Student ID: 233AEB022
 * Course: DE0917 (English) 25/26-R
 * Lab 5 – Task 3: 
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define NAME_LEN     64
#define DATA_FILE    "students.txt"

/* Record format (TSV to allow spaces in name): name<TAB>id<TAB>gpa */
typedef struct {
    char   name[NAME_LEN];
    int    id;
    double gpa;
} Student;

/* Globals avoided where possible in Task 2; in a mini-app like this, keep state local in main and pass pointers */
static void trim_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n && s[n-1] == '\n') s[n-1] = '\0';
}

int load_students(const char *filename, Student *arr, int max_count) {
    if (!filename || !arr || max_count <= 0) return 0;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        /* Gracefully handle missing file */
        return 0;
    }
    int count = 0;
    char line[256];
    while (count < max_count && fgets(line, (int)sizeof line, fp) != NULL) {
        /* Skip empty lines */
        if (line[0] == '\n' || line[0] == '\0') continue;

        Student s = {0};
        /* Parse TSV: name\tid\tgpa (name may contain spaces, but we saved as literal; to support spaces use %*[^\t]) */
        /* We stored name literally; use scanset to read until tab */
        char nameBuf[NAME_LEN] = {0};
        int id = 0;
        double gpa = 0.0;

        if (sscanf(line, "%63[^\t]\t%d\t%lf", nameBuf, &id, &gpa) == 3) {
            strncpy(s.name, nameBuf, NAME_LEN);
            s.name[NAME_LEN - 1] = '\0';
            s.id = id;
            s.gpa = gpa;
            arr[count++] = s;
        } else {
            fprintf(stderr, "Skipping malformed line: %s", line);
        }
    }
    if (fclose(fp) == EOF) {
        perror("Error closing student file");
    }
    return count;
}

int save_students(const char *filename, const Student *arr, int count) {
    if (!filename || !arr || count < 0) return 0;
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening students file for save");
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        /* TSV: name<TAB>id<TAB>gpa */
        if (fprintf(fp, "%s\t%d\t%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            perror("Error writing student record");
            fclose(fp);
            return 0;
        }
    }
    if (fclose(fp) == EOF) {
        perror("Error closing students file after save");
        return 0;
    }
    return 1;
}

void list_students(const Student *arr, int count) {
    if (!arr || count <= 0) {
        printf("No students to display.\n");
        return;
    }
    printf("\n--- Student List (%d) ---\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%d) %s | ID: %d | GPA: %.2f\n", i + 1, arr[i].name, arr[i].id, arr[i].gpa);
    }
    printf("-------------------------\n");
}

int add_student(Student *arr, int count, int max_count) {
    if (!arr || count >= max_count) {
        printf("Cannot add more students (capacity reached).\n");
        return count;
    }

    char name[NAME_LEN];
    char line[128];
    int id = 0;
    double gpa = 0.0;

    printf("Enter name: ");
    if (!fgets(name, (int)sizeof name, stdin)) {
        printf("Input error.\n");
        return count;
    }
    trim_newline(name);
    if (name[0] == '\0') {
        printf("Name cannot be empty.\n");
        return count;
    }

    printf("Enter ID: ");
    if (!fgets(line, (int)sizeof line, stdin)) {
        printf("Input error.\n");
        return count;
    }
    if (sscanf(line, "%d", &id) != 1) {
        printf("Invalid ID.\n");
        return count;
    }

    printf("Enter GPA: ");
    if (!fgets(line, (int)sizeof line, stdin)) {
        printf("Input error.\n");
        return count;
    }
    if (sscanf(line, "%lf", &gpa) != 1) {
        printf("Invalid GPA.\n");
        return count;
    }

    Student s = {0};
    strncpy(s.name, name, NAME_LEN);
    s.name[NAME_LEN - 1] = '\0';
    s.id = id;
    s.gpa = gpa;

    arr[count++] = s;
    printf("Student added successfully!\n");
    return count;
}

static void print_menu(void) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");
    printf("Select an option: ");
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;

    /* Load at startup (gracefully handles missing/empty file) */
    count = load_students(DATA_FILE, students, MAX_STUDENTS);
    if (count > 0) {
        printf("Loaded %d student(s) from %s.\n", count, DATA_FILE);
    } else {
        printf("No existing data found. Starting fresh.\n");
    }

    for (;;) {
        print_menu();
        char choiceLine[32];
        if (!fgets(choiceLine, (int)sizeof choiceLine, stdin)) {
            printf("\nInput ended.\n");
            break;
        }
        int choice = 0;
        if (sscanf(choiceLine, "%d", &choice) != 1) {
            printf("Please enter a number (1-3).\n");
            continue;
        }

        if (choice == 1) {
            list_students(students, count);
        } else if (choice == 2) {
            count = add_student(students, count, MAX_STUDENTS);
        } else if (choice == 3) {
            if (save_students(DATA_FILE, students, count)) {
                printf("Data saved. Goodbye!\n");
            } else {
                printf("Save failed. Exiting anyway.\n");
            }
            break;
        } else {
            printf("Invalid option. Choose 1, 2, or 3.\n");
        }
    }

    return EXIT_SUCCESS;
}
