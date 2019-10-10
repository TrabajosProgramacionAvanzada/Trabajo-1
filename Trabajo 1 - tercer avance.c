#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodeP {
  /*
    Estructura linked list que permite almacenar coeficiente y grado
    de un polinomio de la forma a(x)=(asub(n-1)+A(x))
  */
  long coef;          // Coeficiente
  long grd;           // Grado
  struct nodeP *next; // Puntero de tipo nodeP que apunta al siguiente.
  // struct nodeP *parent; //Puntero de tipo nodeP que apunta al anterior
  // struct nodeP *last_member; //Puntero que apunta al último si y sólo si es
  // la cabeza de la lista
} node;

void push(node **head, long coef, long grd) {
  /*
    Inserta el elemento al inicio de la linkedList.
  */
  node *nNode =
    (node *)malloc(sizeof(node)); // Crear nodo temporal y asignar memoria
  nNode->coef = coef;               // Asignar coef a coef
  nNode->grd = grd;                 // Asignar el grado
  nNode->next = *head; // Apuntar a head
  *head = nNode;       // Igualaron head al nodo temporal.
}

// FunciÃ³n que elimina de la memoria la lista que contiene al polinomio
node *eliminar(node *head) {
  node *copia = NULL;
  copia = head; // Se copia para mantener el puntero del prÃ³ximo nodo
  while (head) {
    copia = copia->next; // Se copia el siguiente
    free(head);          // Se libera memoria
    head = copia;        // Se pasa al siguiente nodo
  }
  return head; // Debe retornar NULL
}

// Funcion copia de polinomios
node *copy(node *P1) {
  node *copia = NULL;
  while (P1 != NULL) {
    push(&copia, P1->coef, P1->grd);
    P1 = P1->next;
  }
  return copia;
}

void display(node **head) {
  /*
    Funcion que muestra el polinomio
  */
  node *temp;           // Crear nodo temporal
  temp = *head;         // Igualar el nodo temporal a nuestra head
  if (temp->coef > 0) { // Si el coeficiente es mayor que cero
    printf("%ld x^%ld ", temp->coef, temp->grd); // Imprime con un signo mas.
  } else if (temp->coef < 0) {                   // Sino
    printf("- %ld x^%ld ", temp->coef * -1,
           temp->grd); // Imprime con un signo menos.
  }
  temp = temp->next;
  // Mostramos el primer elemento antes del bucle para evitar el signo positivo
  // de haber
  while (temp != NULL) {  // Mientras el nodo temporal sea distinto de NULL
    if (temp->coef > 0) { // Si el coeficiente es mayor que cero
      if (temp->grd == 0) {
        printf("+ %ld ", temp->coef);
        temp = temp->next; // Mover al siguiente nodo en la lista.
        continue;
      }
      printf("+ %ld x^%ld ", temp->coef, temp->grd); // Imprime con un signo mas
    } else {
      if (temp->grd == 0) {
        printf("- %ld ", temp->coef * -1);
        temp = temp->next; // Mover al siguiente nodo en la lista.
        continue;
      }
      printf("- %ld x^%ld ", temp->coef * -1, temp->grd);
    }
    temp = temp->next; // Mover al siguiente nodo en la lista.
  }
  printf("\n");
}

long coefGenerator(long lsup) {
  /*
    Funcion que genera un coeficiente dentro del limite superior. Para
    poder tomar el limite inferior se utiliza un generador de numeros
    aleatorios; si sign es par, el numero es positivo, sino, el numero es
    negativo
  */
  int sign = 0;
  sign = rand();
  if (sign % 2 != 0) {
    return (rand() % lsup) * -1;
  }
  return rand() % lsup;
  /*
    Incluimos esta funcion para facilitar las operaciones automaticas.
    Solo es necesario mantener un polinomio en memoria. El siguiente lo
    leemos Â¿Paso por paso?, operando de forma inmediata con el monomio
    siguiente. (Aplicable a suma y resta)
  */
}
node *generator(long grado) {
  /*
    Funcion que devuelve una linkedList que contiene un polinomio de la
    forma a(x)=(asub(n-1)*bsub(n-1))xexp(n-1)+A(x)
  */
  node *head = NULL; // Crear la lista
  long i = 0;        // Variable que itera en el for
  long long lSup = (long long int)pow(
      2, 63); // Se define el limite superior de los coeficientes
  for (i = 0; i < grado; i++) { // Iterar desde el mayor al menor. para de esta
                                // manera tener la linkedlist en orden natural
    push(&head, coefGenerator(lSup),
         i); // Agragar el elemento iesimo a la linkedlist
  }
  return head; // Devolver la linkedList
}

// FunciÃ³n que pide cada coeficiente del polinomio de forma ordenada por el
// grado, de menor a mayor
node *ingresar_plinomio(long grds) {
  node *head = NULL;
  long coef = 0;
  long i = 0;
  for (i = grds - 1; i >= 0;
       i--) { // Se recorre desde el grado 0 al grado mÃ¡ximo dado "grds"
    scanf("%ld", &coef); // Se pide el coeficiente del polinomio
    if (coef != 0) {
      push(&head, coef, i); // Luego se une a la lista
    }
  }
  return head;
}

// Funcion que suma dos polinomios
node *sumarPolinomios(node *p1, node *p2, int suma) {
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *aux3 = NULL;
  node *aux4 = NULL;
  aux1 = p1;
  aux2 = p2;
  aux3 = NULL;
  while (aux1 && aux2) {
    if(aux1->grd == aux2->grd){
      aux1->coef = ((long)aux1->coef + (long)aux2->coef*suma);
      aux3 = aux1;
      aux1 = aux1->next;
      aux2 = aux2->next;
    }else{
      if(aux1->grd > aux2->grd){
	aux3 = aux1;
	aux1 = aux1->next;
      }else{
	aux4 = (node *)malloc(sizeof(node));
	aux4->coef = aux2->coef*suma;
	aux4->grd = aux2->grd;
	aux4->next = aux1;
	if (aux3)
	  aux3->next = aux4;
	else{
	  aux3 = aux4;
	  p1 = aux4;
	}
	aux3 = aux4;
	aux2 = aux2->next;
      }
    }
  }
  if(!aux1 && aux2){
    if(!p1){
      aux4 = (node *)malloc(sizeof(node));
      aux4->coef = aux2->coef*suma;
      aux4->grd = aux2->grd;
      aux4->next = NULL;
      p1 = aux4;
      aux3 = p1;
      aux2 = aux2->next;
    }
    if(p1){
      while(aux2){
	aux4 = (node *)malloc(sizeof(node));
	aux4->coef = aux2->coef*suma;
	aux4->grd = aux2->grd;
	aux4->next = NULL;
	aux3->next = aux4;
	aux3 = aux4;
	aux2 = aux2->next;
      }
    }
  }
  return p1;
}

node *CoefXPol(long coef, long grd, node *p2, node *cdr) {
  node *aux = NULL;
  node *auxP = NULL;
  node *head = NULL;
  auxP = p2;
  if (cdr != NULL) { // Si cdr no está vacío se actualizan los valores
    aux = cdr;
    while (auxP != NULL && aux != NULL) {
      aux->coef = aux->coef + auxP->coef * coef; // Actualizando
      auxP = auxP->next;
      aux = aux->next;
    }
  }
  if (cdr == NULL) { // Si aún quedan valores y cdr terminó, o cdr estaba vacío
    while (auxP != NULL) {
      if (head == NULL) { // Si no hay nodo anterior guardado
        cdr = (node *)malloc(
            sizeof(node)); // Se guarda el primer resultado en cdr como cabeza
        cdr->coef = coef * auxP->coef;
        cdr->grd = grd + auxP->grd;
        cdr->next = NULL;
        aux = cdr;  // Se copia para avanzar sin perder la cabeza
        head = aux; // Se copia para mantener un respaldo del nodo anterior al
                    // avanzar
        aux = aux->next;
        auxP = auxP->next;
      } else {                              // De lo contrario
        aux = (node *)malloc(sizeof(node)); // Se crea el nuevo resultado
        aux->coef = coef * auxP->coef;
        aux->grd = grd + auxP->grd;
        aux->next = NULL;
        head->next = aux; // Se dirige el nodo anterior al actual
        head = aux;       // Se copia el nodo actual y se pasa al siguiente
        aux = aux->next;
        auxP = auxP->next;
      }
    }
  }
  return cdr;
}

node *multiplicarPolinomioFBrut(node *p1, node *p2) { // Función a fuerza bruta
  node *cP1 = NULL;
  node * aux = NULL;
  node *rMult = NULL;
  cP1 = p1;
  while(cP1){
    aux = CoefXPol(cP1->coef, cP1->grd, p2, aux);
    rMult = sumarPolinomios(rMult, aux, 1);
    aux = eliminar(aux);
    cP1 = cP1->next;
  }
  return rMult;
}


node *MultpPol(node *p1, node *p2, node *cdr) {
  node *car = NULL;
  if (cdr == NULL) { // Si el resultado está vacío, es la primera iteración
    car = (node *)malloc(sizeof(node)); // Se define y guarda el primer elemento
    car->coef = p1->coef * p2->coef;
    car->grd = p1->grd + p2->grd;
    car->next = NULL;
    if (p2->next) { // Si el polinomio 2 sigue, se multiplica por el primer
                    // termino del primer polinomio
      car->next = CoefXPol(p1->coef, p1->grd, p2->next, car->next);
    }
    if (p1->next) { // Si el polinomio 1 sigue, se multiplica por el primer
                    // termino del segundo polinomio
      car->next = CoefXPol(p2->coef, p2->grd, p1->next, cdr);
    }
    if (p1->next && p2->next) { // Si ambos continuan sigue la recurción
      car->next = MultpPol(p1->next, p2, car->next);
    }
    return car; // Se devuelve el primer elemento
  } else {      // De lo contrario//
    cdr->coef =
        cdr->coef +
        (p1->coef * p2->coef); // Se actualiza el primer elemento del resutlado
    if (p2->next) { // Si el polinomio 2 sigue, se multiplica por el primer
                    // termino del primer polinomio
      cdr->next = CoefXPol(p1->coef, p1->grd, p2->next, cdr->next);
    }
    if (p1->next) { // Si el polinomio 1 sigue, se multiplica por el primer
                    // termino del segundo polinomio
      cdr->next = CoefXPol(p1->coef, p1->grd, p1->next, cdr->next);
    }
    if (p1->next && p2->next) { // Si ambos continuan sigue la recurción
      cdr->next = MultpPol(p1->next, p2, cdr->next);
    }
    return cdr; // Se devuelve el resultado
  }
}

void splitPoly(node *head, node*split[2], long largo) {
  node *cdr = NULL;
  node *aux = NULL;
  if(largo == 1){
    return;
  }
  long corte = largo/2;
  cdr = head;
  while (corte && cdr) {//Se avanza n/2 posiciones
    aux = cdr;
    cdr = cdr->next;
    corte--;
  }
  split[0] = aux;//Posición (n/2)-1
  split[1] = cdr;//Posición n/2
  split[0]->next = NULL;
  return;
}


node *MultDivYConq0(node *p1, node *p2, long largo1, long largo2){
  node *cdr1[2];
  node *cdr2[2];
  node *aux = NULL;
  node *result = NULL;
  if (p1->next &&
      p2->next) { // Si existen ambas continuaciones se sigue con la recursión
    splitPoly(p1, cdr1, largo1);//p1 = A1(x) ; cdr1 = A0(x)*x^2
    splitPoly(p2, cdr2, largo2);//p2 = B1(x) ; cdr2 = B0(X)*x^2
    largo1 = largo1/2;
    largo2 = largo2/2;
    aux = MultDivYConq0(p1,p2,largo1,largo2);
    result = MultDivYConq0(p1, cdr2[1], largo1, largo2);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    aux = MultDivYConq0(p2, cdr1[1], largo2, largo1);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    aux = MultDivYConq0(cdr1[1], cdr2[1], largo1, largo2);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    cdr1[0]->next = cdr1[1];
    cdr2[0]->next = cdr2[1];
  }else{
    if(p1->next && !p2->next){
      result = CoefXPol(p2->coef, p2->grd, p1, result);
    }else{
      result = CoefXPol(p1->coef, p1->grd, p2, result);
    }
  }
  return result;
}


node *MultDivYConq(node *p1, node *p2){
  node *cdr1[2];
  node *cdr2[2];
  node *aux = NULL;
  node *result = NULL;
  if (p1->next &&
      p2->next) { // Si existen ambas continuaciones se sigue con la recursión
    splitPoly(p1, cdr1, p1->grd+1);//p1 = A1(x) ; cdr1 = A0(x)*x^2
    splitPoly(p2, cdr2, p2->grd+1);//p2 = B1(x) ; cdr2 = B0(X)*x^2
    aux = MultDivYConq0(p1,p2,(p1->grd+1)/2,(p2->grd+1)/2);
    result = MultDivYConq0(p1, cdr2[1], (p1->grd+1)/2, (p2->grd+1)/2);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    aux = MultDivYConq0(p2, cdr1[1], (p2->grd+1)/2, (p1->grd+1)/2);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    aux = MultDivYConq0(cdr2[1], cdr1[1], (p2->grd+1)/2, (p1->grd+1)/2);
    result = sumarPolinomios(result, aux,1);
    aux = eliminar(aux);
    cdr1[0]->next = cdr1[1];
    cdr2[0]->next = cdr2[1];
  }else{
    if(p1->next){
      result = CoefXPol(p2->coef, p2->grd, p1, result);
    }else{
      result = CoefXPol(p1->coef, p1->grd, p2, result);
    }
  }
  return result;
}



node *karatsuba(node *p1, node *p2){//Un sólo paso
  //A(x)*B(x)= (z1 + z2 + (z3 * z4 - z1 -z2))
  node *result = NULL;
  node *cdr1[3];//a1(x)||a0(x)
  node *cdr2[3];//b1(x)||b0(x)
  node *z1 = NULL;//a1(x)*b1(x)
  node *z2 = NULL;//a0(x)*b0(x)
  node *z3 = NULL;//a0(x)+b1(x)
  node *z4 = NULL;//a1(x)*b0(x)
  splitPoly(p1, cdr1, p1->grd+1);
  splitPoly(p2, cdr2, p2->grd+1);
  z1 = MultpPol(p1, p2, z1);
  z2 = MultpPol(cdr1[1], cdr2[1], z2);
  z3 = sumarPolinomios(z3, p1,1);
  z3 = sumarPolinomios(z3, cdr2[1],1);
  z4 = MultpPol(cdr1[1], p2, z4);
  result = sumarPolinomios(result, z1,1);
  result = sumarPolinomios(result, z2,1);
  z3 = sumarPolinomios(z3, z4,1);
  z3 = sumarPolinomios(z3, z1,-1);
  z3 = sumarPolinomios(z3, z2,-1);
  result = sumarPolinomios(result, z3, 1);
  return result;
}


// FunciÃ³n que despliega un menÃº para el usuario

void menu(node *head1, node *head2) {
  int opcion = 0;
  long grdo1 = 0;
  long grdo2 = 0;
  node *aux = NULL;
  do {

    printf("\n1. sumar dos polinomios generados \n2. restar dos polinomios "
           "generados \n3. copiar un polinomio ingresado\n4. multiplicar dos "
           "polinomios generados reducir y conquistar  \n5. multiplicar dos "
           "polinomios generados Fuerza Bruta \n6. Opcion salir.\n");
    scanf("%d", &opcion); // Se guarda la opción ingresada
    switch (opcion) {
    case 1:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(grdo1); // Genera un polinomio de grado n con
                                // coeficientes aleatorios
      head2 = generator(grdo2);
      /*  printf("\nEl primer polinomio generado:\n\n");
           display(&head1);
           printf("\nEl segundo polinomio generado:\n\n");
           display(&head2);
           printf("\n+--------------------------------------------------------------"
                  "--------\n\n");
        */
      head1 = sumarPolinomios(head1, head2, 1);
      display(&head1);
      head1 = eliminar(head1);
      head2 = eliminar(head2);
      break;
    case 2:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(grdo1); // Genera un polinomio de grado n con
                                // coeficientes aleatorios
      head2 = generator(grdo2);
      /*printf("\nEl primer polinomio generado:\n\n");
    display(&head1);
    printf("\nEl segundo polinomio generado:\n\n");
    display(&head2);
    printf("\n-  "
           "-----------------------------------------------------------------"
           "-----\n\n");*/
      head1 = sumarPolinomios(head1, head2,-1);
      head2 = eliminar(head2);
      display(&head1);
      head1 = eliminar(head1);
      break;
    case 3:
      printf("\nIngrese el grado maximo del polinomio: ");
      scanf("%ld", &grdo1);
      head1 = eliminar(head1); // Paso anÃ¡logo al "case 1"
      head2 = eliminar(head2);
      aux = eliminar(aux);
      head1 = ingresar_plinomio(grdo1); // Pide el polinomio al usuario
      head2 = copy(head1);
      // printf("\nEl polinomio ingresado:\n");
      // display(&head1);
      printf("\nEl polinomio copiado:\n");
      display(&head2);
      break;
    case 4:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(grdo1); // Genera un polinomio de grado n con
                                // coeficientes aleatorios
      head2 = generator(grdo2);
      // printf("\nEl primer polinomio generado:\n\n");
      // display(&head1);
      // printf("\nEl segundo polinomio generado:\n\n");
      // display(&head2);
      // printf("\nx  "
      //     "-----------------------------------------------------------------"
      //   "-----\n\n");
      aux = MultpPol(head1, head2, aux);
      display(&aux);
      head1 = eliminar(head1);
      head2 = eliminar(head2);
      aux = eliminar(aux);
      break;
    case 5:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(grdo1); // Genera un polinomio de grado n con
                                // coeficientes aleatorios
      head2 = generator(grdo2);
      /*printf("\nEl primer polinomio generado:\n\n");
           display(&head1);
           printf("\nEl segundo polinomio generado:\n\n");
           display(&head2);
           printf("\nx  "
                  "-----------------------------------------------------------------"
                  "-----\n\n");
           */
      aux = multiplicarPolinomioFBrut(head1, head2);
      head1 = eliminar(head1);
      head2 = eliminar(head2);
      display(&aux);
      aux = eliminar(aux);
      break;
    case 6:
      head1 = eliminar(head1); // Elimina la memoria antes de cerrar el programa
      head2 = eliminar(head2);
      aux = eliminar(aux);
      break;
    default:
      printf("Ingrese una opcion valida\n");
      break;
    }

  } while (opcion != 6);
}

int main() {
  srand(time(NULL)); // Se inicaliza la semilla de la funciÃ³n srand()
  node *head1 = NULL;
  node *head2 = NULL;
  node *P = NULL;
  head1 = generator(8192);
  head2 = generator(8192);  /*
  push(&head1, 1, 0);
  push(&head1, 1, 1);
  push(&head1, 1, 2);
  push(&head1, 1, 3);
  push(&head2, 1, 0);
  push(&head2, 1, 1);
  push(&head2, 1, 2);
  push(&head2, 1, 3);
  display(&head1);
  display(&head2);*/
  P = MultDivYConq(head1, head2);
  display(&P);
  P = eliminar(P);
  //P = karatsuba(head1, head2);
  //display(&P);
  //P = eliminar(P);
  head2 = eliminar(head2);
  head1 = eliminar(head1);
  // menu(head1, head2);
  return 0;
}
