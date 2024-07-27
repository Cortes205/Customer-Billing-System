customerManager: main.o openData.o freeData.o editCustomer.o createTransaction.o editTransaction.o hashAddCustomer.o hashSearchCustomer.o hashAddTransaction.o hashSearchTransaction.o displayCustomers.o displayTransactions.o sortLinkedList.o helpers.o
	gcc -std=c99 -Wall objectFiles/main.o objectFiles/openData.o objectFiles/freeData.o objectFiles/editCustomer.o objectFiles/createTransaction.o objectFiles/editTransaction.o objectFiles/hashAddCustomer.o objectFiles/hashSearchCustomer.o objectFiles/hashAddTransaction.o objectFiles/hashSearchTransaction.o objectFiles/displayCustomers.o objectFiles/displayTransactions.o objectFiles/sortLinkedList.o objectFiles/helpers.o -o bin/customerManager

main.o: src/main.c include/header.h
	gcc -std=c99 -Wall -c src/main.c -o objectFiles/main.o

openData.o: src/openData.c include/header.h
	gcc -std=c99 -Wall -c src/openData.c -o objectFiles/openData.o

freeData.o: src/freeData.c include/header.h
	gcc -std=c99 -Wall -c src/freeData.c -o objectFiles/freeData.o

editCustomer.o: src/editCustomer.c include/header.h
	gcc -std=c99 -Wall -c src/editCustomer.c -o objectFiles/editCustomer.o

createTransaction.o: src/createTransaction.c include/header.h
	gcc -std=c99 -Wall -c src/createTransaction.c -o objectFiles/createTransaction.o

editTransaction.o: src/editTransaction.c include/header.h
	gcc -std=c99 -Wall -c src/editTransaction.c -o objectFiles/editTransaction.o

hashAddCustomer.o: src/hashAddCustomer.c include/header.h
	gcc -std=c99 -Wall -c src/hashAddCustomer.c -o objectFiles/hashAddCustomer.o

hashSearchCustomer.o: src/hashSearchCustomer.c include/header.h
	gcc -std=c99 -Wall -c src/hashSearchCustomer.c -o objectFiles/hashSearchCustomer.o

hashAddTransaction.o: src/hashAddTransaction.c include/header.h
	gcc -std=c99 -Wall -c src/hashAddTransaction.c -o objectFiles/hashAddTransaction.o

hashSearchTransaction.o: src/hashSearchTransaction.c include/header.h
	gcc -std=c99 -Wall -c src/hashSearchTransaction.c -o objectFiles/hashSearchTransaction.o

displayCustomers.o: src/displayCustomers.c include/header.h
	gcc -std=c99 -Wall -c src/displayCustomers.c -o objectFiles/displayCustomers.o

displayTransactions.o: src/displayTransactions.c include/header.h
	gcc -std=c99 -Wall -c src/displayTransactions.c -o objectFiles/displayTransactions.o

sortLinkedList.o: src/sortLinkedList.c include/header.h
	gcc -std=c99 -Wall -c src/sortLinkedList.c -o objectFiles/sortLinkedList.o

helpers.o: src/helpers.c include/header.h
	gcc -std=c99 -Wall -c src/helpers.c -o objectFiles/helpers.o

clean:
	rm objectFiles/*.o bin/customerManager
