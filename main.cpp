#include <iostream>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "funciones.cpp"
using namespace std;

int main(){
	//////////////////////////
	setlocale(LC_ALL, "es_AR.latin-1");
	#ifdef _WIN32
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);  // Para que funcionen las tildes y "Ñ" en los libros
	#endif

    /////////////////////////
	
	menu();
	
	
	return 0;
}


