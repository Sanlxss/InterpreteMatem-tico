#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "definiciones.h"
#include "opciones.h"
#include "estructuraAlmacenamiento.h"

#define MAX_LENGTH 100
#define NUM_STRINGS 11


abb tablaSimbolos;

void imprimirContenidoTabla();
void imprimirWorkspace();
void funcionClear();

/*
    Función para insertar las funciones matemáticas en la tabla de simbolos.
*/
void _insertarFunciones(){
    insertar_FN(&tablaSimbolos,"sqrt", sqrt);
    insertar_FN(&tablaSimbolos,"^", pow);
    insertar_FN(&tablaSimbolos,"sin", sin);
    insertar_FN(&tablaSimbolos,"cos", cos);
    insertar_FN(&tablaSimbolos,"tan", tan);
    insertar_FN(&tablaSimbolos,"asin", asin);
    insertar_FN(&tablaSimbolos,"acos", acos);
    insertar_FN(&tablaSimbolos,"atan", atan);
    insertar_FN(&tablaSimbolos,"log", log10);
    insertar_FN(&tablaSimbolos,"ln", log);
    insertar_FN(&tablaSimbolos,"exp", exp);
}

void _insertarComandos(){
    insertar_CM(&tablaSimbolos,"help", (void*)ayuda);
    insertar_CM(&tablaSimbolos,"echo on",(void*)imprimirPantalla);
    insertar_CM(&tablaSimbolos,"echo off",(void*)noImprimirPantalla);
    insertar_CM(&tablaSimbolos,"workspace", (void*)imprimirWorkspace);
    insertar_CM(&tablaSimbolos,"verTabla", (void*)imprimirContenidoTabla);
    insertar_CM(&tablaSimbolos,"quit", (void*)salirCalc);
    insertar_CM(&tablaSimbolos,"LOAD", (void*)leerFichero);
    insertar_CM(&tablaSimbolos,"clear", (void*)funcionClear);

}


/*
    Función para inicializar la tabla de simbolos.
*/
void inicializarTabla(){
    tipoelem info;
    
    info.lexema=NULL; //inizializamos el lexema

    /*CREAMOS LA TABLA*/
    crear(&tablaSimbolos);

    /*METEMOS LAS FUNCIONES*/
    _insertarFunciones();

    /*METEMOS LOS COMANDOS*/
    _insertarComandos();

    char constantes [2][MAX_LENGTH] = {"pi", "e"};
    double valores[] = {3.14159265359, 2.71828182845};

    //Para cada elemento de los que pusimos arriba los introducimos en la tabla de simbolos.
    for(int i=0; i<2;i++){
        info.lexema = (char*)malloc(strlen(constantes[i])*sizeof (char)+1);
        memset(info.lexema,'\0',strlen(constantes[i])+1);
        strcpy(info.lexema,constantes[i]);
        info.cuerpo.valor = valores[i];
        insertar_CONST(&tablaSimbolos, info);
        free(info.lexema); //liberamos memoria
        info.lexema=NULL;
    }
}


/*
    Funciones para insertar o buscar Identificadores (VARIABLES) en la tabla de simnbolos
*/
double buscar_Variables(char *lex){
    double v;
    tipoelem info;
    info.lexema = (char*)malloc(strlen(lex)*sizeof (char)+1);
    memset(info.lexema,'\0',strlen(lex)+1);
    strncpy(info.lexema,lex,strlen(lex));
    v=buscar_ID(tablaSimbolos, info);
    free(info.lexema); //liberamos memoria
    info.lexema=NULL;
    return v;
}
void insertar_Variables(char *lex, double valor){
    tipoelem info;
    info.lexema = (char*)malloc(strlen(lex)*sizeof (char)+1);
    memset(info.lexema,'\0',strlen(lex)+1);
    strncpy(info.lexema,lex,strlen(lex));
    info.cuerpo.valor=valor;
    insertar_ID(&tablaSimbolos, info);
    free(info.lexema); //liberamos memoria
    info.lexema=NULL;
}


/*
  Función que devuelve 0 si existe un elemento en la tabla de simbolos
  Devuelve 1 si NO exitse

  Las clasese son:
 -ID
 -CONST
 -FUNC
 */
int existeElem(char *lex, int clase){
    return existe(tablaSimbolos, lex, clase);
}

/*
 Funciones para insertar y buscar Constantes en la tabla de simnbolos
*/
double buscar_Constantes(char *lex){
    double v;
    tipoelem info;
    info.lexema = (char*)malloc(strlen(lex)*sizeof (char)+1);
    memset(info.lexema,'\0',strlen(lex)+1);
    strncpy(info.lexema,lex,strlen(lex));
    v= buscar_CONST(tablaSimbolos, info);
    free(info.lexema); //liberamos memoria
    info.lexema=NULL;
    return v;

}

/*
 Función para imprimrir todo el contenido de la tabla de simbolos
*/
void imprimirContenidoTabla(){
    imprimirABB(tablaSimbolos);
}


/*
 Función para imprimrir el workspace (VARIABLES)
*/
void imprimirWorkspace(){
    imprimirVariables(tablaSimbolos);
}


/*
 Función para restaurar el workspace
*/
void funcionClear(){
    destruir(&tablaSimbolos);
    inicializarTabla();
    system("clear");
}

/*
 Función para borrar la tabla de simbolos
*/
void borrarTabla(){
    destruir(&tablaSimbolos);
    printf("\t\t---TABLA BORRADA--\n");

}


/*
 Funciones para devolver operaciones matematicas
*/
cuerpoElem encontrarFuncion(char *f){
    return buscarFuncion(tablaSimbolos, f);
}



/*
    Funcion para buscar el comando en la tabla de simbolos
*/
cuerpoElem encontrarComando(char *f){
    return buscarCom(tablaSimbolos, f);
}