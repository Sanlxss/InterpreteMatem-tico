#include <stdio.h>
#include <stdlib.h>
#include "gestorErrores.h"

FILE *fErrores;

//Función que abre el fichero de errores
void inicializarGestorErrores(){
    fErrores= fopen("ficheroErrores.log", "a");
    if(fErrores==NULL){
        printf("ERRO al abrir/crear el fichero de errores\n");
        EXIT_FAILURE;
    }
    fprintf(fErrores, "-------------INICIO EJECUCION-------------\n\n");
}

//Función que escribe errores en el fichero de errores.
void nuevoError(int codigo, int linea){
    if(fErrores){
        //En función del codigo escribimos un mensaje de error
        switch(codigo){
            case 0: //Error-lexico-> Numero Mal formado.
                fprintf(fErrores, "Error LEXICO: Numero mal formado en la linea %d\n", linea);
                printf("Error LEXICO: Numero mal formado en la linea %d\n", linea);
                break;
            case 1: //Error al abrir el fichero de lectura
                fprintf(fErrores, "Error al abrir el fichero que se quiere analizar\n");
                printf("Error al abrir el fichero que se quiere analizar\n");
                break;
            case 2:
                fprintf(fErrores, "ERROR al abrir el fichero que se quiere analizar: Se ha alcanzado el numero maximo de ficheros que se pueden abrir\n");
                printf("ERROR al abrir el fichero que se quiere analizar: Se ha alcanzado el numero maximo de ficheros que se pueden abrir\n");
                break;
            case 3:
                fprintf(fErrores, "Error SINTACTICO: Error en el analizador sintáctico\n");
                printf("Error SINTACTICO: Error en el analizador sintáctico\n");
                break;
        }
    }
}

//Función que cierra el fichero de errores
void finalizarGestorErrores(){
    fprintf(fErrores, "-------------FIN EJECUCION-------------\n\n");
    fclose(fErrores);
    fErrores=NULL;
}
