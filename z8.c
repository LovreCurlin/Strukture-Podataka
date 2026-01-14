#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct tree* treeP;
typedef struct tree {
    int element;
    struct tree *left;
    struct tree *right;
} tree;

typedef struct {
    treeP items[MAX];
    int front, rear;
} Queue;

treeP createNode(int element);
treeP insert(treeP root, int element);
treeP search(treeP root, int element);
treeP deleteNode(treeP root, int element);
treeP findMin(treeP root);
int inorder(treeP root);
int preorder(treeP root);
int postorder(treeP root);
int levelOrder(treeP root);
int initQueue(Queue *q);
int isEmpty(Queue *q);
int enqueue(Queue *q, treeP node);
treeP dequeue(Queue *q);

int main() {
    treeP root = NULL;
    int choice, element;

    do {
        printf("1 unesi element\n");
        printf("2 trazi element\n");
        printf("3 brisanje elementa\n");
        printf("4 inorder\n");
        printf("5 preorder\n");
        printf("6 postorder\n");
        printf("7 level order\n");
        printf("0 izlaz\n");
        printf("operacija: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("unesi:");
            scanf("%d", &element);
            root = insert(root, element);
            break;

        case 2:
            printf("unesi");
            scanf("%d", &element);
            if (search(root, element))
                printf("Element postoji");
            else
                printf("Element ne postoji");
            break;

        case 3:
            printf("unesi el: ");
            scanf("%d", &element);
            root = deleteNode(root, element);
            break;

        case 4:
            inorder(root);
            break;

        case 5:
            preorder(root);
            break;

        case 6:
            postorder(root);
            break;

        case 7:
            levelOrder(root);
            break;
        }
    } while (choice != 0);

    return EXIT_SUCCESS;
}

treeP createNode(int element) {
    treeP newNode = (treeP)malloc(sizeof(tree));
    newNode->element = element;
    newNode->left = newNode->right = NULL;
    return newNode;
}

treeP insert(treeP root, int element) {
    if (root == NULL)
        return createNode(element);

    if (element < root->element)
        root->left = insert(root->left, element);
    else if (element > root->element)
        root->right = insert(root->right, element);

    return root;
}

treeP search(treeP root, int element) {
    if (root == NULL || root->element == element)
        return root;

    if (element < root->element)
        return search(root->left, element);

    return search(root->right, element);
}

treeP findMin(treeP root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

treeP deleteNode(treeP root, int element) {
    treeP temp;

    if (root == NULL)
        return root;

    if (element < root->element)
        root->left = deleteNode(root->left, element);
    else if (element > root->element)
        root->right = deleteNode(root->right, element);
    else {
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
        temp = findMin(root->right);
        root->element = temp->element;
        root->right = deleteNode(root->right, temp->element);
    }
    return root;
}

int inorder(treeP root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->element);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(treeP root) {
    if (root) {
        printf("%d ", root->element);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(treeP root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->element);
    }
    return EXIT_SUCCESS;
}

int initQueue(Queue *q) {
    q->front = q->rear = 0;
    return EXIT_SUCCESS;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int enqueue(Queue *q, treeP node) {
    q->items[q->rear++] = node;
    return EXIT_SUCCESS;
}

treeP dequeue(Queue *q) {
    return q->items[q->front++];
}

int levelOrder(treeP root) {
    Queue q;
    treeP current;

    if (root == NULL)
        return EXIT_SUCCESS;

    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        current = dequeue(&q);
        printf("%d ", current->element);

        if (current->left)
            enqueue(&q, current->left);
        if (current->right)
            enqueue(&q, current->right);
    }
    return EXIT_SUCCESS;
}
