/*
 * Name: Chamod Chirantha Dilshan Kodithuwakku Arachchige
 * Student ID: 233AEB022
 * Course: DE0917 (English) 25/26-R
 * Lab 5 – Task 4 (Bonus): 
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char  name[64];
    int   age;
    double gpa;
} Student;

static long file_size(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) return (long)st.st_size;
    return -1L;
}

int save_student_text(const char *filename, const Student *s) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("open text"); return 0; }
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        perror("write text"); fclose(fp); return 0;
    }
    if (fclose(fp) == EOF) { perror("close text"); return 0; }
    return 1;
}

int save_student_binary(const char *filename, const Student *s) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) { perror("open binary"); return 0; }
    size_t n = fwrite(s, sizeof(*s), 1u, fp);
    if (n != 1u) { perror("write binary"); fclose(fp); return 0; }
    if (fclose(fp) == EOF) { perror("close binary"); return 0; }
    return 1;
}

int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) { perror("open binary read"); return 0; }
    size_t n = fread(out, sizeof(*out), 1u, fp);
    if (n != 1u) {
        if (ferror(fp)) perror("read binary");
        fclose(fp);
        return 0;
    }
    if (fclose(fp) == EOF) { perror("close binary read"); return 0; }
    return 1;
}

int main(void) {
    const char *text_file = "student_text.txt";
    const char *bin_file  = "student_bin.dat";

    Student s = { "Alice", 21, 3.75 };

    printf("Saving student in text and binary formats...\n");
    if (!save_student_text(text_file, &s)) {
        fprintf(stderr, "Failed to save text version.\n");
        return EXIT_FAILURE;
    }
    if (!save_student_binary(bin_file, &s)) {
        fprintf(stderr, "Failed to save binary version.\n");
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    Student loaded = {0};
    if (!load_student_binary(bin_file, &loaded)) {
        fprintf(stderr, "Failed to load binary version.\n");
        return EXIT_FAILURE;
    }
    printf("Loaded student (binary): %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    long txt_sz = file_size(text_file);
    long bin_sz = file_size(bin_file);
    if (txt_sz >= 0 && bin_sz >= 0) {
        printf("Text file size:   %ld bytes\n", txt_sz);
        printf("Binary file size: %ld bytes\n", bin_sz);
    } else {
        printf("Could not determine file sizes.\n");
    }

    return EXIT_SUCCESS;
}
