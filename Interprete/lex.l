/*DEFINICIONES*/
%{
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "gestorErrores.h"
#include "analizadorSintactico.tab.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void leerFich(char *f);
void cerrar();
void cerrar_ficheros();
int salirLexico();
%}

%option yylineno
%option noyywrap
%option nounput
%option noinput



/*TIPOS DE SEPARADORES*/
SALTOLINEA \n
SEPARADORES (\t|\r|[ ])+
/*----------------------------------------------------------------------*/

/*CARACTERES ESPECIALES*/
PUNTOCOMA ;
COMA ,
PUNTO \.
/*----------------------------------------------------------------------*/


/*CADENAS DE CARACTERES*/
IDENTIFICADOR [a-zA-Z_][a-zA-Z0-9_]*
/*----------------------------------------------------------------------*/


/*NUMEROS*/
DECIMAL [0-9]

ENTERO [1-9]{DECIMAL}*|0

DOBLE_TIPO_A [1-9]{DECIMAL}*\.[0-9]*
DOBLE_TIPO_B (0)?\.[0-9]+
DOBLE_TIPO_C [0-9]+\.?[0-9]+[eE][+-]?{ENTERO}
DOBLE_TIPO_D [0-9]+[eE][+-]?{ENTERO}
DOBLE_TIPO_E \.[0-9]+[eE][+-]?{ENTERO}
DOBLE {DOBLE_TIPO_A}|{DOBLE_TIPO_B}|{DOBLE_TIPO_C}|{DOBLE_TIPO_D}|{DOBLE_TIPO_E}



NUMEROS {ENTERO}|{DOBLE}
/*----------------------------------------------------------------------*/

/*OPERADORES*/
SUMA "+"
RESTA "-"
MULTIPLICACION "*"
DIVISION "/"
MAYOR ">"
MENOR "<"
PARENTESIS_IZ "("
PARENTESIS_DR ")"
MODULO "%"
ELEVADO "^"


OPERADOR_SIMPLE {SUMA}|{RESTA}|{MULTIPLICACION}|{DIVISION}|{MAYOR}|{MENOR}|{PARENTESIS_IZ}|{PARENTESIS_DR}|{MODULO}|{ELEVADO}|{PUNTO}|{COMA}|{PUNTOCOMA}|"%"

IGUAL =
MENOS_IGUAL -=
MENOS_MENOS --
MAS_IGUAL \+=
MAS_MAS \+\+
POR_IGUAL \*=
DIVIDIDO_IGUAL \/=
MENOR_IGUAL <=
MAYOR_IGUAL >=
DISTINTO !=
IGUAL_IGUAL ==

/*----------------------------------------------------------------------*/

/*ESTRUTURA DEL NOMBRE DE LOS FICHEROS*/
FICHERO ([a-zA-Z_]|[0-9]|-|\.)+
/*----------------------------------------------------------------------*/

/*FLUJO ALTERNATIVO*/
%x LEC
/*----------------------------------------------------------------------*/


%%

"load" {BEGIN(LEC); return(LOAD);} //Cuando lee "load" pasa al estado LEC y fespues devuelve LOAD al analizadorSintactivo



"quit"|"workspace"|"verTabla"|"help"|"clear"|"echo on"|"echo off"    {  yylval.lexema = (char *)malloc(strlen(yytext)*sizeof(char)+1);
                                                                        memset(yylval.lexema, '\0', strlen(yytext)+1);
                                                                        strncpy(yylval.lexema,yytext,strlen(yytext));   //Copiamos el nombre del identificador en lexema
                                                                        return(COMANDO_BASICO);  //Devolvemos el IDENTIFICADOR
                                                                    }

<LEC>{FICHERO} {    yylval.lexema = (char *)malloc(strlen(yytext)*sizeof(char)+1);
                    memset(yylval.lexema, '\0', strlen(yytext)+1);
                    strncpy(yylval.lexema, yytext,strlen(yytext)); //Copiamos en lexema lo que leemos y tenemos como yytext
                    BEGIN(INITIAL); //Volvemos al flujo normal
                    return(FICHERO); //Deolvemos FICHERO 
                    }

{SALTOLINEA} {return((int)*yytext);}; //Cuando leemos un salto de linea lo devolvemos como su valor INT al analizadorSintactico
{SEPARADORES} //Ignoramos los espacios
{IDENTIFICADOR} {   yylval.lexema = (char *)malloc(strlen(yytext)*sizeof(char)+1);
                    memset(yylval.lexema, '\0', strlen(yytext)+1);
                    strncpy(yylval.lexema,yytext,strlen(yytext));   //Copiamos el nombre del identificador en lexema
                    return(IDENTIFICADOR);  //Devolvemos el IDENTIFICADOR
                    }


{NUMEROS} { yylval.valor = atof(yytext); //Cuando leemos un numero transformamos el String en su numero Flotante correspondiente
            return(NUMERO);    //Devolvemos NUMERO 
            }

{OPERADOR_SIMPLE} {return(((int)*yytext));} //Cuando leemos un operador devolvemos su valor INT al analizadorSintactico
{IGUAL} {return(IGUAL);};   
{MENOS_IGUAL}   {return(MENOS_IGUAL);}
{MENOS_MENOS}   {return(MENOS_MENOS );}
{MAS_IGUAL} {return(MAS_IGUAL);}
{MAS_MAS} {return(MAS_MAS);}
{POR_IGUAL} {return(POR_IGUAL);}
{DIVIDIDO_IGUAL} {return(DIVIDIDO_IGUAL);}
{MENOR_IGUAL} {return(MENOR_IGUAL);}
{MAYOR_IGUAL} {return(MAYOR_IGUAL);}
{DISTINTO} {return(DISTINTO);}
{IGUAL_IGUAL} {return(IGUAL_IGUAL);}


. {nuevoError(0,yylineno);}
<<EOF>> {cerrar(); return(FIN_EOF);}


%%
FILE *fp[numFicherosMax];
int nFicheros=0;


/*Funcion para leer de un fichero*/ 
/*
podemos tener llamadas a otro fichero desde un fichero => contamos los ficheros que tenemos 
y los guardamos en un ARRAY, de modo que tenemos en cuenta el numero de ficheros abiertos.
*/
void leerFich(char *f){
    nFicheros++;    //añadimos un nuevo fichero
    if(nFicheros<numFicherosMax){
        if((fp[nFicheros-1]=fopen(f,"r"))!=NULL){
            yyin=fp[nFicheros-1];   //en caso e leer establecemos ue la entrada 'yyin' es ese fichero
        }
        else{   //en caso de no leer => reducimos el Contador - reportamos Error - cerramos todos los Ficheros
            nFicheros--;    
            nuevoError(1,0);
            cerrar_ficheros();
        }
    }
    else{ //en caso de no leer => Reducimos el contador - reportamos Error - cerramos todos los Ficheros
        nFicheros--;    
            nuevoError(2,0);
            cerrar_ficheros();
    }
}

/*Función para cerrar UN fichero*/
void cerrar(){
    fclose(fp[nFicheros-1]); //se cierra el fichero 
    fp[nFicheros-1]='\0';   //se elimina del array
    nFicheros--; //se reduce el contador

    if(nFicheros==0){   //Si no hay mas ficheros
        yyin=stdin; //ponemos el valor de yyin por defecto
        yyrestart(stdin);
    }
    else{
        yyin=fp[nFicheros-1]; //si quedan ficheros cambiamos la entrada al fichero padre
    }
}

/*Funcion para cerrar TODOS los ficheros*/
void cerrar_ficheros(){
    for(int i=0; i<nFicheros; i++){
        fclose(fp[i]);
        fp[i]='\0';
    }
    yyin=stdin; //ponemos el valor de yyin por defecto
}


int salirLexico(){
    cerrar_ficheros(); 
    yylex_destroy(); 
    yyterminate();
}


