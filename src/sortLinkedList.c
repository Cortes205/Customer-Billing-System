#include "../include/header.h"

/* Merge Sort */
void sortByLastName(customer** head, customer** tail) {
	if (*head == NULL || (*head)->linkedNext == NULL) {
		return;
	}

	/* Disconnect LinkedList at the midpoint */
	customer* midpoint = middleNode(*head);

	customer* left = *head;
	*head = NULL;

	customer* right = midpoint->linkedNext;
	midpoint->linkedNext = NULL;

	sortByLastName(&left, &midpoint);
	sortByLastName(&right, tail);
	mergeLinkedList(left, right, head, tail);
}

void mergeLinkedList(customer* left, customer* right, customer** head, customer** tail) {
	/* Dummy node to avoid edge case of NULL linked list */
	customer* temp = calloc(1, sizeof(customer));
	temp->linkedNext = NULL;
	*tail = temp;

	while (left != NULL && right != NULL) {

		stringToLowercase(left->lname);
		stringToLowercase(right->lname);

		/* Cycle throught the letters of each name w/o going out of bounds */
		for (int i = 0; i < strlen(left->lname) && i < strlen(right->lname); i++) {
			if (left->lname[i] == right->lname[i]) {
				/* If everything is equal but we've reached the end of the left last name; this one goes first */
				if (i == strlen(left->lname)-1) {
					(*tail)->linkedNext = left;
					*tail = left;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					left = left->linkedNext;
					break;
				/* If everything is equal but we've reached the end of the right last name */
				} else if (i == strlen(right->lname)-1) {
					(*tail)->linkedNext = right;
					*tail = right;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					right = right->linkedNext;
					break;
				}
			/* If the letter at i in left comes before the letter at i in right; merge left */
			} else if (left->lname[i] < right->lname[i]) {
				(*tail)->linkedNext = left;
				*tail = left;
				stringFormatName(left->lname);
				stringFormatName(right->lname);
				left = left->linkedNext;
				break;
			/* If the letter at i in left comes after the letter at i in right; merge right */
			} else if (left->lname[i] > right->lname[i]) {
				(*tail)->linkedNext = right;
				*tail = right;
				stringFormatName(left->lname);
				stringFormatName(right->lname);
				right = right->linkedNext;
				break;
			}
		}
	}

	/* Connect the remains of left to the list */
	if (left != NULL) {
		(*tail)->linkedNext = left;

		/* Keep track of tail - get to the end */
		while ((*tail)->linkedNext != NULL) {
			*tail = (*tail)->linkedNext;
		}
	}

	/* Connect the remains of right to the list */
	if (right != NULL) {
		(*tail)->linkedNext = right;

		while ((*tail)->linkedNext != NULL) {
			*tail = (*tail)->linkedNext;
		}
	}

	/* Set head to the node after the dummy node */
	*head = temp->linkedNext;
	free(temp);
}

customer* middleNode(customer* head) {
	customer* slow = head;
	customer* fast = head->linkedNext;

	/* Once the node going twice as fast reaches the end, the slower one is in the middle */
	while (fast != NULL && fast->linkedNext != NULL) {
		slow = slow->linkedNext;
		fast = fast->linkedNext->linkedNext;
	}

	return slow;
}
