/*
 * slist.c
 *
 *  Created on: 26-Sep-2023
 *      Author: apple
 */

#include <stdio.h>
#include <stdlib.h>
#include "slist.h"



char board[6][7];


void insertTail(slist* list, char player, int rows, int cols)
{

	struct node* newnode;  //create new node

	newnode = malloc(sizeof(struct node)); // Initialize the new node's values
	newnode->player = player;
	newnode->rows = rows;  //array row no.
	newnode->cols = cols;  //array col no.
	newnode->next=NULL;

	if (list->head == NULL)
	{
		list->head = newnode;
		list->tail = newnode;
	}
	else
	{
		//adding new node at tail
		list->tail->next = newnode;
		//adjusting pointers
		list->tail = newnode;
	}

	list->tail->next=NULL;

}

