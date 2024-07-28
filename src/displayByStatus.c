#include "../include/header.h"

void displayByStatus(customer* customerProfile, transaction** transactionMap, char* status) {
	while (customerProfile != NULL) {
		printf("%s, %s: \n\n", customerProfile->lname, customerProfile->fname);
		int numTransactions = 0;
		transactionNode* temp = customerProfile->head;
		while (temp != NULL) {
			transaction* info = hashSearchTransaction(transactionMap, temp->id, getTransactionHashIndex(temp->id));

			if (strcmp(info->status, status) == 0) {
				numTransactions++;
				printf("\tTransaction #%d:\n", numTransactions);
				displayTransactionInfo(info);
				printf("\n");
			}

			temp = temp->next;
		}

		if (numTransactions == 0) {
			printf("\tThere are no Transactions of the Status: %s\n\n", status);
		}

		customerProfile = customerProfile->linkedNext;

	}
}
