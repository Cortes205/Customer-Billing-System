#include "../include/header.h"

void editCustomer(customer* customerProfile, customer** customerMap, transaction** transactionMap, transaction*** transactionArray, int* transactionArraySize) {
	bool editing = true;
	printf("\nOpening Profile...\n");

	while (editing) {
		printf("\n%s, %s:\n\n", customerProfile->lname, customerProfile->fname);
		printf("\t1. View Contact Info\n");
		printf("\t2. Edit Contact Info\n");
		printf("\t3. View All Transactions\n");
		printf("\t4. Edit Transactions\n");
		printf("\t5. Create a Transaction\n");
		printf("\t6. Back to the Main Menu\n\n");

		bool valid = false;
		char userInput[300] = "";
		int option = 0;
		while(!valid) {
			printf("Enter an Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, true, 1, 6);
		}

		printf("\n");

		switch (option) {
			case 1:
				displayContactInfo(customerProfile);
				break;
			case 2:
				editInfo(customerProfile, customerMap);
				break;
			case 3:
				if (!displayTransactions(customerProfile->head, transactionMap)) {
					printf("%s %s does not have any transactions on record.\n", customerProfile->fname, customerProfile->lname);
				}
				break;
			case 4:
				editTransaction(transactionMap, customerProfile);
 				break;
			case 5:
				createTransaction(transactionMap, customerProfile, transactionArray, transactionArraySize);
				break;
			case 6:
				editing = false;
				break;
		}
	}
}

void editInfo(customer* customerProfile, customer** customerMap) {
	/* Made true if this task is needed to be done */
	bool changeTransFile = false;
	bool hashChange = false;
	bool saveAll = false;

	char transFile[FILE_NAME_MAXLEN] = "customers/";
	char newTransFile[FILE_NAME_MAXLEN] = "customers/";

	/* Keeping copies of old info in case changes are made then discarded */

	char oldFName[NAME_MAXLEN] = "";
	char oldLName[NAME_MAXLEN] = "";
	char oldAddress[ADDRESS_MAXLEN] = "";
	char oldPhone[PHONE_MAXLEN] = "";
	char oldEmail[EMAIL_MAXLEN] = "";

	createFileName(transFile, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);

	strcpy(oldFName, customerProfile->fname);
	strcpy(oldLName, customerProfile->lname);
	strcpy(oldAddress, customerProfile->address);
	strcpy(oldPhone, customerProfile->phoneNumber);
	strcpy(oldEmail, customerProfile->email);

	bool editMode = true;
	while (editMode) {

		printf("\nContact Info Editing:\n\n");
		printf("\t\tFirst Name: %s\n", customerProfile->fname);
		printf("\t\tLast Name: %s\n", customerProfile->lname);
		displayContactInfo(customerProfile);

		printf("\n\t1. Change First Name\n");
		printf("\t2. Change Last Name\n");
		printf("\t3. Change Address\n");
		printf("\t4. Change Phone Number\n");
		printf("\t5. Change Email Address\n");
		printf("\t6. Save & Go Back\n");
		printf("\t7. Discard Changes & Go Back\n\n");

		bool valid = false;
		char userInput[300] = "";
		int option = 0;
		while (!valid) {
			printf("Enter an Option: ");
			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';
			valid = validateIntegerInput(userInput, &option, true, 1, 7);
		}

		switch (option) {
			case 1:
				printf("\nEnter New First Name: ");

				strcpy(userInput, "");
				fgets(userInput, NAME_MAXLEN, stdin);
				userInput[strlen(userInput)-1] = '\0';
				stringFormatName(userInput);

				if (hashSearchCustomerByPhone(customerMap, userInput, customerProfile->lname, customerProfile->phoneNumber, getCustomerHashIndex(userInput, customerProfile->lname))) {
					printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				} else {
					strcpy(customerProfile->fname, userInput);
					changeTransFile = true;
					hashChange = true;
				}
				break;
			case 2:
				printf("\nEnter New Last Name: ");

				strcpy(userInput, "");
				fgets(userInput, NAME_MAXLEN, stdin);
				userInput[strlen(userInput)-1] = '\0';
				stringFormatName(userInput);

				if (hashSearchCustomerByPhone(customerMap, customerProfile->fname, userInput, customerProfile->phoneNumber, getCustomerHashIndex(customerProfile->fname, userInput))) {
					printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				} else {
					strcpy(customerProfile->lname, userInput);
					changeTransFile = true;
					hashChange = true;
				}
				break;
			case 3:
				printf("\nEnter New Address: ");

				fgets(customerProfile->address, ADDRESS_MAXLEN, stdin);
				customerProfile->address[strlen(customerProfile->address)-1] = '\0';

				break;
			case 4:
				printf("\nEnter New Phone Number: ");

				strcpy(userInput, "");
				fgets(userInput, PHONE_MAXLEN, stdin);
				userInput[strlen(userInput)-1] = '\0';

				stringUnformatPhone(userInput);
				stringFormatPhone(userInput);

				if (hashSearchCustomerByPhone(customerMap, customerProfile->fname, customerProfile->lname, userInput, getCustomerHashIndex(customerProfile->fname, customerProfile->lname))) {
					printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				} else {
					strcpy(customerProfile->phoneNumber, userInput);
					changeTransFile = true;
				}
				break;
			case 5:
				printf("\nEnter New Email Address: ");

				fgets(customerProfile->email, EMAIL_MAXLEN, stdin);
				customerProfile->email[strlen(customerProfile->email)-1] = '\0';

				break;
			case 6:
				saveAll = true;
			case 7:
				editMode = false;
				break;
		}
	}

	if (saveAll) {
		char mainFile[FILE_NAME_MAXLEN] = "customers.db";
		saveCustomerChanges(mainFile, customerMap, customerProfile);

		if (changeTransFile) {
			createFileName(newTransFile, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);
			rename(transFile, newTransFile);
		}

		if (hashChange) {
			changeCustomerHashPosition(customerMap, oldFName, oldLName, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);
		}
	} else {
		/* If changes are discarded, copy back old info */
		strcpy(customerProfile->fname, oldFName);
		strcpy(customerProfile->lname, oldLName);
		strcpy(customerProfile->address, oldAddress);
		strcpy(customerProfile->phoneNumber, oldPhone);
		strcpy(customerProfile->email, oldEmail);
	}
}

bool saveCustomerChanges(char file[FILE_NAME_MAXLEN], customer** customerMap, customer* customerProfile) {
	FILE *fptr = fopen(file, "a+");
	FILE *tempFptr = fopen("temp.db", "a+");
	if (fptr == NULL || tempFptr == NULL) {
		printf("ERROR: Changes Could Not Be Saved\n");
		return false;
	}

	fseek(fptr, 0, SEEK_SET);
	fseek(tempFptr, 0, SEEK_SET);

	char buffer[300] = "";
	/* This is the offset of file positioning */
	int addition = 0;
	/* Copy all customer info to a new file EXCEPT for the old customer info 
	replace it with the new info */
	while (fgets(buffer, 300, fptr)) {
		if (ftell(fptr) == customerProfile->filePosition) {
			char* info = formatCustomerInfo(customerProfile);
			fprintf(tempFptr, "%s\n", info);
			/* This is how many bytes info after the new info will be offset by */
			addition = strlen(info) - strlen(buffer) + 1;
			customerProfile->filePosition = ftell(fptr) + addition;
			free(info);
		} else {
			/* No new line because fgets already has it */
			fprintf(tempFptr, "%s", buffer);

			/* Get the customer node and set its file position with the offset */
			customer* customerToChange = calloc(1, sizeof(customer));
			fillCustomerInfo(buffer, customerToChange);
			unsigned long int index = getCustomerHashIndex(customerToChange->fname, customerToChange->lname);
			customer* realCustomerNode = hashSearchCustomerByPhone(customerMap, customerToChange->fname, customerToChange->lname, customerToChange->phoneNumber, index);

			realCustomerNode->filePosition = ftell(fptr) + addition;

			free(customerToChange);

		}
	}

	/* Remove old file, rename temp file to be name of old file */
	remove(file);
	rename("temp.db", file);

	fclose(fptr);
	fclose(tempFptr);
	return true;
}

/* Formatted for file */
char* formatCustomerInfo(customer* customerProfile) {
	char* info = calloc(300, sizeof(char));

	stringUnspace(customerProfile->address);
	stringUnformatPhone(customerProfile->phoneNumber);

	sprintf(info, "%s %s %s %s %s", customerProfile->fname, customerProfile->lname, customerProfile->address, customerProfile->phoneNumber, customerProfile->email);

	stringSpaceOut(customerProfile->address);
	stringFormatPhone(customerProfile->phoneNumber);
	return info;
}

void changeCustomerHashPosition(customer** customerMap, char* oldFName, char* oldLName, char* fname, char* lname, char* phoneNumber) {
	unsigned long int index = getCustomerHashIndex(oldFName, oldLName);
	customer* tempPrev = NULL;
	customer* temp = customerMap[index];
	while (temp != NULL) {
		if (strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0 && strcmp(temp->phoneNumber, phoneNumber) == 0) {
			/* Disconnect node from HashMap */
			if (tempPrev == NULL) {
				customerMap[index] = temp->hashNext;
			} else {
				tempPrev->hashNext = temp->hashNext;
			}
			temp->hashNext = NULL;
			break;
		}
		tempPrev = temp;
		temp = temp->hashNext;
	}

	/* Reinsert the disconnected node */
	unsigned long int newIndex = getCustomerHashIndex(fname, lname);
	hashAddCustomer(customerMap, temp, newIndex);
}
