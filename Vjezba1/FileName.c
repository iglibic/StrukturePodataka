/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100
#define MAX_NAME_LENGTH 256
#define FILE_NOT_OPENED (-1)

typedef struct {
    char fName[MAX_NAME_LENGTH];
    char lName[MAX_NAME_LENGTH];
    int points;
} Student;

int numOfRows(const char* FileName);
Student* loadStudents(const char* FileName, int numOfStudents);
int printStudents(Student* student, int numOfStudents);

int main() {
    int totalStudent = numOfRows("Studenti.txt");

    if (totalStudent == FILE_NOT_OPENED || totalStudent == 0) {
        printf("No students found or file could not be opened!\n");
        return EXIT_FAILURE;
    }

    Student* students = loadStudents("Studenti.txt", totalStudent);
    if (students == NULL) {
        return EXIT_FAILURE;
    }

    printStudents(students, totalStudent);
    free(students);

    return EXIT_SUCCESS;
}

int numOfRows(const char* FileName) {
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL) {
        printf("File could not be opened!\n");
        return FILE_NOT_OPENED;
    }

    int totalStudents = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        totalStudents++;
    }

    fclose(fp);
    return totalStudents;
}

Student* loadStudents(const char* FileName, int numOfStudents) {
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL) {
        printf("File could not be opened!\n");
        return NULL;
    }

    Student* student = (Student*)malloc(numOfStudents * sizeof(Student));
    if (student == NULL) {
        fclose(fp);
        printf("Error! Could not allocate memory!\n");
        return NULL;
    }

    for (int i = 0; i < numOfStudents; i++) {
        if (fscanf(fp, "%s %s %d", student[i].fName, student[i].lName, &student[i].points) != 3) {
            printf("Error reading student data.\n");
            free(student);
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    return student;
}

int printStudents(Student* student, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        double relativePoints = (double)student[i].points / MAX_POINTS * 100;
        printf("Name: %s %s \nPoints: %d \nRelative points: %.2f%%\n\n",
            student[i].fName, student[i].lName, student[i].points, relativePoints);
    }

    return EXIT_SUCCESS;
}
