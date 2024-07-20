#include "../include/header.h"

customer* hashSearchCustomer(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], int storageIndex) {
	customer* temp = customerMap[storageIndex];
	while (temp != NULL) {
		if (strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0) {
			break;
		}
		temp = temp->hashNext;
	}
	return temp;
}
