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
			printf("FATAL ERROR: Transaction of the ID %d Does not Exist in the Database - Double Check the Invoices and Report This Potential Bug", head->id);
		} else {
			printf("\nTransaction #%d:\n", transCount);
			printf("\tTransaction ID: %d\n", currentTransaction->id);
			printf("\tService Date: %s\n", currentTransaction->serviceDate);
			printf("\tDescription: %s\n", currentTransaction->service);
			printf("\tTotal Amount: $%.2lf\n", currentTransaction->totalAmount);
			printf("\tBalance Paid: $%.2lf\n", currentTransaction->paidAmount);
			printf("\tBalance Owing: $%.2lf\n", currentTransaction->owingAmount);
			printf("\tDue Date: %s\n", currentTransaction->dueDate);
			printf("\tStatus: %s\n", currentTransaction->status);
			transCount++;
		}

		head = head->next;
	}
	return true;
}
