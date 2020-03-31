#include <stdio.h>
#include "tree.h"

/*Создание дерева из одного элемента*/
node* newn(int x) {
    node* p;
    p = new node;
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/*Добавление левого сына*/
void setleft(node *p, int x) {
    node* p1;
    p1 = new node;
    p->left = p1;
    p1->info = x;
    p1->left = NULL;
    p1->right = NULL;
}

/*Добавление правого дерева*/
void setright(node *p, int x) {
    node* p1;
    p1 = new node;
    p->right = p1;
    p1->info = x;
    p1->left = NULL;
    p1->right = NULL;
}

/*Добавление элемента в дерево*/
void add(node *p, int x) {
    node* next = p;
    while (next) {
        p = next;
        if (x >= p->info) next = p->right;
        else next = p->left;
    }
    if (x >= p->info) p->right = newn(x);
    else p->left = newn(x);
}

/*Печать дерева в прямом порядке*/
void print1(node *p) {
    printf("%5d",p->info);
    if (p->left)
        print1(p->left);
    if (p->right)
        print1(p->right);
}

/*Печать дерева в обратном порядке*/
void print2(node *p) {
    if (p->left)
        print2(p->left);
    if (p->right)
        print2(p->right);
    printf("%5d",p->info);
}

/*Печать дерева в симметричном порядке*/
void print3(node *p) {
    if (p->left)
        print3(p->left);
    printf("%5d",p->info);
    if (p->right)
        print3(p->right);
}

/*Нахождение суммы нечётных элементов дерева*/
int sum(node *p, int *k) {
    int S = 0;
    if ((p->info)%2) S+=p->info, *k+=1;
    if (p->left)
        S+=sum(p->left, k);
    if (p->right)
        S+=sum(p->right, k);
    return S;
}

/*Удаление из дерева всех элементов, равных x*/
node* del(node *p, int x) {
    node *tree,*curr,*t;
    tree = p;
    if (!p) return NULL;
    if (p->info == x) {
        tree = p->right;
        curr = tree;
        if (tree) {
            while (curr)
                t = curr, curr = curr->left;
            t->left = p->left;
        }
        else tree = p->left;
        delete p;
        tree = del(tree, x);
    }
    else if (p->info > x) p->left = del(p->left,x);
    else p->right = del(p->right,x);
    return tree;
}

/*Является ли узел листом*/
int leave(node* p) {//является ли узел листом
    if (!(p->left || p->right)) return 1;
    else return 0;
}

/*Удаление листьев*/
void del_leaves(node* prev, node **curr) {
    if (leave(*curr)) {
        if (prev) {
            if (prev->left == *curr)
                prev->left = NULL;
            else
                prev->right = NULL;
        }
        delete *curr;
        *curr = NULL;
    }
    else {
        if ((*curr)->left)
            del_leaves(*curr,&((*curr)->left));
        if ((*curr)->right)
            del_leaves(*curr,&((*curr)->right));
    }
}

/*Удаление дерева*/
void deltree(node* p) {
    if (p->left) deltree(p->left);
    if (p->right) deltree(p->right);
    delete p;
}

/*Удаление из дерева элементов, меньших x*/
node* delless(node* p, int x) {
    node* tree;
    tree = p;
    if (p) {
        if (p->info < x) {
            tree=p->right;
            deltree(p);
            tree=delless(tree, x);
        }
        else p->left=delless(p->left, x);
    }
    return tree;
}
