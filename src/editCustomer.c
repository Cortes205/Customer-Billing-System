#include "../include/header.h"

void editCustomer(customer* customerProfile, customer** customerMap, transaction** transactionMap) {
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
		printf("\t6. Back to the Main Menu\n\n");


		bool valid = false;
		while(!valid) {
			printf("Enter an Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, 1, 6);
		}

		printf("\n");
		char transFile[FILE_NAME_MAXLEN] = "customers/";
		char newTransFile[FILE_NAME_MAXLEN] = "customers/";

		char oldFName[NAME_MAXLEN] = "";
		char oldLName[NAME_MAXLEN] = "";

		bool editMode = false;
		bool newFileName = false;
		bool hashChange = false;
		switch (option) {
			case 1:
				displayContactInfo(customerProfile);
				break;
			case 2:
				stringUnformatPhone(customerProfile->phoneNumber);
				createFileName(transFile, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);
				stringToLowercase(transFile);
				stringFormatPhone(customerProfile->phoneNumber);

				strcpy(oldFName, customerProfile->fname);
				strcpy(oldLName, customerProfile->lname);

				editMode = true;
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
					printf("\t6. Save & Go Back\n\n");

					valid = false;
					while (!valid) {
						printf("Enter an Option: ");
						fgets(userInput, 300, stdin);
						userInput[strlen(userInput)-1] = '\0';
						valid = validateIntegerInput(userInput, &option, 1, 6);
					}

					switch (option) {
						case 1:
							printf("\nEnter New First Name: ");

							fgets(userInput, NAME_MAXLEN, stdin);
							userInput[strlen(userInput)-1] = '\0';

							strcpy(customerProfile->fname, userInput);
							stringFormatName(customerProfile->fname);

							newFileName = true;
							hashChange = true;
							break;
						case 2:
							printf("\nEnter New Last Name: ");

							fgets(userInput, NAME_MAXLEN, stdin);
							userInput[strlen(userInput)-1] = '\0';

							strcpy(customerProfile->lname, userInput);
							stringFormatName(customerProfile->lname);

							newFileName = true;
							hashChange = true;
							break;
						case 3:
							printf("\nEnter New Address: ");

							fgets(userInput, ADDRESS_MAXLEN, stdin);
							userInput[strlen(userInput)-1] = '\0';

							strcpy(customerProfile->address, userInput);
							break;
						case 4:
							printf("\nEnter New Phone Number: ");

							fgets(userInput, PHONE_MAXLEN, stdin);
							userInput[strlen(userInput)-1] = '\0';

							strcpy(customerProfile->phoneNumber, userInput);
							stringUnformatPhone(customerProfile->phoneNumber);
							stringFormatPhone(customerProfile->phoneNumber);

							newFileName = true;
							break;
						case 5:
							printf("\nEnter New Email Address: ");

							fgets(userInput, EMAIL_MAXLEN, stdin);
							userInput[strlen(userInput)-1] = '\0';

							strcpy(customerProfile->email, userInput);
							break;
						case 6:
							editMode = false;
							break;
					}
				}

				char mainFile[FILE_NAME_MAXLEN] = "customers.db";
				saveChanges(mainFile, customerMap, customerProfile);

				if (newFileName) {
					stringUnformatPhone(customerProfile->phoneNumber);
					createFileName(newTransFile, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);
					stringToLowercase(newTransFile);
					stringFormatPhone(customerProfile->phoneNumber);
					rename(transFile, newTransFile);
				}

				if (hashChange) {
					changeHashPosition(customerMap, oldFName, oldLName, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);
				}
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

bool saveChanges(char file[FILE_NAME_MAXLEN], customer** customerMap, customer* customerProfile) {
	FILE *fptr = fopen(file, "a+");
	FILE *tempFptr = fopen("temp.db", "a+");
	if (fptr == NULL || tempFptr == NULL) {
		printf("ERROR: Changes Could Not Be Saved\n");
		return false;
	}

	fseek(fptr, 0, SEEK_SET);
	fseek(tempFptr, 0, SEEK_SET);

	char buffer[300] = "";
	int addition = 0;
	while (fgets(buffer, 300, fptr)) {
		if (ftell(fptr) == customerProfile->filePosition) {
			char* info = formatInfo(customerProfile);
			fprintf(tempFptr, "%s\n", info);
			addition = strlen(info) - strlen(buffer) + 1;
			customerProfile->filePosition = ftell(fptr) + addition;
			free(info);
		} else {
			fprintf(tempFptr, "%s", buffer);

			customer* customerToChange = calloc(1, sizeof(customer));
			fillCustomerInfo(buffer, customerToChange);
			unsigned long int index = getCustomerHashIndex(customerToChange->fname, customerToChange->lname);
			customer* realCustomerNode = hashSearchCustomerByPhone(customerMap, customerToChange->fname, customerToChange->lname, customerToChange->phoneNumber, index);

			if (realCustomerNode != NULL) realCustomerNode->filePosition = ftell(fptr) + addition;
			else printf("SHIT WAS NULLLLLLL\n");
			free(customerToChange);

		}
	}

	remove(file);
	rename("temp.db", file);

	fclose(fptr);
	fclose(tempFptr);
	return true;
}

char* formatInfo(customer* customerProfile) {
	char* info = calloc(300, sizeof(char));

	stringUnspace(customerProfile->address);
	stringUnformatPhone(customerProfile->phoneNumber);

	strcat(info, customerProfile->fname);
	strcat(info, " ");
	strcat(info, customerProfile->lname);
	strcat(info, " ");
	strcat(info, customerProfile->address);
	strcat(info, " ");
	strcat(info, customerProfile->phoneNumber);
	strcat(info, " ");
	strcat(info, customerProfile->email);

	stringSpaceOut(customerProfile->address);
	stringFormatPhone(customerProfile->phoneNumber);
	return info;
}

void changeHashPosition(customer** customerMap, char* oldFName, char* oldLName, char* fname, char* lname, char* phoneNumber) {
	unsigned long int index = getCustomerHashIndex(oldFName, oldLName);
	customer* tempPrev = NULL;
	customer* temp = customerMap[index];
	while (temp != NULL) {
		if (strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0 && strcmp(temp->phoneNumber, phoneNumber) == 0) {
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

	unsigned long int newIndex = getCustomerHashIndex(fname, lname);
	hashAddCustomer(customerMap, temp, newIndex);
}
