/*
 * muse_list.h
 *
 *  Created on: Sep 24, 2015
 *      Author: hangshi
 */

#ifndef MUSE_LIST_H_
#define MUSE_LIST_H_

// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);

typedef enum {
	FALSE, TRUE
} bool;

typedef bool (*listIterator)(void *);

typedef struct _listNode {
	void *data;
	int len;
	struct _listNode *next;
} listNode;

typedef struct {
	int logicalLength;
	int elementSize;
	listNode *head;
	listNode *tail;
	freeFunction freeFn;
} muse_list;

void list_new(muse_list *list, int elementSize, freeFunction freeFn);
void list_destroy(muse_list *list);

void list_prepend(muse_list *list, void *element);
void list_append(muse_list *list, void *element);
int list_size(muse_list *list);

void list_for_each(muse_list *list, listIterator iterator);
void list_head(muse_list *list, void *element, bool removeFromList);
void list_tail(muse_list *list, void *element);

#endif /* MUSE_LIST_H_ */
