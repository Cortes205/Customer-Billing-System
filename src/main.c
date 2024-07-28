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
		printf("\t1. View All Customers\n");
		printf("\t2. View a Customer's Profile\n");
		printf("\t3. Create New Customer Profile\n");
		printf("\t4. View a Transaction by ID\n");
		printf("\t5. Display All Transactions by Status for Every Customer\n");
		printf("\t6. Display Transactions From a Specific Date\n");
		printf("\t7. Exit\n\n");

		bool valid = false;
		char userInput[300] = "";
		int option = 0;
		while (!valid) {
			printf("Enter Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, true, 1, 9);
		}

		if (option != 7) printf("\n");

		unsigned long int index = 0;
		char fname[NAME_MAXLEN] = "";
		char lname[NAME_MAXLEN] = "";
		customer* currentCustomer = NULL;
		switch(option) {
			case 1:
				sortByLastName(&head, &tail);
				displayCustomers(head);
				break;
			case 2:
				printf("Enter Customer First Name: ");
				scanf("%s", fname);

				printf("Enter Customer Last Name: ");
				scanf("%s", lname);
				getchar();

				stringFormatName(fname);
				stringFormatName(lname);

				index = getCustomerHashIndex(fname, lname);
				currentCustomer = hashSearchCustomer(customerMap, fname, lname, index);

				if (currentCustomer == NULL) {
					break;
				}

				editCustomer(currentCustomer, customerMap, transactionMap);

				break;
			case 3:
				createCustomer(customerMap, &head, &tail);
				break;
			case 4:
				editTransaction(transactionMap, NULL);
				break;
			case 5:
				strcpy(userInput, "");
				printf("Search by Status: ");

				fgets(userInput, 300, stdin);
				userInput[strlen(userInput)-1] = '\0';
				stringToUppercase(userInput);

				sortByLastName(&head, &tail);
				displayByStatus(head, transactionMap, userInput);
				break;
			case 6:
				break;
			case 7:
				running = false;
				break;
		}
	}

	freeData(&head, transactionMap);
	free(transactionMap);
	free(customerMap);
	return 0;
}
