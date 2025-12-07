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

int numberOfStudents(char* );                     // prototip funkcije koja prebrojava koliko je studenata na listi
int importStudents(char*, student*, int);         // prototip funkcije koja upisuje podatke iz datoteke u strukturu
float relativeScore(int);                         // prototip funkcije koja racuna relativni broj bodova
int print(student* , int);

int main() {
    student* s;
    int i;                                                           
    int numberOfRows = numberOfStudents(listOfStudents);             // poziv funkcije koja vraca broj studenata na listi
    s = malloc(numberOfRows * sizeof(student));                      // dinamicki alociramo memoriju za s
    if (!s) {
	    printf("error with memory allocation");
	    return EXIT_FAILURE;
    }
    importStudents(Students.txt, s, numberOfRows);                 // poziv funkcije koja upisuje podatke iz datoteke u strukturu
    print(s, numberOfRows);

    free(s);                                                      
    return EXIT_SUCCESS;
}

int numberOfStudents(char* fileName) {    // funkcija koja preborjava studente
    FILE* list = fopen(fileName, "r");
    if (!list) {
	    printf("Error opening file\n");
	    return EXIT_FAILURE;
    }
    char buffer[50];
    int count = 0;
    while (fgets(buffer, 50, list))
	    count++;
    fclose(list);
    return count;                // funkcija vraca broj redova(studenata)
}

int importStudents(char* fileName, student* s, int numberOfRows) {                      // funkcije koja upisuje podatke iz datoteke u strukturu
    FILE* list = fopen(fileName, "r");
    if (!list) {
	    printf("Error opening file");
	    return EXIT_FAILURE;
    }
    for (int i = 0;i < n; i++)
	    fscanf(list, "%s %s %d", s[i].firstName, s[i].lastName, &s[i].score);
    fclose(list);
    return EXIT_SUCCESS;
}

float relativeScore(int score) {             //funkcija koja racuna relativni broj bodova
    return (float)score / maxPoints * 100;   // funkcija vraca rezultat tipa float 
}

int print(student* s, int n) {
	for (int i = 0; i < n; i++)
		printf("%s %s %d %.2f\n", s[i].firstName, s[i].lastName, s[i].score, relativeScore(s[i].score));
	return EXIT_SUCCESS;
}

