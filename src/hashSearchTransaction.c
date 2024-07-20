#include "../include/header.h"

transaction* hashSearchTransaction(transaction** transactionMap, int id, int storageIndex) {
	transaction* temp = transactionMap[storageIndex];
	while (temp != NULL) {
		if (temp->id == id) {
			break;
		}
		temp = temp->hashNext;
	}
	return temp;
}
