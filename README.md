# Customer Billing System
Interactive command line interface application used
to manage customer profiles and transactions

******DISCLAIMER***

This project has not yet been fully developed but has been
put onto Github to track progress and view older versions.

Current Goals:

* Bring Functionality to the menu and all of its steps

## Setup

### Project Folder
Open your computer's terminal and cd to a directory of your choice.

Ensure [git](https://git-scm.com/) is installed on your system, then clone this repository using:

```sh
git clone https://github.com/Cortes205/Customer-Billing-System
```

or you can download it manually as a zipfile.

## Usage

### Execute
Open the terminal in the program's directory

Ensure you have the following:
* A C compiler
* Make tools

To run this program, use the following commands:

```sh
make
```

```sh
./bin/customerManager
```

The first command will compile all the files together, and
the second command will run the program in your terminal

### Runtime
******To be written once the program is fully functional***


## About This Project
This is a project suggestion that I saw online; however,
I wanted to do it in my own way. I recently began learning
about HashMaps and wanted to find a way to implement them into this project.
However, storing customers and transactions in HashMaps only is not the best
if for example: one would like to know all the transactions that belong to an
arbitrary customer. Therefore, I have not only stored the data in HashMaps;
I created a LinkedList within each customer profile. The HashMaps allow the
user to look up a customer name or transaction id number in O(1) time complexity, and
the LinkedLists allow the user to access all transactions specific to a customer.

This project is good practice before my next semester where I learn more about
Data Structures & Algorithms. I am working ahead by learning about HashMaps and
refining my skills in C by Merge Sorting words in a LinkedList, managing lots of pointers, files, and memory!

[Linkedin](https://www.linkedin.com/in/cortes205/)
