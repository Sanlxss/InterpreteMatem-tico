#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opciones.h"
#include "analizadorSintactico.tab.h"
#include "tablaSimbolos.h"
#include "gestorErrores.h"



int main(int argc, char *argv[]){

    printf("Bienvenido al Interprete Matematico\n");
    printf("\tSi necesita ayuda escriba '-h' en linea de comandos\n");

    //INICIAMOS GESTOR ERRORES
    inicializarGestorErrores();
    //INICIALIZAMOS LA TABLA
    inicializarTabla();
    

    //Comrobamos el tipo de ejcución que desea.
    if(argc == 1){
        printf("Bienvenido ya puede utilizar la calculadaora\n-------------------------------\n");
    }
    else if(argc == 2 && strcmp(argv[1],"-h")==0){
        ayuda();
    }
    else if(argc == 3 && strcmp(argv[1],"-l")==0){
        leerFichero(argv[2]);
    }
    else{
        printf("Argumentos incorrectos, consulte la sección de ayuda utilizando '-h'\n");
        borrarTabla();
        finalizarGestorErrores();
        return 1;
    }

    //REALIZAMOS EL ANALISIS
    yyparse();

    //FINALIZAMOS LA EJECUCION
    printf("\nFINALIZANDO EJECUCION\n");
    borrarTabla();
    finalizarGestorErrores();
    return 0;
}