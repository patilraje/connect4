/*
 * slist.h
 *
 *  Created on: 26-Sep-2023
 *      Author: apple
 */

#ifndef SLIST_H_
#define SLIST_H_

#include <stdio.h>
struct node
{
	char player;
	int rows;
	int cols;
	struct node* next;
};

struct singlylinkedlist
{
	struct node* head;
	struct node* tail;
};

typedef struct singlylinkedlist slist;

void insertTail(slist* list, char player, int rows, int cols);

#endif /* SLIST_H_ */
