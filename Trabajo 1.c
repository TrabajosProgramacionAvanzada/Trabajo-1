/*Programa en 64 bits:
  Programa para generar polinomios de grado n, o ingresarlos, y leerlos
  Compilador: GCC 9.1.0 
  Integrantes: 
  - Pedro Figueroa
  - Javier Gómez
  - Ignacio Sanhueza
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


typedef struct nodeP{
/*
	Estructura linked list que permite almacenar coeficiente y grado
	de un polinomio de la forma a(x)=(asub(n-1)*bsub(n-1))xexp(n-1)+A(x)
*/
	long coef; //Coeficiente
	long grd; //Grado
	struct nodeP *next; //Puntero de tipo nodeP que apunta al siguiente.
  //struct nodeP *parent;
}node;

void push(node **head, long coef, long grd){
	/*
		Inserta el elemento al inicio de la linkedList.
	*/
	node *nNode=malloc(sizeof(node)); //Crear nodo temporal y asignar memoria
	nNode->coef=coef; //Asignar coef a coef
	nNode->grd=grd; //Asignar el grado
	nNode->next=*head; //Apuntar a head
	*head=nNode; //Igualar head al nodo temporal.
}
void display(node **head){
	/*
		Funcion que muestra el polinomio
	*/
	node *temp; //Crear nodo temporal
	temp=*head; //Igualar el nodo temporal a nuestra head
	while(temp!=NULL){ //Mientras el nodo temporal sea distinto de NULL
		if(temp->coef>0 && temp->grd==0){ //Si el coeficiente es mayor que cero
			printf("%ldx%ld", temp->coef, temp->grd); //Imprime con un signo mas.
		}else if(temp->coef>0){ // Sino
			printf("+%ldx%ld", temp->coef, temp->grd); //Imprime con un signo menos.
		}else{
          printf("%ldx%ld", temp->coef, temp->grd);
        }
		temp=temp->next;//Mover al siguiente nodo en la lista.
	}
	printf("\n");
}
long coefGenerator(long lsup){
	/*
		Funcion que genera un coeficiente dentro del limite superior. Para poder tomar el limite inferior
		se utiliza un generador de numeros aleatorios; si sign es par, el numero es positivo, sino, el numero
		es negativo
	*/
	int sign=0;
	sign=rand();
	if(sign%2!=0){
		return (rand()%lsup)*-1;
	}
	return rand()%lsup;
	/*
		Incluimos esta funcion para facilitar las operaciones automaticas.
		Solo es necesario mantener un polinomio en memoria. El siguiente lo
		leemos ¿Paso por paso?, operando de forma inmediata con el monomio
		siguiente. (Aplicable a suma y resta)
	*/
}
node *generator(long grado){
	/*
		Funcion que devuelve una linkedList que contiene un polinomio de la forma
        a(x)=(asub(n-1)*bsub(n-1))xexp(n-1)+A(x)
	*/
	node *head=NULL; //Crear la lista
	long i=0; //Variable que itera en el for
	long lSup=pow(2,63); //Se define el limite superior de los coeficientes
	for(i=grado; i>=0; i--){ //Iterar desde el mayor al menor. para de esta manera tener la linkedlist en orden natural
		push(&head, coefGenerator(lSup), i); //Agragar el elemento iesimo a la linkedlist
	}
	return head; //Devolver la linkedList
}

//Función que pide cada coeficiente del polinomio de forma ordenada por el grado, de menor a mayor
node *ingresar_plinomio(long grds){
  node *head=NULL;
  long coef=0;
  long i=0;
  for(i=grds; i>=0; i--){//Se recorre desde el grado 0 al grado máximo dado "grds"
    scanf("%ld", &coef);//Se pide el coeficiente del polinomio
    if(coef!=0){
      push(&head, coef, i);//Luego se une a la lista
    }
  }
  return head;
}

//Función que elimina de la memoria la lista que contiene al polinomio
node *eliminar(node *head){
  node *copia = NULL;
  copia = head;//Se copia para mantener el puntero del próximo nodo
  while(head){
    copia = copia->next;//Se copia el siguiente
    free(head);//Se libera memoria
    head = copia;//Se pasa al siguiente nodo
  }
  return head;//Debe retornar NULL
}

//Función que despliega un menú para el usuario
void menu(node *head){
    int opcion=0;
    long grdo =0;
    do{

        printf("1. generar polinomio \n2. ingresar polinomio \n3. opcion leer polinomio  \n4. opcion sair\n");
        scanf("%d", &opcion);//Se guarda la opción ingresada
        switch(opcion){
        case 1:
            scanf("%ld",&grdo);
	    head=eliminar(head);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            break;
        case 2:
	    scanf("%ld", &grdo);
	    head=eliminar(head);//Paso análogo al "case 1"
            head=ingresar_plinomio(grdo);//Pide el polinomio al usuario
            break;
        case 3:
	  if(head)//Si la cabeza de la lista no es NULL
	    display(&head);//Se muestra
            else{
	      printf("\nDebe ingresar un polinomio o generarlo antes de leerlo!\n");
            }
	    break;
        case 4:
            break ;
	    head=eliminar(head);//Elimina la memoria antes de cerrar el programa
            break;
        default:
            printf("Ingrese una opcion valida\n");
            break;

        }

    }while(opcion != 4);

}


int main(){


  srand(time(NULL));//Se inicaliza la semilla de la función srand()
	node *head=NULL;
	menu(head);
	return 0;
}
