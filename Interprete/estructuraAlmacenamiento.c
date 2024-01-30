#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuraAlmacenamiento.h"
#include "definiciones.h"


/*Estructura de los nodos del arbol*/
struct celda{
    tipoelem info;
    short clase;
    struct celda *izq, *der;
};
/*-------------------------------*/

//FUNCION COMPROBACION VACIO
unsigned es_vacio(abb A) {
    return A == NULL;
}

//FUNCION IMPRIME DATOS DE UN NODO
void leer(abb A) {
    if(A->clase == ID){
        printf("VARIABLE -> %s = %f\n", A->info.lexema, A->info.cuerpo.valor);
    }
    else if(A->clase == FUNC){
        printf("FUNCION -> %s\n", A->info.lexema);
    }
    else if(A->clase == CONST){
        printf("CONSTANTE -> %s = %f\n", A->info.lexema, A->info.cuerpo.valor);
    }
    else if(A->clase == COM){
        printf("COMANDO -> %s\n", A->info.lexema);
    }
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

//FUNCION ORDEN LECTURA ARBOL
void inorden(abb A){
    if(!es_vacio(A)){
        inorden(izq(A));
        leer(A);
        inorden(der(A));
    }
}

//FUNCION ORDEN LECTURA VARIABLES
void variablesInorden(abb A){
    if(!es_vacio(A)){
        variablesInorden(izq(A));

        if(A->clase == ID){
            printf("VARIABLE -> %s = %f\n", A->info.lexema, A->info.cuerpo.valor);
        }
        
        variablesInorden(der(A));
    }
}


/*FUNCIONES PUBLICAS*/
//FUNCION CREACION ARBOL
void crear(abb *A) {
    *A = NULL;
}

//FUNCION DESTRUCCION ARBOL
void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        destruir(&(*A)->der);
        (*A)->izq = NULL;
        (*A)->der = NULL;
        free(((*A)->info.lexema));
        (*A)->info.lexema = NULL;
        free(*A);
        *A = NULL;
    }
}


//FUNCION de BUSQUEDA  --> IDENTIFICADORES
double buscar_ID(abb A, tipoelem E){      
    if(strcmp((A)->info.lexema, E.lexema)==0){
        return (A)->info.cuerpo.valor;
        //Si esta a la izquierda
    }else if(strcmp((A)->info.lexema, E.lexema) < 0){
        return buscar_ID((A)->izq, E);
        //Si estaá a la derecha.
    }else{
        return buscar_ID((A)->der, E);
    }
}

//FUNCION de BUSQUEDA e INSERCION --> IDENTIFICADORES
void insertar_ID(abb *A, tipoelem E){
    //si esta vacio
    if(es_vacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(strlen(E.lexema)*sizeof (char)+1);
        memset((*A)->info.lexema, '\0',strlen(E.lexema)+1); 
        strcpy((*A)->info.lexema, E.lexema);
        (*A)->info.cuerpo.valor =E.cuerpo.valor;
        (*A)->clase = ID;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    }
        //Si lo encuentro        
    else if(strcmp((*A)->info.lexema, E.lexema)==0){
        (*A)->info.cuerpo.valor=E.cuerpo.valor;
        //Si esta a la izquierda
    }else if(strcmp((*A)->info.lexema, E.lexema) < 0){
        return insertar_ID(&(*A)->izq, E);
        //Si estaá a la derecha.
    }else{
        return insertar_ID(&(*A)->der, E);
    }
}

//FUNCION de INSERCION --> FUNCIONES
void insertar_FN(abb *A, char *lexema, double(*funcion)()){
    //si esta vacio
    if(es_vacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(strlen(lexema)*sizeof (char)+1);
        memset((*A)->info.lexema, '\0',strlen(lexema)+1);
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.cuerpo.funcion =funcion;
        (*A)->clase = FUNC;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    }
        //Si lo encuentro
    else if(strcmp((*A)->info.lexema, lexema)==0){
        (*A)->info.cuerpo.funcion=funcion;
    }else if(strcmp((*A)->info.lexema, lexema) < 0){
        return insertar_FN(&(*A)->izq, lexema, funcion);
        //Si estaá a la derecha.
    }else{
        return insertar_FN(&(*A)->der, lexema, funcion);
    }
}


//FUNCION de INSERCION --> FUNCIONES
void insertar_CM(abb *A, char *lexema, double(*funcion)()){
    //si esta vacio
    if(es_vacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(strlen(lexema)*sizeof (char)+1);
        memset((*A)->info.lexema, '\0',strlen(lexema)+1);
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.cuerpo.funcion =funcion;
        (*A)->clase = COM;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    }
        //Si lo encuentro
    else if(strcmp((*A)->info.lexema, lexema)==0){
        (*A)->info.cuerpo.funcion=funcion;
    }else if(strcmp((*A)->info.lexema, lexema) < 0){
        return insertar_CM(&(*A)->izq, lexema, funcion);
        //Si estaá a la derecha.
    }else{
        return insertar_CM(&(*A)->der, lexema, funcion);
    }
}


//FUNCION de BUSQUEDA e INSERCION -->>CONSTANTES
double buscar_CONST(abb A, tipoelem E){
    //Si lo encuentro
    if(strcmp((A)->info.lexema, E.lexema)==0){
        return (A)->info.cuerpo.valor;
        //Si esta a la izquierda
    }else if(strcmp((A)->info.lexema, E.lexema) < 0){
        return buscar_CONST((A)->izq, E);
        //Si estaá a la derecha.
    }else{
        return buscar_CONST((A)->der, E);
    }
}

//FUNCION de BUSQUEDA e INSERCION -->>CONSTANTES
void insertar_CONST(abb *A, tipoelem E){
    //si esta vacio
    if(es_vacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(strlen(E.lexema)*sizeof (char)+1);
        memset((*A)->info.lexema, '\0',strlen(E.lexema)+1); 
        strcpy((*A)->info.lexema, E.lexema);
        (*A)->info.cuerpo.valor =E.cuerpo.valor;
        (*A)->clase = CONST;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    }
        //Si lo encuentro
    else if(strcmp((*A)->info.lexema, E.lexema)==0){
        (*A)->info.cuerpo.valor= E.cuerpo.valor;
        //Si esta a la izquierda
    }else if(strcmp((*A)->info.lexema, E.lexema) < 0){
        return insertar_CONST(&(*A)->izq, E);
        //Si estaá a la derecha.
    }else{
        return insertar_CONST(&(*A)->der, E);
    }
}

//FUNCION PUBLICA IMPRIMIR ARBOL
void imprimirABB(abb A){
    printf("\t\t--TABLA DE SIMBOLOS--\n");
    inorden(A);
    printf("\t\t---------------------\n");
}

void imprimirVariables(abb A){
    printf("\t\t--VARIABLES--\n");
    variablesInorden(A);
    printf("\t\t---------------------\n");
}

int existe(abb A, char *lexema, int clase){
    //si esta vacio
    if(es_vacio(A)){
        return 1;
    }
        //Si lo encuentro
    else if(strcmp((A)->info.lexema, lexema)==0){
        if((A)->clase == clase){
            return 0;
        }
        else{
            return 1;
        }
        //Si esta a la izquierda
    }else if(strcmp((A)->info.lexema, lexema) < 0){
        return existe((A)->izq, lexema, clase);
        //Si estaá a la derecha.
    }else{
        return existe((A)->der, lexema, clase);
    }
}

//Funciones para realizar calculos matematicos
cuerpoElem buscarFuncion(abb A, char *f){
    if(strcmp((A)->info.lexema, f)==0){
        return A->info.cuerpo;   
        //Si esta a la izquierda
    }else if(strcmp((A)->info.lexema, f) < 0){
        return buscarFuncion((A)->izq, f);
        //Si estaá a la derecha.
    }else{
        return buscarFuncion((A)->der, f);
    }
}


//Funcion para devolver la función del comando.
cuerpoElem buscarCom(abb A, char *f){
    if(strcmp((A)->info.lexema, f)==0){
        return A->info.cuerpo;   
        //Si esta a la izquierda
    }else if(strcmp((A)->info.lexema, f) < 0){
        return buscarCom((A)->izq, f);
        //Si estaá a la derecha.
    }else{
        return buscarCom((A)->der, f);
    }
}

