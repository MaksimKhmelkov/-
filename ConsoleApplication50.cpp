/*#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

structNode{
int data;
structNode* left;
structNode* right;
};

structNode* root;

int isValueExists(structNode* r, intvalue)
{
    if (r == NULL) {
        return 0;
    }

    if (r->data == value) {
        return 1;
    }

    return isValueExists(r->left, value) || isValueExists(r->right, value);
}

structNode* CreateTree(structNode* root, structNode* r, intdata)
{

    if (isValueExists(root, data)) {
        printf("Элемент %d уже существует в дереве! Добавление отменено.\n", data);
        returnroot;
    }

    if (r == NULL)
    {
        r = (structNode*)malloc(sizeof(structNode));
        if (r == NULL)
        {
            printf("Ошибкавыделенияпамяти"); exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) returnr;
        if (data > root->data)
            root->left = r;
        else
            root->right = r;
        returnr;
    }
    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    returnroot;
}

void print_tree(structNode* r, intl)
{
    if (r == NULL)
    {
        return;
    }
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}
int searchElement(structNode* r, intvalue)
{
    if (r == NULL) {
        return 0;
    }

    if (r->data == value) {
        return 1;
    }


    if (searchElement(r->left, value) || searchElement(r->right, value)) {
        return 1;
    }

    return 0;
}

int countOccurrences(structNode* r, intvalue)
{
    if (r == NULL) {
        return 0;
    }

    int count = 0;

    if (r->data == value) {
        count = 1;
    }

    return count + countOccurrences(r->left, value) + countOccurrences(r->right, value);
}

int countTotalNodes(structNode* r) {
    if (r == NULL) return 0;
    return 1 + countTotalNodes(r->left) + countTotalNodes(r->right);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;
    root = NULL;

    printf("-1 - окончание построения дерева\n");
    printf("Дубликаты элементов не допускаются!\n");

    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, root, D);
        }
    }

    printf("Построенное дерево:\n");
    print_tree(root, 0);
    printf("\n");

    int totalNodes = countTotalNodes(root);
    printf("=== ОЦЕНКА СЛОЖНОСТИ ПРОЦЕДУРЫ ПОИСКА ===\n");
    printf("Количество узлов в дереве: %d\n", totalNodes);
    printf("Сложностьфункции searchElement: O(n)\n");
    printf("где n = %d (количествоузлов)\n", totalNodes);

    int searchValue;
    printf("Введите значение для поиска в дереве: ");
    scanf_s("%d", &searchValue);

    if (searchElement(root, searchValue)) {
        printf("Элемент %d НАЙДЕН в дереве.\n", searchValue);
    }
    else {
        printf("Элемент %d НЕ НАЙДЕН в дереве.\n", searchValue);
    }


    int countValue;
    printf("Введите значение для подсчёта вхождений: ");
    scanf_s("%d", &countValue);

    int occurrences = countOccurrences(root, countValue);
    printf("Элемент %d встречается в дереве %d раз(а).\n", countValue, occurrences);

    printf("\nНажмите любую клавишу для выхода...");
    scanf_s("%d", &D);

    return 0;
}*/
