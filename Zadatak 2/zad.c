/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct person* Position;                         // pokazivač na strukturu persoN

typedef struct person
{
    char firstName[20];
    char lastName[20];
    int yearOfBirth;
    Position Next;                                       // pokazivač na sljedeći element u povezanom popisu
} person;


Position createPerson();                                   // funkcija alocira memoriju i unosi podatke o osobi
Position addToBeginning(Position head);                    // dodaje na pocetak liste
Position addToEnd(Position head);                          // dodaje na kraj liste
int printList(Position head);                              // ispisuje listu
Position findPerson(Position head, char* lastName);        // pronalaz prezime sa liste
Position deletePerson(Position head, char* lastName);      // brise osobu sa liste


int main()
{
    char choice;
    Position Head = NULL;                               // početak liste
    char lastName[20];

    do
    {
        puts("A. Add a person at the beginning of the list");
        puts("B. Print the list");
        puts("C. Add a person at the end of the list");
        puts("D. Find someone on the list");
        puts("E. Delete someone from the list");
        puts("F. Exit");
        puts("Choose an operation:");
        scanf(" %c", &choice);                          // unos odabrane operacije

        switch (toupper(choice))
        {
        case 'A':
            Head = addToBeginning(Head);                // dodajemo osobu na početak
            break;

        case 'B':
            printList(Head);                            // ispisujemo listu
            break;

        case 'C':
            Head = addToEnd(Head);                      // dodajemo osobu na kraj
            break;

        case 'D':
        {
            printf("Enter the last name of the person you want to find: ");
            scanf("%s", lastName);
            Position found = findPerson(Head, lastName); // tražimo osobu po prezimenu
            if (found)
                printf("%s %s %d found\n", found->firstName, found->lastName, found->yearOfBirth);
            else
                printf("%s not found\n", lastName);
            break;
        }

        case 'E':
        {
            printf("Enter the last name of the person you want to delete: ");
            scanf("%s", lastName);
            Head = deletePerson(Head, lastName);         // brišemo osobu s unesenim prezimenom
            break;
        }

        case 'F':
            puts("End of task");                      // izlaz iz programa
            break;

        default:
            puts("Error. Please choose again");
            break;
        }

    }
    while (toupper(choice) != 'F');                     // ponavljamo dok se ne unese F

    Position temp;

    while (Head != NULL)                     //  while dok lista nije prazna
    {
        temp = Head;                         // zapamti trenutni čvor
        Head = Head->Next;                   // pomakni se na sljedeći
        free(temp);                          // obriši zapamćeni čvor
    }


    return 0;
}


Position createPerson()
{
    Position newPerson = (Position)malloc(sizeof(person));  // dinamička alokacija memorije za novu osobu
    if (!newPerson)
    {
        printf("Memory allocation error!\n");
        return NULL;
    }

    printf("Enter first name: ");
    scanf("%s", newPerson->firstName);
    printf("Enter last name: ");
    scanf("%s", newPerson->lastName);
    printf("Enter year of birth: ");
    scanf("%d", &newPerson->yearOfBirth);

    newPerson->Next = NULL;                                // novi element još nije povezan s nikim
    return newPerson;
}

Position addToBeginning(Position head)
{
    Position newPerson = createPerson();                   // kreiramo novu osobu
    if (!newPerson) return head;

    newPerson->Next = head;                                // pokazivač novog elementa pokazuje na stari početak
    return newPerson;                                      // novi element postaje novi početak (head)
}

Position addToEnd(Position head)
{
    Position newPerson = createPerson();                   // kreiramo novu osobu
    if (!newPerson) return head;

    if (head == NULL)                                      // ako je lista prazna
        return newPerson;                                  // nova osoba postaje početak

    Position temp = head;
    while (temp->Next != NULL)                             // prolazimo do zadnjeg elementa
        temp = temp->Next;

    temp->Next = newPerson;                                // zadnji element pokazuje na novu osobu
    return head;
}

int printList(Position head)
{
    if (head == NULL)                                      // ako je lista prazna
    {
        printf("The list is empty\n");
        return 0;
    }

    Position current = head;
    while (current != NULL)                                // prolazimo kroz svaki element dok ne dođemo do kraja
    {
        printf("%s %s %d\n", current->firstName, current->lastName, current->yearOfBirth);
        current = current->Next;                           // prelazak na sljedeći element
    }

    return 0;
}

Position findPerson(Position head, char* lastName)
{
    Position p = head;
    while (p != NULL)
    {
        if (strcmp(p->lastName, lastName) == 0)            // provjera prezimena
            return p;                                      // vraća pokazivač na pronađenu osobu
        p = p->Next;                                       // sljedeći element
    }
    return NULL;                                           // ako nije pronađeno
}

Position deletePerson(Position head, char* lastName)
{
    if (head == NULL)                                      // prazna lista
        return NULL;

    Position delPerson = findPerson(head, lastName);       // tražimo osobu za brisanje
    if (!delPerson)
    {
        printf("%s not found\n", lastName);
        return head;
    }

    if (delPerson == head)                                 //  briše prvi element
    {
        head = head->Next;                                 // sljedeći
        free(delPerson);                                   // oslobađamo memoriju
        printf("Person deleted\n");
        return head;
    }

    Position p = head;
    while (p->Next != delPerson)                           // tražimo element prije onog koji brišemo
        p = p->Next;

    p->Next = delPerson->Next;                             // preskačemo obrisani element
    free(delPerson);                                       // oslobađamo memoriju
    printf("Person deleted\n");
    return head;
}
