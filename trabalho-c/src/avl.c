#include "avl.h"

Avl avltree_create(avltree_cmpfn compare, avltree_free f) {
    Avl tree = malloc(sizeof(struct avltree));
    if (tree != NULL) {
        tree->root = NULL;
        tree->compare = compare;
        tree->count = 0;
        tree->freeNode = f;
    }
    return tree;
}

static void avltreenode_delete(avltreenode *node, avltree_free f) {
    if (f != NULL) f(node->data);
    free(node);
}

static void avltree_empty_recursive(avltreenode *root, avltree_free f) {
    if (root->left) {
        avltree_empty_recursive(root->left, f);
    }
    if (root->right) {
        avltree_empty_recursive(root->right, f);
    }
    avltreenode_delete(root, f);
}

void avltree_empty(Avl tree, avltree_free f) {
    if (tree->root) {
        avltree_empty_recursive(tree->root, f);
        tree->root = NULL;
        tree->count = 0;
    }
}

void avltree_delete(Avl tree) {
    if (tree) {
        avltree_empty(tree, tree->freeNode);
        free(tree);
    }
}

static void avltree_for_each_recursive(const avltreenode *root,
                                       avltree_forfn fun, void *a0) {
    if (root->left != NULL) {
        avltree_for_each_recursive(root->left, fun, a0);
    }
    fun(root->data, a0);
    if (root->right != NULL) {
        avltree_for_each_recursive(root->right, fun, a0);
    }
}

static void avltree_for_each_recursive2(const avltreenode *root,
                                        avltree_forfn2 fun, void *a, void *r) {
    if (root->left != NULL) {
        avltree_for_each_recursive2(root->left, fun, a, r);
    }
    fun(root->data, a, r);
    if (root->right != NULL) {
        avltree_for_each_recursive2(root->right, fun, a, r);
    }
}

void avltree_for_each(const Avl tree, avltree_forfn fun, void *a0) {
    if (tree->root) {
        avltree_for_each_recursive(tree->root, fun, a0);
    }
}

void avltree_for_each2(const Avl tree, avltree_forfn2 fun, void *a, void *r) {
    if (tree->root) {
        avltree_for_each_recursive2(tree->root, fun, a, r);
    }
}

struct avlsearchresult {
    avltreenode *node;
    avltreenode *parent;
};

typedef struct avlsearchresult avlsearchresult;

static int avltree_search(const Avl tree, avlsearchresult *result,
                          const void *data) {
    int found = 0;

    result->node = tree->root;
    while (!found && result->node != NULL) {
        int rv = tree->compare(result->node->data, data);
        if (rv == 0) {
            found = 1;
        } else {
            result->parent = result->node;
            if (rv > 0) {
                result->node = result->node->left;
            } else if (rv < 0) {
                result->node = result->node->right;
            }
        }
    }
    return found;
}

static avltreenode *avltreenode_create(void *data) {
    avltreenode *node = malloc(sizeof(avltreenode));
    if (node) {
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->leftheight = 0;
        node->rightheight = 0;
        node->data = data;
    }
    return node;
}

static int avltreenode_get_max_height(const avltreenode *node) {
    int height;
    if (node->leftheight > node->rightheight) {
        height = node->leftheight;
    } else {
        height = node->rightheight;
    }
    return height;
}

static void avltreenode_fix_height(avltreenode *node) {
    node->leftheight = 0;
    node->rightheight = 0;
    if (node->left) {
        node->leftheight = avltreenode_get_max_height(node->left) + 1;
    }
    if (node->right) {
        node->rightheight = avltreenode_get_max_height(node->right) + 1;
    }
}

static void avltree_rotate_left(Avl tree, avltreenode *node) {
    avltreenode *right = node->right;
    if (node == tree->root) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->parent = node->parent;
    if (right->left) {
        node->right = right->left;
        node->right->parent = node;
    } else {
        node->right = NULL;
    }
    right->left = node;
    node->parent = right;
    avltreenode_fix_height(node);
    avltreenode_fix_height(right);
}

static void avltree_rotate_right(Avl tree, avltreenode *node) {
    avltreenode *left = node->left;
    if (node == tree->root) {
        tree->root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }
    left->parent = node->parent;
    if (left->right) {
        node->left = left->right;
        node->left->parent = node;
    } else {
        node->left = NULL;
    }
    left->right = node;
    node->parent = left;
    avltreenode_fix_height(node);
    avltreenode_fix_height(left);
}

static int avltreenode_get_balance_factor(const avltreenode *node) {
    return node->leftheight - node->rightheight;
}

static void avltree_rebalance(Avl tree, avltreenode *node) {
    avltreenode *current = node;
    while (current != NULL) {
        avltreenode *parent = current->parent;
        int balance;
        avltreenode_fix_height(current);
        balance = avltreenode_get_balance_factor(current);
        if (balance == -2) {
            /* Right heavy */
            const int rightbalance =
                avltreenode_get_balance_factor(current->right);
            if (rightbalance < 0) {
                avltree_rotate_left(tree, current);
            } else {
                avltree_rotate_right(tree, current->right);
                avltree_rotate_left(tree, current);
            }
        } else if (balance == 2) {
            /* Left heavy */
            const int leftbalance =
                avltreenode_get_balance_factor(current->left);
            if (leftbalance > 0) {
                avltree_rotate_right(tree, current);
            } else {
                avltree_rotate_left(tree, current->left);
                avltree_rotate_right(tree, current);
            }
        }
        current = parent;
    }
}

void *avltree_add(Avl tree, void *data) {
    void *temp = NULL;
    avlsearchresult result;
    result.node = NULL;
    result.parent = NULL;

    if (avltree_search(tree, &result, data)) {
        temp = result.node->data;
        result.node->data = data;
    } else {
        avltreenode *node = avltreenode_create(data);
        if (result.node == tree->root) {
            tree->root = node;
        } else {
            int rv = tree->compare(data, result.parent->data);
            if (rv < 0) {
                result.parent->left = node;
            } else {
                result.parent->right = node;
            }
            node->parent = result.parent;
            avltree_rebalance(tree, node);
        }
        tree->count++;
    }

    return temp;
}

void *avltree_find(const Avl tree, const void *data) {
    void *temp = NULL;
    avlsearchresult result;
    result.node = NULL;
    result.parent = NULL;

    if (avltree_search(tree, &result, data)) {
        temp = result.node->data;
    }
    return temp;
}

static int avltree_search_by(const Avl tree, avlsearchresult *result,
                             const void *data, avltree_cmpfn compare) {
    int found = 0;

    result->node = tree->root;
    while (!found && result->node != NULL) {
        int rv = compare(result->node->data, data);
        if (rv == 0) {
            found = 1;
        } else {
            result->parent = result->node;
            if (rv > 0) {
                result->node = result->node->left;
            } else if (rv < 0) {
                result->node = result->node->right;
            }
        }
    }
    return found;
}

void *avltree_find_by(const Avl tree, const void *data, avltree_cmpfn compare) {
    void *temp = NULL;
    avlsearchresult result;
    result.node = NULL;
    result.parent = NULL;

    if (avltree_search_by(tree, &result, data, compare)) {
        temp = result.node->data;
    }
    return temp;
}

static avltreenode *avltreenode_find_min(avltreenode *node) {
    avltreenode *current = node;

    while (current->left) {
        current = current->left;
    }
    return current;
}

static void avltree_remove_node(Avl tree, avltreenode *node) {
    if (node->left && node->right) {
        /* Node with 2 children */
        avltreenode *successor = avltreenode_find_min(node->right);
        node->data = successor->data;
        avltree_remove_node(tree, successor);
    } else {
        avltreenode *parent = node->parent;
        if (node->left) {
            /* Node with only left child */
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = node->left;
                    node->parent->left->parent = node->parent;
                } else {
                    node->parent->right = node->left;
                    node->parent->right->parent = node->parent;
                }
            } else {
                tree->root = node->left;
                tree->root->parent = NULL;
            }
        } else if (node->right) {
            /* Node with only right child */
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = node->right;
                    node->parent->left->parent = node->parent;
                } else {
                    node->parent->right = node->right;
                    node->parent->right->parent = node->parent;
                }
            } else {
                tree->root = node->right;
                tree->root->parent = NULL;
            }
        } else {
            /* Node with no children */
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = NULL;
                } else {
                    node->parent->right = NULL;
                }
            } else {
                tree->root = NULL;
            }
        }
        avltreenode_delete(node, tree->freeNode);
        avltree_rebalance(tree, parent);
        tree->count--;
    }
}

void *avltree_remove(Avl tree, const void *data) {
    void *temp = NULL;
    avlsearchresult result;
    result.node = NULL;
    result.parent = NULL;

    if (avltree_search(tree, &result, data)) {
        temp = result.node->data;
        avltree_remove_node(tree, result.node);
    }
    return temp;
}

size_t avltree_get_count(const Avl tree) { return tree->count; }