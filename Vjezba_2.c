/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
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

int main() {
    position head = (position)malloc(sizeof(struct person));
    if (!head) return EXIT_FAILURE;
    head->next = NULL;

    addFirst(head, "Ivan", "Ivic", 2004);
    addFirst(head, "Nika", "Nikic", 2011);
    addLast(head, "Luka", "Lukic", 2006);

    printList(head->next);

    position toDelete = findByLname(head->next, "Ivic");
    if (toDelete) {
        deletePerson(head, toDelete);
        printList(head->next);
    }

    freeList(head);
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
