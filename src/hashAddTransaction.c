#include "../include/header.h"

/* Closed Addressing to handle collisions */
void hashAddTransaction(transaction** transactionMap, transaction* addition, int storageIndex) {
	if (transactionMap[storageIndex] == NULL) {
		transactionMap[storageIndex] = addition;
	} else {
		transaction* temp = transactionMap[storageIndex];
		while (temp->hashNext != NULL) {
			temp = temp->hashNext;
		}
		temp->hashNext = addition;
	}
}
