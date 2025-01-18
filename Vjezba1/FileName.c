#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define FILE_NOT_OPENED (-1)
#define MAX 1024
#define MAX_POINTS 100

typedef struct {
	char name[MAX];
	char surname[MAX];
	int points;
}Students;

int numOfRows(const char* fileName);
Students* LoadStudents(const char* fileName, int numOfStudents);
int printStudents(Students* students, int numOfStudents);

int main() {

	int numberOfStudents = numOfRows("Studenti.txt");
	
	Students* students = LoadStudents("Studenti.txt", numberOfStudents);
	if (students == NULL) {
		printf("Error: Could not load students!");
		return EXIT_FAILURE;
	}

	printStudents(students, numberOfStudents);

	free(students);

	return EXIT_SUCCESS;
}

int numOfRows(const char* fileName) {
	FILE* fp = fopen(fileName, "r");
		if (fp == NULL) {
			printf("Error: Could not open the file!");
			return FILE_NOT_OPENED;
		}

	int totalStudents = 0;
	char buffer[MAX] = 0;

	while (fgets(buffer, MAX, fp)) {
		totalStudents++;
	}

	fclose(fp);

	return totalStudents;
}

Students* LoadStudents(const char* fileName, int numOfStudents) {
	FILE* fp = fopen(fileName, "r");
		if (fp == NULL) {
			printf("Error: Could not open the file!");
			return NULL; //Vraća NULL jer funkcija ne vraća vrijednost nego pokazivač, pa ne može vratiti neku vrijednost
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
		printf("Name: %s %s, Points: %d, Relative points: %f", students[i].name, students[i].surname, students[i].points, relativePoints);
	}
}
