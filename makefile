customerManager: main.o openData.o freeData.o hashAddCustomer.o helpers.o
	gcc -std=c99 -Wall objectFiles/main.o objectFiles/openData.o objectFiles/freeData.o objectFiles/hashAddCustomer.o objectFiles/helpers.o -o bin/customerManager

main.o: src/main.c include/header.h
	gcc -std=c99 -Wall -c src/main.c -o objectFiles/main.o

openData.o: src/openData.c include/header.h
	gcc -std=c99 -Wall -c src/openData.c -o objectFiles/openData.o

freeData.o: src/freeData.c include/header.h
	gcc -std=c99 -Wall -c src/freeData.c -o objectFiles/freeData.o

hashAddCustomer.o: src/hashAddCustomer.c include/header.h
	gcc -std=c99 -Wall -c src/hashAddCustomer.c -o objectFiles/hashAddCustomer.o

helpers.o: src/helpers.c include/header.h
	gcc -std=c99 -Wall -c src/helpers.c -o objectFiles/helpers.o

clean:
	rm objectFiles/*.o bin/customerManager
