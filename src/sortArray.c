#include "../include/header.h"

void sortByDate(transaction** transactionArray, int transactionArraySize) {
	if (transactionArraySize < 2) return;

	int middle = transactionArraySize / 2;
	int leftSize = middle;
	int rightSize = transactionArraySize - middle;

	transaction** left = calloc(leftSize, sizeof(transaction*));
	transaction** right = calloc(rightSize, sizeof(transaction*));

	int k = 0;
	for (int i = 0; i < leftSize; i++) {
		left[i] = transactionArray[k];
		k++;
	}

	for (int i = 0; i < rightSize; i++) {
		right[i] = transactionArray[k];
		k++;
	}

	sortByDate(left, leftSize);
	sortByDate(right, rightSize);
	mergeArray(left, leftSize, right, rightSize, transactionArray);

	free(left);
	free(right);
}

void mergeArray(transaction** left, int leftSize, transaction** right, int rightSize, transaction** transactionArray) {
	int i = 0, j = 0, k = 0;
	while (i < leftSize && j < rightSize) {
		int leftMonth = 0, rightMonth = 0;
		int leftDay = 0, rightDay = 0;
		int leftYear = 0, rightYear = 0;

		stringUnformatDate(left[i]->serviceDate, &leftMonth, &leftDay, &leftYear);
		stringUnformatDate(right[i]->serviceDate, &rightMonth, &rightDay, &rightYear);

		if (leftYear == rightYear) {
			if (leftMonth == rightMonth) {
				if (leftDay <= rightDay) {
					transactionArray[k] = left[i];
					i++;
				} else {
					transactionArray[k] = right[j];
					j++;
				}
			} else if (leftMonth < rightMonth) {
				transactionArray[k] = left[i];
				i++;
			} else {
				transactionArray[k] = right[j];
				j++;
			}
		} else if (leftYear < rightYear) {
			transactionArray[k] = left[i];
			i++;
		} else {
			transactionArray[k] = right[j];
			j++;
		}

		k++;
	}

	while (i < leftSize) {
		transactionArray[k] = left[i];
		i++;
		k++;
	}

	while (j < rightSize) {
		transactionArray[k] = right[j];
		j++;
		k++;
	}
}
