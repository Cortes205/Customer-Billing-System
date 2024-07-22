#include "../include/header.h"

customer* hashSearchCustomer(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], int storageIndex) {
	customer* temp = customerMap[storageIndex];
	customer** customersOfName = calloc(0, sizeof(customer));
	int numCustomers = 0;
	while (temp != NULL) {
		if (strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0) {
			numCustomers++;
			customersOfName = realloc(customersOfName, numCustomers * sizeof(customer));
			customersOfName[numCustomers-1] = temp;
		}
		temp = temp->hashNext;
	}

	if (numCustomers == 0) {
		printf("%s %s does not exist in the database.\n\n", fname, lname);
		temp = NULL;
	} else if (numCustomers == 1) {
		temp = customersOfName[0];
	} else {
		temp = multipleCustomers(customersOfName, numCustomers);
	}

	free(customersOfName);
	return temp;
}

customer* multipleCustomers(customer** customersOfName, int numCustomers) {
	printf("\nThere are multiple customers of the name %s %s:\n", customersOfName[0]->fname, customersOfName[0]->lname);

	for (int i = 0; i < numCustomers; i++) {
		printf("\nCustomer #%d:\n", (i+1));
		displayContactInfo(customersOfName[i]);
	}

	printf("\n\tInput %d to go Back\n\n", (numCustomers+1));

	bool valid = false;
	char userInput[300] = "";
	int option = 0;
	while (!valid) {
		printf("Enter an Option: ");
		fgets(userInput, 300, stdin);
		userInput[strlen(userInput)-1] = '\0';
		valid = validateIntegerInput(userInput, &option, 1, numCustomers+1);
	}

	if (option == numCustomers+1) {
		printf("\n");
		return NULL;
	}

	return customersOfName[option-1];
}

customer* hashSearchCustomerByPhone(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], char phoneNumber[PHONE_MAXLEN], int storageIndex) {
	customer* temp = customerMap[storageIndex];
	while (temp != NULL) {
		if (strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0 && strcmp(temp->phoneNumber, phoneNumber) == 0) {
			break;
		}
		temp = temp->hashNext;
	}
	return temp;
}
