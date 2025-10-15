/*
1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci.Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i učitati iz datoteke sve zapise.Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova / max_br_bodova * 100
*/

#include<stdio.h>
#include<stdlib.h>
#define maxPoints 60       // maksimalan broj bodova na kolokviju

typedef struct {           // definicija strukture student
    char firstName[20];    // string ime studenta
    char lastName[20];     // string prezime studenta
    int score;             // intiger broj bodova koje je student ostvario
} student;

int numberOfStudents(FILE* );                     // prototip funkcije koja prebrojava koliko je studenata na listi
int importStudents(FILE*, student*, int);         // prototip funkcije koja upisuje podatke iz datoteke u strukturu
float relativeScore(int);                         // prototip funkcije koja racuna relativni broj bodova

int main()
{

    student* s;
    int i;                                                           
    FILE* listOfStudents = fopen("Students.txt", "r");               // otvaranje datoteke za citanje

    int numberOfRows = numberOfStudents(listOfStudents);             // poziv funkcije koja vraca broj studenata na listi

    s = malloc(numberOfRows * sizeof(student));                      // dinamicki alociramo memoriju za s

    rewind(listOfStudents);                                          // vracamo pokazivac na pocetak datoteke
    importStudents(listOfStudents, s, numberOfRows);                 // poziv funkcije koja upisuje podatke iz datoteke u strukturu

    for (i = 0; i < numberOfRows; i++)
        printf("%-10s %s \t\t%d   %.2f\n", s[i].firstName, s[i].lastName, s[i].score, relativeScore(s[i].score));   // ispis elemenata strukture

    free(s);     // oslobadanje alociranu memoriju                                                     

    return 0;
}

int numberOfStudents(FILE* listOfStudents)     // funkcija koja preborjava studente
{
    char string[100];
    int count = 0;

    while (fgets(string, 100, listOfStudents)) // cita svaku liniju iz datotek dok ne dode do kraja
        count++;                               // brojaca koji broji svaki red

    return count;                              // funkcija vraca broj redova(studenata)
}

int importStudents(FILE* listOfStudents, student* s, int numberOfRows)                       // funkcije koja upisuje podatke iz datoteke u strukturu
{
    int i;
    for (i = 0; i < numberOfRows; i++)
        fscanf(listOfStudents, "%s %s %d", s[i].firstName, s[i].lastName, &s[i].score);      // upis podataka u strukturu

    return 0;
}

float relativeScore(int score)               //funkcija koja racuna relativni broj bodova
{
    return (float)score / maxPoints * 100;   // funkcija vraca rezultat tipa float 
}
