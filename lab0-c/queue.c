/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
	//because we setting option malloc size and then we allocated overflow malloc size
	if(!q)
		return NULL;
    q->head = NULL;
	q->q_insert_tail = NULL;
	q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
	if(!q)
		return;
	list_ele_t *tmp;
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
	while(q->head)
	{
		tmp = q->head;
		q->head = tmp->next;
		free(tmp->value);
		free(tmp);
	}
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
	if(!q)
		return false;
    list_ele_t *newh;
	unsigned int len = strlen(s) + 1;
	newh = malloc(sizeof(list_ele_t));
	if(!newh)
		return false;
	char* new_val = malloc(sizeof(char) * len);
	if(!new_val){
		free(newh);
		return false;
	}
	strcpy(new_val,s);
	new_val[len-1] = '\0';
	newh->value = new_val;
	newh->pre = NULL;
	q->q_size++;
    /* What should you do if the q is NULL? */
    if(q->head){
		list_ele_t* pre_h = q->head;
		pre_h->pre = newh;
		newh->next = pre_h;
    }
	else{
		q->q_insert_tail = newh;
		newh->next =  NULL;
	} 
    q->head = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if(!q || !*s)
    	return false;
	list_ele_t *new_one,*tmp; 
	unsigned int len = strlen(s) + 1;
	new_one = malloc(sizeof(list_ele_t));
	if(!new_one)
		return false;
	char* new_str = malloc(sizeof(char) * len);
	if(!new_str){
		free(new_one);
		return false;
	}	
	strcpy(new_str,s);
	new_str[len-1] = '\0';
	new_one->value = new_str;
	new_one->next = NULL;
	q->q_size++;
	if(!q->head)
	{
		new_one->pre = NULL;
		q->head = new_one;
		q->q_insert_tail = new_one;	
		return true;
	}
	tmp = q->q_insert_tail;
	tmp->next = new_one;
	new_one->pre = tmp;
	q->q_insert_tail = new_one;
	return true;
	
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
	if(!q || !q->head)
		return false;
    /* You need to fix up this code. */
	list_ele_t *pre_head = q->head;
    q->head = pre_head->next;
	if(q->head)
		q->head->pre = NULL;
	if(sp && bufsize){
		strncpy(sp,pre_head->value,bufsize);
		sp[bufsize - 1] = '\0';
	}
	free(pre_head->value);
	free(pre_head);
	q->q_size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(!q)
		return 0;
    return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
list_ele_t* MyList_reverse(list_ele_t* ReverList,queue_t *q)
{
	if(!ReverList->next){
		q->q_insert_tail = ReverList->pre;
		ReverList->next = ReverList->pre;
		q->q_insert_tail->pre = ReverList;
		return ReverList;
	}
	list_ele_t* new_head = MyList_reverse(ReverList->next,q);
	q->q_insert_tail->next = ReverList;
	ReverList->pre = q->q_insert_tail;
	ReverList->next = NULL;
	q->q_insert_tail = ReverList;
	return new_head;
	
}

void q_reverse(queue_t *q)
{
	if(!q || !q->head || !q->head->next)
		return;
	list_ele_t* hh= q->q_insert_tail;
	list_ele_t* nexth = hh->pre;
	hh->next = NULL;
	hh->pre =NULL;
	list_ele_t* res = hh;
	while(nexth)
	{
		list_ele_t* tmp = nexth;
		nexth = nexth->pre;
		hh->next = tmp;
		tmp->pre = hh;
		tmp->next =NULL;
		hh = tmp;
	}
	q->head =res;
	q->q_insert_tail = hh;
}
