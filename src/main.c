#include "../include/header.h"

int main() {
	printf("=== Customer Billing System ===\n\n");

	/* Sequential Array of Pointers Pointing to All Transactions */
	int transactionArraySize = 0;
	transaction** transactionArray = calloc(0, sizeof(transaction*));

	/* Array of Pointers Pointing to All Transactions and Customers (to be Stored at Hashed Indicies) */
	transaction** transactionMap = calloc(HASH_SIZE, sizeof(transaction*));
	customer** customerMap = calloc(HASH_SIZE, sizeof(customer*));

	/* Head and Tail of Customer Linked List */
	customer* head = NULL;
	customer* tail = NULL;

	bool running = true;
	if (!openData("customers.db", &head, &tail, customerMap, transactionMap, &transactionArray, &transactionArraySize)) {
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

			/* Store the Valid Integer in Option (call by ref.) */
			valid = validateIntegerInput(userInput, &option, true, 1, 7);
		}

		if (option != 7) printf("\n");

		/* Variables to be Used in Certain Cases */
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

				editCustomer(currentCustomer, customerMap, transactionMap, &transactionArray, &transactionArraySize);

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
				sortByDate(transactionArray, transactionArraySize);

				/* Left is the first occurence of the date - Right is the last */
				/* Initialized this way so that if no transactions are found,
				no values are returned and the for-loop does not run below */
				int left = 0, right = -1;

				/* To be assigned - call by reference */
				int month = 0, day = 0, year = 0;

				char date[DATE_MAXLEN] = "";
				takeDateInput(userInput, "Service", &month, &day, &year);
				sprintf(date, "%d/%d/%d", month, day, year);

				if (!searchByDate(transactionArray, transactionArraySize, month, day, year, &left, &right)) {
					printf("\nThere are no Transactions From %s\n\n", date);
				} else {
					printf("\nTransactions from %s:\n\n", date);
				}

				for (int i = left; i <= right; i++) {
					printf("\t\tPayor: %s %s\n", transactionArray[i]->payor->fname, transactionArray[i]->payor->lname);
					displayTransactionInfo(transactionArray[i]);
					printf("\n");
				}

				break;
			case 7:
				running = false;
				break;
		}
	}

	freeData(&head, transactionMap);
	free(transactionMap);
	free(customerMap);
	free(transactionArray);
	return 0;
}
