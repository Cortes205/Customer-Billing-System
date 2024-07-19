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

unsigned long int getTransactionHashIndex(int id) {
	unsigned long int index = 0;
	index = id * pow(sumDigits(id), 2);
	index %= HASH_SIZE;
	return index;
}

void stringToLowercase(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] > 64 && string[i] < 91) {
			string[i] += 32;
		}
	}
}

void stringUppercaseAfterSpace(char* string) {
	for (int i = 1; i < strlen(string); i++) {
		if (string[i-1] == 32) {
			if (string[i] > 96 && string[i] < 123) {
				string[i] -= 32;
			}
		}
	}
}

void stringUnspace(char* string) {
	char temp[500] = "";
	int j = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] != 32) {
			temp[j] = string[i];
			j++;
		}
	}
	temp[strlen(temp)] = '\0';
	strcpy(string, temp);
}

void stringFormatPhone(char* string) {
	char temp[25] = "(";

	char areaCode[4] = "";
	for (int i = 0; i < 3; i++) {
		areaCode[i] = string[i];
	}
	strcat(temp, areaCode);
	strcat(temp, ") ");

	char prefix[4] = "";
	int j = 0;
	for (int i = 3; i < 6; i++) {
		prefix[j] = string[i];
		j++;
	}
	strcat(temp, prefix);
	strcat(temp, "-");

	char lastFour[5] = "";
	j = 0;
	for (int i = 6; i < 10; i++) {
		lastFour[j] = string[i];
		j++;
	}
	strcat(temp, lastFour);

	strcpy(string, temp);
}

void stringSpaceOut(char* string) {
	char temp[500] = "";
	int j = 0;
    for (int i = 0; i < strlen(string); i++) {
		if (string[i] > 64 && string[i] < 91 && i != 0) {
			temp[j] = 32;
			j++;
		}
		temp[j] = string[i];
		j++;
	}

	strcpy(string, temp);
}
