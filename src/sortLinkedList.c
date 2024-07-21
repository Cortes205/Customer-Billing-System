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
	while (left != NULL && right != NULL) {

		stringToLowercase(left->lname);
		stringToLowercase(right->lname);

		int i = 0;
		while (i < strlen(left->lname) && i < strlen(right->lname)) {
			if (left->lname[i] == right->lname[i]) {
				if (i == strlen(left->lname)-1) {
					if (*head == NULL) {
						*head = left;
					} else {
						(*tail)->linkedNext = left;
					}
					*tail = left;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					left = left->linkedNext;
					break;
				} else if (i == strlen(right->lname)-1) {
					if (*head == NULL) {
						*head = right;
					} else {
						(*tail)->linkedNext = right;
					}
					*tail = right;
					stringFormatName(left->lname);
					stringFormatName(right->lname);
					right = right->linkedNext;
					break;
				}
			} else if (left->lname[i] < right->lname[i]) {
				if (*head == NULL) {
					*head = left;
				} else {
					(*tail)->linkedNext = left;
				}
				*tail = left;
				stringFormatName(left->lname);
				stringFormatName(right->lname);
				left = left->linkedNext;
				break;
			} else if (left->lname[i] > right->lname[i]) {
				if (*head == NULL) {
					*head = right;
				} else {
					(*tail)->linkedNext = right;
				}
				*tail = right;
				stringFormatName(left->lname);
				stringFormatName(right->lname);
				right = right->linkedNext;
				break;
			}
			i++;
		}
	}

	while (left != NULL) {
		if (*head == NULL) {
			*head = left;
		} else {
			(*tail)->linkedNext = left;
		}
		*tail = left;
		left = left->linkedNext;
	}

	while (right != NULL) {
		if (*head == NULL) {
			*head = right;
		} else {
			(*tail)->linkedNext = right;
		}
		*tail = right;
		right = right->linkedNext;
	}
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
