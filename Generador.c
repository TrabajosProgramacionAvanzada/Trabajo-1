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
} node;

void push(node **head, long coef, long grd) {
  /*
    Inserta el elemento al inicio de la linkedList.
  */
  node *nNode = (node *)malloc(sizeof(node)); // Crear nodo temporal y asignar memoria
  nNode->coef = coef;               // Asignar coef a coef
  nNode->grd = grd;                 // Asignar el grado
  nNode->next = *head; // Apuntar a head
  *head = nNode;       // Igualaron head al nodo temporal.

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

node *sumarPolinomios(node *p1, node *p2) {
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *aux3 = NULL;
  node *aux4 = NULL;
  aux1 = p1;
  aux2 = p2;
  aux3 = NULL;
  while (aux1 && aux2) {
    if(aux1->grd == aux2->grd){
      aux1->coef = ((long)aux1->coef + (long)aux2->coef);
      aux3 = aux1;
      aux1 = aux1->next;
      aux2 = aux2->next;
    }else{
      if(aux1->grd > aux2->grd){
  aux3 = aux1;
  aux1 = aux1->next;
      }else{
  aux4 = (node *)malloc(sizeof(node));
  aux4->coef = aux2->coef;
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
      aux4->coef = aux2->coef;
      aux4->grd = aux2->grd;
      aux4->next = NULL;
      p1 = aux4;
      aux3 = p1;
      aux2 = aux2->next;
    }
    if(p1){
      while(aux2){
  aux4 = (node *)malloc(sizeof(node));
  aux4->coef = aux2->coef;
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

node *split(node *P, long k, node **car){
  int i=0;
  long c=0;
  node *aux1=NULL;
  node *fN=NULL;
  node *aux2=NULL;
  c=((P->grd)+1)/2;
  aux1=P;
  for(i=0; i<k; i++){
    if(i==0){
      push(car, aux1->coef, aux1->grd-c);
      aux2=*car;
    }else{
      push(&aux2->next, aux1->coef, aux1->grd-c);
      aux2=aux2->next;
    }
    aux1=aux1->next;
  }
  fN=aux1;
  return fN;
}

node *split2(node *P, long k, node **car){
  int i=0;
  long c=0;
  node *aux1=NULL;
  node *fN=NULL;
  node *aux2=NULL;
  c=((P->grd)+1)/2;
  aux1=P;
  for(i=0; i>c; i++){
    if(i==0){
      push(car, aux1->coef, aux1->grd);
      aux2=*car;
    }else{
      push(&aux2->next, aux1->coef, aux1->grd);
      aux2=aux2->next;
    }
    aux1=aux1->next;
  }
  fN=aux1;
  return fN;
}

node * diferencia(node *p1, node *p2){
  node *aux1=p1;
  node *aux2=p2;
  while(aux1 && aux2){
    if(aux1->grd==aux2->grd){
      aux1->coef=aux1->coef - aux2->coef;
      aux1=aux1->next;
      aux2=aux2->next;
    }else if(aux1->grd>aux2->grd){
      aux1=aux1->next;
    }
  }
  return aux1;
}

node *karatsuba1(node *p1, node *p2, long l){
  long k=0;
  k=l/2;
  node *car1=NULL;
  node *car2=NULL;
  node *c0=NULL;
  node *c1=NULL;
  node *c2=NULL;
  node *cdr1=NULL;
  node *cdr2=NULL;
  if(p1->next && p2->next){
    cdr1=split(p1, k, &car1);
    cdr2=split(p2, k, &car2);
  }
  if(k>4){
    c0=MultpPol(cdr1, cdr2, NULL);
    c2=karatsuba(split2(p1,k, NULL),split2( p2, k, NULL ));
    c3=sumarPolinomios()
    c1=diferencia(karatsuba(diferencia(p1, cdr1), diferencia(p2, cdr2), k), diferencia(c2, c0)); 
  }else{
    return MultpPol(p1, p2, NULL);
  }
  return sumarPolinomios(sumarPolinomios(c1, c2), c0);
}




int main(){
  node *P1=NULL;
  node *P2=NULL;
  node *P3=NULL;
  node *car1=NULL;
  node *cdr1=NULL;
  node *car2=NULL;
  node *cdr2=NULL;
  long f=8;
  P1=generator(f);
  P2=generator(f);
  P3=karatsuba(P1, P2, f);
  display(&P3);
  return 0;
}
