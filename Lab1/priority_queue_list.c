#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void push(int element, struct element* el)
{
	struct queue* p = (struct queue*)malloc(sizeof(struct queue));
	p->next = NULL;
	p->previous = NULL;
	p->number = element;
	

	if (el->head == NULL) {
		
		el->tail = p;
		el->head = el->tail;
	}
	else {
		p->previous = el->tail;
		el->tail->next = p;
		el->tail = p;
	}
	el->tail->next = NULL;
}

void insert(int number, int pr, struct element* el)
{
	struct queue* p = (struct queue*)malloc(sizeof(struct queue));
	p->next = NULL;
	p->previous = NULL;
	p->number = number;
	p->priority = pr;
	
	struct queue* q;
	struct queue* w;

	if (el->head == NULL) {
		el->tail = p;
		el->head = el->tail;
	}
	else if (el->head == el->tail) {
		if (el->head->priority < p->priority) {
			el->tail->next = p;
			p->previous = el->tail;
			el->tail = p;
		}
		else {
			el->tail->previous = p;
			p->next = el->tail;
			el->head = p;
		}

	}
	else {
		
		if (el->tail->priority < p->priority) {
			p->previous = el->tail;
			el->tail->next = p;
			el->tail = p;
		}
		else {
			w = el->tail;
			q = el->tail->previous;

			
			while (w->priority >= p->priority && w->previous!= NULL) {
				w = w->previous;	

			}
			if (p->priority < w->priority) {
				q = w->previous;
				w->previous = p;
				p->next = w;
				if (w == el->head) {
					el->head = p;
				}
				else {
					p->previous = q;
					q->next = p;
				}
			}
			else {
				q = w->next;
				w->next = p;
				p->previous = w;
				p->next = q;
				q->previous = p;
			}
			

		}
		
	}
	el->tail->next = NULL;
}

void pop(struct element* el) {
	struct element* q;
	if (el->head == el->tail) {
		q = el->head;
		el->head = el->tail = NULL;
	}
	else {
		q = el->tail;
		el->tail = el->tail->previous;
	}
	free(q);
}

void qremove(struct element* el) {
	struct element* q;
	if (el->head == el->tail) {
		q = el->head;
		el->head = el->tail = NULL;
	}
	else {
		q = el->head;
		el->head = el->head->next;
	}
	free(q);
}

void merge_two_el(struct element* a, struct element* b) {

	if (a->head == NULL)
		return b;
	if (b->head == NULL)
		return a;
	if (a->head == NULL && b->head == NULL)
		return 0;


	
	a->tail->next = b->head;
	b->head->previous = a->tail;
	a->tail = b->tail;

}

void order(struct element* el) {

	struct element* new_q = (struct queue*)malloc(sizeof(struct queue));
	new_q->head = NULL;
	new_q->tail = NULL;
	struct queue* p = el->head;
	while (p->next != NULL) {
		insert(p->number, p->priority, new_q);
		p = p->next;
	}
	insert(p->number, p->priority, new_q);
	el->head = new_q->head;
	el->tail = new_q->tail;

}

void print(struct element* el) {
	struct queue* p = el->head;

	if (el->head && el->tail) {
		while (p != el->tail) {
			printf("%d ", p->number);
			p = p->next;
		}
		printf("%d\n", el->tail->number);
	}
}
