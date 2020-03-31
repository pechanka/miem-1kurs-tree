#include <iostream>
#include <stdio.h>
#include "tree.h"
#define CLR while(getchar()!='\n')

using namespace std;

node* inputkeys() {
    node* tree;
    int x, n;
    printf("Введите числа (признак окончания ввода - буква): ");
    x = scanf("%d",&n);
    while (x != 1) {
        CLR;
        printf("Вы должны ввести хотя бы одно число\n");
        printf("Введите числа (признак окончания ввода - буква): ");
        x = scanf("%d",&n);
    }
    tree = newn(n);
    x = scanf("%d",&n);
    while (x == 1) {
        add(tree, n);
        x = scanf("%d",&n);
    }
    return tree;
}
node* inputfile() {
    int n;
    char s[81];
    node* tree;
    FILE *f;
    do {
        printf("Введите название файла: ");
        gets(s);
        f = fopen(s,"r");
    }
    while (!f);
    int x = fscanf(f,"%d",&n);
    if (x == 1)
        tree = newn(n);
    else return NULL;
    x = fscanf(f,"%d",&n);
    while (x == 1) {
        add(tree,n);
        x = fscanf(f,"%d",&n);
    }
    fclose(f);
    return tree;
}
int main()
{
    int x, n, s;
    node* tree;
    setlocale(LC_ALL,"RUS");
    do {
        printf("Выберите вариант ввода (1 - ввод с клавиатуры, 2 - ввод из файла): ");
        x = scanf("%d",&n);
        CLR;
    } while (x != 1 || (n!=1 && n!=2));
    if (n == 1)
        tree = inputkeys();
    else
        tree = inputfile();
    if (!tree)
        printf("Ошибка при вводе данных. Не удалось сформировать дерево");
    else {
        printf("Прохождение дерева в прямом порядке:\n");
        print1(tree);
        printf("\nПрохождение дерева в обратном порядке:\n");
        print2(tree);
        printf("\nПрохождение дерева в симметричном порядке:\n");
        print3(tree);
        n = 0; //количество нечётных элементов
        s = sum(tree, &n); //сумма нечётных элементов
        if (!n) printf("\nНет нечётных элементов в дереве");
        else
            printf("\nСумма нечётных элементов дерева: %d",s);
    }
    return 0;
}

