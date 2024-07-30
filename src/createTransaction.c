#include "../include/header.h"

void createTransaction(transaction** transactionMap, customer* payor, transaction*** transactionArray, int* transactionArraySize) {
	transaction* addition = calloc(1, sizeof(transaction));
	transactionNode* infoAddition = calloc(1, sizeof(transaction));

	bool valid = false;
	bool saveInfo = false;
	char userInput[300] = "";
	int intInput = 0;
	double doubleInput = 0;
	int month = 0, day = 0, year = 0;
	while (!valid) {
		printf("Transaction Creation Menu:\n\n");

		printf("Enter Transaction ID: ");

		fgets(userInput, 300, stdin);
		userInput[strlen(userInput)-1] = '\0';

		valid = validateIntegerInput(userInput, &intInput, true, 100000, 999999);

		if (!valid) {
			continue;
		}

		unsigned long int possibleIndex = getTransactionHashIndex(intInput);
		if (hashSearchTransaction(transactionMap, intInput, possibleIndex) != NULL) {
			printf("\nERROR: The Transaction of ID %d Already Exists - Please Try Again or Edit That Transaction First\n\n", intInput);
			valid = false;
			continue;
		}

		addition->id = intInput;
		infoAddition->id = intInput;

		takeDateInput(userInput, "Service", &month, &day, &year);
		sprintf(addition->serviceDate, "%d/%d/%d", month, day, year);

		printf("Enter Service Description: ");
		fgets(addition->service, SERVICE_MAXLEN, stdin);
		addition->service[strlen(addition->service)-1] = '\0';
		stringUppercaseAfterSpace(addition->service);

		takeDoubleInput(userInput, "Enter Total Amount: ", &doubleInput);
		addition->totalAmount = doubleInput;

		takeDoubleInput(userInput, "Enter Paid Amount: ", &doubleInput);
		addition->paidAmount = doubleInput;

		takeDoubleInput(userInput, "Enter Owing Amount: ", &doubleInput);
		addition->owingAmount = doubleInput;

		takeDateInput(userInput, "Due", &month, &day, &year);
		sprintf(addition->dueDate, "%d/%d/%d", month, day, year);

		printf("Enter Status: ");
		fgets(addition->status, STATUS_MAXLEN, stdin);
		addition->status[strlen(addition->status)-1] = '\0';
		stringToUppercase(addition->status);

		printf("\n");
		displayTransactionInfo(addition);
		printf("\n");

		valid = false;
		bool confirming = true;
		while (confirming) {
			printf("Is This Info Correct (Y/N)? ");
			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';
			confirming = yesOrNo(userInput);

			if (strcmp(userInput, "N") == 0) {
				while (!valid) {
					printf("Would You Like to Try Again (Y/N)? ");
					fgets(userInput, 300, stdin);
					userInput[strlen(userInput)-1] = '\0';
					valid = !yesOrNo(userInput);
				}

				if (strcmp(userInput, "Y") == 0) {
					valid = false;
					printf("\n");
				}

			} else if (!confirming) {
				valid = true;
				saveInfo = true;
			}
		}
	}

	if (saveInfo) {
		if (payor->head == NULL) {
			payor->head = infoAddition;
			payor->tail = infoAddition;
		} else {
			payor->tail->next = infoAddition;
			payor->tail = infoAddition;
		}

		addition->payor = payor;
		unsigned long int index = getTransactionHashIndex(addition->id);
		hashAddTransaction(transactionMap, addition, index);

		(*transactionArraySize)++;
		*transactionArray = realloc(*transactionArray, *transactionArraySize * sizeof(transaction*));
		(*transactionArray)[(*transactionArraySize)-1] = addition;

		char transFile[FILE_NAME_MAXLEN] = "customers/";
		createFileName(transFile, payor->fname, payor->lname, payor->phoneNumber);

		FILE *fptr = fopen(transFile, "a+");
 		if (fptr == NULL) {
			printf("ERROR: File Did Not Open - Please Try Again\n\n");
			free(addition);
			free(infoAddition);
			addition = NULL;
			infoAddition = NULL;
			return;
		}

		char *info = formatTransactionInfo(addition);
		fprintf(fptr, "%s\n", info);
		free(info);

		fseek(fptr, 0, SEEK_END);
		addition->filePosition = ftell(fptr);

		fclose(fptr);
	} else {
		free(addition);
		free(infoAddition);
	}
}

bool yesOrNo(char *string) {
	stringToUppercase(string);
	if (strcmp(string, "Y") != 0) {
		if (strcmp(string, "N") == 0) {
			return false;
		}
		printf("ERROR: Invalid Input - Please Try Again");
		return true;
	}
	return false;
}
