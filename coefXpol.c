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
  node *aux;
  node *nNode = (node *)malloc(sizeof(node)); 
  nNode->coef = coef;              
  nNode->grd = grd;                 
  nNode->next=*head;
  *head=nNode;
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

node *polCoefC(long grd){
  int i=0;
  node *final=NULL;
  for(i=0; i<=grd; i++){
    push(&final, 0, i);
  }
  return final;
}
node *coefXPol(long coef, long grd, node *p, node *r){
  node *auxr=r;
  node *auxp=p;
  while(auxp){
    if(auxp->grd+grd==auxr->grd){
      auxr->coef= auxr->coef+ auxp->coef * coef;
      auxp=auxp->next;
      auxr=auxr->next;
    }else{
      auxr=auxr->next;
    }
  }
  return r;
}

node *RyC(node *p1, node *p2, node *r){
  node *aux1=NULL;
  aux1=p1;
  while(aux1->next){
    r=coefXPol(aux1->coef, aux1->grd, p2, r);
    aux1=aux1->next;
  }
  r=coefXPol(aux1->coef, aux1->grd, p2, r);
  return r;
}

int main(){
  node *P1=NULL;
  node *P2=NULL;
  node *P3=NULL;
  push(&P1, 1, 0);
  push(&P1, 1, 1);
  push(&P1, 1, 2);
  push(&P1, 1, 3);
  push(&P1, 1, 4);
  push(&P2, 1, 0);
  push(&P2, 1, 1);
  push(&P2, 1, 2);
  push(&P2, 1, 3);
  push(&P2, 1, 4);
  P3=RyC(P1, P2, polCoefC(P1->grd+P2->grd));
  display(&P3);
  return 0;
}
