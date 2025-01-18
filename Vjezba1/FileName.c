#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 1024
#define MAX_POINTS 100

typedef struct
{
    char name[50];
    char surname[50];
    int points;
} Student;

int NumberOfRows(const char *fileName);
Student *LoadStudents(const char *fileName, int numberOfStudents);
void PrintStudents(Student *students, int numberOfStudents);

int main()
{
    const char *fileName = "imedat.txt";
    int numOfRows = NumberOfRows(fileName);

    if (numOfRows == -1)
    {
        printf("Error opening the file.\n");
        return EXIT_FAILURE; // Replaced ERROR_OF with EXIT_FAILURE
    }

    Student *students = LoadStudents(fileName, numOfRows);

    if (students == NULL)
    {
        printf("Error loading students.\n");
        return EXIT_FAILURE; // Replaced ERROR_OF with EXIT_FAILURE
    }

    PrintStudents(students, numOfRows);

    free(students);

    return EXIT_SUCCESS; // Success message
}

int NumberOfRows(const char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        return -1;
    }

    int numOfRows = 0;
    char buffer[MAX] = {};

    while (fgets(buffer, MAX, fp))
    {
        numOfRows++;
    }

    fclose(fp);
    return numOfRows;
}

Student *LoadStudents(const char *fileName, int numberOfStudents)
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        return NULL;
    }

    Student *students = (Student *)malloc(numberOfStudents * sizeof(Student));
    if (students == NULL)
    {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < numberOfStudents; i++)
    {
        fscanf(fp, "%s %s %d", students[i].name, students[i].surname, &students[i].points);
    }

    fclose(fp);
    return students;
}

void PrintStudents(Student *students, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; i++)
    {
        double relativePoints = (double)students[i].points / MAX_POINTS * 100;
        printf("Name: %s, Surname: %s, Absolute Points: %d, Relative Points: %.2f%%\n",
               students[i].name, students[i].surname, students[i].points, relativePoints);
    }
}
