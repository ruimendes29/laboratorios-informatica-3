/**
 * Arraylist implementation
 * (c) 2011 @marekweb
 *
 * Uses dynamic extensible arrays.
 */
#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct arraylist *ArrayList;

typedef int (*arraylist_cmpfn)(const void *, const void *);

void arraylist_destroy(ArrayList l);

void arraylist_splice(ArrayList l, ArrayList source, unsigned int index);

void arraylist_join(ArrayList l, ArrayList source);

ArrayList arraylist_copy(ArrayList);

ArrayList arraylist_slice_end(ArrayList l, unsigned int index);

ArrayList arraylist_slice(ArrayList l, unsigned int index, unsigned int length);

void arraylist_clear(ArrayList);

void *arraylist_remove(ArrayList l, unsigned int index);

void arraylist_insert(ArrayList l, unsigned int index, void *value);

void arraylist_set(ArrayList l, unsigned int index, void *value);

void *arraylist_get(ArrayList l, unsigned int index);

void *arraylist_pop(ArrayList);

void arraylist_add(ArrayList l, void *item);

unsigned int arraylist_size(ArrayList l);

void arraylist_allocate(ArrayList l, unsigned int size);

ArrayList arraylist_create(arraylist_cmpfn comp);

int arraylist_find_by(ArrayList l, void *item, arraylist_cmpfn comp);

int arraylist_find(ArrayList l, void *item);

ArrayList arraylist_insertLast(ArrayList l, void *item, arraylist_cmpfn comp);

#define arraylist_iterate(l, index, item) \
    for (index = 0, item = l->body[0]; index < l->size; item = l->body[++index])

struct arraylist {
    unsigned int size;      // Count of items currently in list
    unsigned int capacity;  // Allocated memory size, in items
    void **body;  // Pointer to allocated memory for items (of size capacity *
                  // sizeof(void*))
    arraylist_cmpfn compare;
};

#define INTERFACE 0

#endif
