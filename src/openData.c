#include "../include/header.h"

bool openData(char fileName[FILE_NAME_MAXLEN], customer** head, customer** tail, customer** customerMap, transaction** transactionMap, transaction*** transactionArray, int* transactionArraySize) {
	FILE *fptr = fopen(fileName, "a+");
	FILE *transPtr = NULL;
	if (fptr == NULL) {
		printf("ERROR: File '%s' Did Not Open Correctly\n", fileName);
		return false;
	}
	fseek(fptr, 0, SEEK_SET); // Although 'a+' is already at end of the file I just do this anyways

	/* Dummy node to avoid edge case of NULL linked list */
	customer *temp = calloc(1, sizeof(customer));
	*tail = temp;

	char buffer[300] = "";
	while (fgets(buffer, 300, fptr)) {
		/* Read Customer Information */
		buffer[strlen(buffer)-1] = '\0';
		customer* newCustomer = calloc(1, sizeof(customer));

		fillCustomerInfo(buffer, newCustomer);

		/* Useful info when editing */
		newCustomer->filePosition = ftell(fptr);

		(*tail)->linkedNext = newCustomer;
		*tail = newCustomer;

		unsigned long int customerIndex = getCustomerHashIndex(newCustomer->fname, newCustomer->lname);
		hashAddCustomer(customerMap, newCustomer, customerIndex);

		/* Make transaction file name based off customer name and phone number */
		char transFile[FILE_NAME_MAXLEN] = "customers/";
		createFileName(transFile, newCustomer->fname, newCustomer->lname, newCustomer->phoneNumber);

		transPtr = fopen(transFile, "a+");
		if (transPtr == NULL) {
			printf("ERROR: File '%s' Did Not Open Correctly\n", transFile);
			continue;
		}
		fseek(transPtr, 0, SEEK_SET);

		/* Another dummy node */
		transactionNode* tempTrans = calloc(1, sizeof(transactionNode));
		newCustomer->tail = tempTrans;

		char transBuffer[500] = "";
		while (fgets(transBuffer, 500, transPtr)) {
			/* Read transaction info belonging to newCustomer */
			transBuffer[strlen(transBuffer)-1] = '\0';
			transaction* newTransaction = calloc(1, sizeof(transaction));
			transactionNode* newID = calloc(1, sizeof(transactionNode));

			fillTransactionInfo(transBuffer, newTransaction);

			newTransaction->payor = newCustomer;
			newTransaction->filePosition = ftell(transPtr);

			newID->id = newTransaction->id;
			newID->next = NULL;

			newCustomer->tail->next = newID;
			newCustomer->tail = newID;

			unsigned long int transactionIndex = getTransactionHashIndex(newID->id);
			hashAddTransaction(transactionMap, newTransaction, transactionIndex);

			(*transactionArraySize)++;
			*transactionArray = realloc(*transactionArray, (*transactionArraySize) * sizeof(transaction*));
			(*transactionArray)[*transactionArraySize-1] = newTransaction;
		}
		fclose(transPtr);

		/* Set transaction head to node after dummy node */
		newCustomer->head = tempTrans->next;
		free(tempTrans);
		tempTrans = NULL;

	}
	fclose(fptr);

	/* Set customer head to node after dummy node */
	*head = temp->linkedNext;
	free(temp);
	temp = NULL;

	return true;
}
