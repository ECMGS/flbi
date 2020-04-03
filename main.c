#include <stdio.h>
#include <stdlib.h>

// El fichero
FILE *f;

// Tamaño del programa
int sPrograma;

// Instrucciones
char *instrucciones;

// Stack
unsigned char stack[30000];

// Punteros
// Puntero del stack
unsigned short ps;
// Puntero del programa
unsigned int pp;

// Stack
int *bucles;

// Constructores
int cargarArchivo(const char*);
int leerInstrucciones();

// Lee el archivo de texto y carga las instrucciones en en memoria
int cargarArchivo(const char* archivo) {
	
	// Abre el archivo que se le ha pasado por los argumentos
	f = fopen(archivo, "r");
	
	// Si no se puede abrir el archivo, el método devuelve 0
	if (f == NULL)
		return 0;
	
	// Lee el tamaño del archivo	
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, 0);
	
	// Almacena en memoria suficientes bytes como para todas las instrucciones
	instrucciones = (char*) malloc(fsize);
	
	// Guarda el archivo en su propio array
	char c; 
	int i;
	while (c = fgetc(f)) {
		if (feof(f))
			break;
		if (c != '+' && c != '-' && c != '<' && c != '>' && c != '.' && c != ',' && c != '[' && c != ']') 
			continue;
		instrucciones[i] = c;
		i++;	
	}
	
	// Establece el tamaño del programa
	sPrograma = i;

	// Cierra el archivo (ya no es necesario)
	fclose(f);
	return 1;
}

int leerInstrucciones() {
	// Lee instruccion por instruccion
	for (pp; pp < sPrograma; pp++) {
#ifdef DEBUG
		printf("leyendo instruccion %i %c\n", pp, instrucciones[pp]);
#endif
		// Ejecuta las instrucciones
		switch (instrucciones[pp]) {
			case '>':
				ps++;
				break;
			case '<':
				ps--;
				break;
			case '+':
				stack[ps]++;
				break;
			case '-':
				stack[ps]--;
				break;
			case '.':
				putchar(stack[ps]);
				break;
			case ',':
				stack[ps] = getchar();
				break;
			case '[':
				// Si el stack no es igual a 0, guarda la posición del stack
				if (stack[ps]) {
					*(bucles++) = pp-1;
				} else {
					// Si es igual a 0 busca el punto de finalización del bucle
					// bucles internos
					short bi = 0;
					while (1) {
						char inst = instrucciones[++pp];
						// Si la instrucción es [ es que hay un bucle interno, incrementa bi
						if (inst == '[') {
#ifdef DEBUG
							printf("encontrado bucle interno | num bi %i", bi);
#endif
							bi++;
						} else if (inst == ']' && !bi) {	// Si no hay / estamos fuera de los bucles internos y vemos ] pasa a la siguiente línea y continua la ejecución
							break;
						} else if (inst == ']') {			// Si hay bucles internos y encuentra ] decrementa bi
#ifdef DEBUG
							printf("encontrado salida bucle interno | num bi %i", bi);
#endif
							bi--;
						}
					}
				}
				break;
			case ']':
				pp = *(--bucles);		// Vuelve al inicio del bucle y decrementa el puntero de bucles
				break;
		}
#ifdef DEBUG
		printf("el stack está en %i con valor %i", ps, stack[ps]);

		char s[10];
		gets(s);
#endif
	}

	return 0;
}

// método principal
int main(int argc, char *argv[]) {

	// Si se pasa un archivo lo carga, si no, carga el archivo de ejemplo	
	int ca = 0;
	if (argc > 1) {
		ca = cargarArchivo(argv[1]);
	} else {
		ca = cargarArchivo("ej.bf");	
	}
	
	// Si no se puede leer el archivo devuelve 2 
	if (!ca) {
		printf ("No se ha podido cargar el archivo de texto\n");
		return 2;
	}
	
	// Inicialización de punteros
	pp = 0;
	ps = 0;
	
	// Puntero de bucles, incluye la referencia al pp del inicio del bucle
	bucles = (int*) malloc(3000*sizeof(int));
	
	// Inicia toda la memoria a cero
	int i;
	for (i = 0; i < 30000; i++) {
		stack[i] = 0;
	}
	
	printf("entorno preparado\ntamaño del programa %i\n", sPrograma);

	// Ejecuta el programa
	leerInstrucciones();
	
	// Inserta un espacio de línea para el siguiente comando
	printf("\n");
	
	return 0;
}
