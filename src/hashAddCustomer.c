#include "../include/header.h"

void hashAddCustomer(customer** customerMap, customer* addition, unsigned long int storageIndex) {
	if (customerMap[storageIndex] == NULL) {
		customerMap[storageIndex] = addition;
	} else {
		customer* temp = customerMap[storageIndex];
		while (temp->hashNext != NULL) {
			temp = temp->hashNext;
		}
		temp->hashNext = addition;
	}
}
