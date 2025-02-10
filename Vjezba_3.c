/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define FILE_NOT_OPENED (-1)
#define MAX_NAME 256

typedef struct person* position;
struct person {
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
};

position createNewPerson(char* fName, char* lName, int birthYear);
int addFirst(position head, char* fName, char* lName, int birthYear);
int addLast(position head, char* fName, char* lName, int birthYear);
int printList(position first);
position findLast(position head);
position findByLname(position first, char* lName);
position findPrevious(position first, position target);
int deletePerson(position head, position toDelete);
int freeList(position head);

int insert_after(position target, char* fname, char* lname, int birth_year);
int insert_before(position head, position target, char* fname, char* lname, int birth_year);
int write_to_file(position first, char* filename);
int read_from_file(position head, char* filename);

int main() {
    position head = (position)malloc(sizeof(struct person));
    if (!head) return EXIT_FAILURE;
    head->next = NULL;

    addFirst(head, "Ivan", "Ivic", 2004);
    addFirst(head, "Nika", "Nikic", 2011);
    addFirst(head, "Luka", "Lukic", 2006);

    addLast(head, "Marko", "Markic", 1998);
    addLast(head, "Ana", "Anic", 2005);

    printf("Lista nakon dodavanja:\n");
    printList(head->next);

    position found = findByLname(head->next, "Nikic");
    if (found) {
        printf("\nPronađena osoba: %s %s, %d\n", found->fname, found->lname, found->birth_year);
    }
    else {
        printf("\nOsoba nije pronađena.\n");
    }

    position toDelete = findByLname(head->next, "Ivic");
    if (toDelete) {
        printf("\nBrisanje osobe: %s %s\n", toDelete->fname, toDelete->lname);
        deletePerson(head, toDelete);
    }

    printf("\nLista nakon brisanja:\n");
    printList(head->next);

    if (write_to_file(head->next, "lista.txt") == FILE_NOT_OPENED) {
        printf("Greška pri otvaranju datoteke za pisanje!\n");
    }

    position newHead = (position)malloc(sizeof(struct person));
    newHead->next = NULL;
    if (read_from_file(newHead, "lista.txt") == FILE_NOT_OPENED) {
        printf("Greška pri otvaranju datoteke za čitanje!\n");
    }
    else {
        printf("\nLista nakon čitanja iz datoteke:\n");
        printList(newHead->next);
    }

    freeList(head);
    freeList(newHead);

    return EXIT_SUCCESS;
}


position createNewPerson(char* fName, char* lName, int birthYear) {
    position newPerson = (position)malloc(sizeof(struct person));
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate the memmory!");
        return NULL;
    }

    strcpy(newPerson->fname, fName);
    strcpy(newPerson->lname, lName);
    newPerson->birth_year = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int addFirst(position head, char* fName, char* lName, int birthYear) {
    position newPerson = createNewPerson(fName, lName, birthYear);
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate the memmory!");
        return FILE_NOT_OPENED;
    }

    newPerson->next = head->next;
    head->next = newPerson;

    return EXIT_SUCCESS;
}

int addLast(position head, char* fName, char* lName, int birthYear) {
    position newPerson = createNewPerson(fName, lName, birthYear);
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate the memmory!");
        return FILE_NOT_OPENED;
    }

    position last = findLast(head);
    last->next = newPerson;

    return EXIT_SUCCESS;
}

int printList(position first) {
    position temp = first;

    while (temp) {
        printf("First name: %s\n Last name: %s\n Birth year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

position findLast(position head) {
    position temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    return temp;
}

position findByLname(position first, char* lName) {
    position temp = first;

    while (temp) {
        if (strcmp(temp->lname, lName) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

position findPrevious(position first, position target) {
    position temp = first;

    if (target == NULL) {
        printf("ERROR!");
        return NULL;
    }

    while (temp->next != NULL && temp->next != target) {
        temp = temp->next;
    }

    return temp;
}

int deletePerson(position head, position toDelete) {
    if (head == NULL || toDelete == NULL) {
        return FILE_NOT_OPENED;
    }

    if (head->next == toDelete) { // Ako je toDelete prvi element
        head->next = toDelete->next;
        free(toDelete);
        return EXIT_SUCCESS;
    }

    position previous = findPrevious(head, toDelete);
    if (previous == NULL) {
        printf("Error!");
        return -1;
    }

    previous->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int freeList(position head) {
    position temp = head->next;

    while (temp) {
        position toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    head->next = NULL;

    return EXIT_SUCCESS;
}

int insert_after(position target, char* fname, char* lname, int birth_year) {
    if (target == NULL) {
        return EXIT_FAILURE;
    }

    position newPerson = createNewPerson(fname, lname, birth_year);
    if (newPerson == NULL) {
        return EXIT_FAILURE;
    }

    newPerson->next = target->next;
    target->next = newPerson;

    return EXIT_SUCCESS;
}

int insert_before(position head, position target, char* fname, char* lname, int birth_year) {
    position previous = findPrevious(head, target);
    if (previous == NULL) {
        return EXIT_FAILURE;
    }

    return insert_after(previous, fname, lname, birth_year);
}

int write_to_file(position first, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open the file!");
        return FILE_NOT_OPENED;
    }

    position temp = first;

    while (temp) {
        fprintf(fp, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int read_from_file(position head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open the file!");
        return FILE_NOT_OPENED;
    }

    char fname[MAX_NAME], lname[MAX_NAME];
    int birth_year;

    while (fscanf(fp, "%s %s %d", fname, lname, &birth_year) == 3) {
        addLast(head, fname, lname, birth_year);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
