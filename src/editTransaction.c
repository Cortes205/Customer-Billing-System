#include "../include/header.h"

void editTransaction(transaction** transactionMap, customer* customerProfile) {
	transaction* transactionInfo = NULL;

	bool valid = false;
	char userInput[300] = "";
	int option = 0;

	while (transactionInfo == NULL) {
		valid = false;
		strcpy(userInput, "");
		option = 0;
		while (!valid) {
			printf("Input '-1' to Go Back\n");
			printf("Enter the Transaction ID: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			if (strcmp(userInput, "-1") == 0) {
				return;
			}

			valid = validateIntegerInput(userInput, &option, true, 100000, 999999);
		}

		unsigned long int index = getTransactionHashIndex(option);
		transactionInfo = hashSearchTransaction(transactionMap, option, index);

		if (transactionInfo == NULL) {
			printf("ERROR: This Transaction Does Not Exist - Please Try Again\n\n");
		} else if (transactionInfo->payor != customerProfile) {
			printf("ERROR: This Transaction Does Not Belong to %s %s - Please Try Again\n\n", customerProfile->fname, customerProfile->lname);
			transactionInfo = NULL;
		}
	}

	char transFile[FILE_NAME_MAXLEN] = "customers/";

	char oldServiceDate[DATE_MAXLEN] = "";
	char oldDescription[SERVICE_MAXLEN] = "";
	char oldDueDate[DATE_MAXLEN] = "";
	char oldStatus[STATUS_MAXLEN] = "";

	createFileName(transFile, customerProfile->fname, customerProfile->lname, customerProfile->phoneNumber);

	int oldId = transactionInfo->id;
	strcpy(oldServiceDate, transactionInfo->serviceDate);
	strcpy(oldDescription, transactionInfo->service);
	double oldTotal = transactionInfo->totalAmount;
	double oldPaid = transactionInfo->paidAmount;
	double oldOwing = transactionInfo->owingAmount;
	strcpy(oldDueDate, transactionInfo->dueDate);
	strcpy(oldStatus, transactionInfo->status);

	bool saveAll = false;
	bool editMode = true;
	bool hashChange = false;
	while (editMode) {

		printf("\nTransaction Info Editing:\n\n");
		printf("\t\tPayor: %s %s\n", transactionInfo->payor->fname, transactionInfo->payor->lname);
		displayTransactionInfo(transactionInfo);

		printf("\n\t1. Change Transaction ID\n");
		printf("\t2. Change Service Date\n");
		printf("\t3. Change Service Description\n");
		printf("\t4. Change Total\n");
		printf("\t5. Change Amount Paid\n");
		printf("\t6. Change Amount Owing\n");
		printf("\t7. Change Due Date\n");
		printf("\t8. Change Status\n");
		printf("\t9. Save Changes & Go Back\n");
		printf("\t10. Discard Changes & Go Back\n\n");

		valid = false;
		strcpy(userInput, "");
		option = 0;
		while (!valid) {
			printf("Enter an Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, true, 1, 10);
		}

		printf("\n");
		int month = 0, day = 0, year = 0;
		double input = -1;
		switch (option) {
			case 1:
				valid = false;
				strcpy(userInput, "");
				option = 0;
				while (!valid) {
					printf("Input '-1' to Go Back\n");
					printf("Enter New Transaction ID: ");

					fgets(userInput, 300, stdin);
					userInput[strlen(userInput)-1] = '\0';

					if (strcmp(userInput, "-1") == 0) {
						break;
					}

					valid = validateIntegerInput(userInput, &option, true, 100000, 999999);

					unsigned long int possibleIndex = getTransactionHashIndex(option);
					if (hashSearchTransaction(transactionMap, option, possibleIndex) != NULL) {
						printf("\nERROR: The Transaction of ID %d Already Exists - Please Try Again or Edit That Transaction First\n\n", option);
						valid = false;
					}
				}

				if (!valid) {
					break;
				}

				transactionInfo->id = option;

				hashChange = true;
				break;
			case 2:
				takeDateInput(userInput, "new Service", &month, &day, &year);
				sprintf(transactionInfo->serviceDate, "%d/%d/%d", month, day, year);
				break;
			case 3:
				printf("Enter new Service Description: ");
				fgets(transactionInfo->service, SERVICE_MAXLEN, stdin);
				transactionInfo->service[strlen(transactionInfo->service)-1] = '\0';
				stringUppercaseAfterSpace(transactionInfo->service);
				break;
			case 4:
				takeDoubleInput(userInput, "Enter new Total Amount: ", &input);
				transactionInfo->totalAmount = input;
				break;
			case 5:
				takeDoubleInput(userInput, "Enter new Paid Amount: ", &input);
				transactionInfo->paidAmount = input;
				break;
			case 6:
				takeDoubleInput(userInput, "Enter new Owing Amount: ", &input);
				transactionInfo->owingAmount = input;
				break;
			case 7:
				takeDateInput(userInput, "new Due", &month, &day, &year);
				sprintf(transactionInfo->dueDate, "%d/%d/%d", month, day, year);
				break;
			case 8:
				printf("Enter new Status: ");
				fgets(transactionInfo->status, STATUS_MAXLEN, stdin);
				transactionInfo->status[strlen(transactionInfo->status)-1] = '\0';
				stringToUppercase(transactionInfo->status);
				break;
			case 9:
				saveAll = true;
			case 10:
				editMode = false;
				break;
		}
	}

	if (saveAll) {
		saveTransactionChanges(transFile, transactionMap, transactionInfo);

		if (hashChange) {
			changeTransactionIdNodes(transactionInfo->payor->head, oldId, transactionInfo->id);
			changeTransactionHashPosition(transactionMap, oldId, transactionInfo->id);
		}
	} else {
		transactionInfo->id = oldId;
		strcpy(transactionInfo->serviceDate, oldServiceDate);
		strcpy(transactionInfo->service, oldDescription);
		transactionInfo->totalAmount = oldTotal;
		transactionInfo->paidAmount = oldPaid;
		transactionInfo->owingAmount = oldOwing;
		strcpy(transactionInfo->dueDate, oldDueDate);
		strcpy(transactionInfo->status, oldStatus);
	}
}

void changeTransactionIdNodes(transactionNode* head, int oldId, int id) {
	while (head != NULL) {
		if (head->id == oldId) {
			head->id = id;
			break;
		}
		head = head->next;
	}
}

void changeTransactionHashPosition(transaction** transactionMap, int oldId, int id) {
	unsigned long int oldIndex = getTransactionHashIndex(oldId);
	transaction* tempPrev = NULL;
	transaction* temp = transactionMap[oldIndex];

	while (temp != NULL) {
		if (temp->id == id) {
			if (tempPrev == NULL) {
				transactionMap[oldIndex] = temp->hashNext;
			} else {
				tempPrev->hashNext = temp->hashNext;
			}
			temp->hashNext = NULL;
			break;
		}
		tempPrev = temp;
		temp = temp->hashNext;
	}

	unsigned long int newIndex = getTransactionHashIndex(id);
	hashAddTransaction(transactionMap, temp, newIndex);
}

bool saveTransactionChanges(char file[FILE_NAME_MAXLEN], transaction** transactionMap, transaction* transactionInfo) {
	FILE *fptr = fopen(file, "a+");
	FILE *tempFptr = fopen("customers/temp.db", "a+");
	if (fptr == NULL || tempFptr == NULL) {
		printf("ERROR: Changes Could Not Be Saved\n");
		return false;
	}

	fseek(fptr, 0, SEEK_SET);
	fseek(tempFptr, 0, SEEK_SET);

	char buffer[300] = "";
	int addition = 0;
	while (fgets(buffer, 300, fptr)) {
		if (ftell(fptr) == transactionInfo->filePosition) {
			char* info = formatTransactionInfo(transactionInfo);
			fprintf(tempFptr, "%s\n", info);
			addition = strlen(info) - strlen(buffer) + 1;
			transactionInfo->filePosition = ftell(fptr) + addition;
			free(info);
		} else {
			fprintf(tempFptr, "%s", buffer);

			transaction* transactionToChange = calloc(1, sizeof(customer));
			fillTransactionInfo(buffer, transactionToChange);
			unsigned long int index = getTransactionHashIndex(transactionToChange->id);
			transaction* realTransactionNode = hashSearchTransaction(transactionMap, transactionToChange->id, index);

			realTransactionNode->filePosition = ftell(fptr) + addition;

			free(transactionToChange);
		}
	}

	remove(file);
	rename("customers/temp.db", file);

	fclose(fptr);
	fclose(tempFptr);
	return true;
}

char* formatTransactionInfo(transaction* transactionInfo) {
	char* info = calloc(300, sizeof(char));
	stringUppercaseAfterSpace(transactionInfo->service);
	stringUnspace(transactionInfo->service);
	sprintf(info, "%d %s %s %.2lf %.2lf %.2lf %s %s", transactionInfo->id, transactionInfo->serviceDate, transactionInfo->service, transactionInfo->totalAmount, transactionInfo->paidAmount, transactionInfo->owingAmount, transactionInfo->dueDate, transactionInfo->status);
	stringSpaceOut(transactionInfo->service);
	return info;
}