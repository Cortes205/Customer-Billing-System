#include "../include/header.h"

void createCustomer(customer** customerMap, customer** head, customer** tail) {
	customer* addition = calloc(1, sizeof(customer));

	bool saveInfo = false;
	bool creating = true;
	while (creating) {
		printf("\nCustomer Creation Menu: \n\n");
		bool valid = false;
		while (!valid) {
			printf("Enter First Name: ");

			fgets(addition->fname, NAME_MAXLEN, stdin);
			addition->fname[strlen(addition->fname)-1] = '\0';
			stringFormatName(addition->fname);

			if (hashSearchCustomerByPhone(customerMap, addition->fname, addition->lname, addition->phoneNumber, getCustomerHashIndex(addition->fname, addition->lname))) {
				printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				valid = false;
			} else {
				valid = true;
			}
		}

		valid = false;
		while (!valid) {
			printf("Enter Last Name: ");

			fgets(addition->lname, NAME_MAXLEN, stdin);
			addition->lname[strlen(addition->lname)-1] = '\0';
			stringFormatName(addition->lname);

			if (hashSearchCustomerByPhone(customerMap, addition->fname, addition->lname, addition->phoneNumber, getCustomerHashIndex(addition->fname, addition->lname))) {
				printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				valid = false;
			} else {
				valid = true;
			}
		}

		printf("Enter Address: ");

		fgets(addition->address, ADDRESS_MAXLEN, stdin);
		addition->address[strlen(addition->address)-1] = '\0';


		valid = false;
		while (!valid) {
			printf("Enter Phone Number: ");

			fgets(addition->phoneNumber, PHONE_MAXLEN, stdin);
			addition->phoneNumber[strlen(addition->phoneNumber)-1] = '\0';
			stringUnformatPhone(addition->phoneNumber);
			stringFormatPhone(addition->phoneNumber);

			if (hashSearchCustomerByPhone(customerMap, addition->fname, addition->lname, addition->phoneNumber, getCustomerHashIndex(addition->fname, addition->lname))) {
				printf("\nERROR: A Customer With This Name and Phone Number Already Exists - Please Try Again or Edit The Other Customer First\n\n");
				valid = false;
			} else {
				valid = true;
			}
		}

		printf("Enter Email Address: ");

		fgets(addition->email, NAME_MAXLEN, stdin);
		addition->email[strlen(addition->email)-1] = '\0';


		printf("\n");
		printf("\t\tFirst Name: %s\n", addition->fname);
		printf("\t\tLast Name: %s\n", addition->lname);
		displayContactInfo(addition);
		printf("\n");

		valid = false;
		bool confirming = true;
		char userInput[300] = "";
		while (confirming) {
			printf("Is This Info Correct (Y/N)? ");
			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			/* Confirming = False if input == 'Y' || input == 'N' */
			confirming = yesOrNo(userInput);

			/* But if userInput == 'N' */
			if (strcmp(userInput, "N") == 0) {
				while (!valid) {
					printf("Would You Like to Try Again (Y/N)? ");
					fgets(userInput, 300, stdin);
					userInput[strlen(userInput)-1] = '\0';
					/* Since yesOrNo returns false for a valid option, ! makes it return true */
					valid = !yesOrNo(userInput);
					/* If valid = true, make creating false */
					creating = !valid;
				}

				/* But if userInput == 'Y' then creating = true */
				if (strcmp(userInput, "Y") == 0) {
					creating = true;
				}
			} else if (!confirming) {
				creating = false;
				saveInfo = true;
			}

			printf("\n");
		}
	}

	/* Choose whether or not save or delete new customer */
	if (saveInfo) {
		/* Add new customer to LinkedList */
		if (*head == NULL) {
			*head = addition;
			*tail = addition;
		} else {
			(*tail)->linkedNext = addition;
			*tail = addition;
		}

		addition->head = NULL;
		addition->tail = NULL;

		hashAddCustomer(customerMap, addition, getCustomerHashIndex(addition->fname, addition->lname));

		addition->linkedNext = NULL;

		/* Write customer to file */
		FILE* fptr = fopen("customers.db", "a+");
		if (fptr == NULL) {
			printf("ERROR: File Did Not Open - Please Try Again\n\n");
			free(addition);
			addition = NULL;
			return;
		}

		char *info = formatCustomerInfo(addition);
		fprintf(fptr, "%s\n", info);
		free(info);

		fseek(fptr, 0, SEEK_END);
		addition->filePosition = ftell(fptr);

		fclose(fptr);

		/* Create transaction file for customer */
		char transFile[FILE_NAME_MAXLEN] = "customers/";
		createFileName(transFile, addition->fname, addition->lname, addition->phoneNumber);

		fptr = fopen(transFile, "a+");
		if (fptr != NULL) {
			/* Shouldn't be null, but good to check */
			fclose(fptr);
		}

	} else {
		free(addition);
	}
}
