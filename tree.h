#ifndef TREE_H
#define TREE_H

struct node {
    int info;
    node *left, *right;
};

node* newn(int x);
void add(node *p, int x);
void print1(node *p);
void print2(node *p);
void print3(node *p);
int sum(node *p, int *k);
node* del(node* p, int x);
void del_leaves(node* prev, node **curr);
int deltree(node* p);
node* delless(node* p, int x);

#endif // TREE_H
