#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

typedef struct person* position;
struct person {
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
};

position createPerson(char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int append_list(position head, char* fname, char* lname, int birth_year);
int print_list(position first);
position find_by_lname(position first, char* lname);
position find_last(position head);
position find_previous(position first, position target);
int delete_person(position head, position target);
int free_list(position head);

int main() {
    position head = (position)malloc(sizeof(struct person));
    if (!head) return EXIT_FAILURE;
    head->next = NULL;

    addFirst(head, "Ivan", "Horvat", 1998);
    addFirst(head, "Marko", "Novak", 2000);
    addLast(head, "Ana", "Kovač", 1995);

    printf("List of persons:\n");
    printList(head->next);

    position personToDelete = findByLname(head->next, "Novak");
    if (personToDelete) {
        deletePerson(head, personToDelete);
        printf("\nUpdated list after deletion:\n");
        printList(head->next);
    }

    freeList(head);

    return EXIT_SUCCESS;
}

position createPerson(char* fname, char* lname, int birth_year) {
    position new_person = (position)malloc(sizeof(struct person));
    if (new_person == NULL) {
        printf("Error: Memory allocation failed!");
        return NULL;
    }
    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = createPerson(fname, lname, birth_year);
    if (new_person == NULL) {
        printf("Error: Could not allocate the memory!");
        return -1;
    }
    new_person->next = head->next;
    head->next = new_person;

    return EXIT_SUCCESS;
}

int append_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = createPerson(fname, lname, birth_year);
    if (new_person == NULL) {
        printf("Error: Could not allocate the memory!");
        return -1;
    }
    position last = find_last(head);
    last->next = new_person;

    return EXIT_SUCCESS;
}

int print_list(position first) {
    position temp = first;

    while (temp) {
        printf("First name: %s\n Last name: %s\n Birth year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

position find_last(position head) {
    position temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    return temp;
}

position find_by_lname(position head, char* lname) {
    position temp = head;

    while (temp) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

position find_previous(position first, position target) {
    position temp = first;

    if (first == target) {
        return NULL;
    }

    while (temp->next != NULL && temp->next != target) {
        temp = temp->next;
    }

    return temp;
}

int delete_person(position head, position toDelete) {
    if (head == NULL || toDelete == NULL) {
        printf("Error!");
        return -1;
    }

    position previous = find_previous(head, toDelete); {
        if (previous == NULL) {
            printf("Error!");
            return -1;
        }
    }
    previous->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int free_list(position head) {
    position temp = head->next;

    while (temp) {
        position toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    head->next = NULL;

    return EXIT_SUCCESS;
}
