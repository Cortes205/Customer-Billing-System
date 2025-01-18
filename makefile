OBJ = createCustomer.o createTransaction.o displayByStatus.o displayCustomers.o displayTransactions.o editCustomer.o editTransaction.o freeData.o hashAddCustomer.o hashAddTransaction.o hashSearchCustomer.o hashSearchTransaction.o helpers.o main.o openData.o searchArray.o sortArray.o sortLinkedList.o
OUT = customerManager
HEADS = include/header.h
CFLAGS = gcc -std=c99 -Wall

all: ${OUT}

${OUT}: ${OBJ}
	${CFLAGS} ${OBJ} -o bin/${OUT}

createCustomer.o: src/createCustomer.c ${HEADS}
	${CFLAGS} -c src/createCustomer.c

createTransaction.o: src/createTransaction.c ${HEADS}
	${CFLAGS} -c src/createTransaction.c

displayByStatus.o: src/displayByStatus.c ${HEADS}
	${CFLAGS} -c src/displayByStatus.c

displayCustomers.o: src/displayCustomers.c ${HEADS}
	${CFLAGS} -c src/displayCustomers.c

displayTransactions.o: src/displayTransactions.c ${HEADS}
	${CFLAGS} -c src/displayTransactions.c

editCustomer.o: src/editCustomer.c ${HEADS}
	${CFLAGS} -c src/editCustomer.c

editTransaction.o: src/editTransaction.c ${HEADS}
	${CFLAGS} -c src/editTransaction.c

freeData.o: src/freeData.c ${HEADS}
	${CFLAGS} -c src/freeData.c

hashAddCustomer.o: src/hashAddCustomer.c ${HEADS}
	${CFLAGS} -c src/hashAddCustomer.c

hashAddTransaction.o: src/hashAddTransaction.c ${HEADS}
	${CFLAGS} -c src/hashAddTransaction.c

hashSearchCustomer.o: src/hashSearchCustomer.c ${HEADS}
	${CFLAGS} -c src/hashSearchCustomer.c

hashSearchTransaction.o: src/hashSearchTransaction.c ${HEADS}
	${CFLAGS} -c src/hashSearchTransaction.c

helpers.o: src/helpers.c ${HEADS}
	${CFLAGS} -c src/helpers.c

main.o: src/main.c ${HEADS}
	${CFLAGS} -c src/main.c

openData.o: src/openData.c ${HEADS}
	${CFLAGS} -c src/openData.c

searchArray.o: src/searchArray.c ${HEADS}
	${CFLAGS} -c src/searchArray.c

sortArray.o: src/sortArray.c ${HEADS}
	${CFLAGS} -c src/sortArray.c

sortLinkedList.o: src/sortLinkedList.c ${HEADS}
	${CFLAGS} -c src/sortLinkedList.c

clean:
	rm *.o bin/${OUT}