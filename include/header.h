#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct transactionNode {
	int id;
	struct transactionNode* next;
} transactionNode;

#define NAME_MAXLEN 25
#define ADDRESS_MAXLEN 100
#define PHONE_MAXLEN 20
#define EMAIL_MAXLEN 100

typedef struct customer {
	char fname[NAME_MAXLEN];
	char lname[NAME_MAXLEN];
	char address[ADDRESS_MAXLEN];
	char phoneNumber[PHONE_MAXLEN];
	char email[EMAIL_MAXLEN];
	transactionNode* head; // Linked list of transactions belonging to a customer
	transactionNode* tail; // Tail of transactions to make adding quicker
	struct customer* hashNext; // Customers in the same index spot (hash collision handling)
	struct customer* linkedNext; // Linked list of all customers (makes freeing easier)
} customer;

#define SERVICE_MAXLEN 125
#define DATE_MAXLEN 10
#define STATUS_MAXLEN 25

typedef struct transaction {
	int id;
	char serviceDate[DATE_MAXLEN];
	char service[SERVICE_MAXLEN];
	double totalAmount;
	double paidAmount;
	double owingAmount;
	char dueDate[DATE_MAXLEN];
	char status[STATUS_MAXLEN];
	customer* payor; // Customer that is the payor of a given transaction
	struct transaction* hashNext; // Transactions in the same index spot (hash collision handling)
} transaction;

#define FILE_NAME_MAXLEN 75
#define HASH_SIZE 1000

bool openData(char fileName[FILE_NAME_MAXLEN], customer** head, customer** tail, customer** customerMap, transaction** transactionMap);

void sortByLastName(customer** head, customer** tail);
void displayCustomers(customer* head);

void createCustomer(customer** customerMap, customer** tail);
void editCustomer(customer* customerProfile);

void createTransaction(transaction** transactionMap, customer* payor);
void editTransaction(transaction* transactionInfo);

void freeData(customer** head, transaction** transactionMap);

void hashAddTransaction(transaction** transactionMap, transaction* addition, int storageIndex);
transaction* hashSearchTransaction(transaction** transactionMap, int id, int storageIndex);

void hashAddCustomer(customer** customerMap, customer* addition, unsigned long int storageIndex);
customer* hashSearchCustomer(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], int storageIndex);


// Helpers
int sumDigits(int num);
unsigned long int getCustomerHashIndex(char fname[NAME_MAXLEN], char lname[NAME_MAXLEN]);
unsigned long int getTransactionHashIndex(int id);
void stringToLowercase(char* string);
void stringUppercaseAfterSpace(char* string);
void stringUnspace(char* string);
void stringFormatPhone(char* string);
void stringFormatName(char* string);
void stringSpaceOut(char* string);