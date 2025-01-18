#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX 1024
#define MAX_POINTS 100
#define FILE_NOT_OPENED (-1)

typedef struct {
    char name[MAX];
    char surname[MAX];
    int points;
} Students;

int numOfRows(const char* fileName);
Students* LoadStudents(const char* fileName, int numOfStudents);
int printStudents(Students* students, int numOfStudents);

int main() {
    int totalStudents = numOfRows("Studenti.txt");

    if (totalStudents == FILE_NOT_OPENED) {
        printf("Error: Could not open the file!\n");
        return FILE_NOT_OPENED;
    }

    Students* students = LoadStudents("Studenti.txt", totalStudents);
    if (students == NULL) {
        printf("Error: Could not load students!\n");
        return EXIT_FAILURE;
    }

    printStudents(students, totalStudents);

    free(students);

    return EXIT_SUCCESS;
}

int numOfRows(const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        return FILE_NOT_OPENED;
    }

    char buffer[MAX];
    int totalStudents = 0;

    while (fgets(buffer, MAX, fp)) {
        totalStudents++;
    }

    fclose(fp);
    return totalStudents;
}

Students* LoadStudents(const char* fileName, int numOfStudents) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        return NULL;
    }

    Students* students = (Students*)malloc(numOfStudents * sizeof(Students));
    if (students == NULL) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < numOfStudents; i++) {
        fscanf(fp, "%s %s %d", students[i].name, students[i].surname, &students[i].points);
    }

    fclose(fp);
    return students;
}

int printStudents(Students* students, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        float relativePoints = (float)students[i].points / MAX_POINTS * 100;
        printf("Name: %s, Surname: %s, Points: %d, Relative points: %.2f%%\n",
            students[i].name, students[i].surname, students[i].points, relativePoints);
    }
    return 0;
}
