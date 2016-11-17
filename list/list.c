/**
 * CS 2110 - Fall 2016 - Homework #10
 *
 * @author YOUR NAME HERE
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct. Has a next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO */
/* Design consideration: Only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES */
typedef struct dnode
{
    struct dnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;

/* Do not create any global variables here. Your list library should obviously
 * work for multiple concurrent lists */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
    (void)data;
	
	node* nnode = (node*) malloc(sizeof(node));
	nnode->next = NULL;
	nnode->data = data;
 
	return nnode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * @return an empty list
  */
list* create_list(void)
{
    /// @todo Implement changing the return value!
    (void)create_node;
    
	list *llist = (list*) malloc(sizeof(list));
	llist->head = NULL;
	llist->size = 0;
	
	return llist;
}

/** front
  *
  * Gets the data at the front of the list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the list or NULL.
  */
void *front(list *llist)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember, the
    /// user should never deal with the list nodes.
    (void)llist;
	if (llist == NULL) {
		return NULL; 
	}

	if (!is_empty(llist)) {
		void* data = llist->head->data;
		return data;
	}
	
	return NULL;
}

/** get
  *
  * Gets the data at the specified index in the list
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the list or NULL if index is
  *         out of range of the list.
  */
void *get(list *llist, int index)
{
    /// @todo Implement changing the return value!
    (void)llist;
    (void)index;

	if ((llist == NULL) || (index < 0) || (index >= llist->size)) {
		return NULL; 
	}
	if (!is_empty(llist)) {
		if (index < llist->size) {
			node* current = llist->head;
			int count = 0;
			while (count < index) {
				if (current->next != NULL) {
				  current = current->next;
				} else {
				  break;
				}
				count += 1;
			}
			void* data = current->data;
			return data;
		}
	}
	return NULL;
}

/** add
  *
  * Add the element at the specified index in the list
  * You should be able to add up to exactly one past the length of the list.
  * For example, if you have no elements in the list,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the list,
  * you should be able to add to index 2 but no further.
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return false if the index is out of bounds
  *         (do not add the data in this case)
  *         otherwise return true
  */
bool add(list *llist, int index, void *data)
{
    /// @todo Implement changing the return value!
    (void) llist;
    (void) index;
    (void) data;
	
	if ((llist == NULL) || (index < 0) || (data == NULL)) {
		return NULL;
	}

	if (index < llist->size+1) {
		if (!is_empty(llist)) {

			node* current = llist->head;
			node* previous = NULL;
			int ix = 0;
			while ((ix-index) < 0) {
				
				previous = current;
				current = previous->next;
				ix += 1;
				
			}
			if (previous == NULL) {
				node* temp = create_node(data);
				temp->next = current;
				llist->head = temp;
				return 1;
			} else {
				node* temp = create_node(data);
				temp->next = current;
				previous->next = temp;
				llist->size += 1;
				return 1;
			}	
		} else {
			llist->head = create_node(data);
			llist->size += 1;
			return 1;
		}
	}

	return NULL;
}

/** list_remove
  *
  * Removes the data from the specified index in the list
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the list or NULL if index is
  *         out of range of the list.
  */
void *list_remove(list *llist, int index)
{
    /// @todo Implement changing the return value!
    (void) llist;
    (void) index;
    int i = 0;

	if ((llist == NULL) || (index < 0) || (index >= llist->size)) {
		return NULL; 
	} 

	if (!is_empty(llist)) {
		node* previous = NULL;
		node* current = llist->head;
		while ((index-i) > 0) {
			previous = current;
			current = current->next;
			i += 1;
		}

		if(previous == NULL) {
			void* data = current->data;
			llist->head = llist->head->next;    
			free(current);
			llist->size -= 1;
			return data;
		}
	
		void* data = current->data;
		previous->next = current->next;
		free(current);
		llist->size -= 1;

		return data;
	}
	
	return NULL;
}

/** push_front
  *
  * Adds the data to the front of the list.
  *
  * @param llist a pointer to the list structure.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list *llist, void *data)
{
    /// @todo Implement
    (void) llist;
    (void) data;

	if ((llist == NULL) || (data == NULL)) {
		return;
	}

	if (is_empty(llist)) {
		llist->head = create_node(data);
		llist->size += 1;
	} else {
		node* hhead = llist->head;
		llist->head = create_node(data);
		llist->head->next = hhead;
		llist->size += 1;
	}
}

/** pop_front
  *
  * Removes the node at the front of the list, and returns its data to the user
  *
  * @param llist a pointer to the list.
  * @return The data in the first node, or NULL if the list is NULL or empty
  */
void *pop_front(list *llist)
{
    /// @todo Implement
    (void) llist;
	if (llist == NULL)
		return NULL; 
	
	if (!is_empty(llist)) {
		node* head = llist->head;
		void* data = llist->head->data;
		llist->head = llist->head->next;
		llist->size -= 1;
		free(head);
		return data;
	}
	
	return NULL;
}

/** contains
  *
  * Traverses the list, trying to see if the list contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a list of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the list which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param llist a pointer to the list structure
  * @param data The data, to see if it exists in the list
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the list, or NULL if it doesn't exist
  */
void *contains(list *llist, void *data, list_eq eq_func) {
    /// @todo Implement
    (void) llist;
    (void) data;
    (void) eq_func;

	if ((llist == NULL) || (data == NULL) || (eq_func == NULL)) {
		return NULL;
	}
	
	node* current = llist->head;
	while (!(eq_func(data, current->data) == 0)) {
		if (current->next != NULL) {
		current = current->next;
		} else {
		break;
		}
	}

	if (eq_func(data, current->data) == 0) {
		return current->data;
	}

	return NULL;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the list structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this list, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the list for in your test
  * @return The list structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
list* copy_list(list *llist, list_copy copy_func)
{
    /// @todo implement
    (void)llist;
    (void) copy_func;
	if ((llist == NULL) | (copy_func == NULL)) {
		return NULL; 
	}
	list* copy_llist = create_list();
	if (!(llist == NULL)) {
		int ix = 0;
		node* current = llist->head;
		add(copy_llist, ix, copy_func(current->data)); 
		ix += 1;
		while (ix < llist->size) {
			current = current->next;
			add(copy_llist, ix, copy_func(current->data));
			ix += 1;
		}
		return copy_llist;
	}
    return NULL;
}

/** size
  *
  * Gets the size of the list
  *
  * @param llist a pointer to the list structure
  * @return The size of the list
  */
int size(list *llist)
{
    ///@note simply return the size of the list. It's that easy!
    (void)llist;
	if (llist == NULL) {
		return 0;
	}
	return llist->size;
}

/** split_list
  *
  * Splits a list into two lists based on a predicate function.
  * If the predicate function returns true then that element should
  * be removed from original list and be in a new list returned
  * by this function. If the predicate function doesn't return true
  * for any elements then the function should return an empty list.
  *
  * @param llist a pointer to the list structure
  * @param pred_func a pointer to a function that when it returns true, it
  *                  should remove the element from the original list and
  *                  add it to the returned list.
  * @return a new list consiting of only the elements in the original list
  *                 that the pred_func returned a true value for.
  */
list *split_list(list *llist, list_pred pred_func)
{
    /// @todo create a new list to return
    /// @todo use pred_func on the data to determine which elements to remove
    /// @todo remove elements from the current list
    /// @todo add the removed elements to the new list
    (void) llist;
    (void) pred_func;

	list *rlist = create_list();
	int lsize = llist->size;
	int ix = 0;
	int lindex = 0;
	int rindex = 0;
	if (!is_empty(llist)) {
		node* current = llist->head; 
		node* next = NULL;
		while (ix < lsize) {
			next = current->next;
			if (pred_func(current->data)) {
				push_front(rlist, list_remove(llist, lindex)); 
				rindex += 1;
				lindex = lindex;
			} else {
				lindex += 1;
				rindex = rindex;
			}
			current = next;
			ix += 1;
		}  
	}

    return rlist;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list structure
  * @return 1 if the list is indeed empty, or 0 otherwise.
  */
int is_empty(list *llist)
{
    /// @note an empty list should have a size of zero and head points to NULL.
    (void) llist;
	if (llist == NULL) {
		return 0; 
	} 
	if (llist->head == NULL && llist->size == 0) {
		return 1;
	}
	return 0;
}

/** empty_list
  *
  * Empties the list. After this is called, the list should be empty.
  * This does not free the list struct itself, just all nodes and data within.
  *
  * @param llist a pointer to the list structure
  * @param free_func function used to free the nodes' data.
  */
void empty_list(list *llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes, not the list structure itself.
    /// @note do not free the list structure itself.
    (void) llist;
    (void) free_func;
	if ((llist == NULL) || (free_func == NULL)) {
		return;
	}

	int limit = llist->size;

	for (int ix = limit-1; ix >= 0; ix--) {
		free_func(list_remove(llist, ix)); 
	}
}

/** traverse
  *
  * Traverses the list, calling a function on each node's data.
  *
  * @param llist a pointer to the list structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(list *llist, list_op do_func)
{
    /// @todo Implement
    (void) llist;
    (void) do_func;
	if ((llist == NULL) || (do_func == NULL)) {
		return;
	}
	if (!is_empty(llist)) {
		node* current = llist->head;
		while (current->next != NULL) {
			do_func(current->data);
			current = current->next;
		}
		do_func(current->data);
	}
}
