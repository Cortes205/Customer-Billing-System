#include "../include/header.h"

void displayCustomers(customer* head) {
	if (head == NULL) {
		printf("There are no customers yet.\n");
		return;
	}

	printf("Customer List (Last Name, First Name):\n\n");
	while (head != NULL) {
		printf("\t%s, %s\n", head->lname, head->fname);
		head = head->linkedNext;
	}
	printf("\n");
}
