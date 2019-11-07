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
  node *nNode =
      (node *)malloc(sizeof(node)); // Crear nodo temporal y asignar memoria
  nNode->coef = coef;               // Asignar coef a coef
  nNode->grd = grd;                 // Asignar el grado
  nNode->next = *head;              // Apuntar a head
  *head = nNode;                    // Igualaron head al nodo temporal.
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
    if (aux1->grd == aux2->grd) {
      aux1->coef = ((long)aux1->coef + (long)aux2->coef * suma);
      aux3 = aux1;
      aux1 = aux1->next;
      aux2 = aux2->next;
    } else {
      if (aux1->grd > aux2->grd) {
        aux3 = aux1;
        aux1 = aux1->next;
      } else {
        aux4 = (node *)malloc(sizeof(node));
        aux4->coef = aux2->coef * suma;
        aux4->grd = aux2->grd;
        aux4->next = aux1;
        if (aux3)
          aux3->next = aux4;
        else {
          aux3 = aux4;
          p1 = aux4;
        }
        aux3 = aux4;
        aux2 = aux2->next;
      }
    }
  }
  if (!aux1 && aux2) {
    if (!p1) {
      aux4 = (node *)malloc(sizeof(node));
      aux4->coef = aux2->coef * suma;
      aux4->grd = aux2->grd;
      aux4->next = NULL;
      p1 = aux4;
      aux3 = p1;
      aux2 = aux2->next;
    }
    if (p1) {
      while (aux2) {
        aux4 = (node *)malloc(sizeof(node));
        aux4->coef = aux2->coef * suma;
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
  for(i=0; i<= grd; i++){
    push(&final,0, i);
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

void splitPoly(node *head, node *split[2], long rango) {
  node *cdr = NULL;
  node *aux1 = NULL;
  node *aux2 = NULL;
  long corte;
  cdr = head;
  corte = rango;
  while (corte) { // Se avanza n/2 posiciones
    if(!aux1){
      push(&aux1, cdr->coef, cdr->grd);
      split[0] = aux1;
    }else{
      push(&aux1->next, cdr->coef, cdr->grd);
      aux1 = aux1->next;
    }
    cdr = cdr->next;
    corte--;
  }
  while (cdr) { // Se avanza n/2 posiciones
    if(!aux2){
      push(&aux2, cdr->coef, cdr->grd);
      split[1] = aux2;
    }else{
      push(&aux2->next, cdr->coef, cdr->grd);
      aux2 = aux2->next;
    }
    cdr = cdr->next;
    corte--;
  }
  return;
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

node *MultDivYConq0(node *p1, node *p2, long n, node* result) {
  node *cdr1[2];
  node *cdr2[2];
  node *aux = NULL;
  long k = n/2;
  long mayor = 0;
  printf("\nentre!\n");
  if(!result)
    printf("\nno funciona!\n");
  if (p1->next &&
      p2->next) { // Si existen ambas continuaciones se sigue con la recursión
    splitPoly(p1, cdr1, k); // cdr1[0] = A1(x) ; cdr1[1] = A0(x)
    display(&cdr1[0]);
    display(&cdr1[1]);
    splitPoly(p2, cdr2, k); // cdr2[0] = B1(x) ; cdr2[1] = B0(X)
    display(&cdr2[0]);
    display(&cdr2[1]);
    aux = MultDivYConq0(cdr1[0], cdr2[0], k, aux);
    display(&result);
    result = coefXPol( 1, n, aux, result);
    display(&result);
    if(cdr1[0]->grd + cdr2[1]->grd <= cdr1[1]->grd + cdr2[0]->grd){
      mayor = cdr1[1]->grd + cdr2[0]->grd;
    }else
      mayor = cdr1[0]->grd + cdr2[1]->grd;
		       result = coefXPol( 1, k, sumarPolinomios(MultDivYConq0(cdr1[0], cdr2[1], k, result), MultDivYConq0(cdr1[1], cdr2[0], k, result), 1), result);
    display(&result);
    result = sumarPolinomios(result, MultDivYConq0(cdr1[1], cdr2[1], k, result), 1);
    display(&result);
  } else {
    if(p1->next){
      printf("\np1 sigue\n");
      result = coefXPol(p2->coef, p2->grd, p1, result);
      display(&result);
    }else{
      printf("\np2 sigue o ambas no siguen\n");
      if(!result)
	printf("\nno funciona!\n");
      result = coefXPol(p1->coef, p1->grd, p2, result);
      display(&result);
    }
  }
  return result;
}

node *MultDivYConq(node *p1, node *p2, long n1, long n2) {
  node *cdr1[2];
  node *cdr2[2];
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *aux3 = NULL;
  node *result = polCoefC(p1->grd + p2->grd);
  long mayor = 0;
  if (p1->next &&
      p2->next) { // Si existen ambas continuaciones se sigue con la recursión
    splitPoly(p1, cdr1, n1/2);
    splitPoly(p2, cdr2, n2/2);
    result = RyC(cdr1[0], cdr2[0], result);
    result = RyC(cdr1[0], cdr2[1], result);
    result = RyC(cdr1[1], cdr2[0], result);
    result =RyC(cdr1[1], cdr2[1], result);
    
  return result;
  }else{
    result = RyC(p1, p2, result);
  }
}

void splitPolyK(node *head, node *split[2], long rango) {
  node *cdr = NULL;
  node *aux1 = NULL;
  node *aux2 = NULL;
  long corte;
  cdr = head;
  corte = rango;
  while (corte) { // Se avanza n/2 posiciones
    if(!aux1){
      push(&aux1, cdr->coef, cdr->grd- rango);
      split[0] = aux1;
    }else{
      push(&aux1->next, cdr->coef, cdr->grd - rango);
      aux1 = aux1->next;
    }
    cdr = cdr->next;
    corte--;
  }
  while (cdr) { // Se avanza n/2 posiciones
    if(!aux2){
      push(&aux2, cdr->coef, cdr->grd);
      split[1] = aux2;
    }else{
      push(&aux2->next, cdr->coef, cdr->grd);
      aux2 = aux2->next;
    }
    cdr = cdr->next;
    corte--;
  }
  return;
}

node* complete(node *p, long k){
  while(k){
    push(&p, 0, p->grd +1);
    k--;
  }
  return p;
}

node* elimSobrantes(node *p){
  node *aux = p;
  node *aux2 = NULL;
  while(aux && aux->coef == 0){
    aux2 = aux->next;
    free(aux);
    aux = aux2;
  }
  return aux;
}

node *karatsuba0(node *p1, node *p2, long l) {//Paso inductivo (recursivo) de karatsuba
  long k = 0;
  k = l / 2;
  node *cdr1[2];
  node *cdr2[2];
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *c1 = NULL;
  node *c2 = NULL;
  node *c3 = NULL;
  node *c4 = NULL;
  node *result = polCoefC(p1->grd + p2->grd);
  if(p1->next && p2->next){
    splitPolyK(p1, cdr1, k);//A(x)1*X^(2^(k-1)) && A(x)0
    splitPolyK(p2, cdr2, k);//B(x)1*X^(2^(k-1)) && B(x)0
    c1 = karatsuba0(cdr1[0], cdr2[0], k);//(A(x)1 * B(x)1)
    c2 = sumarPolinomios(c2, cdr1[0],1);
    c2 = sumarPolinomios(c2, cdr1[1],1);
    c3 = sumarPolinomios(c3, cdr2[0],1);
    c3 = sumarPolinomios(c3, cdr2[1],1);
    c4 = karatsuba0(c2, c3, k);//((A(x)1 + A(x)0)*(B(x)1 + B(x)0))
    result = karatsuba0(cdr1[1], cdr2[1], k);//(A(x)0 * B(x)0)
    c4 = sumarPolinomios(c4, c1, -1);
    c4 = sumarPolinomios(c4, result, -1);//((A(x)1 + A(x)0)*(B(x)1 + B(x)0)) - (A(x)1 * B(x)1) - (A(x)0 * B(x)0)
    aux1 = polCoefC(l + c1->grd);
    aux1 = coefXPol(1, l, c1, aux1);//(A(x)1 * B(x)1)^(2^k)
    aux2 = polCoefC(k  + c4->grd);
    aux2 = coefXPol(1, k, c4, aux2);//c4^(2^(k-1))
    result = sumarPolinomios(result, aux1, 1);
    result = sumarPolinomios(result, aux2, 1);
    return result;
  }else{
    return RyC(p1, p2, result);
  }
}



node *karatsuba(node *p1, node *p2, long l1, long l2) {//Primer paso de karatsuba
  long k = 0;
  long l = 0;
  long pow2[25] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
  node *cdr1[2];
  node *cdr2[2];
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *c1 = NULL;
  node *c2 = NULL;
  node *c3 = NULL;
  node *c4 = NULL;
  node *result = polCoefC(p1->grd + p2->grd - 1);
  if(l1 < l2){
    p1 = complete(p1, l2 - l1);
  }else if(l1 > l2){
    p2 = complete(p2, l1 - l2);
  }
  l = p1->grd +1;
  for(k = 0; k < 24 ; k++){
    if(p1->grd+1 > pow2[k] && p1->grd+1 < pow2[k+1]){
      p1 = complete(p1, (pow2[k+1] - (p1->grd +1)));
      p2 = complete(p2, (pow2[k+1] - (p2->grd +1)));
      l = pow2[k+1];
      break;
    }
  }
  k = l/2;
  if(p1->next && p2->next){
    splitPolyK(p1, cdr1, k);//A(x)1*X^(2^(k-1)) && A(x)0
    splitPolyK(p2, cdr2, k);//B(x)1*X^(2^(k-1)) && B(x)0
    c1 = karatsuba0(cdr1[0], cdr2[0], k);//(A(x)1 * B(x)1)
    c2 = sumarPolinomios(c2, cdr1[0],1);
    c2 = sumarPolinomios(c2, cdr1[1],1);
    c3 = sumarPolinomios(c3, cdr2[0],1);
    c3 = sumarPolinomios(c3, cdr2[1],1);
    c4 = karatsuba0(c2, c3, k);//((A(x)1 + A(x)0)*(B(x)1 + B(x)0))
    result = karatsuba0(cdr1[1], cdr2[1], k);//(A(x)0 * B(x)0)
    c4 = sumarPolinomios(c4, c1, -1);
    c4 = sumarPolinomios(c4, result, -1);//((A(x)1 + A(x)0)*(B(x)1 + B(x)0)) - (A(x)1 * B(x)1) - (A(x)0 * B(x)0)
    aux1 = polCoefC(l + c1->grd);
    aux1 = coefXPol(1, l, c1, aux1);//(A(x)1 * B(x)1)^(2^k)
    aux2 = polCoefC(k  + c4->grd);
    aux2 = coefXPol(1, k, c4, aux2);//c4^(2^(k-1))
    result = sumarPolinomios(result, aux1, 1);
    result = sumarPolinomios(result, aux2, 1);
    return elimSobrantes(result);
  }else{
    return elimSobrantes(RyC(p1, p2, result));
  }
}


int main() {
  node *P1 = NULL;
  node *P2 = NULL;
  node *P3 = NULL;
  long f = 4;
  P1 = generator(16384);
  P2 = generator(16384);/*
  push(&P1, 1, 0);
  push(&P1, 1, 1);
  push(&P1, 1, 2);
  push(&P1, 1, 3);
  push(&P2, 1, 0);
  push(&P2, 1, 1);
  push(&P2, 1, 2);
  push(&P2, 1, 3);*/
  P3 = karatsuba(P1, P2, P1->grd+1, P2->grd+1);
  //printf("\nkaratsuba:\n");
  display(&P3);
  P3 = eliminar(P3);
  return 0;
}
