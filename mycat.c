#include <stdio.h>		// Funcion para imprimir por pantalla
#include <sys/types.h>		// Funcion de llamada del sistema para abrir archivos
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		// Funciones de llamadas del sistema para leer, escribir y cerrar archivos

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Error de argumentos\n"); // Error al no introducir suficientes argumentos
		return -1;
	} else {
		int fd; // Variable para guardar el descriptor de fichero
		fd = open(argv[1], O_RDONLY); // Guardamos el valor
		if (fd == -1) {
			printf("Error de apertura\n"); // Error al abrir el fichero
			return -1;
		}
		char buf[BUFFER_SIZE]; // Variable para guardar la información que leamos
		ssize_t bytes_leidos; // Variable para saber si se han leído todos los bytes y/o saber cuántos
		do {
			bytes_leidos = read(fd,buf, BUFFER_SIZE); // Guardamos el valor y leemos del descriptor para guardar en buf
			if (bytes_leidos == -1) {
				printf("Error de lectura\n"); // Error al leer el fichero
				return -1;
			}
			write(STDOUT_FILENO, buf, bytes_leidos); // Imprimimos por pantalla los bytes que han sido leídos
		} while (bytes_leidos != 0); // Condición de bucle para seguir imprimiendo mientras no se haya leído todo
		fd = close(fd); // Cerramos el archivo
		if (fd == -1) {
			printf("Error de cierre\n"); // Error al cerrar el fichero
			return -1;
		}
		return 0;
	}
}
