/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct poly* Position;
typedef struct poly
{
    int coef;
    int pow;
    Position next;
} poly;

int multiply(Position p, Position q, Position r);
int addP(Position head);
int sum(Position p, Position q, Position r);
Position sortPoly(Position head);
int PrintPoly(Position head);
int ReadFromFile(Position head, char* filename);
Position CreateNode(int coef, int exp);

int main()
{
    poly head1 = { .coef = 0, .pow = 0, .next = NULL };
    poly head2 = { .coef = 0, .pow = 0, .next = NULL };
    poly sumP = { .coef = 0, .pow = 0, .next = NULL };
    poly mulP = { .coef = 0, .pow = 0, .next = NULL };

    ReadFromFile(&head1, "poly1.txt");
    ReadFromFile(&head2, "poly2.txt");

    head1.next = sortPoly(head1.next);
    head2.next = sortPoly(head2.next);

    sum(head1.next, head2.next, &sumP);
    multiply(head1.next, head2.next, &mulP);

    printf("zbroj: ");
    PrintPoly(sumP.next);

    printf("umnozak: ");
    PrintPoly(mulP.next);

    return 0;
}

int ReadFromFile(Position head, char* filename)
{
    FILE* pol = fopen(filename, "r");

    if (!pol)
    {
        printf("error\n");
        return -1;
    }

    int coef, exp;
    Position q = head;
    while (fscanf(pol, "%d %d", &coef, &exp) == 2)
    {
        Position newNode = CreateNode(coef, exp);
        q->next = newNode;
        q = newNode;
    }
    fclose(pol);
    return 0;
}

Position CreateNode(int coef, int exp)
{
    Position newNode = (Position)malloc(sizeof(poly));
    newNode->coef = coef;
    newNode->pow = exp;
    newNode->next = NULL;
    return newNode;
}

int PrintPoly(Position head)
{
    while (head != NULL)
    {
        printf("%dx^%d ", head->coef, head->pow);
        head = head->next;
    }
    printf("\n");
    return 0;
}
Position sortPoly(Position head)
{

    Position sorted = NULL;
    bool swapped;
    do
    {
        swapped = false;
        Position before = NULL;
        Position q = head;
        Position p = head->next;
        Position temp = NULL;

        while (p != NULL)
        {
            if (q->pow < p->pow)
            {

                temp = p->next;
                p->next = q;
                q->next = temp;

                if (before == NULL)
                    head = p;
                else
                    before->next = p;


                before = p;
                p = q->next;
                swapped = true;

            }
            else
            {
                before = q;
                q = p;
                p = p->next;
            }
        }
        sorted = q;
    }
    while(swapped);
    return head;
}
int sum(Position p1, Position p2, Position r)
{
    Position last = r;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->pow == p2->pow)
        {
            int sumCoef = p1->coef + p2->coef;
            if (sumCoef != 0)
            {
                Position newNode = CreateNode(sumCoef, p1->pow);
                last->next = newNode;
                last = newNode;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->pow > p2->pow)
        {
            Position newNode = CreateNode(p1->coef, p1->pow);
            last->next = newNode;
            last = newNode;
            p1 = p1->next;
        }
        else
        {
            Position newNode = CreateNode(p2->coef, p2->pow);
            last->next = newNode;
            last = newNode;
            p2 = p2->next;
        }
    }


    while (p1 != NULL)
    {
        Position newNode = CreateNode(p1->coef, p1->pow);
        last->next = newNode;
        last = newNode;
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        Position newNode = CreateNode(p2->coef, p2->pow);
        last->next = newNode;
        last = newNode;
        p2 = p2->next;
    }

    return 0;
}

int multiply(Position p1, Position p2, Position r)
{
    Position last = r;
    Position temp;

    while (p1 != NULL)
    {
        temp = p2;
        while (temp != NULL)
        {
            int c= p1->coef * temp->coef;
            int e = p1->pow + temp->pow;

            Position newNode = CreateNode(c, e);
            last->next = newNode;
            last = newNode;

            temp = temp->next;
        }
        p1 = p1->next;
    }

    r->next = sortPoly(r->next);
    addP(r->next);

    return 0;
}


int addP(Position head)
{
    if (!head)
        return 0;

    Position p = head;

    while (p->next != NULL)
    {
        if (p->pow == p->next->pow)
        {
            p->coef += p->next->coef;
            Position temp = p->next;
            p->next = p->next->next;
            free(temp);
        }
        else
        {
            p = p->next;
        }
    }
    return 0;
}
