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
#define maxPoints 60

typedef struct {

    char firstName[20];
    char lastName[10];
    int score;

} student;

int numberOfStudents(FILE* );
int enterOfStudents(FILE*, student*, int);
float relativeScore(int);

int main()
{

    student* s;
    int i;
    FILE* listOfStudents = fopen("Students.txt", "r");

    int numberOfRows = numberOfStudents(listOfStudents);

    s = malloc(numberOfRows * sizeof(student));

    rewind(listOfStudents);
    enterOfStudents(listOfStudents, s, numberOfRows);

    for (i = 0; i < numberOfRows; i++)
        printf("%-10s %s \t\t%d   %.2f\n", s[i].firstName, s[i].lastName, s[i].score, relativeScore(s[i].score));

    free(s);

    return 0;
}

int numberOfStudents(FILE* listOfStudents)
{
    char string[100];
    int count = 0;

    while (fgets(string, 100, listOfStudents))
        count++;

    return count;
}

int enterOfStudents(FILE* listOfStudents, student* s, int numberOfRows)
{
    int i;
    for (i = 0; i < numberOfRows; i++)
        fscanf(listOfStudents, "%s %s %d", s[i].firstName, s[i].lastName, &s[i].score);

    return 0;


}

float relativeScore(int score)
{
    return (float)score / maxPoints * 100;
}
