#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define T 100 /*Tamaño máximo de caracteres en una cadena*/
#define E 15  /*Número máximo de integrantes en un equipo*/
#define M 30  /*Numero máximo de equipos en la liga*/
/*struct para almacenar los datos de un jugador*/
typedef struct JUGADOR{
	char nombre[T];
	int edad;
	float estatura;
	int num_jugador;
	char posicion[T];
}jugadores;
/*struct para almacenar equipos*/
typedef struct EQUIPO{
	char nombre[T];
	int dia;
	int mes;
	int semana;
	int num_jugadores;
	int num_goles;
	jugadores jugador[E];
}equipo;
void Insertar_Equipo(equipo *,int *);/*Función para insertar equipos*/
void Consultar_Calendario(equipo*,int,FILE*);/*Función para mostrar el calendario de juegos*/
void Consultar_Datos(equipo*,int);/*Mostrar datos de un solo equipo*/
void Mostrar_datos(equipo*,int,FILE*);/*Mostrar datos de todos los equipos*/
void Mostrar_Marcadores(equipo*,int,FILE*);/*Mostrar marcadores de equipos (número de goles)*/
void Modificar(equipo*,int);/*Modificar los datos de algún equipo*/
void Borrar_Equipo(equipo*,int*);/*Borra algún equipo registrado*/
void Disponibilidad(int);/*Consultar el cupo para los equipos que se quieran registrar*/
int Menu();/*Función para mostrar el menú*/
main(){
	system("COLOR 9");/*Definir color de fuente azul claro*/
	/*Asignación dinámica de memoria, para crear un arreglo de 50 elementos*/
	equipo *equipos=NULL;
	equipos = (equipo*)malloc(sizeof(equipo)*T);
	/*Declaración de los objetos tipo FILE, los cuales almacenarán los datos de los equipos*/
	FILE *Calendario=NULL;/*Archivo para almacenar el calendario de juegos*/
	FILE *MostrarDatos=NULL;/*Archivo para mostrar los datos de todos los equipos registrados*/
	FILE *Marcadores=NULL;/*Archivo para mostrar el marcador de todos los equipos*/
	/*Se crean los archivos en modo escritura*/
	Calendario =fopen("Calendario.txt","w");
	MostrarDatos = fopen("Mostrar_Datos.txt","w");
	Marcadores = fopen("Marcadores.txt","w");
	int pos=0;
	int o = 0;
	int opc =0;
	int e=0;
	int mod=0;
	do{
	fflush(stdin);
	system("cls");/*Limpiar la pantalla*/
	opc=Menu();/*Capturar el valor de la opción con el valor retornado por Menú*/
	switch (opc){
		case 1:
			Insertar_Equipo(equipos,&pos);
			break;
		case 2:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			Consultar_Calendario(equipos,pos,Calendario);
			break;
		case 3:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			printf("Ingrese el numero de registro del equipo:\n");
			scanf("%d",&e);
			Consultar_Datos(equipos,e-1);
			break;
		case 4:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			Mostrar_datos(equipos,pos,MostrarDatos);
			break;
		case 5:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			Mostrar_Marcadores(equipos,pos,Marcadores);
			break;
		case 6:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			printf("Ingrese el numero de equipo que desea modificar:\n");
			scanf("%d",&mod);
			Modificar(equipos,mod-1);
			break;
		case 7:
			if(pos==0){
				printf("No hay equipos registrados\n");
				break;
			}
			Borrar_Equipo(equipos,&pos);
			break;
		case 8:
			Disponibilidad(pos);
			break;
		case 9:
			printf("Adios UnU");
			exit(1);
			break;
		default:/*Si la opción tecleada no existe, se imprimirá un mensaje de error*/
			printf("Valor incorrecto...\n");
			break;
		}
		fflush(stdin);
		do{
			printf("\nDesea consultar otra opcion\?\n");
			printf("[1] Si\t[2]No\n");
			scanf("%d",&o);
		}while(o<1||o>2);
	}while(o!=2);
	/*Cierre de los archivos*/
	fclose(Marcadores);
	fclose(Calendario);
	fclose(MostrarDatos);
	free(equipos);/*Liberar memoria*/
}

/*Función para mostrar las opciones que puede elegir el usuario*/
int Menu(){
	int res =0;/*Variable para almacenar la respuesta del usuario*/
	printf("*****Bienvenido/a a la liga de futbol rapido*****\n\n");
	printf("Ingresar equipo........................1|\n");
	printf("Consultar calendario...................2|\n");
	printf("Consultar datos de equipo..............3|\n");
	printf("Mostrar datos de todos los equipos.....4|\n");
	printf("Consultar marcadores...................5|\n");
	printf("Modificar datos de equipo..............6|\n");
	printf("Borrar equipo..........................7|\n");
	printf("Consultar disponibilidad de lugares....8|\n");
	printf("Salir..................................9|\n");
	printf("----------------------------------------|\n");
	printf("Seleccione una opcion:	");
	scanf("%d",&res);
	return res;
}

/*Función para insertar equipos en un arreglo*/
void Insertar_Equipo(equipo *equipo,int* pos){
	system("cls");
	if(*pos<M){
	fflush(stdin);
	printf("Nombre del eqipo:\n");
	fgets(equipo[*pos].nombre,T,stdin);
	
	printf("Fecha de juego dd/mm/aaaa\n");
	printf("Dia: ");
	scanf("%d",&equipo[*pos].dia);
	printf("\nSemana: ");
	scanf("%d",&equipo[*pos].semana);
	printf("\nMes: ");
	scanf("%d",&equipo[*pos].mes);
	
	do{/*Este bucle se ejecutará mientras el usuario ingrese un número incorrecto de jugadores*/
	printf("Numero de jugadores\n");/*Con un mmáximo de 15 jugadores y un mínimo de 7*/
	scanf("%d",&equipo[*pos].num_jugadores);
	if((equipo[*pos].num_jugadores<7)||(equipo[*pos].num_jugadores>15)){
		system("cls");
		system("COLOR 4");/*Color de las letras rojo, para indicar que el usuario cometió un error*/
		//system("cls");/*se 'limpia la pantalla'*/
		printf("El numero de integrantes del equipo debe ser mayor o igual a 7 y menor e igual a 15\n");
		printf("Por favor, introduzca un valor correcto\n");
		}
	}while((equipo[*pos].num_jugadores<7)||(equipo[*pos].num_jugadores>15));
	system("COLOR 7");
	system("cls");
	/*Bucle para ingresar los datos de los jugadores*/
	for(int i=0;(i<equipo[*pos].num_jugadores)&&(i<E);i++){
		system("cls");
		printf("Ingrese los datos del jugador [%d]:\n",i+1);
		fflush(stdin);
		printf("Nombre:\n");
		fgets(equipo[*pos].jugador[i].nombre,T,stdin);
	
		printf("Edad:\n");
		fflush(stdin);	
		scanf("%d",&equipo[*pos].jugador[i].edad);
	
		printf("Estatura:\n");
		scanf("%f",&equipo[*pos].jugador[i].estatura);
	
		printf("Numero del jugador:\n");
		scanf("%d",&equipo[*pos].jugador[i].num_jugador);
	
		fflush(stdin);
		printf("Posicion:\n");
		fgets(equipo[*pos].jugador[i].posicion,T,stdin);
	}
	printf("Registro guardado exitosamente!! \n");
	printf("Numero de registro del equipo: %d\n",*pos+1);
	(*pos)++;/*Aumenta el valor del contenido en 1 del puntero pos*/
	}else{
		printf("Ya no se pueden registrar mas equipos :(\n");
	}
}

/*Función para mostrar el calendario*/
/*Esta función mostrará la fecha en que jugará cada equipo*/
void Consultar_Calendario(equipo* equipos,int tam,FILE * Calendario){
	system("cls");
	Calendario = fopen("Calendario.txt","a");
	printf("Calendario de todos los partidos\n");
	printf("|	Dia	|    semana	|     mes	|\n");
	fprintf(Calendario,"Calendario de todos los partidos\n");
	fprintf(Calendario,"|	Dia	|    semana	|     mes	|\n");
	for(int i=0;i<tam;i++){
		printf("|	%d	|	%d	|	%d	|\n",equipos[i].dia,equipos[i].semana,equipos[i].mes);
		fprintf(Calendario,"|	%d	|	%d	|	%d	|\n",equipos[i].dia,equipos[i].semana,equipos[i].mes);
	}	
}

/*Función para mostrar los datos de un equipo*/
/*Esta función muestra los datos de un solo equipo, el que el usuario elija*/
void Consultar_Datos(equipo* equipos,int num){
	system("cls");
	if(num<0){
		printf("No hay equipos registrados\n");
	}else{
	printf("Nombre del equipo: %s\n",equipos[num].nombre);
	printf("fecha del partido: %d/%d/%d\n",equipos[num].dia,equipos[num].semana,equipos[num].mes);
	printf("Integrantes del equipo:\n");
	for(int i=0;i<equipos[num].num_jugadores;i++){
		printf("Nombre: %s\n",equipos[num].jugador[i].nombre);
		printf("Edad: %d\n",equipos[num].jugador[i].edad);
		printf("Estatura: %.2f\n",equipos[num].jugador[i].estatura);
		printf("Numero de jugador: %d\n",equipos[num].jugador[i].num_jugador);
		printf("Posicion: %s\n",equipos[num].jugador[i].posicion);
		printf("\n");
	}
	}
}

/*Función para mostrar los datos de todos los equipos*/
/*A diferencia de la función anterior, ésta función no le da la opción al usuario de elegir un solo
equipo, sino que muestra todos los registros que se han guardado*/
void Mostrar_datos(equipo* equipos,int tam,FILE *MostrarDatos){
	system("cls");
	if(tam==0){
		printf("No hay equipos registrados\n");
	}else{
		MostrarDatos = fopen("Mostrar_Datos.txt","a");
		for(int i=0;i<tam;i++){/*Recorrer los equipos*/
			printf("Nombre del equipo: %s\n",equipos[i].nombre);
			printf("Fecha en que jugara: %d/%d/%d\n",equipos[i].dia,equipos[i].semana,equipos[i].mes);
			printf("Numero de jugadores: %d\n",equipos[i].num_jugadores);
			/*Sentencia para guardar los datos de equipos en archivos txt*/
			fprintf(MostrarDatos,"Nombre del equipo: %s\n",equipos[i].nombre);
			fprintf(MostrarDatos,"Fecha en que jugara: %d/%d/%d\n",equipos[i].dia,equipos[i].semana,equipos[i].mes);
			fprintf(MostrarDatos,"Numero de jugadores: %d\n",equipos[i].num_jugadores);
			for(int j=0;(j<equipos[i].num_jugadores)&& (j<E);j++){/*Bucle para mostrar jugadores*/
				printf("\tnombre: %s\n",equipos[i].jugador[j].nombre);
				printf("\tedad: %d\n ",equipos[i].jugador[j].edad);
				printf("\testatura: %.2f\n",equipos[i].jugador[j].estatura);
				printf("\tnumero de jugador: %d \n",equipos[i].jugador[j].num_jugador);
				printf("\tposicion: %s\n\n",equipos[i].jugador[j].posicion);
			/*Sentencia para guardar los registros de todos los equipos en un archivo txt*/
			fprintf(MostrarDatos,"\tnombre: %s\n",equipos[i].jugador[j].nombre);
			fprintf(MostrarDatos,"\tedad: %d\n ",equipos[i].jugador[j].edad);
			fprintf(MostrarDatos,"\testatura: %.2f\n",equipos[i].jugador[j].estatura);
			fprintf(MostrarDatos,"\tnumero de jugador: %d \n",equipos[i].jugador[j].num_jugador);
			fprintf(MostrarDatos,"\tposicion: %s\n\n",equipos[i].jugador[j].posicion);
			}
		}
	}
}
/*Función para mostrar los marcadores de los equipos*/
/*Esta función le asigna un número aleatorio de goles a un equipo*/
void Mostrar_Marcadores(equipo* equipos,int tam,FILE* Maracdores){
	system("cls");
	if(tam==0){
		printf("No hay equipos registrados\n");
	}else{
	Maracdores = fopen("Marcadores.txt","a");
	srand (time(NULL));
	for(int i=0;i<tam;i++){
		/*En cada iteración se le asignará un 'x' número de goles al i-ésimo equipo*/
		printf("\nNombre del equipo [%d]: %s",i+1,equipos[i].nombre);
		printf("Numero de goles: %d",equipos[i].num_jugadores=rand()%(10+1));
		/*Sentencia para guardar los registros de los marcadores en un archivo txt*/
		fprintf(Maracdores,"\nNombre del equipo [%d]: %s",i+1,equipos[i].nombre);
		fprintf(Maracdores,"Numero de goles: %d",equipos[i].num_jugadores);
		}
	}
}
/*Función para modificar los datos de algún equipo*/
void Modificar(equipo* equipo,int pos){
	system("cls");
	printf("Ingrese los nuevos datos:\n");
	printf("Nombre del eqipo:\n");
	fflush(stdin);
	fgets(equipo[pos].nombre,T,stdin);
	
	printf("Fecha de juego dd/mm/aaaa\n");
	printf("Dia: ");
	scanf("%d",&equipo[pos].dia);
	printf("\nSemana: ");
	scanf("%d",&equipo[pos].semana);
	printf("\nMes: ");
	scanf("%d",&equipo[pos].mes);
	
	do{/*Este bucle se ejecutará mientras el usuario ingrese un número incorrecto de jugadores*/
	printf("Numero de jugadores\n");/*Con un mmáximo de 15 jugadores y un mínimo de 7*/
	scanf("%d",&equipo[pos].num_jugadores);
	if((equipo[pos].num_jugadores<7)||(equipo[pos].num_jugadores>15)){
		system("cls");
		system("COLOR 4");/*Color de las letras rojo, para indicar que el usuario cometió un error*/
		//system("cls");/*se 'limpia la pantalla'*/
		printf("El numero de integrantes del equipo debe ser mayor o igual a 7 y menor e igual a 15\n");
		printf("Por favor, introduzca un valor correcto\n");
		}
	}while((equipo[pos].num_jugadores<7)||(equipo[pos].num_jugadores>15));
	system("COLOR 7");
	system("cls");
	/*Bucle para actualizar los datos de los jugadores*/
	for(int i=0;(i<equipo[pos].num_jugadores)&&(i<E);i++){
		system("cls");
		printf("Ingrese los datos del jugador [%d]:\n",i+1);
		fflush(stdin);
		printf("Nombre:\n");
		fgets(equipo[pos].jugador[i].nombre,T,stdin);
	
		printf("Edad:\n");
		fflush(stdin);	
		scanf("%d",&equipo[pos].jugador[i].edad);
	
		printf("Estatura:\n");
		scanf("%f",&equipo[pos].jugador[i].estatura);
	
		printf("Numero del jugador:\n");
		scanf("%d",&equipo[pos].jugador[i].num_jugador);
	
		fflush(stdin);
		printf("Posicion:\n");
		fgets(equipo[pos].jugador[i].posicion,T,stdin);
	}
	printf("Registro actualizado exitosamente!! \n");
	printf("Numero de registro del equipo: %d\n",pos+1);	
}

void Borrar_Equipo(equipo* equipo,int *cont){
	int b,i;
	system("cls");
	if((*cont)==0)
		printf("No hay registros en el sistema");
	else{
		printf("Ingrese el registro a borrar\n");
		scanf("%d",&b);
		if((b<0)||(b==0)||(b>*(cont)))
				printf("\nOpcion  invalida");
			else{
				if(b==(*cont)){
					--(*cont);
					printf("Registro eliminado correctamente");
				}else{
					for(i=0;i<(*cont);i++){
						equipo[i]=equipo[i+1];
					}
					--(*cont);
					printf("Registro eliminado correctamente");
				}
		}
	}
}

void Disponibilidad(int pos){
	int disp=0;
	if(pos==M){
		printf("Ya no se puede inscribir ningun equipo, cupo lleno UnU");
	}else{
		printf("\nQuedan %d lugares disponibles para inscribirse\n",disp=M-pos);
	}
}
