#include <stdio.h>	// Función para introducir por pantalla
#include <sys/types.h>	// Función de llamada del sistema fstat
#include <sys/stat.h>
#include <fcntl.h>	// Función de llamada del sistema fcntl
#include <dirent.h>	// Funciones de llamadas del sistema para leer, escribir y cerrar directorios
#include <unistd.h>


int main(int argc, char *argv[]) {
	if(argc > 1) {
		printf("Error de argumentos\n"); // Error al introducir demasiados argumentos
		return -1;
	} else {
		char buf[PATH_MAX]; // Variable donde almacenar el directorio
		getcwd(buf, PATH_MAX); // Almacenamos el directorio con toda su longitud
		DIR *dir; // Variable donde guardaremos el descriptor de directorio
		dir = opendir(buf); // Abrimos el directorio contenido en buf y guardamos su descriptor en dir
		if (dir == NULL) {
			printf("Error de apertura\n"); // Error al abrir el directorio
			return -1;
		}
		struct dirent *dirent; // Variable donde almacenaremos cada entrada del directorio
		dirent = readdir(dir);
		while (dirent != NULL) { // Condición del bucle para seguir imprimiendo mientras no se haya leído todo
			if(dirent -> d_type == DT_REG) { // Solo imprimiremos la información de ficheros regulares
				int fd;
				fd = open(dirent -> d_name, O_RDONLY); // Abrimos el archivo
				if (fd == -1) {
					printf("Error de apertura\n"); // Error al abrir el fichero
					return -1;
				}
				int puntero; // Variable donde almacenaremos el tamaño del fichero
				puntero = lseek(fd, 0, SEEK_END);
				fd = close(fd); // Cerramos el fichero
				if (fd == -1) {
					printf("Error de cerrado\n"); // Error al cerrar el fichero
					return -1;
				}
				printf("%s", dirent -> d_name); // Imprimimos cada entrada del directorio según el orden devuelto
				printf("	"); // Imprimimos un salto de espacio tabulador
				printf("%d\n", puntero); // Imprimimos el tamaño del fichero
			}
		dirent = readdir(dir); // Leemos la siguiente entrada
		}
		int fdir;
		fdir = closedir(dir); // Cerramos el directorio
		if (fdir == -1) {
			printf("Error de cierre\n"); // Error al cerrar el fichero
			return -1;
		}
		return 0;
	}
}
