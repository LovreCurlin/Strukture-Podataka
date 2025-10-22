/*
2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
A.dinamički dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamički dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct person* Position;
typedef struct person
{
    char firstName[20];
    char lastName[20];
    int yearOfBirth;
    Position Next;
} person;

Position createPerson();
Position addToBeginning(Position head);
Position addToEnd(Position head);
int printList(Position head);
Position findPerson(Position head, char* lastName);
Position deletePerson(Position head, char* lastName);


int main()
{
    char choice;
    Position Head = NULL;
    char firstName[20];
    char lastName[20];



    do
    {

        puts("A. Add a perosn at the begining of the list");
        puts("B. Print the list");
        puts("C. Add a perosn at the end of the list");
        puts("D. Find someone on the list");
        puts("E. Delete someone from the list");
        puts("F. Exit");
        puts("Choose the opration:");
        scanf(" %c", &choice);

        switch (toupper(choice))
        {
        case 'A':
        {
            Head = addToBeginning(Head);
            break;
        }

        case 'B':
        {
            printList(Head);
            break;
        }
        case 'C':
          {Head = addToEnd(Head);
            break;
          }

        case 'D':
          {
             printf("Enter the surname of the person taht you want to find: ");
                scanf("%s", lastName);
                Position found = findPerson(Head, lastName);
                if (found)
                    printf("%s %s %d. found\n",found->firstName, found->lastName, found->yearOfBirth);
                else
                    printf("%s not found.\n", lastName);
                break;
          }
        case 'E':
            puts("ispis  e");
            break;
        case 'F':
            puts("End of task");
            break;
        default:
            puts("You entered the wrong operation");
            break;




        }



    }
    while (toupper(choice) != 'F');




    return 0;

}
Position createPerson()
{
    Position newPerson = (Position)malloc(sizeof(person));
    if (!newPerson)
    {
        printf("Error");
        return NULL;
    }
    printf("Unesite ime: ");
    scanf("%s", newPerson->firstName);
    printf("Unesite prezime: ");
    scanf("%s", newPerson->lastName);
    printf("Year of birth: ");
    scanf("%d", &newPerson->yearOfBirth);

    newPerson->Next = NULL;
    return newPerson;
}

Position addToBeginning(Position head)
{
    Position newPerson = createPerson();
    if (!newPerson) return head;

    newPerson->Next = head;
    return newPerson;
}

Position addToEnd(Position head)
{
    Position newPerson = createPerson();
    if (!newPerson) return head;

    if (head == NULL)
    {
        return newPerson;
    }

    Position temp = head;
    while (temp->Next != NULL)
    {
        temp = temp->Next;
    }

    temp->Next = newPerson;
    return head;



}
Position findPerson(Position head, char* lastName)
{
    Position p = head;
    while (p != NULL)
    {
        if (strcmp(p->lastName, lastName) == 0)
            return p;
        p =p->Next;
    }
    return NULL;
}

Position deletePerson(Position head,char* lastName)
{
    if (head == NULL)
        return NULL;

    Position delPerson = findPerson(head, lastName);
    if (!delPerson)
    {
        printf("%s not found.\n", lastName);
        return head;
    }

    if (delPerson == head)
    {
        head = head->Next;
        free(delPerson);
        printf("Pers\n");
        return head;
    }

    Position p= head;
    while (p->Next != delPerson)
        p = p->Next;

    p->Next = delPerson->Next;
    free(delPerson);

    printf("Osoba obrisana.\n");
    return head;
}



int printList(Position head)
{
    if (head == NULL)
    {
        printf("Lista je prazna.\n");
        return;
    }


    Position current = head;
    while (current != NULL)
    {
        printf("%s %s %d\n", current->firstName, current->lastName, current->yearOfBirth);
        current = current->Next;
    }
    return 0;
}
