#include "../include/header.h"

bool openData(char fileName[FILE_NAME_MAXLEN], customer** head, customer** tail, customer** customerMap, transaction** transactionMap) {
	FILE *fptr = fopen(fileName, "a+");
	FILE *transPtr = NULL;
	if (fptr == NULL) {
		printf("ERROR: File '%s' Did Not Open Correctly\n", fileName);
		return false;
	}
	fseek(fptr, 0, SEEK_SET);

	customer *temp = NULL;
	char buffer[300] = "";
	while (fgets(buffer, 300, fptr)) {
		buffer[strlen(buffer)-1] = '\0';
		customer* newCustomer = calloc(1, sizeof(customer));

		fillCustomerInfo(buffer, newCustomer);

		newCustomer->filePosition = ftell(fptr);

		if (temp == NULL) {
			*head = newCustomer;
			*tail = newCustomer;
			temp = *head;
		} else {
			temp->linkedNext = newCustomer;
			temp = temp->linkedNext;
			*tail = temp;
		}

		unsigned long int customerIndex = getCustomerHashIndex(newCustomer->fname, newCustomer->lname);
		hashAddCustomer(customerMap, newCustomer, customerIndex);

		char transFile[FILE_NAME_MAXLEN] = "customers/";
		createFileName(transFile, newCustomer->fname, newCustomer->lname, newCustomer->phoneNumber);

		transPtr = fopen(transFile, "a+");
		if (transPtr == NULL) {
			printf("ERROR: File '%s' Did Not Open Correctly\n", transFile);
			continue;
		}
		fseek(transPtr, 0, SEEK_SET);

		char transBuffer[500] = "";
		while (fgets(transBuffer, 500, transPtr)) {
			transBuffer[strlen(transBuffer)-1] = '\0';
			transaction* newTransaction = calloc(1, sizeof(transaction));
			transactionNode* newID = calloc(1, sizeof(transactionNode));
			
			fillTransactionInfo(transBuffer, newTransaction);

			newTransaction->payor = newCustomer;
			newTransaction->filePosition = ftell(transPtr);

			newID->id = newTransaction->id;
			newID->next = NULL;

			if (newCustomer->head == NULL) {
				newCustomer->head = newID;
				newCustomer->tail = newID;
			} else {
				newCustomer->tail->next = newID;
				newCustomer->tail = newID;
			}

			unsigned long int transactionIndex = getTransactionHashIndex(newID->id);
			hashAddTransaction(transactionMap, newTransaction, transactionIndex);
		}
		fclose(transPtr);
	}
	fclose(fptr);
	return true;
}
