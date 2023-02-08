#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue_list.h"




int
main(int argc, char **argv) {
	
/*	
	//---------------------------------------------------------------- zad 1 --------------------------------------------------
	struct element* el = (struct queue*)malloc(sizeof(struct queue));
	el->head = NULL;
	el->tail = NULL;

	push(5, el);
	push(4, el);
	push(3, el);
	push(3, el);
	push(7, el);
	pop(el);
	push(8, el);*/

	//---------------------------------------------------------------- zad 2 --------------------------------------------------
	struct element* el = (struct queue*)malloc(sizeof(struct queue));
	el->head = NULL;
	el->tail = NULL;
	
	insert(3, 2, el);
	insert(4, 4, el);
	insert(6, 5, el);
	insert(8, 3, el);
	insert(11, 11, el);
	insert(2, 3, el);
	qremove(el);
	insert(1, 7, el);
	//---------------------------------------------------------------- zad 3 (tworzy ca³oœæ z sekcj¹ z zad 2) --------------------------------------------------
	struct element* el2 = (struct queue*)malloc(sizeof(struct queue));
	el2->head = NULL;
	el2->tail = NULL;

	insert(5, 7, el2);
	insert(40, 5, el2);
	insert(9, 9, el2);
	insert(1, 3, el2);
	insert(110, 15, el2);
	insert(88, 6, el2);
	qremove(el2);
	insert(90, 8, el2);

	merge_two_el(el, el2);
	print(el);
	order(el);

	// drukowanie kolejki
	print(el);
		
	return 0;
}
