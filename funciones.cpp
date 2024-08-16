#include <iostream>
#include <stdio.h>
#include <string.h>
#include "cabezales.h"
#define BOOKS_DIR "./Libros/"

////////////////////////////////////////////////////////////////////
//                          Crear Libros                          //
///////////////////////////////////////////////////////////////////

BookData inputBook() {
	BookData bookData{};
	printf("Escribe el titulo del libro: ");
	scanf("%250[^\n]", bookData.title);
	getchar(); // Descarta el salto de linea
	
	char* author[250] = { 0 };
	printf("Escribe el autor del libro: ");
	scanf("%250[^\n]", bookData.author);
	getchar();
	int edition{};
	printf("Escribe el año de la Edicion: ");
	scanf("%d", &edition);
	snprintf(bookData.edition, sizeof bookData.edition, "%d", edition); // Pasa de un entero a una string 
	
	
	return bookData;
	
}

// Creacion de archivo que guarda las ID para que no se reseteen
void createID(int id){
	char ids[256];
	FILE* file;
	if (file = fopen("ID.txt", "w")) {
		sprintf(ids, "%d", id);
		fputs(ids, file);
		fclose(file);
	}
	else {
		printf("Error creando el archivo");
	}
}

	
int readID() {
	FILE* file;
	char ids[256];
	if (file = fopen("ID.txt", "r")) {
		fgets(ids, sizeof ids, file);
		int id = strtol(ids, nullptr, 10); // Agarra el numero de ID, y descarta los espacios de caracteres vacíos restantes
		fclose(file);
		return id;
	}
	else {
		printf("Error al leer archivo de ID's");
	}
	return 0;
}

// Crea el archivo segun el titulo, por eso se usa strcpy asi agrega el nombre del titulo al archivo
// A su vez agrega el "Titulo" dentro del archivo escribiendo
// BOOKS_DIR es la direccion de los libros

void createFile(BookData bookData) {
	char ids[256];
	sprintf(ids, "%d", bookData.id);
	char filename[300]{ 0 };
	strcpy(filename, BOOKS_DIR); // Entra a ./Libros/
	strcat(filename, ids); // Concatena el ID del archivo nuevo ./Libros/id
	strcat(filename, ".txt"); // Concatena la extension del archivo ./Libros/id.txt
	
	char contents[8000] = { 0 };
	strcat(contents, ids);
	strcat(contents, "\n");
	strcat(contents, bookData.title);
	strcat(contents, "\n");
	strcat(contents, bookData.author);
	strcat(contents, "\n");
	strcat(contents, bookData.edition);
	
	FILE* file;
	if (file = fopen(filename, "w")) {
		fputs(contents, file);
		fclose(file);
	}
	else {
		printf("Error creando el archivo");
	}
}


BookData readFile (int id) {
    char filename[300] = BOOKS_DIR; // filename = "./Libros/"
	char ids[256];
	snprintf(ids, sizeof ids, "%d", id); // id pase a string
	strcat(filename, ids); // filename = "./Libros/id"
	strcat(filename, ".txt"); // filename = "./Libros/id.txt"
	// Titulo = Al valor que le pase como titulo
	BookData bookData;
	FILE* file;
	if (file = fopen (filename, "r")) {
		fgets(ids, sizeof ids, file);
		bookData.id = strtol(ids, nullptr, 10); // Convierto ids a entero en base 10
		fgets(bookData.title, sizeof bookData.title, file);
		fgets(bookData.author, sizeof bookData.author, file);
		fgets(bookData.edition, sizeof bookData.edition, file);
		// fgets coloca un salto de linea automatico, strcpy + strtok lo quita del string!
		strcpy(bookData.title, strtok(bookData.title, "\n")); //strtok divide el string a partir del caracter que pasas como parametro y devuelve la primer mitad
		strcpy(bookData.author, strtok(bookData.author, "\n"));
		strcpy(bookData.edition, strtok(bookData.edition, "\n"));
		fclose(file);
	} else {
		//printf("Error leyendo el archivo");
		bookData.id = -1; // No existe el archivo
	}
	return bookData;
}

void editFile (int id) {
	printf(" ID: %d \n", id);
	BookData lector = readFile(id);
	printf(" Titulo: %s \n Autor: %s \n Edicion: %s \n", lector.title, lector.author, lector.edition);
	BookData modificaciones = inputBook();
	modificaciones.id = lector.id;
	// removeFile(lector.title);
	createFile(modificaciones);
}

void createList (bookList &list) {
	list = NULL;
	int idTop = readID();
	int i;
	
	for (i=0;i<=idTop;i++) {
		BookData reader = readFile(i);
		//printf("%d", reader.id);
		if (reader.id != -1) {
			bookList aux;
			aux = new nodo;
			aux -> book = reader;
			aux -> sig = list;
			list = aux;
		}
	}
}

void printList (bookList list) {
	
	while (list != NULL) {
		printf("%d - %s[%s] - [%s] \n", list->book.id, list->book.title, list->book.edition, list->book.author);
		list = list -> sig;
	}
}

// ID Archivo counter

void removeFile (int id) {
	char ids[256];
	char filename[300] = BOOKS_DIR; // filename = "./Libros/"
	snprintf(ids, sizeof ids, "%d", id); // id pase a string
	strcat(filename, ids); // filename = "./Libros/id"
	strcat(filename, ".txt"); // filename = "./Libros/id.txt"
	remove(filename);
}


////////////////////////////////////////////////////////////////////
//                           MENU                                 //
///////////////////////////////////////////////////////////////////

void menu () {
	int opc;
	BookData bookData;
	bookList list = new nodo;
	createList(list);
	do {
		printf("\n******************************** \n Seleccione una opcion: \n 1- Agregar Libro \n 2- Editar Libro \n 3- Leer Archivo \n 4- Eliminar Archivo \n 5- Ver lista de Libros \n 0- Salir \n******************************** \n");
		scanf("%d", &opc);
		getchar();
		printf("ID actual: %d \n", readID());
		switch (opc){
			case 0:
				printf("Cerrar programa");
				break;
			case 1:
				{
				BookData bookData{ inputBook() };
				bookData.id = readID() + 1;
				createID(bookData.id);
				createFile(bookData);
				createList(list);
				break;
			}
			case 2:
				{
				int id;
				printf("Elige el titulo del archivo que quieras modificar: ");
				scanf("%d", &id);
				getchar();
				printf("\n");
				editFile(id);	
				createList(list);
				//BookData lector = readFile(bookData.title);
				break;
				}
			case 3:
				{
				int id;
				printf("Elige el ID del archivo que quieras leer: ");
				scanf("%d", &id);
				getchar();
				BookData lector = readFile(id);
				printf("%s[%s] - [%s] \n \n", lector.title, lector.edition, lector.author);
				break;
				}
			case 4: {
					int id;
					printf("Elige el ID del archivo que quieras eliminar: ");
					scanf("%d", &id);
					getchar();
					removeFile(id);
					createList(list);
					break;
				}
			case 5: {
				printList(list);
				break;
			}
			default: printf("Usted no ha elegido un numero valido en el menu \n");
        }
		system("PAUSE");
		system("cls");
	} while (opc != 0);
}
