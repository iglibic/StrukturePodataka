#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OF 1
#define MAX 1024
#define MAX_BODOVA 100

typedef struct {
    char ime[MAX];
    char prezime[MAX];
    int bodovi;
} Student;

int NumberOfRows(const char* fileName);
Student* UcitajStudente(const char* fileName, int numOfRows);
void IspisiStudente(Student* studenti, int numOfRows);

int main() {
    const char* fileName = "imedat.txt";
    int numOfRows = NumberOfRows(fileName);

    if (numOfRows == -1) {
        printf("Greška pri otvaranju datoteke!\n");
        return ERROR_OF;
    }

    Student* studenti = UcitajStudente(fileName, numOfRows);
    
    IspisiStudente(studenti, numOfRows);
    free(studenti);

    return 0;
}

int NumberOfRows(const char* fileName) {
    FILE *fp = NULL;
    int numOfRows = 0;
    char buffer[MAX] = {};

    fp = fopen(fileName, "r");
    if (!fp) {
        return -1;
    }

    while (fgets(buffer, MAX, fp)) {
        if (buffer[0] != '\n') {
            numOfRows++;
        }
    }

    fclose(fp);
    return numOfRows;
}

Student* UcitajStudente(const char* fileName, int numOfRows) {
    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        return NULL;
    }

    Student* studenti = (Student*)malloc(numOfRows * sizeof(Student));
    if (!studenti) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < numOfRows; i++) {
        fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }

    fclose(fp);
    return studenti;
}

void IspisiStudente(Student* studenti, int numOfRows) {
    for (int i = 0; i < numOfRows; i++) {
        float rel_bodovi = (float)studenti[i].bodovi / MAX_BODOVA * 100;
        printf("Ime: %s, Prezime: %s, Bodovi: %d, Relativni bodovi: %.2f%%\n", 
               studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rel_bodovi);
    }
}
