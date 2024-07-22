#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct transactionNode {
	int id;
	struct transactionNode* next;
} transactionNode;

#define NAME_MAXLEN 30
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
	long int filePosition;
} customer;

#define SERVICE_MAXLEN 125
#define DATE_MAXLEN 15
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
	long int filePosition;
} transaction;

#define FILE_NAME_MAXLEN 90
#define HASH_SIZE 1000

bool openData(char fileName[FILE_NAME_MAXLEN], customer** head, customer** tail, customer** customerMap, transaction** transactionMap);

void sortByLastName(customer** head, customer** tail);
void merge(customer* left, customer* right, customer** head, customer** tail);
customer* middleNode(customer* head);

void displayCustomers(customer* head);

bool displayTransactions(transactionNode* head, transaction** transactionMap);

void createCustomer(customer** customerMap, customer** tail);

void editCustomer(customer* customerProfile, customer** customerMap, transaction** transactionMap);
bool saveChanges(char file[FILE_NAME_MAXLEN], customer** customerMap, customer* customerProfile);
char* formatInfo(customer* customerProfile);
void changeHashPosition(customer** customerMap, char* oldFName, char* oldLName, char* fname, char* lnam, char* phoneNumber);

void createTransaction(transaction** transactionMap, customer* payor);

void editTransaction(transaction* transactionInfo);

void freeData(customer** head, transaction** transactionMap);

void hashAddTransaction(transaction** transactionMap, transaction* addition, int storageIndex);

transaction* hashSearchTransaction(transaction** transactionMap, int id, int storageIndex);

void hashAddCustomer(customer** customerMap, customer* addition, unsigned long int storageIndex);

customer* hashSearchCustomer(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], int storageIndex);
customer* multipleCustomers(customer** customersOfName, int numCustomers);
customer* hashSearchCustomerByPhone(customer** customerMap, char fname[NAME_MAXLEN], char lname[NAME_MAXLEN], char phoneNumber[PHONE_MAXLEN], int storageIndex);


// Helpers
int sumDigits(int num);
unsigned long int getCustomerHashIndex(char fname[NAME_MAXLEN], char lname[NAME_MAXLEN]);
unsigned long int getTransactionHashIndex(int id);
void displayContactInfo(customer* customerProfile);
void stringToLowercase(char* string);
void stringUppercaseAfterSpace(char* string);
void stringUnspace(char* string);
void stringFormatPhone(char* string);
void stringUnformatPhone(char* string);
void stringFormatName(char* string);
void stringSpaceOut(char* string);
bool isNAN(char* string);
bool validateIntegerInput(char* string, int* input, int leftBound, int rightBound);
void createFileName(char* file, char* fname, char* lname, char* phoneNumber);
void fillCustomerInfo(char *info, customer* addition);