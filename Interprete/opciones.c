#include "lex.yy.h"
#include "analizadorSintactico.tab.h"


int imprimirP=1; //Variable global para controlar la impresión de pantalla.

/*Funcion para imprimir la ayuda*/
void ayuda(){
    printf("\n\n----------------------------------------------\nEsta es la sección de ayuda:\n");
    printf("####<--ARGUMENTOS DE EJECUCION-->####\n"
    "\t opcion: -h : muestra la sección de ayuda\n"
    "\t opcion -l : carga un fichero\n"

    "\n####<--FUNCIONALIDADES SISTEMA-->####\n"
    "\t'verTabla' -> muestra el contenido de la tabla de simbolos\n"
    "\t'load {nombreFichero}' -> carga un fichero\n"
    "\t'workspace' -> muestra por pantalla el conjunto de variables y su valor en la sesion actual\n"
    "\t'clear' -> permite borrar el espacio de trabajo\n"
    "\t'help' -> mostrar ayuda\n"
    "\t'echo on' -> activar impresion por pantalla\n"
    "\t'echo off' -> desactivar impresion por pantalla\n"
    "\t'quit' -> salir del programa\n"


    "\n-----------FUNCIONES-----------\n"
    "\tsqrt()\n"
    "\t^\n"

    "\tsin()\n"
    "\tcos()\n"
    "\ttan()\n"
    "\tasin()\n"
    "\tacos()\n"
    "\tatan()\n"
    
    "\tlog()\n"
    "\tln()\n"
    
    "\texp\n"

    "\n-----------OPERACIONES-----------\n"
    "\tOperaciones Basicas (+,-,*,/)\n"

    "\n--------CONSTANTES UTILIZADAS----------\n"
    "\tpi = 3.14159265359\n"
    "\te = 2.71828182845\n"

    "\n-------VARIABLES--------\n"
    "Se permite la definicion (nombreVariables= valor) y redefinicion (nombreVariables= variable+funcion) de variables\n");
}

/*Funcion para acceder a la lectura de fichero*/
void leerFichero(char *f){
    leerFich(f);
}

/*Funcion para activar la impresión de pasos por pantalla*/
void imprimirPantalla(){
    printf("\nImpresion de pantalla activada\n");
    imprimirP=1;
}

/*Funcion para desactivar la impresión de pasos por pantalla*/
void noImprimirPantalla(){
    printf("\nImpresion de pantalla desactivada\n");
    imprimirP=0;
}

/*Funcion para salir de la calculadora y finalizar todo*/
void salirCalc(){
    salirLexico();
}