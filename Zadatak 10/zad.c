/*10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki čvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo država sortirano po nazivu. Svaki čvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati države i gradove te omogućiti korisniku putem
tastature pretragu gradova određene države koji imaju broj stanovnika veći od unosa na
tastaturi.
*/

#define _CRT_SECURE_NO_WARNINGS
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
	cityListPosition city;
	countryTreePosition left, right;
}countryTree;

countryListPosition createCountryList(char* name);
countryListPosition addCountryToList(countryListPosition curr, char* name);
cityTreePosition createCityTree(char* name, int population);
cityTreePosition addCityToTree(cityTreePosition curr, char* cityName, int population);
int printCityTree(cityTreePosition curr);
int printCountryList(countryListPosition curr);

int printCityList(countryTreePosition curr);
int printCountryTree(countryTreePosition curr);
cityListPosition cityListAdd(cityListPosition curr, char* name, int population);
cityListPosition createCityList(char* name, int population);
countryTreePosition addCountryToTree(countryTreePosition curr, countryTreePosition newCountry);
countryTreePosition createCountryTree(char* name);

int main() {
	char country[20], countryFile[24], city[20];
	int population;
	countryList countryListHead = { .name = {""}, .next = NULL, .city = NULL };
	countryTreePosition countryTree = NULL;
	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) {
		printf("Could not open drzave.txt\n");
		return EXIT_FAILURE;
	}

	while (fscanf(fp, " %19[^,], %23s", country, countryFile) == 2)
	{
		countryListPosition new = addCountryToList(&countryListHead, country);

		countryTreePosition newTreeNode = createCountryTree(country);
		countryTree = addCountryToTree(countryTree, newTreeNode);

		FILE* countryFilePtr = fopen(countryFile, "r");
		if (!countryFilePtr) {
			printf("Could not open %s\n", countryFile);
			continue;
		}

		while (fscanf(countryFilePtr, " %19[^,], %d", city, &population) == 2) {
			new->city = addCityToTree(new->city, city, population);
			newTreeNode->city = cityListAdd(newTreeNode->city, city, population);
		}
	}

	printf("stablo gradova:\n");
	printCountryList(countryListHead.next);

	printf("stablo drzava:\n");
	printCountryTree(countryTree);
	find(&countryListHead);

}
countryListPosition createCountryList(char* name) {
	countryListPosition newCountry =(countryListPosition)malloc(sizeof(countryList));
	strcpy(newCountry->name, name);
	newCountry->city = NULL;
	newCountry->next = NULL;
	return newCountry;
}
countryListPosition addCountryToList(countryListPosition curr, char* name){
    countryListPosition new = createCountryList(name);
	while (curr->next && strcmp(new->name, curr->next->name) > 0)
	curr = curr->next;
	new->next = curr->next;
	curr->next = new;
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
cityTreePosition addCityToTree(cityTreePosition curr, char* cityName, int population )
{
	if (!curr)
		return createCityTree(cityName, population);

	if (population < curr->population)
		curr->left = addCityToTree(curr->left, cityName, population);
	else if (population > curr->population)
		curr->right = addCityToTree(curr->right, cityName, population);
	else if (strcmp(cityName, curr->name) < 0)
		curr->left = addCityToTree(curr->left, cityName, population);
	else
		curr->right = addCityToTree(curr->right, cityName, population);
	return curr;
}
int printCountryList(countryListPosition curr)
{
	while (curr) {
		printf("%s:\n", curr->name);
		printCityTree(curr->city);
		curr = curr->next;
	}
	return EXIT_SUCCESS;
}
int printCityTree(cityTreePosition curr)
{
	if (!curr) return EXIT_SUCCESS;
	printCityTree(curr->left);
	printf("\t%s, %d\n", curr->name, curr->population);
	printCityTree(curr->right);
	return EXIT_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
countryTreePosition createCountryTree(char* name)
{
	countryTreePosition new = malloc(sizeof(countryTree));
	if (!new) return NULL;

	strcpy(new->name, name);
	new->left = NULL;
	new->right = NULL;

	new->city = malloc(sizeof(cityList));
	new->city->next = NULL;

	return new;
}

countryTreePosition addCountryToTree(countryTreePosition curr, countryTreePosition newCountry) {
	if (!curr)
		return newCountry;

	if (strcmp(newCountry->name, curr->name) < 0)
		curr->left = addCountryToTree(curr->left, newCountry);
	else if (strcmp(newCountry->name, curr->name) > 0)
		curr->right = addCountryToTree(curr->right, newCountry);
	return curr;
}
cityListPosition createCityList(char* name, int population) {
	cityListPosition newCity = (cityListPosition)malloc(sizeof(cityList));
	strcpy(newCity->name, name);
	newCity->population = population;
	newCity->next = NULL;
	return newCity;
}

cityListPosition cityListAdd(cityListPosition head, char* name, int population)
{
	cityListPosition newCity = createCityList(name, population);
	if (!newCity) return head;

	cityListPosition curr = head;

	while (curr->next && newCity->population > curr->next->population)
		curr = curr->next;

	while (curr->next && curr->next->population == newCity->population && strcmp(newCity->name, curr->next->name) > 0)
		curr = curr->next;

	newCity->next = curr->next;
	curr->next = newCity;

	return head;
}

int printCountryTree(countryTreePosition curr){
	if (!curr) return EXIT_SUCCESS;

	printCountryTree(curr->left);

	printf("%s\n", curr->name);
	printCityList(curr);
	printf("\n");

	printCountryTree(curr->right);

	return EXIT_SUCCESS;
}

int printCityList(countryTreePosition root) {

	cityListPosition curr = root->city->next;
	while (curr != NULL)
	{
		printf("\n\t%s %d", curr->name, curr->population);
		curr = curr->next;
	}
	return 0;
}

int find(countryListPosition head)
{
	countryListPosition curr = head->next;
	char country[max];
	int populationMin;
	scanf("%29s", &country);
	scanf("%d", &populationMin);
	while (curr && strcmp(curr->name, country) != 0)
		curr = curr->next;
	if (curr)
		printCity(curr->city, populationMin);
}

int printCity(cityTreePosition root, int MinPopulation)
{
	if (!root) return 0;
	printCity(root->left, MinPopulation);
	if (root->population > MinPopulation)
		printf("\t%s, %d\n", root->name, root->population);
	printCity(root->right, MinPopulation);
}








































