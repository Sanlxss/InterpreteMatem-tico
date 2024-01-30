#include "estructuraAlmacenamiento.h"

/*
 * Funcion para inicializar la tabla.
 */
void inicializarTabla();


/*
 * Funciones para buscar o insertar en la tabla variables
 * */
double buscar_Variables(char *lex);
void insertar_Variables(char *lex, double valor);


/*
 * Funciones para buscar o insertar en la tabla constantes
 */
double buscar_Constantes(char *lex);


/*
 * Funciones para imprimir el contenido de la tabla
 */
void imprimirContenidoTabla();


/*
 Función para imprimir las variables con sus valores
 */
void imprimirWorkspace();


/*
 * Función que devuelve 0 si existe un elemento en la tabla de simbolos
 * Devuelve 1 si NO exitse

  Las clasese son:
 -ID
 -CONST
 -FUNC
 */
int existeElem(char *lex, int clase);


/*
 * Función para reiniciar el estado de la tabla a su versión inicial
 * */
void funcionClear();


/*
 * Funcion para eliminar la tabla y liberar memoria
 */
void borrarTabla();


/*
Funciones para devolver operaciones matematicas
*/
cuerpoElem encontrarFuncion(char *f);


/*
    Funcion para devolver la función del comando 
*/
cuerpoElem encontrarComando(char *f);