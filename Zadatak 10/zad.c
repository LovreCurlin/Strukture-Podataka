/*10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki čvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

typedef struct cityTree* cityTreePosition;
typedef struct cityTree {
	char name[max];
	int population;
	cityTreePosition left, right;
}cityTree;

typedef struct countryList* countryListPosition;
typedef struct countryList {
	char name[max];
	cityTreePosition city;
	countryListPosition next;
}countryList;

typedef struct cityList* cityListPosition;
typedef struct cityList{
	char name[max];
	int population;
	cityListPosition next;
}cityList;

typedef struct countryTree* countryTreePosition;
typedef struct countryTree {
	char name[max];
	cityList city;
	countryTreePosition left, right;
}countryTree;

countryListPosition createCountryList(char* name);
countryListPosition addCountryToList(countryListPosition current, char* name);
cityTreePosition createCityTree(char* name, int population);
cityTreePosition addCityToTree(cityTreePosition current, char* cityName, int population);
int printCityTree(cityTreePosition current);
int printCountryList(countryListPosition current);

int main() {
	char country[20], countryFile[24], city[20];
	int population;
	countryList countryListHead = { .name = {""}, .next = NULL, .city = NULL };
	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) {
		printf("Could not open drzave.txt\n");
		return EXIT_FAILURE;
	}

	while (fscanf(fp, " %19[^,], %23s", country, countryFile) == 2) {
		countryListPosition new = addCountryToList(&countryListHead, country);
		FILE* countryFilePtr = fopen(countryFile, "r");
		if (!countryFilePtr) {
			printf("Could not open %s\n", countryFile);
			continue;
		}

		while (fscanf(countryFilePtr, " %19[^,], %d", city, &population) == 2) {
			new->city = addCityToTree(new->city, city, population);
		}
	}
	printf("LISTA DRZAVA SA GRADOVIMA (STABLO GRADOVA):\n");
	printCountryList(countryListHead.next);


	rewind(fp);
	while (fscanf(fp, " %19[^,], %23s", country, countryFile) == 2);

}
countryListPosition createCountryList(char* name) {
	countryListPosition newCountry =(countryListPosition)malloc(sizeof(countryList));
	strcpy(newCountry->name, name);
	newCountry->city = NULL;
	newCountry->next = NULL;
	return newCountry;
}
countryListPosition addCountryToList(countryListPosition current, char* name){
    countryListPosition new = createCountryList(name);
	while (current->next && strcmp(new->name, current->next->name) > 0)
	current = current->next;
	new->next = current->next;
	current->next = new;
	return new;
}

cityTreePosition createCityTree(char* name, int population) {
	cityTreePosition newCityTree = malloc(sizeof(cityTree));
	if (!newCityTree) return 0;
	strcpy(newCityTree->name, name);
	newCityTree->population = population;
	newCityTree->left = newCityTree->right = NULL;
	return newCityTree;
}
cityTreePosition addCityToTree(cityTreePosition current, char* cityName, int population )
{
	if (!current)
		return createCityTree(cityName, population);

	if (population < current->population)
		current->left = addCityToTree(current->left, cityName, population);
	else if (population > current->population)
		current->right = addCityToTree(current->right, cityName, population);
	else if (strcmp(cityName, current->name) < 0)
		current->left = addCityToTree(current->left, cityName, population);
	else
		current->right = addCityToTree(current->right, cityName, population);
	return current;
}
int printCountryList(countryListPosition current)
{
	while (current) {
		printf("%s:\n", current->name);
		printCityTree(current->city);
		current = current->next;
	}
	return EXIT_SUCCESS;
}
int printCityTree(cityTreePosition current)
{
	if (!current) return EXIT_SUCCESS;
	printCityTree(current->left);
	printf("\t%s, %d\n", current->name, current->population);
	printCityTree(current->right);
	return EXIT_SUCCESS;
}
/*countryTreePosition createCountryTree(char* name) {
	countryTreePosition new = (countryTreePosition)malloc(sizeof(countryTree));
	strcpy(new->name, name);
	new->left = NULL;
	new->right = NULL;
	new->cityList = NULL;
	return new;
}
countryTreePosition addCountryToTree(CountryTreePosition current, CountryTreePosition newCountry)
	if (!current) return newCountry;
	if (strcmp(newCountry->name, current->name) < 0)
		current->left = addCountryToTree(current->left, newCountry);
	else if (strcmp(newCountry->name, current->name) > 0)
		current->right = addCountryToTree(current->right, newCountry);
	return current;
}
*/













































