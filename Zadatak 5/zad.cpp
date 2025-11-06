#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct s* Position;
typedef struct s {
    float value;
    Position next;
}s;


Position createVariable(float value){ // funkcija kreira novi cvor
    Position newVariable = (Position)malloc(sizeof(s));
    if (newVariable == NULL){
        printf("Memory allocation error");
        return NULL;
    }
    newVariable->next = NULL;
    newVariable->value = value;
    return newVariable;
}


Position push(Position head, float var){// funkcija koja dodaje element an vrh stoga

    Position newVariable = createVariable(var); // kreira novog cvor
    if (!newVariable) {
        printf("Memory allocation error");
        return NULL;
    }

    if (head == NULL){
        return newVariable;
    }

    newVariable->next = head;
    return newVariable;       // novi  vrh
}

Position pop(Position head, float* value){ // funkcija skida 1 element sa stoga
    if (head == NULL){       // provjera je li stog prazan
        printf("Stog je prazan");
        return NULL;
    }

    *value = head->value;   // uzmi vrijednost sa vrha
    Position temp = head;
    head = head->next;      // pomaicanje vrha na sljedeci cvor
    free(temp);             // oslobodi memoriju starog vrha

    return head;            // novi vrh stoga
}

int main(){
    Position head = NULL;
    float result = 0;
    float var1, var2;

    FILE* fp = fopen("izraz.txt", "r");
    if (fp == NULL) {
        printf("Error with file opening");
        return EXIT_FAILURE;
    }

    char ch;
    while (fscanf(fp, " %c", &ch) == 1) {       // citanje karaktera iz datoteke

        if (isdigit(ch))
            head = push(head, (float)(ch - '0'));
        else {
            if (head == NULL || head->next == NULL) {
                printf("Nema dovoljno elemenata");
                fclose(fp);
                return EXIT_FAILURE;
            }
            head = pop(head, &var2);  // skini dva operanda sa stoga
            head = pop(head, &var1);
            switch (ch) {
            case '+':
                result = var1 + var2;
                break;
            case '-':
                result = var1 - var2;
                break;
            case '*':
                result = var1 * var2;
                break;
            case '/':
                if (var2 == 0) {
                    printf("Error cant divide with zero");
                    fclose(fp);
                    return EXIT_FAILURE;
                }
                result = var1 / var2;
                break;
            default:
                printf("Unknown operator");
                fclose(fp);
                return EXIT_FAILURE;
            }
        head = push(head, result); // Dodaj rezultat nazad na stog
        }
    };
    if (!head)
        printf("Empty\n");                   // stog prazan
    else if (head->next != NULL)
        printf("More than one variable");    // na stogu je više od jednog elementa
    else
        printf("Result: %.2f", head->value);

    return EXIT_SUCCESS;
}
