#include <stdio.h>
#include "tree.h"

node* newn(int x) {//создание дерева из одного элемента
    node* p;
    p = new node;
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}
void setleft(node *p, int x) {//добавить левого сына в дерево
    node* p1;
    p1 = new node;
    p->left = p1;
    p1->info = x;
    p1->left = NULL;
    p1->right = NULL;
}
void setright(node *p, int x) {//добавить правого сына в дерево
    node* p1;
    p1 = new node;
    p->right = p1;
    p1->info = x;
    p1->left = NULL;
    p1->right = NULL;
}
void add(node *p, int x) {//добавить элемент в дерево поиска
    node* next = p;
    while (next) {
        p = next;
        if (x >= p->info) next = p->right;
        else next = p->left;
    }
    if (x >= p->info) p->right = newn(x);
    else p->left = newn(x);
}
void print1(node *p) { //прохождение в прямом порядке
    printf("%5d",p->info);
    if (p->left)
        print1(p->left);
    if (p->right)
        print1(p->right);
}
void print2(node *p) { //прохождение в обратном порядке
    if (p->left)
        print2(p->left);
    if (p->right)
        print2(p->right);
    printf("%5d",p->info);
}
void print3(node *p) { //прохождение в симметричном порядке
    if (p->left)
        print3(p->left);
    printf("%5d",p->info);
    if (p->right)
        print3(p->right);
}
int sum(node *p, int *k) {//сумма нечётных элементов дерева
    int S = 0;
    if ((p->info)%2) S+=p->info, *k+=1;
    if (p->left)
        S+=sum(p->left, k);
    if (p->right)
        S+=sum(p->right, k);
    return S;
}
node* del(node *p, int x) {//удаление из дерева всех элементов, равных x
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
int leave(node* p) {//является ли узел листом
    if (!(p->left || p->right)) return 1;
    else return 0;
}
void del_leaves(node* prev, node **curr) {//удаление листьев
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
int deltree(node* p) {
    int x = 0;
    if (p->left) x+=deltree(p->left);
    if (p->right) x+=deltree(p->right);
    delete p;
    x+=1;
    return x;
}
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
