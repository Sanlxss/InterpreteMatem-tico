#ifndef ESTRUCTURAALMACENAMIENTO_H
#define ESTRUCTURAALMACENAMIENTO_H


//Estructura con el valor asociado a un TIPOELEM
typedef struct{
    double valor;
    double (*funcion)();
}cuerpoElem;

//Estructura de la información que tenemos, TIPOELEM
typedef struct {
    char *lexema;
    cuerpoElem cuerpo;
}tipoelem;



//Establecemos cual es la clave de ordenacion
typedef char *tipoclave;

//Establecemos como tipo opaco la forma del arbol.
typedef struct celda *abb;

/*FUNCIONAS PUBLICAS*/

//Creamos el arbol binario
void crear(abb *A);

//Destruiimos el arbol binario
void destruir(abb *A);

//Funcion buscar-insertar variables(identificadores) con sus valores
double buscar_ID(abb A, tipoelem E);
void insertar_ID(abb *A,tipoelem E);

//Funcion ppara insertar operaciones
void insertar_FN(abb *A, char *lexema, double(*funcion)());


//Funcion ppara insertar comandos
void insertar_CM(abb *A, char *lexema, double(*funcion)());

//Función para buscar-insertar constantes
double buscar_CONST(abb A, tipoelem E);
void insertar_CONST(abb *A,tipoelem E);

//Funcion que comprueba que exista un valor en el arbol, si existe devuelve 0 en csao contrario devuelve 1
int existe(abb A, char *lexema, int clase);

//Imprimimos el arbol binario
void imprimirABB(abb A);
//Imprimimos las variables
void imprimirVariables(abb A);

//Funciones para realizar calculos matematicos
cuerpoElem buscarFuncion(abb A, char *f);



//Funcion para devolver la función del comando.
cuerpoElem buscarCom(abb A, char *f);

#endif