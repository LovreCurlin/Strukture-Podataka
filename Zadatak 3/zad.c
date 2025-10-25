/*
3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct person* Position;                         // pokazivač na strukturu persoN

typedef struct person
{
    char firstName[20];
    char lastName[20];
    int yearOfBirth;
    Position Next;                                       // pokazivač na sljedeći element u povezanom popisu
} person;


Position createPerson();                                  // funkcija alocira memoriju i unosi podatke o osobi
Position addToBeginning(Position );                       // dodaje na pocetak liste
Position addToEnd(Position );                             // dodaje na kraj liste
int printList(Position );                                 // ispisuje listu
Position findPerson(Position, char* );                    // pronalaz prezime sa liste
Position deletePerson(Position, char* );                  // brise osobu sa liste
Position addAfter(Position, char*);
Position addBefore(Position, char*);
int sortByLastName(Position);
int putInFile(Position);
Position importFromFile(Position);

int main()
{
    int choice;
    Position Head = NULL;                               // početak liste
    char lastName[20];

    do
    {
        puts("1. Add a person at the beginning of the list");
        puts("2. Print the list");
        puts("3. Add a person at the end of the list");
        puts("4. Find someone on the list");
        puts("5. Delete someone from the list");
        puts("6. addafter someone from the list");
        puts("7. addbefore someone from the list");
        puts("0. Exit");
        puts("Choose an operation:");
        scanf("%d", &choice);                          // unos odabrane operacije

        switch (choice)
        {
        case 1:
            Head = addToBeginning(Head);                // dodajemo osobu na početak
            break;

        case 2:
            printList(Head);                            // ispisujemo listu
            break;

        case 3:
            Head = addToEnd(Head);                      // dodajemo osobu na kraj
            break;

        case 4:
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

        case 5:
        {
            printf("Enter the last name of the person you want to delete: ");
            scanf("%s", lastName);
            Head = deletePerson(Head, lastName);         // brišemo osobu s unesenim prezimenom
            break;
        }
        case 6:
        {
            printf("Enter the last name of the person you want to add after: ");
            scanf("%s", lastName);
            Head = addAfter(Head, lastName);         // brišemo osobu s unesenim prezimenom
            break;
        }
        case 7:
        {
            printf("Enter the last name of the person you want to add before: ");
            scanf("%s", lastName);
            Head = addBefore(Head, lastName);         // brišemo osobu s unesenim prezimenom
            break;
        }
        case 8:
        {
            printf("upis u listu: \n");
            putInFile(Head);
            break;
        }
        case 9:
        {
            sortByLastName(Head);
            break;
        }
        case 10:
        {
            Head = importFromFile(Head);
            break;
        }
        case 0:
            puts("End of task");                      // izlaz iz programa
            break;

        default:
            puts("Error. Please choose again");
            break;
        }

    }
    while (choice!= 0);                       // ponavljamo dok se ne unese

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
Position addAfter(Position head, char* lastName)
{


    Position findP = findPerson(head, lastName);
    if (!findP)
    {
        printf("%s not found\n", lastName);
        return head;
    }

    Position newPerson = createPerson();
    if (!newPerson) return head;

    Position p = head;
    while (p != findP)
        p = p->Next;

    newPerson->Next = p->Next;
    p->Next = newPerson;
    printf("Person added\n");
    return head;


}

Position addBefore(Position head, char* lastName)
{


    Position findP = findPerson(head, lastName);
    if (!findP)
    {
        printf("%s not found\n", lastName);
        return head;
    }

    Position newPerson = createPerson();
    if (!newPerson) return head;

    if (findP == head)
    {
        newPerson->Next = head;
        head = newPerson;
        return head;

    }

    Position p = head;
    while (p->Next != findP)
        p = p->Next;


    newPerson->Next = p->Next;
    p->Next = newPerson;
    printf("Person added\n");
    return head;


}

int putInFile(Position head)
{
    FILE* listOfPeople = fopen("list.txt", "w");
    if (!listOfPeople)
    {
        perror("Error opening file");
        return -1;
    }
    Position p = head;
    char s[100];
    while (p != NULL)
    {
        fprintf(listOfPeople, "%s %s %d\n", p->firstName, p->lastName, p->yearOfBirth);
        p = p->Next;

    }
    fclose(listOfPeople);
    return 0;
}

int sortByLastName(Position head)
{

    Position sorted = NULL;
    bool swapped;
    do
    {
        swapped = false;
        Position before = NULL;
        Position q = head;
        Position p = head->Next;
        Position temp = NULL;

        while (p != NULL)
        {
            if (strcmp(q->lastName, p->lastName) > 0)
            {

                temp = p->Next;
                p->Next = q;
                q->Next = temp;

                if (before == NULL)
                    head = p;
                else
                    before->Next = p;


                before = p;
                p = q->Next;
                swapped = true;

            }
            else
            {
                before = q;
                q = p;
                p = p->Next;
            }
        }
        sorted = q;
    } while(swapped);

    printf("List successfully sorted by last name.\n");

    return 0;
}

Position importFromFile(Position head)
{
    FILE* file = fopen("list.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    char firstName[20], lastName[20];
    int yearOfBirth;
char string[100];
    int count = 0;

    while (fgets(string, 100, file))
    {

        Position newPerson = (Position)malloc(sizeof(person));
        if (!newPerson)
        {
            printf("Memory allocation error\n");
            fclose(file);
            return -1;
        }
        sscanf(string, "%s %s %d", newPerson->firstName, newPerson->lastName, &newPerson->yearOfBirth);

        newPerson->Next = NULL;


        if (head == NULL)
        {
            head = newPerson;
        }
        else
        {
            Position temp = head;
            while (temp->Next != NULL)
                temp = temp->Next;
            temp->Next = newPerson;
        }
    }

    fclose(file);
    printf("List imported\n");
    return head;
}
