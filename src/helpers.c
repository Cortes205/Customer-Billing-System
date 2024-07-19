#include "../include/header.h"

int sumDigits(int num) {
	if (num < 0) return sumDigits(num * -1);
	if (num < 10) return num;
	return (num % 10) + sumDigits(num / 10);
}

unsigned long int getCustomerHashIndex(char fname[NAME_MAXLEN], char lname[NAME_MAXLEN]) {
	unsigned long int index = 0;
	for (int i = 0; i < strlen(fname); i++) {
		index += fname[i];
		index *= fname[i];
	}

	for (int i = 0; i < strlen(lname); i++) {
		index += lname[i];
		index *= lname[i];
	}

	index %= HASH_SIZE;
	return index;
}
