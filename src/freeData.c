#include "../include/header.h"

void freeData(customer** head, transaction** transactionMap) {
	customer* temp = *head;
	customer* tempPrev = NULL;

	transactionNode* currTransNode = NULL;
	transactionNode* prevTransNode = NULL;

	transaction* currTrans = NULL;
	transaction* prevTrans = NULL;

	while (temp != NULL) {
		currTransNode = temp->head;
		while (currTransNode != NULL) {
			unsigned long int index = getTransactionHashIndex(currTransNode->id);
			currTrans = transactionMap[index];
			while (currTrans != NULL) {
				prevTrans = currTrans;
				currTrans = currTrans->hashNext;
				free(prevTrans);
				prevTrans = NULL;
			}
			prevTransNode = currTransNode;
			currTransNode = currTransNode->next;
			free(prevTransNode);
			prevTransNode = NULL;
		}
		tempPrev = temp;
		temp = temp->linkedNext;
		free(tempPrev);
		tempPrev = NULL;
	}
}
