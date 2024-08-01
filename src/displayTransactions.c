#include "../include/header.h"

bool displayTransactions(transactionNode* head, transaction** transactionMap) {
	if (head == NULL) {
		return false;
	}

	int transCount = 1;
	while (head != NULL) {
		unsigned long int index = getTransactionHashIndex(head->id);
		transaction* currentTransaction = hashSearchTransaction(transactionMap, head->id, index);

		if (currentTransaction == NULL) {
			/* This should never happen unless something is very wrong */
			printf("\nFATAL ERROR: Transaction of the ID %d Does not Exist in the Database - Double Check the Invoices and Report This Potential Bug\n", head->id);
		} else {
			printf("\nTransaction #%d:\n", transCount);
			displayTransactionInfo(currentTransaction);
			transCount++;
		}

		head = head->next;
	}
	return true;
}
