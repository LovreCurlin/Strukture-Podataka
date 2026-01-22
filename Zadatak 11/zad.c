/*11. Prepraviti zadatak 10 na način da se formira hash tablica država.Tablica ima 11 mjesta, a
funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova države zatim
računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice.Države s istim ključem se
pohranjuju u vezanu listu sortiranu po nazivu države.Svaki čvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 11;


typedef struct cityTree* CityTreePosition;
typedef struct cityTree {
    char name[20];
    int population;
    CityTreePosition left;
    CityTreePosition right;
} CityTree;

typedef struct countryHash* CountryHashPosition;
typedef struct countryHash {
    char name[20];
    CityTreePosition city;    
    CountryHashPosition next;   
} CountryHash;

CountryHashPosition createHashCountry(char* );
int printHashTable(CountryHashPosition* );
int printCityTree(CityTreePosition );
CityTreePosition addCityToTree(CityTreePosition , CityTreePosition );
CityTreePosition createCity(char* , int );
int addCountryToHash(CountryHashPosition* , CountryHashPosition);
int hashIndex(char* );
int find(CountryHashPosition* hash);
int printHashTable(CountryHashPosition* table);
int main() {

    CountryHashPosition hash[11] = { NULL };
    char country[20], countryFile[30], city[20];
    int population;

    FILE* fp = fopen("drzave.txt", "r");
    if (!fp) {
        printf("Greska pri otvaranju drzave.txt\n");
        return EXIT_FAILURE;
    }
    while (fscanf(fp, " %19[^,], %29s", country, countryFile) == 2) {
        CountryHashPosition newCountry = createHashCountry(country);
        addCountryToHash(hash, newCountry);
        FILE* sfp = fopen(countryFile, "r");
        while (fscanf(sfp, " %19[^,], %d", city, &population) == 2) {
            CityTreePosition newCity = createCity(city, population);
            newCountry->city = addCityToTree(newCountry->city, newCity);
        }
    }
    printHashTable(hash);
    find(hash);
}

CountryHashPosition createHashCountry(char* name) {
    CountryHashPosition newCountry = malloc(sizeof(CountryHash));
    if (!newCountry)return NULL;

    strcpy(newCountry->name, name);
    newCountry->city = NULL;
    newCountry->next = NULL;
}

int hashIndex(char* Name)
{
    int sum = 0;
    for (int i = 0; i < 5 && Name[i] != '\0'; i++)
        sum += (int)Name[i];

    return sum % HASH_SIZE;
}

int addCountryToHash(CountryHashPosition* hash, CountryHashPosition newCountry)
{
    int index = hashIndex(newCountry->name);
    CountryHashPosition current = hash[index];

    if (!current || strcmp(newCountry->name, current->name) < 0) {
        newCountry->next = current;
        hash[index] = newCountry;
        return 0;
    }

    while (current->next && strcmp(newCountry->name, current->next->name) > 0)
        current = current->next;

    newCountry->next = current->next;
    current->next = newCountry;
    return 0;
}

CityTreePosition createCity(char* name, int population) {
    CityTreePosition newCity = (CityTreePosition)malloc(sizeof(CityTree));

    strcpy(newCity->name, name);
    newCity->population = population;
    newCity->left = newCity->right = NULL;
    return newCity;
}

CityTreePosition addCityToTree(CityTreePosition root, CityTreePosition newCity)
{
    if (!root)
        return newCity;
    if (newCity->population < root->population)
        root->left = addCityToTree(root->left, newCity);
    else if (newCity->population > root->population)
        root->right = addCityToTree(root->right, newCity);
    else if (strcmp(newCity->name, root->name) < 0)
        root->left = addCityToTree(root->left, newCity);
    else
        root->right = addCityToTree(root->right, newCity);

    return root;
}

int printCityTree(CityTreePosition root)
{  
    if (!root) return;
    printCityTree(root->left);
    printf("\t%s, %d\n", root->name, root->population);
    printCityTree(root->right);

    return EXIT_SUCCESS;
}
int printMinPopulationCity(CityTreePosition root, int minPopulation)
{   
    if (!root) return 0;
    printMinPopulationCity(root->left, minPopulation);
   if(root->population > minPopulation)
       printf("\t%s, %d\n", root->name, root->population);
   printMinPopulationCity(root->right, minPopulation);

    return EXIT_SUCCESS;
}
int printHashTable(CountryHashPosition* hash)
{
    for (int i = 0; i < 11; i++) {

        if (hash[i] == NULL)
            continue;

        printf("\ntablica %d\n", i);

        CountryHashPosition current = hash[i];
        while (current) {
            printf("%s:\n", current->name);
            printCityTree(current->city);
            current = current->next;
        }
    }
    return EXIT_SUCCESS;
}

int find(CountryHashPosition* hash) {

    char country[30];
    int populationMin;
    scanf("%29s", &country);
    scanf("%d", &populationMin);
    int index = hashIndex(country);
    while (hash[index] && strcmp(hash[index]->name, country) != 0)
        hash[index] = hash[index]->next;
        
    if (hash[index])
        printMinPopulationCity(hash[index]->city, populationMin);

}