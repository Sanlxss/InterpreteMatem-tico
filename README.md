# Interprete de comandos matemáticos

Se ha desarrollado un Interprete de comandos matemáticos para la asignatura de Compiladores e Interpretes del grado de Ingenieria Informática de la USC.


## Compilación.
Para compilar el interprete se descargará este directorio y se guardarán en el todos los archivos, incluidos los ficheros que se quieran ejecutar.
A continuación desde un terminal de Linux, se ejecutarán las siguientes acciones en el siguiente orden:
- Ejecutar el comando 'bison -d -Wconflicts-sr analizadorSintactico.y' que nos proporcionará el fichero 'analizadorSintactico.tab.c' junto con su 'analizadorSintactico.tab.h'
- Copiar las cabeceras de las funciones definidas en 'nalizadorSintactico.y' y la estructura de componente lexico en el fichero 'analizadorSintactico.tab.h'. 
    **NO copiar #inlcude lex.yy.h NI cuerpoElem func**
- Ejecutar el comando 'flex --header-file="lex.yy.h" lex.l' que nos proporcionará el fichero 'lex.yy.c' junto con su 'lex.yy.h'.
- Copiar las cabeceras de las funciones definidas en 'lex.l' y la estructura de componente lexico en el fichero 'lex.yy.h'.
- Ejecutar el comando 'make' para compilar todos los ficheros que forman el ejecutable.

En el caso de querer deshacer la compilacion (borrar todos los fichero resultantes de estas) se ejecutará el comando 'make cleanall'.


## Ejecución
Para la ejecución, una vez compilado el analizador, se ejecutará en el terminal alguno de los siguientes comandos:
- ./calculadora  -> ejecuta la calculadora 
- ./calculadora -h  -> ejecuta la calculadora mostrando la sección de ayuda
- ./calculadora -l {nombreFichero}  -> ejecuta la calculadora analizando el fichero indicando
