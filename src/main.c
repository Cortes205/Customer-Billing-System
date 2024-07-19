#include "../include/header.h"

int main() {
	printf("=== Customer Billing System ===\n\n");

	transaction** transactionMap = calloc(HASH_SIZE, sizeof(transaction*));
	customer** customerMap = calloc(HASH_SIZE, sizeof(customer*));
	customer* head = NULL;
	customer* tail = NULL;

	bool running = true;
	if (!openData("customers.db", &head, &tail, customerMap, transactionMap)) {
		running = false;
	}

	while (running) {
		printf("Main Menu:\n\n");
		printf("\t1. Open a Customer's Profile\n");
		printf("\t2. Open a Transaction by ID\n");
		printf("\t3. Create New Customer Profile\n");
		printf("\t4. Exit\n\n");

		printf("Enter Option: ");

		running = false;
	}

	freeData(&head, transactionMap);
	free(transactionMap);
	free(customerMap);
	return 0;
}
