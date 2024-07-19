#include "../include/header.h"

bool openData(char fileName[FILE_NAME_MAXLEN], customer** head, customer** tail, customer** customerMap, transaction** transactionMap) {
	FILE *fptr = fopen(fileName, "a+");
	if (fptr == NULL) {
		printf("ERROR: File '%s' Did Not Open Correctly\n", fileName);
		return false;
	}
	fseek(fptr, 0, SEEK_SET);

	customer *temp = NULL;
	char buffer[300] = "";
	while (fgets(buffer, 300, fptr)) {
		customer* addition = calloc(1, sizeof(customer));
		sscanf(buffer, "%s%s%s%s%s", addition->fname, addition->lname, addition->address, addition->phoneNumber, addition->email);
		addition->head = NULL;
		addition->hashNext = NULL;
		addition->linkedNext = NULL;

		if (temp == NULL) {
			*head = addition;
			*tail = addition;
			temp = *head;
		} else {
			temp->linkedNext = addition;
			temp = temp->linkedNext;
			*tail = temp;
		}

		unsigned long int index = getCustomerHashIndex(addition->fname, addition->lname);
		hashAddCustomer(customerMap, addition, index);
	}
	return true;
}
