#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <stdlib.h>

struct avltreenode {
    struct avltreenode* left;
    struct avltreenode* right;
    struct avltreenode* parent;
    unsigned int leftheight;
    unsigned int rightheight;
    void* data;
};

typedef struct avltreenode avltreenode;

typedef int (*avltree_cmpfn)(const void*, const void*);
typedef void (*avltree_forfn)(void*, void*);
typedef void (*avltree_forfn2)(void*, void*, void*);
typedef void (*avltree_free)(void*);

struct avltree {
    avltreenode* root;
    size_t count;
    avltree_cmpfn compare;
    avltree_free freeNode;
};

typedef struct avltree* Avl;

Avl avltree_create(avltree_cmpfn compare, avltree_free);
void avltree_delete(Avl tree);
void avltree_for_each(const Avl tree, avltree_forfn fun, void*);
void avltree_for_each2(const Avl tree, avltree_forfn2 fun, void*, void*);
void* avltree_add(Avl tree, void* data);
void* avltree_find(const Avl tree, const void* data);
void* avltree_find_by(const Avl tree, const void* data, avltree_cmpfn compare);
void* avltree_remove(Avl tree, const void* data);
void avltree_empty(Avl tree, avltree_free);
size_t avltree_get_count(const Avl tree);

#endif /* AVLTREE_H */