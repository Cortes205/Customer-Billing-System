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

void displayTransactionInfo(transaction* transactionInfo) {
	printf("\t\tTransaction ID: %d\n", transactionInfo->id);
	printf("\t\tService Date: %s\n", transactionInfo->serviceDate);
	printf("\t\tService Description: %s\n", transactionInfo->service);
	printf("\t\tTotal Amount: $%.2lf\n", transactionInfo->totalAmount);
	printf("\t\tBalance Paid: $%.2lf\n", transactionInfo->paidAmount);
	printf("\t\tBalance Owing: $%.2lf\n", transactionInfo->owingAmount);
	printf("\t\tDue Date: %s\n", transactionInfo->dueDate);
	printf("\t\tStatus: %s\n", transactionInfo->status);
}

void stringToLowercase(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		/* If uppercase, then shift down */
		if (string[i] > 64 && string[i] < 91) {
			string[i] += 32;
		}
	}
}

void stringToUppercase(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		/* If lowercase, then shift up*/
		if (string[i] > 96 && string[i] < 123) {
			string[i] -= 32;
		}
	}
}

void stringUppercaseAfterSpace(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		if (i == 0) {
			/* If lowercase at the start, then shift up */
			if (string[i] > 96 && string[i] < 123) {
				string[i] -= 32;
			}
		/* If there is a space before the ith letter */
		} else if (string[i-1] == 32) {
			/* If lowercase, then shfit up */
			if (string[i] > 96 && string[i] < 123) {
				string[i] -= 32;
			}
		}
	}
}

void stringUnspace(char* string) {
	char temp[500] = "";
	int j = 0;
	/* Copy letter by letter but skip spaces */
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] != 32) {
			temp[j] = string[i];
			j++;
		}
	}
	temp[strlen(temp)] = '\0';

	/* Overwrite old string - avoiding storage on the heap */
	strcpy(string, temp);
}

void stringFormatPhone(char* string) {
	char temp[PHONE_MAXLEN] = "(";

	char areaCode[4] = "";
	for (int i = 0; i < 3 && i < strlen(string); i++) {
		areaCode[i] = string[i];
	}
	strcat(temp, areaCode);
	strcat(temp, ") ");

	char prefix[4] = "";
	int j = 0;
	for (int i = 3; i < 6 && i < strlen(string); i++) {
		prefix[j] = string[i];
		j++;
	}
	strcat(temp, prefix);
	strcat(temp, "-");

	char lastFour[5] = "";
	j = 0;
	for (int i = 6; i < 10 && i < strlen(string); i++) {
		lastFour[j] = string[i];
		j++;
	}
	strcat(temp, lastFour);

	strcpy(string, temp);
}

/* Good function to also get rid of non-digit input */
void stringUnformatPhone(char* string) {
	char temp[PHONE_MAXLEN] = "";
	int j = 0;
	for (int i = 0; i < strlen(string); i++) {
		/* If the ith char is a digit, copy it */
		if (string[i] > 47 && string[i] < 58) {
			temp[j] = string[i];
			j++;
		}
	}
	strcpy(string, temp);
}

void stringFormatName(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		/* If Lowercase */
		if (string[i] > 96 && string[i] < 123) {
			if (i == 0) {
				string[i] -= 32;
				continue;
			/* ASCII 39 = ' - Formats names like O'Callaghan */
			} else if (string[i-1] == ' ' || string[i-1] == 39) {
				string[i] -= 32;
			/* Formats names like McPhee*/
			} else if (i == 2 && string[0] == 'M' && string[1] == 'c') {
				string[i] -= 32;
			/* Formats names like MacTavish */
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

/* Make spaces before capital letters */
void stringSpaceOut(char* string) {
	char temp[500] = "";
	int j = 0;
    for (int i = 0; i < strlen(string); i++) {
		/* If uppercase and not beginning, insert space */
		if (string[i] > 64 && string[i] < 91 && i != 0) {
			temp[j] = 32;
			j++;
		}
		temp[j] = string[i];
		j++;
	}

	strcpy(string, temp);
}

void stringReplace(char* string, char target, char replace) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == target) {
			string[i] = replace;
		}
	}
}

void stringUnformatDate(char* string, int* month, int* day, int* year) {
	stringReplace(string, '/', ' ');
	sscanf(string, "%d%d%d", month, day, year);
	stringReplace(string, ' ', '/');
}

bool isNAN(char* string, bool isDouble) {
	bool hasDecimal = false;
	for (int i = 0; i < strlen(string); i++) {
		/* If the ith char is something other than a digit */
		if (string[i] < 48 || string[i] > 57) {

			if (i == 0 && string[i] == '-') {
				continue;
			}

			if (isDouble && !hasDecimal && string[i] == '.' && i != 0) {
				hasDecimal = true;
				continue;
			}

			return true;
		}
	}
	return false;
}

bool validateIntegerInput(char* string, int* input, bool bounds, int leftBound, int rightBound) {
	if (isNAN(string, false)) {
		printf("ERROR: Input is not a Number - Please Try Again\n\n");
		return false;
	} else {
		sscanf(string, "%d", input);
		if (bounds && (*input < leftBound || *input > rightBound)) {
			printf("ERROR: Input is not in the range of %d-%d - Please Try Again\n\n", leftBound, rightBound);
			return false;
		}
	}
	return true;
}

bool validateDoubleInput(char* string, double* input, bool bounds, int leftBound, int rightBound) {
	if (isNAN(string, true)) {
		printf("ERROR: Input is not a Number - Please Try Again\n\n");
		return false;
	} else {
		sscanf(string, "%lf", input);
		if (bounds && (*input < leftBound || *input > rightBound)) {
			printf("ERROR: Input is not in the range of %d-%d - Please Try Again\n\n", leftBound, rightBound);
			return false;
		}
	}
	return true;
}

bool validateDateInput(int month, int day, int year) {
	char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year % 4 == 0) days[1] = 29;

	if (month < 0 || month > 12) {
		printf("\nERROR: Month is not in the range of 1-12 - Please Try Again\n\n");
		return false;
	}

	if (day < 1 || day > days[month-1]) {
		printf("\nERROR: Day is not in the range of 1-%d for %s - Please Try Again\n\n", days[month-1], months[month-1]);
		return false;
	}

	if (year < 0) {
		printf("\nERROR: Year is not valid - Please Try Again\n\n");
		return false;
	}

	return true;
}

void createFileName(char* file, char* fname, char* lname, char* phoneNumber) {
	stringUnformatPhone(phoneNumber);
	strcat(file, fname);
	strcat(file, lname);
	strcat(file, phoneNumber);
	strcat(file, ".db");
	stringFormatPhone(phoneNumber);
	stringToLowercase(file);
}

/* Sets up customer node */
void fillCustomerInfo(char *info, customer* newCustomer) {
	sscanf(info, "%s%s%s%s%s", newCustomer->fname, newCustomer->lname, newCustomer->address, newCustomer->phoneNumber, newCustomer->email);

	stringSpaceOut(newCustomer->address);

	stringFormatPhone(newCustomer->phoneNumber);

	newCustomer->head = NULL;
	newCustomer->tail = NULL;
	newCustomer->hashNext = NULL;
	newCustomer->linkedNext = NULL;
}

/* Sets up transaction node */
void fillTransactionInfo(char *info, transaction* newTransaction) {
	sscanf(info, "%d%s%s%lf%lf%lf%s%s", &(newTransaction->id), newTransaction->serviceDate, newTransaction->service, &(newTransaction->totalAmount), &(newTransaction->paidAmount), &(newTransaction->owingAmount), newTransaction->dueDate, newTransaction->status);

	stringSpaceOut(newTransaction->service);

	newTransaction->hashNext = NULL;
}

void takeDateInput(char* userInput, char* prompt, int* month, int* day, int* year) {
	bool valid = false;
	while (!valid) {
		strcpy(userInput, "");
		while (!valid) {
			printf("Enter %s Month: ", prompt);

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, month, false, 0, 0);
		}

		valid = false;
		strcpy(userInput, "");
		while (!valid) {
			printf("Enter %s Day: ", prompt);

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, day, false, 0, 0);
		}

		valid = false;
		strcpy(userInput, "");
		while (!valid) {
			printf("Enter %s Year: ", prompt);

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, year, false, 0, 0);
		}

		valid = validateDateInput(*month, *day, *year);
	}
}

void takeDoubleInput(char* userInput, char* prompt, double *input) {
	bool valid = false;
	strcpy(userInput, "");
	*input = -1;
	while (!valid) {
		printf("%s", prompt);

		fgets(userInput, 300, stdin);
		userInput[strlen(userInput)-1] = '\0';

		valid = validateDoubleInput(userInput, input, false, 0, 0);

		if (*input < 0) {
			printf("ERROR: Amount Cannot be Less Than Zero - Please Try Again\n\n");
			valid = false;
		}
	}
}
