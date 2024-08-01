#include "../include/header.h"

void freeData(customer** head, transaction** transactionMap) {
	customer* temp = *head;
	customer* tempPrev = NULL;

	transactionNode* currTransNode = NULL;
	transactionNode* prevTransNode = NULL;

	transaction* currTrans = NULL;
	transaction* prevTrans = NULL;

	/*
		Traverse the customer LinkedList.
		At each customer node, traverse the transactionNodes linked list.
		At each transactionNode, get the transaction from the HashMap and free it, as well as anything else in the same index due to collisions.
		Free all transactionNodes,
		Repeat to free all customers.
	*/

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
