#include "../include/header.h"

void sortByLastName(customer** head, customer** tail) {
	if (*head == NULL || (*head)->linkedNext == NULL) {
		return;
	}

	customer* midpoint = middleNode(*head);

	customer* left = *head;
	*head = NULL;

	customer* right = midpoint->linkedNext;
	midpoint->linkedNext = NULL;

	sortByLastName(&left, &midpoint);
	sortByLastName(&right, tail);
	merge(left, right, head, tail);
}

void merge(customer* left, customer* right, customer** head, customer** tail) {
	customer* temp = calloc(1, sizeof(customer));
	temp->linkedNext = NULL;
	*tail = temp;

	while (left != NULL && right != NULL) {

		stringToLowercase(left->lname);
		stringToLowercase(right->lname);

		for (int i = 0; i < strlen(left->lname) && i < strlen(right->lname); i++) {
			if (left->lname[i] == right->lname[i]) {
				if (i == strlen(left->lname)-1) {
					(*tail)->linkedNext = left;
					*tail = left;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					left = left->linkedNext;
					break;
				} else if (i == strlen(right->lname)-1) {
					(*tail)->linkedNext = right;
					*tail = right;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					right = right->linkedNext;
					break;
				}
			} else if (left->lname[i] < right->lname[i]) {
				(*tail)->linkedNext = left;
				*tail = left;
				stringFormatName(left->lname);
				stringFormatName(right->lname);
				left = left->linkedNext;
				break;
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

	while (left != NULL) {
		(*tail)->linkedNext = left;
		*tail = left;
		left = left->linkedNext;
	}

	while (right != NULL) {
		(*tail)->linkedNext = right;
		*tail = right;
		right = right->linkedNext;
	}

	*head = temp->linkedNext;
	free(temp);
}

customer* middleNode(customer* head) {
	customer* slow = head;
	customer* fast = head->linkedNext;

	while (fast != NULL && fast->linkedNext != NULL) {
		slow = slow->linkedNext;
		fast = fast->linkedNext->linkedNext;
	}

	return slow;
}
