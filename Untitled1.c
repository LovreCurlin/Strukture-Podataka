#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

struct dir;
typedef struct dir* Position;
typedef struct dir {
	char name[MAX];
	Position next;
	Position child;
} Dir;

struct stack;
typedef struct stack* Node;
typedef struct stack {
	Position p;
	Node next;
} Stack;

Position createDir(char* name);
Node createNode(Position p);
int insertDir(Position p, char* name);
int md(Position p);
int push(Node q, Position p);
int printDirectory(Position current, int depth);
Position pop(Node q);
Position cddir(Position p, Node q);
Position cd(Position p, Node q);


int main()
{
	Dir head;
	Position temp = NULL;
	Stack s;
	int a;

	head.next = NULL;
	head.child = NULL;

	s.p = NULL;
	s.next = NULL;
	strcpy(head.name, "C:");

	temp = &head;

	do {
		puts("\n1 - md\n2 - cd dir\n3 - cd..\n4 - dir (ispis stabla)\n5 - izlaz");
		if (scanf("%d", &a) != 1) break;
		switch(a) {
		case 1:
			md(temp);
			break;
		case 2:
			temp = cddir(temp, &s);
			break;
		case 3:
			temp = cd(temp, &s);
			break;
		case 4:
			printf("%s/:\n", temp->name);
			printDirectory(temp, 1);
			break;
		default:
			break;
		}
	}while(a != 5);

	return 0;
}

Position createDir(char* name) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Dir));
	if (q == NULL) {
		perror("Error allocating memory!\n");
		return NULL;
	}
	strcpy(q->name, name);
	q->next = NULL;
	q->child = NULL;
	return q;
}

int md(Position p) {
	char name[MAX];
	printf("Insert name of directory: ");
	scanf("%s", name);
	Position q = createDir(name);
	if (q != NULL) {
		q->next = p->child;
		p->child = q;
	}
	return 0;
}

Node createNode(Position p) {
	Node q = (Node)malloc(sizeof(Stack));
	if (q == NULL) {
		perror("Error allocating memory!\n");
		return NULL;
	}
	q->p = p;
	q->next = NULL;
	return q;
}

int push(Node q, Position p) {
	Node r = createNode(p);
	if (r != NULL) {
		r->next = q->next;
		q->next = r;
	}
	return 0;
}

Position pop(Node q) {
	Node temp = NULL;
	Position el = NULL;
	if (q->next != NULL) {
		temp = q->next;
		q->next = temp->next;
		el = temp->p;
		free(temp);
	}
	return el;
}

Position cddir(Position p, Node q) {
	char name[MAX];
	Position temp = p->child;
	if (temp == NULL) {
		printf("Directory is empty!\n");
		return p;
	}
	printf("Insert name of directory: ");
	scanf("%s", name);
	while(temp != NULL && strcmp(temp->name, name) != 0)
		temp = temp->next;
	if (temp == NULL) {
		printf("Directory doesn't exist!\n");
		return p;
	}
	push(q, p);
	return temp;
}

Position cd(Position p, Node q) {
	Position r = pop(q);
	if (r == NULL) return p;
	return r;
}


int printDirectory(Position current, int depth) {
    int i = 0;
    Position currentSubdirectory = NULL;

    if (current->child != NULL) {
        currentSubdirectory = current->child;
        while (currentSubdirectory != NULL) {
            for (i = 0; i < depth; i++)
                printf("  ");
            printf("%s\n", currentSubdirectory->name);
            printDirectory(currentSubdirectory, depth + 1);
            currentSubdirectory = currentSubdirectory->next;
        }
    }
    else if (depth == 1) {
        for (i = 0; i < depth; i++)
            printf("  ");
        printf("empty\n");
    }

    return 0;
}
