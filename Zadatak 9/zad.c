/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.
*/
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct Node* treePosition;
typedef struct Node {
	int data;
	treePosition left, right;
}tree;

treePosition insert(treePosition, int);
int replace(treePosition);
int inorder(treePosition, int [], int*);

int main() {
	int a[10], ind = 0, i = 0;
	treePosition root = NULL;
	FILE* fp = fopen("brojev.txt", "w");
	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);
	/*srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int x = (rand() % 81) + 10;
		printf("%d ", x);
		root = insert(root, x);
	}*/
	inorder(root, a, &ind);
	for (i = 0; i < ind; i++)
        fprintf(fp, "%d ", a[i]);
    fprintf(fp,"\n replace:");

    ind =0;
    replace(root);
    inorder(root, a, &ind);
    for (i = 0; i < ind; i++)
        fprintf(fp, "%d ", a[i]);

    fclose(fp);
    return 0;
}

treePosition insert(treePosition root, int data) {
	if (root == NULL) {
		treePosition newNode = (treePosition)malloc(sizeof(tree));
		newNode->data = data;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
    if (data < root->data)
		root->right = insert(root->right, data);
	else
		root->left = insert(root->left, data);
	return root;
}
int replace(treePosition root) {
	if (root == NULL)
		return 0;
	int prev = root->data;
	int sumLeft = replace(root->left);
	int sumRight = replace(root->right);
	root->data = sumLeft + sumRight;
	return root->data + prev;
}
int inorder(treePosition root, int a[], int* i) {
    if (root != NULL) {
        inorder(root->left, a, i);
        a[*i] = root->data;
        (*i)++;
        inorder(root->right, a, i);
    }
    return 0;
}


