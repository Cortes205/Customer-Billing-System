#include "../include/header.h"

void editCustomer(customer* customerProfile, transaction** transactionMap) {
	bool editing = true;
	printf("\nOpening Profile...\n");

	char userInput[300] = "";
	int option = 0;
	while (editing) {
		printf("\n%s, %s:\n\n", customerProfile->lname, customerProfile->fname);
		printf("\t1. View Contact Info\n");
		printf("\t2. Edit Contact Info\n");
		printf("\t3. View All Transactions\n");
		printf("\t4. Edit Transactions\n");
		printf("\t5. Create a Transaction\n");
		printf("\t6. Back\n\n");


		bool valid = false;
		while(!valid) {
			printf("Enter an Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, 1, 6);
		}

		printf("\n");
		switch (option) {
			case 1:
				printf("\t\tHome Address: %s\n", customerProfile->address);
				printf("\t\tPhone Number: %s\n", customerProfile->phoneNumber);
				printf("\t\tEmail Address: %s\n", customerProfile->email);
				break;
			case 2:
				break;
			case 3:
				if (!displayTransactions(customerProfile->head, transactionMap)) {
					printf("%s %s does not have any transactions on record.\n", customerProfile->fname, customerProfile->lname);
				}
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				editing = false;
				break;
		}
	}
}
