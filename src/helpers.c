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

void displayContactInfo(customer* customerProfile) {
	printf("\t\tHome Address: %s\n", customerProfile->address);
	printf("\t\tPhone Number: %s\n", customerProfile->phoneNumber);
	printf("\t\tEmail Address: %s\n", customerProfile->email);
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

void stringFormatName(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		/* If Lowercase */
		if (string[i] > 96 && string[i] < 123) {
			if (i == 0) {
				string[i] -= 32;
				continue;
			/* ASCII 39 = ' */
			} else if (string[i-1] == ' ' || string[i-1] == 39) {
				string[i] -= 32;
			} else if (i == 2 && string[0] == 'M' && string[1] == 'c') {
				string[i] -= 32;
			} else if (i == 3 && string[0] == 'M' && string[1] == 'a' && string[2] == 'c') {
				string[i] -= 32;
			}
		/* If Uppercase */
		} else if (string[i] > 64 && string[i] < 91) {
			if (i == 2 && string[0] == 'M' && string[1] == 'c') continue;
			if (i == 3 && string[0] == 'M' && string[1] == 'a' && string[2] == 'c') continue;
			
			if (i != 0 && string[i-1] != ' ' && string[i-1] != 39) {
				string[i] += 32;
			}
		}
	}
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

bool isNAN(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] < 48 || string[i] > 57) {
			if (i == 0 && string[i] == 45) {
				continue;
			}
			return true;
		}
	}
	return false;
}

bool validateIntegerInput(char* string, int* input, int leftBound, int rightBound) {

	if (isNAN(string)) {
		printf("ERROR: Input is not a Number - Please Try Again\n\n");
		return false;
	} else {
		sscanf(string, "%d", input);
		if (*input < leftBound || *input > rightBound) {
			printf("ERROR: Input is not in the range of %d-%d - Please Try Again\n\n", leftBound, rightBound);
			return false;
		}
	}
	return true;
}
