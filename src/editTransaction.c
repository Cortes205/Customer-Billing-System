#include "../include/header.h"

void editTransaction(transaction** transactionMap, customer* customerProfile) {
	transaction* transactionInfo = NULL;

	bool valid = false;
	char userInput[300] = "";
	int option = 0;

    while (transactionInfo == NULL) {
        valid = false;
		strcpy(userInput, "");
		option = 0;
        while (!valid) {
            printf("Input '-1' to Go Back\n");
            printf("Enter the Transaction ID: ");

            fgets(userInput, 300, stdin);
            userInput[strlen(userInput)-1] = '\0';

            if (strcmp(userInput, "-1") == 0) {
                return;
            }

            valid = validateIntegerInput(userInput, &option, 100000, 999999);
        }

        unsigned long int index = getTransactionHashIndex(option);
        transactionInfo = hashSearchTransaction(transactionMap, option, index);

        if (transactionInfo == NULL) {
			printf("ERROR: This Transaction Does Not Exist - Please Try Again\n\n");
        } else if (transactionInfo->payor != customerProfile) {
			printf("ERROR: This Transaction Does Not Belong to %s %s - Please Try Again\n\n", customerProfile->fname, customerProfile->lname);
			transactionInfo = NULL;
        }
    }

	bool editMode = true;
	bool hashChange = false;
	while (editMode) {

		printf("\nTransaction Info Editing:\n\n");
		printf("\t\tPayor: %s %s\n", transactionInfo->payor->fname, transactionInfo->payor->lname);
		displayTransactionInfo(transactionInfo);

		printf("\n\t1. Change Transaction ID\n");
		printf("\t2. Change Service Date\n");
		printf("\t3. Change Service Description\n");
		printf("\t4. Change Total\n");
		printf("\t5. Change Amount Paid\n");
		printf("\t6. Change Amount Owing\n");
		printf("\t7. Change Due Date\n");
		printf("\t8. Change Status\n");
		printf("\t9. Save Changes & Go Back\n");
		printf("\t10. Discard Changes & Go Back\n\n");

		valid = false;
		strcpy(userInput, "");
		option = 0;
		while (!valid) {
			printf("Enter an Option: ");

			fgets(userInput, 300, stdin);
			userInput[strlen(userInput)-1] = '\0';

			valid = validateIntegerInput(userInput, &option, 1, 10);
		}

		bool saveAll = false;
		switch (option) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				saveAll = true;
			case 10:
				editMode = false;
				break;
		}

		if (saveAll) {

		} else {

		}

	}
}
