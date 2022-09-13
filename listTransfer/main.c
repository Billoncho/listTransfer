// NOTE: in the last example we looked at the basics of a doubly linked list
// here, I'll show you how you would normally use them as a 'queue'
// a queue is a 'first-in, first-out' (FIFO) structure
// NOTE: you can also easily insert and remove items at any point in the queue if you wish, but it is more common to keep to FIFO operations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Author: Billy Gene Ridgeway
Date: Sept. 13th. 2022
Purpose: Learn about transfering a list in C.
*/

// This what is going to be in the queue.
typedef struct listitem {
	struct listitem *next;			// Pointer to the next item.
	struct listitem *prev;			// Pointer to the previous item.
	int data;						// Some integer data.
} LISTITEM;

// This is the queue 'header.'
typedef struct {
	struct listitem *first;			// Pointer to 1st. item.
	struct listitem *last;			// Pointer to last item.
} LISTHDR;

LISTHDR src;						// This is the 'source' list.
LISTHDR dst;						// This is the 'destination' list.

									// This puts an item in at the end of a queue.
void enqueue(LISTHDR *queue, LISTITEM *item) {
	LISTITEM *temp;

	temp = queue->last;				// Get the 'last' item in the queue and keep hold of it.
	queue->last = item;				// Put the item in the queue at the end.
	item->prev = temp;				// Link back to old 'last' item.
	item->next = (LISTITEM*)queue;	// Set the forward link of the new item.
	temp->next = item;				// Finally set the forward link of the old 'last' item to the new one.
}

// This removes an item from the front of a queue and returns the item, or NULL if there are no more items.
LISTITEM *dequeue(LISTHDR *queue) {
	LISTITEM *temp;

	temp = queue->first;				// Get the 'first' item.
	if (temp == (LISTITEM*)queue) {		// If the head of the queue points to itself,
		temp = NULL;					// then the queue is empty.		
	} else {
		queue->first = temp->next;		// Set the queue header to point to the 'second' item.
		queue->first->prev = (LISTITEM*)queue;
	}
	return temp;
}

int main() {
	LISTITEM *temp;

	// First, make empty 'source' and 'destination' queues.
	src.first = (LISTITEM*)&src;
	src.last = (LISTITEM*)&src;
	dst.first = (LISTITEM*)&dst;
	dst.last = (LISTITEM*)&dst;

	for (int i = 0; i < 3; i++) {			// Populate the queue.
		temp = malloc(sizeof(LISTITEM)); 	// Allocate some memory for the new queue item.
		temp->data = i;						// Set the item's data to the loop count so that we can see where it is in the queue.
		enqueue(&src, temp);				// Put it in the queue.
	}

	// Now let's remove from the 'source' queue and add to the 'destination queue.
	// NOTE: It would be possible to write a 'copy' function which does this, but it's better to use the existing 'enqueue' and 'dequeue'
	// methods that I've already developed, the reason being that I know that they work! This is a good example of code reuse rather than 're-invent'.
	// In general, it is usually better to re-use something which has been tested and works rather than someting new which may have errors.

	printf("\nBuilding the destination queue ...\n\n");
	do {							// Keep going until the 'source' queue is empty.
		temp = dequeue(&src);		// If the queue is empty we will get NULL returned.
		if (temp != NULL) {
			printf("Data is %d\n", temp->data);
			enqueue(&dst, temp);
		}
	} while (temp != NULL);

	// See what we've got.
	printf("\nDestination queue ...\n\n");
	do {							// Keep going until the queue is empty.
		temp = dequeue(&dst);		// If the queue is empty we will get NULL returned.
		if (temp != NULL) {
			printf("Destination data is %d\n", temp->data);
			free(temp);				// Call 'free' to clean up.
		}
	} while (temp != NULL);

	printf("\nSource queue ...\n\n");
	temp = dequeue(&src);		// If the queue is empty we will get NULL returned.
	if (temp == NULL) {
		printf("Source queue is empty.\n\n");
	}
	return 0;
}

