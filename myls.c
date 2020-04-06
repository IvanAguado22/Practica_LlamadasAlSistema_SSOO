#include <stdio.h>		// Función para imprimir por pantalla
#include <unistd.h>		// Función de llamada del sistema getcwd
#include <sys/types.h>		// Funciones de llamadas del sistema para leer, escribir y cerrar directorios
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]) {
	if (argc < 2) {
		char buf[PATH_MAX]; // Variable donde almacenar el directorio
		getcwd(buf,PATH_MAX); // Almacenamos el directorio con toda su longitud
		DIR *dir; // Variable donde guardaremos el descriptor de directorio
		dir = opendir(buf); // Abrimos el directorio contenido en buf y guardamos su descriptor en dir
		if (dir == NULL) {
			printf("Error de apertura\n"); // Error al abrir el directorio
			return -1;
		}
		struct dirent *dirent; // Variable donde almacenaremos cada entrada del directorio
		dirent = readdir(dir);
		while (dirent != NULL) { // Condición de bucle para seguir imprimiendo mientras no se haya leído todo
			printf("%s\n", dirent -> d_name); // Imprimimos cada entrada del directorio según el orden devuelto
			dirent = readdir(dir); // Leemos la siguiente entrada
		}
		int fdir;
		fdir = closedir(dir);
		if (fdir == -1) {
			printf("Error de cierre\n"); // Error al cerrar el fichero
			return -1;
		}
	} else {
		DIR *dir; // Variable donde guardaremos el descriptor de directorio
		dir = opendir(argv[1]); // Abrimos el directorio obtenido como parámetro y guardamos su descriptor en dir
		if (dir == NULL) {
			printf("Error de apertura\n"); // Error al abrir el directorio
			return -1;
		}
		struct dirent *dirent; // Variable donde almacenaremos cada entrada del directorio
		dirent = readdir(dir);
		while (dirent != NULL) { // Condición de bucle parar seguir imprimiendo mientras no se haya leído todo
			printf("%s\n", dirent -> d_name); // Imprimimos cada entrada del directorio según el orden devuelto
			dirent = readdir(dir); // Leemos la siguiente entrada
		}
		int fdir;
		fdir = closedir(dir);
		if (fdir == -1) {
			printf("Error de cierre\n"); // Error al cerrar el fichero
			return -1;
		}
	}
	return 0;
}
