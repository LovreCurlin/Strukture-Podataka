/*6. Napisati program koji cita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini racun. Na pocetku svake datoteke je zapisan datum u kojem vremenu je
racun izdat u formatu YYYY-MM-DD. Svaki sljedeci red u datoteci predstavlja artikl u formatu
naziv, kolicina, cijena. Potrebno je formirati vezanu listu racuna sortiranu po datumu. Svaki cvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je
omoguciti upit kojim ce korisnik saznati koliko je novaca sveukupno potrošeno na specificni
artikl u odredenom vremenskom razdoblju i u kojoj je kolicini isti kupljen.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct items* ItemPosition;
typedef struct items
{
    char item[50];
    int count;
    float price;
    ItemPosition next;
} items;

typedef struct recept* ReceptPosition;
typedef struct recept
{
    int year, month, day;
    ItemPosition itemsHead;
    ReceptPosition next;
} recept;

int import(ReceptPosition, char*);
ItemPosition findItem(ReceptPosition, char* item);
int importItems(ReceptPosition, char*);
ReceptPosition createRecept(int, int, int);
int printList(ReceptPosition );
ItemPosition createItem(char*,int, float);
int importItems(ReceptPosition, char* );
int specificItem(char*, int, int, ReceptPosition);
int date(ReceptPosition );
int freeRacepts(ReceptPosition );
int freeItems(ItemPosition );

int main() {
    recept head;
    head.next = NULL;
    char filename[50];
    char sitem[50];
    int date1 = 0, date2 =0, y, m, d;
    FILE* fp = fopen("racuni.txt", "r");
    if(!fp) {
        printf("Error!!!");
        return EXIT_FAILURE;
    }

    while (fscanf(fp, "%49s", filename)==1)
        import(&head, filename);

    printList(&head);
    printf("Unesite ime artikla ta koji zelite znati ukupbu potrosnju u doredenom vremenskom razdoblju:");
    scanf("%s", &sitem);
    printf("unesite vremnesko razdoblje u kojem zelite pretrazivati\n");
    scanf("%d %d %d", &y, &m, &d);
    date1 = y*10000 + m*100 + d;
    printf("do\n");
    scanf("%d %d %d", &y, &m, &d);
    date2 = y*10000 + m*100 + d;
    specificItem(sitem,date1, date2, &head);
    fclose(fp);
    freeRacepts(head.next);
    return EXIT_SUCCESS;
}

int import(ReceptPosition p, char* filename) {
    FILE* fp = fopen(filename, "r");
    if(!fp) {
        printf("Error!!!");
        return EXIT_FAILURE;
    }
    int y, m, d;
    fscanf(fp, "%d-%d-%d", &y, &m, &d);
    ReceptPosition q = createRecept(y, m, d);
    ReceptPosition temp = NULL;

    while (p->next != NULL) {
        if (date(p->next) > date(q)){
            temp = p->next;
            break;
        }
        p = p->next;
    }
    q->next = temp;
    p->next = q;
    importItems(q, filename);
    fclose(fp);
    return EXIT_SUCCESS;
}

ReceptPosition createRecept(int y, int m, int d) {
    ReceptPosition newRecept = (ReceptPosition)malloc(sizeof(recept));
    if(!newRecept) {
        printf("Error with memory allocation!");
        return NULL;
    }
    newRecept->year = y;
    newRecept->month = m;
    newRecept->day = d;
    newRecept->itemsHead = NULL;
    newRecept->next = NULL;
    return newRecept;
}

int printList(ReceptPosition p) {
    p = p->next;
    while (p != NULL) {
        printf("%04d-%02d-%02d\n", p->year, p->month, p->day);
        ItemPosition q = p->itemsHead;
        q = q->next;
        while (q != NULL){
            printf("%-10s  %d  %.2f\n", q->item, q->count, q->price);
            q = q->next;
        }
        printf("\n");
        p = p->next;
    }
}

ItemPosition createItem(char* itemName, int count, float price){
    ItemPosition newItem = (ItemPosition)malloc(sizeof(items));
    if(!newItem){
        printf("Error with memory allocation!");
        return NULL;
    }
    strcpy(newItem->item, itemName);
    newItem->count = count;
    newItem->price = price;
    newItem->next = NULL;
    return newItem;
}

int importItems(ReceptPosition p, char* filename) {
    FILE* fp = fopen(filename, "r");
    char firstLine[50];
    char item[50];
    int count;
    float price;
    p->itemsHead = (ItemPosition)malloc(sizeof(items));
    p->itemsHead->next = NULL;
    fgets(firstLine, 50, fp);
    ItemPosition last = p->itemsHead;

    while (fscanf(fp, "%49s %d %f", item, &count, &price) == 3) {
        ItemPosition q = createItem(item, count, price);
        ItemPosition s = p->itemsHead;
        ItemPosition temp = NULL;
        while (s->next != NULL) {
            if (strcmp(s->next->item, q->item) > 0) {
                temp = s->next;
                break;
            }
            s = s->next;
        }
        q->next = temp;
        s->next = q;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

ItemPosition findItem(ReceptPosition p, char* item) {
    ItemPosition found = p->itemsHead;

    if (found != NULL)
        found = found->next;

    while (found != NULL) {
        if (strcmp(found->item, item) == 0)
            return found;
        found = found->next;
    }
    return NULL;
}


int specificItem(char* sitem, int date1, int date2,ReceptPosition p) {
    int count = 0;
    float price = 0;
    p = p->next;
    while(p != NULL) {
        if(date(p) >= date1 && date(p) <= date2) {
            ItemPosition q = findItem(p, sitem);
            if(q != NULL) {
                count += q->count;
                price += q->count*q->price;
            }
        }
        p = p->next;
    }
    if (count > 0)
        printf("\nArtikl %s u odabranom razdoblju je kupljen %d pura sto iznosi %.2f eura", sitem, count, price);
    else
        printf("Odabrani proizvod nije pronaden u odabranom razdoblju");
    return EXIT_SUCCESS;
}

int date(ReceptPosition p) {
    return p->year * 10000 + p->month * 100 + p->day;
}


int freeRacepts(ReceptPosition p) {
    ReceptPosition temp;
    while(p != NULL) {
        temp = p;
        p = temp->next;
        freeItems(temp->itemsHead);
        free(temp);
    }
    return EXIT_SUCCESS;
}

int freeItems(ItemPosition p) {
    ItemPosition temp;
    while(p != NULL) {
        temp = p;
        p = temp->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}
