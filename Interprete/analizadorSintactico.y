%{
#include "lex.yy.h"
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "gestorErrores.h"
#include "opciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void mostrarAyuda();
void yyerror(char *s);
void liberarMemoria(void *x);

extern int imprimirP;

cuerpoElem func;
%}

%union{
    double valor;
    char *lexema;
};


%token <valor> NUMERO
%token <lexema> IDENTIFICADOR
%token <lexema> FICHERO


%token <lexema> COMANDO_BASICO


/*TERMINALES*/
/*-----------------------------------------------------------*/
%token IMPRIMIR
%token ON 
%token OFF 
%token WORKSPACE 
%token AYUDA 
%token LOAD 
%token CLEAR 
%token TABLA 
%token QUIT
%token FIN_EOF


%token IGUAL
%token MENOS_IGUAL
%token MENOS_MENOS
%token MAS_IGUAL 
%token MAS_MAS 
%token POR_IGUAL
%token DIVIDIDO_IGUAL
%token MENOR_IGUAL
%token MAYOR_IGUAL
%token DISTINTO
%token IGUAL_IGUAL
/*-----------------------------------------------------------*/


/*ASOCIATIVIDAD y PRECEDENCIA*/
/*-----------------------------------------------------------*/
/*ASIGNACIONES*/
%right IGUAL
%left MAS_MAS
%left MENOS_MENOS
%left MAS_IGUAL
%left MENOS_IGUAL
%left POR_IGUAL
%left DIVIDIDO_IGUAL

/*COMPARACIONES*/
%left IGUAL_IGUAL
%left DISTINTO
%left '<' '>'
%left MENOR_IGUAL
%left MAYOR_IGUAL

/*OPERACIONES*/
%left '+' '-'
%left '*' '/'
%left NEG

/*FUNCIONES*/
%right '^'
/*-----------------------------------------------------------*/


%start input;
%type <valor> expr
%type <valor> opciones
%type <valor> asignacion
%type <valor> comparaciones
%type <valor> funciones

%%

input:  %empty  {
                    printf("\n-->");
                }
        | input line
;


line:   '\n'
        | FIN_EOF   {
                        printf("\nFin Lectura Fichero\n");printf("\n-->");
                    }


        | expr '\n' {
                        printf("\n-->");
                    }
        | expr ';' '\n' {   
                            if(!isnan($1)){
                                if(imprimirP==1){
                                    printf("%lf", $1);
                                }
                            }
                            printf("\n-->");
                        }
        | expr FIN_EOF {
                                printf("\n-->");
                            }
        | expr ';' FIN_EOF  {   
                                if(!isnan($1)){
                                    if(imprimirP==1){
                                        printf("%lf", $1);
                                    }
                                }
                                printf("\n-->");
                            }

        | comparaciones '\n'    {
                                    printf("\n-->");
                                }
        | comparaciones ';' '\n'    {   
                                        if(!isnan($1)){
                                            if(imprimirP==1){
                                                printf("%lf", $1);
                                            }
                                        }
                                        printf("\n-->");
                                    }
        | comparaciones FIN_EOF {
                                    printf("\n-->");
                                }
        | comparaciones ';' FIN_EOF {   
                                        if(!isnan($1)){
                                            if(imprimirP==1){
                                                printf("%lf", $1);
                                            }
                                        }
                                        printf("\n-->");
                                    }


        | opciones '\n' {
                            printf("\n-->");
                        }
        | opciones FIN_EOF  {
                                printf("\n-->");
                            }

        | error {   
                    yyerror("\nError en el Analizador Sintactico\n");
                    printf("\n-->");
                }
;


expr:   NUMERO  {
                    $$=$1;
                }
        | expr '+' expr {
                            $$=$1+$3;
                        }
        | expr '-' expr {
                            $$=$1-$3;
                        }
        | expr '*' expr {   
                            $$=$1*$3;
                        }
        | expr '/' expr {
                            if($3!=0){
                                $$=$1/$3;
                            }
                            else{
                                yyerror("\nDivision por CERO->ERROR\n");    
                                $$=NAN;
                            }
                        }
        | '+' expr %prec NEG    {
                                    $$=+$2;
                                }
        | '-' expr %prec NEG    {
                                    $$=-$2;
                                }
        | '(' expr ')'  {
                            $$=$2;
                        } 

        | IDENTIFICADOR {   
                            if(existeElem($1,ID)==0){
                                $$=buscar_Variables($1);
                                liberarMemoria($1);
                            }
                            else if(existeElem($1,CONST)==0){
                                $$=buscar_Constantes($1);
                                liberarMemoria($1);
                            }
                            else{
                                yyerror("\nVariable NO inicializada\n");                                
                                $$=NAN;
                                liberarMemoria($1);
                            }
                        }  
        | asignacion 
        | funciones   

;


asignacion: IDENTIFICADOR IGUAL expr    {  if(existeElem($1,CONST)==0){
                                                yyerror("\nNo se puede modificar e valor de una CONSTANTE\n");
                                                $$=NAN;
                                                liberarMemoria($1);
                                            }
                                            else if(existeElem($1,FUNC)==0){
                                                yyerror("\nNo se puede modificar e valor de una FUNCION\n");
                                                $$=NAN;
                                                liberarMemoria($1);
                                            }
                                            else if(existeElem($1,COM)==0){
                                                yyerror("\nNo se puede modificar e valor de un COMANDO\n");
                                                $$=NAN;
                                                liberarMemoria($1);
                                            }
                                            else{
                                                insertar_Variables($1, $3);
                                                $$=$3;
                                                liberarMemoria($1);
                                            }
                                        }
            | IDENTIFICADOR MAS_MAS     {   if(existeElem($1, ID)==0){
                                                insertar_Variables($1,buscar_Variables($1)+1);
                                                $$=buscar_Variables($1);
                                                liberarMemoria($1);
                                            }
                                            else{
                                                yyerror("\nVariable NO inicializada\n");
                                                $$=NAN;
                                                liberarMemoria($1);
                                            }
                                        }
            | IDENTIFICADOR MENOS_MENOS     {   if(existeElem($1, ID)==0){
                                                    insertar_Variables($1,buscar_Variables($1)-1);
                                                    $$=buscar_Variables($1);
                                                    liberarMemoria($1);
                                                }
                                                else{
                                                    yyerror("\nVariable NO inicializada\n");
                                                    $$=NAN;
                                                    liberarMemoria($1);
                                                }
                                            }
            | IDENTIFICADOR MAS_IGUAL expr      {   if(existeElem($1, ID)==0){
                                                        insertar_Variables($1,buscar_Variables($1)+$3);
                                                        $$=buscar_Variables($1);
                                                        liberarMemoria($1);
                                                    }
                                                    else{
                                                        yyerror("\nVariable NO inicializada\n");
                                                        $$=NAN;
                                                        liberarMemoria($1);
                                                    }
                                                }
            | IDENTIFICADOR MENOS_IGUAL expr    {   if(existeElem($1, ID)==0){
                                                        insertar_Variables($1,buscar_Variables($1)-$3);
                                                        $$=buscar_Variables($1);
                                                        liberarMemoria($1);
                                                    }
                                                    else{
                                                        yyerror("\nVariable NO inicializada\n");
                                                        $$=NAN;
                                                        liberarMemoria($1);
                                                    }
                                                }
            | IDENTIFICADOR POR_IGUAL expr      {   if(existeElem($1, ID)==0){
                                                        insertar_Variables($1,buscar_Variables($1)*$3);
                                                        $$=buscar_Variables($1);
                                                        liberarMemoria($1);
                                                    }
                                                    else{
                                                        yyerror("\nVariable NO inicializada\n");
                                                        $$=NAN;
                                                        liberarMemoria($1);
                                                    }
                                                }
            | IDENTIFICADOR DIVIDIDO_IGUAL expr     {   if(existeElem($1, ID)==0){
                                                            if($3!=0){
                                                                insertar_Variables($1,buscar_Variables($1)/$3);
                                                                $$=buscar_Variables($1);
                                                                liberarMemoria($1);
                                                            }
                                                            else{
                                                                yyerror("\nDivisin por CERO->ERROR\n");
                                                                $$=NAN; 
                                                                liberarMemoria($1);   
                                                            }
                                                        }
                                                        else{
                                                            yyerror("\nVariable NO inicializada\n");
                                                            $$=NAN;
                                                            liberarMemoria($1);
                                                        }
                                                    }
;   


funciones:  IDENTIFICADOR '(' expr ')'  {   if(existeElem($1,FUNC)==0){
                                                func=encontrarFuncion($1);
                                                $$=func.funcion($3);
                                                liberarMemoria($1);
                                            }
                                            else{
                                                yyerror("\nFuncion no registrada en la calculadora\n");
                                                $$=NAN;
                                                liberarMemoria($1);
                                            }
                                        }
            | IDENTIFICADOR '(' expr ',' expr ')'   {   if(existeElem($1,FUNC)==0){
                                                            func=encontrarFuncion($1);
                                                            $$=func.funcion($3,$5);
                                                            liberarMemoria($1);
                                                        }
                                                        else{
                                                            yyerror("\nFuncion no registrada en la calculadora\n");
                                                            $$=NAN;
                                                            liberarMemoria($1);
                                                        }
                                                    }
            | expr '^' expr     {   if(existeElem("^",FUNC)==0){
                                        func=encontrarFuncion("^");
                                        $$=func.funcion($1,$3);
                                    }
                                    else{
                                        yyerror("\nFuncion no registrada en la calculadora\n");
                                        $$=NAN;
                                    }
                                }
;


comparaciones:  expr IGUAL_IGUAL expr   {   if(!isnan($1) && !isnan($3)){
                                                if($1==$3){
                                                    printf("TRUE\n");
                                                    $$=NAN;
                                                }
                                                else{
                                                    printf("FALSE\n");
                                                    $$=NAN;
                                                }
                                            }
                                            else{
                                                yyerror("\nError sintactico, comparacion mal formada\n");
                                                $$=NAN;
                                            }
                                        }
                | expr DISTINTO expr    {   if(!isnan($1) && !isnan($3)){
                                                if($1!=$3){
                                                    printf("TRUE\n");
                                                    $$=NAN;
                                                }
                                                else{
                                                    printf("FALSE\n");
                                                    $$=NAN;
                                                }
                                            }
                                            else{
                                                yyerror("\nError sintactico, comparacion mal formada\n");
                                                $$=NAN;
                                            }
                                        } 
                | expr '<' expr     {   if(!isnan($1) && !isnan($3)){
                                            if($1<$3){
                                                printf("TRUE\n");
                                                $$=NAN;
                                            }
                                            else{
                                                printf("FALSE\n");
                                                $$=NAN;
                                            }
                                        }
                                        else{
                                            yyerror("\nError sintactico, comparacion mal formada\n");
                                            $$=NAN;
                                        }
                                    }  
                | expr MENOR_IGUAL expr     {   if(!isnan($1) && !isnan($3)){
                                                    if($1<=$3){
                                                        printf("TRUE\n");
                                                        $$=NAN;
                                                    }
                                                    else{
                                                        printf("FALSE\n");
                                                        $$=NAN;
                                                    }
                                                }
                                                else{
                                                    yyerror("\nError sintactico, comparacion mal formada\n");
                                                    $$=NAN;
                                                }
                                            } 
                | expr '>' expr     {   if(!isnan($1) && !isnan($3)){
                                            if($1>$3){
                                                printf("TRUE\n");
                                                $$=NAN;
                                            }
                                            else{
                                                printf("FALSE\n");
                                                $$=NAN;
                                            }
                                        }
                                        else{
                                            yyerror("\nError sintactico, comparacion mal formada\n");
                                            $$=NAN;
                                        }
                                    }  
                | expr MAYOR_IGUAL expr     {   if(!isnan($1) && !isnan($3)){
                                                    if($1>=$3){
                                                        printf("TRUE\n");
                                                        $$=NAN;
                                                    }
                                                    else{
                                                        printf("FALSE\n");
                                                        $$=NAN;
                                                    }
                                                }
                                                else{
                                                    yyerror("\nError sintactico, comparacion mal formada\n");
                                                    $$=NAN;
                                                }
                                            }                                                                 
;


opciones:   COMANDO_BASICO  {   printf("Buscando Comando\n");
                                    if(existeElem($1, COM)==0){  
                                        printf("\n\tLlamando a comando: %s\n", $1);                                      
                                        func=encontrarComando($1);
                                        func.funcion();
                                        if(strcmp($1,"quit")==0){
                                            liberarMemoria($1);
                                            YYACCEPT;
                                        }
                                        else{
                                            liberarMemoria($1);
                                        }
                                    }
                                    else{
                                        printf("Comando no encontrado\n");
                                        liberarMemoria($1);
                                    }
                            }

            | LOAD FICHERO  {
                                printf("\nIniciando lectura de fichero\n"); 
                                func=encontrarComando("LOAD");
                                func.funcion($2);                                
                                $$=NAN;
                                liberarMemoria($2);
                            }
;


%%


void yyerror(char *s){
    printf("%s", s);
    nuevoError(3,-1);
}

void mostrarAyuda(){
    ayuda();
}

void liberarMemoria(void *x){
    free(x);
}
