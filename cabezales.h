#include <iostream>
#include <stdio.h>


typedef struct {
	int id;
	char title[250];
	char author[250];
	char edition[10];
} BookData;


typedef struct nodo_list {
	BookData book; 
	nodo_list*sig;
} nodo;

typedef nodo * bookList;

BookData inputBook();

void createID();

int readID();

void createFile(BookData bookData);

BookData readFile (int id);

void editFile (int id);

void removeFile(int id);

void menu();





