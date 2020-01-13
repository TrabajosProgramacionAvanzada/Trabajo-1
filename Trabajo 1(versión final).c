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
  nNode->next = *head;              // Apuntar a head
  *head = nNode;                    // Igualaron head al nodo temporal.
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
    if(temp->coef != 0){
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

node *polCoefC(long grd) {
  int i = 0;
  node *final = NULL;
  for (i = 0; i <= grd; i++) {
    push(&final, 0, i);
  }
  return final;
}

node *coefXPol(long coef, long grd, node *p, node *r) {
  node *auxr = r;
  node *auxp = p;
  while (auxp) {
    if (auxp->grd + grd == auxr->grd) {
      auxr->coef = auxr->coef + auxp->coef * coef;
      auxp = auxp->next;
      auxr = auxr->next;
    } else {
      while (auxp->grd + grd != auxr->grd) {
        auxr = auxr->next;
      }
    }
  }
  return r;
}

// Función que multiplica polinomios por medio del método reducir y conquistar
node *RyC(node *p1, node *p2, node *r) {
  node *aux1 = NULL;
  aux1 = p1;
  while (aux1) { // Mientras siga existiendo el primer polinomio
    r = coefXPol(aux1->coef, aux1->grd, p2,
                 r); // Se actualiza el resultado sumando la multiplicación del
                     // término mayor con el segundo polinomio
    aux1 = aux1->next; // Se mueve sólo el primer polinomio
  }
  return r;
}

node *multiplicarPolinomioFBrut(node *p1, node *p2) { // Función a fuerza bruta
  node *cP1 = NULL;
  node *aux = NULL;
  cP1 = p1;
  aux = polCoefC(
      p1->grd +
      p2->grd); // Se crea un polinomio vacío de tamaño igual al resultado
  while (cP1) {
    aux = coefXPol(cP1->coef, cP1->grd, p2,
                   aux); // Se avanza con uno y se actualiza el resultado
    cP1 = cP1->next;
  }
  return aux;
}

void splitPoly(node *head, node *split[2], long rango) {
  node *cdr = NULL;
  node *aux1 = NULL;
  node *aux2 = NULL;
  long corte;
  cdr = head;
  corte = rango;  // rango = cantidad de nodos a avanzar
  while (corte) { // Se avanza n/2 posiciones
    if (!aux1) {
      push(&aux1, cdr->coef,
           cdr->grd); // Se guarda la primera mitad en split[0] = A(x)1
      split[0] = aux1;
    } else {
      push(&aux1->next, cdr->coef,
           cdr->grd); // Continua guardando en orden inverso al push (aux1->next
                      // = NULL)
      aux1 = aux1->next;
    }
    cdr = cdr->next;
    corte--;
  }
  while (cdr) { // Se guarda la segunda mitad en split[1] = A(x)0
    if (!aux2) {
      push(&aux2, cdr->coef, cdr->grd);
      split[1] = aux2;
    } else {
      push(&aux2->next, cdr->coef, cdr->grd);
      aux2 = aux2->next;
    }
    cdr = cdr->next;
  }
  return;
}

// Función para multiplicar polinomios por medio de un paso del método dividir y
// conquistar
node *MultDivYConq(node *p1, node *p2, long n1, long n2) {
  node *cdr1[2];
  node *cdr2[2];
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *aux3 = NULL;
  node *result = polCoefC(p1->grd + p2->grd);
  long mayor = 0;
  if (p1->next && p2->next) {    // Si existen ambas continuaciones se sigue
    splitPoly(p1, cdr1, n1 / 2); // Se parten a la mitad los polinomios
    splitPoly(p2, cdr2, n2 / 2);
    result = RyC(cdr1[0], cdr2[0],
                 result); // Se actualiza el primer resultado A(x)1 * B(x)1
    result = RyC(cdr1[0], cdr2[1], result); // A(x)1 * B(x)0
    result = RyC(cdr1[1], cdr2[0], result); // A(x)0 * B(x)1
    result = RyC(cdr1[1], cdr2[1], result); // A(x)0 * B(x)0
    return result;
  } else {
    result =
        RyC(p1, p2,
            result); // De lo contrario se usa directamente reducir y conquistar
  }
}

void splitPolyK(node *head, node *split[2],
            long rango) { // Es igual a splitPoly(), solo que reduce la mitad
                          // mayor en sus grados
  node *cdr = NULL;
  node *aux1 = NULL;
  node *aux2 = NULL;
  long corte;
  cdr = head;
  corte = rango;
  while (corte) {
    if (!aux1) {
      push(&aux1, cdr->coef, cdr->grd - rango);
      split[0] = aux1;
    } else {
      push(&aux1->next, cdr->coef, cdr->grd - rango);
      aux1 = aux1->next;
    }
    cdr = cdr->next;
    corte--;
  }
  while (cdr) {
    if (!aux2) {
      push(&aux2, cdr->coef, cdr->grd);
      split[1] = aux2;
    } else {
      push(&aux2->next, cdr->coef, cdr->grd);
      aux2 = aux2->next;
    }
    cdr = cdr->next;
  }
  return;
}

node *complete(node *p, long k) {
  while (k) {
    push(&p, 0, p->grd + 1);
    k--;
  }
  return p;
}

node *elimSobrantes(node *p) {
  node *aux = p;
  node *aux2 = NULL;
  while (aux && aux->coef == 0) {
    aux2 = aux->next;
    free(aux);
    aux = aux2;
  }
  return aux;
}


node *karatsuba0(node *p1, node *p2, long l,
                 node *result) { // Paso inductivo (recursivo) de karatsuba
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
  if (p1->next && p2->next) {
    splitPolyK(p1, cdr1, k); // A(x)1*X^(2^(k-1)) && A(x)0
    splitPolyK(p2, cdr2, k); // B(x)1*X^(2^(k-1)) && B(x)0
    c1 = polCoefC(k);
    c1 = karatsuba0(cdr1[0], cdr2[0], k, c1); //(A(x)1 * B(x)1)
    c2 = sumarPolinomios(c2, cdr1[0], 1);
    c2 = sumarPolinomios(c2, cdr1[1], 1);
    c3 = sumarPolinomios(c3, cdr2[0], 1);
    c3 = sumarPolinomios(c3, cdr2[1], 1);
    c4 = polCoefC(k);
    c4 = karatsuba0(c2, c3, k, c4); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0))
    result = karatsuba0(cdr1[1], cdr2[1], k, result); //(A(x)0 * B(x)0)
    c4 = sumarPolinomios(c4, c1, -1);
    c4 = sumarPolinomios(c4, result, -1); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0)) -
                                          //(A(x)1 * B(x)1) - (A(x)0 * B(x)0)
    aux1 = polCoefC(l + c1->grd);
    aux1 = coefXPol(1, l, c1, aux1); //(A(x)1 * B(x)1)^(2^k)
    aux2 = polCoefC(k + c4->grd);
    aux2 = coefXPol(1, k, c4, aux2); // c4^(2^(k-1))
    result = sumarPolinomios(result, aux1, 1);
    result = sumarPolinomios(result, aux2, 1);
    c1 = eliminar(c1);
    c2 = eliminar(c2);
    c3 = eliminar(c3);
    c4 = eliminar(c4);
    aux1 = eliminar(aux1);
    aux2 = eliminar(aux2);
    cdr1[0] = eliminar(cdr1[0]);
    cdr1[1] = eliminar(cdr1[1]);
    cdr2[0] = eliminar(cdr2[0]);
    cdr2[1] = eliminar(cdr2[1]);
    return result;
  } else {
    return RyC(p1, p2, result);
  }
}

void cutin(node *cut[2], long long int rango){//Corta un polinomio en dos partes tales que la primera tenga n términos
  long long int c = rango;
  node *aux = NULL;
  cut[0] = cut[1];
  while(c != 0 && cut[1]){//avanza n posiciones
    aux = cut[1];
    cut[1] = cut[1]->next;
    c--;
  }
  aux->next = NULL;//corta el enlaze entre el último término de cut[0] con el primero de cut[1]
  return;
}

node *Karatsuba(node *p1, node *p2, long l1, long l2,
                int def) { // Primer paso de karatsuba
  long k = 0;
  long l = 0;
  long pow2[25] = {1,       2,       4,       8,       16,     32,     64,
                   128,     256,     512,     1024,    2048,   4096,   8192,
                   16384,   32768,   65536,   131072,  262144, 524288, 1048576,
                   2097152, 4194304, 8388608, 16777216};
  node *cdr1[2];
  node *cdr2[2];
  node *aux1 = NULL;
  node *aux2 = NULL;
  node *aux3[2];
  node *aux4[2];
  node *c1 = NULL;
  node *c2 = NULL;
  node *c3 = NULL;
  node *c4 = NULL;
  node *result = polCoefC(p1->grd + p2->grd);
  if (l1 < l2) {
    p1 = complete(p1, l2 - l1);
  } else if (l1 > l2) {
    p2 = complete(p2, l1 - l2);
  }
  l = p1->grd + 1;
  for (k = 0; k < 24; k++) {
    if (p1->grd + 1 > pow2[k] && p1->grd + 1 < pow2[k + 1]) {//Caso en el que el largo de uno de los polinomios no sea una potencia de dos
      return RyC(p1, p2, result); //Ocupamos reducir y conquistar. uwu
    }
  }
  k = l / 2;
  if (p1->next && p2->next &&
      def != 0 && l >= 1500) {            // Caso para el paso inductivo de Karatsuba
    splitPolyK(p1, cdr1, k); // A(x)1*X^(2^(k-1)) && A(x)0
    splitPolyK(p2, cdr2, k); // B(x)1*X^(2^(k-1)) && B(x)0
    c1 = polCoefC(k);
    c1 = karatsuba0(cdr1[0], cdr2[0], k, c1); //(A(x)1 * B(x)1)
    c2 = sumarPolinomios(c2, cdr1[0], 1);
    c2 = sumarPolinomios(c2, cdr1[1], 1);
    c3 = sumarPolinomios(c3, cdr2[0], 1);
    c3 = sumarPolinomios(c3, cdr2[1], 1);
    c4 = polCoefC(k);
    c4 = karatsuba0(c2, c3, k, c4); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0))
    result = karatsuba0(cdr1[1], cdr2[1], k, result); //(A(x)0 * B(x)0)
    c4 = sumarPolinomios(c4, c1, -1);
    c4 = sumarPolinomios(c4, result, -1); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0)) -
                                          //(A(x)1 * B(x)1) - (A(x)0 * B(x)0)
    aux1 = polCoefC(l + c1->grd);
    aux1 = coefXPol(1, l, c1, aux1); //(A(x)1 * B(x)1)^(2^k)
    aux2 = polCoefC(k + c4->grd);
    aux2 = coefXPol(1, k, c4, aux2); // c4^(2^(k-1))
    result = sumarPolinomios(result, aux1, 1);
    result = sumarPolinomios(result, aux2, 1);
    c1 = eliminar(c1);
    c2 = eliminar(c2);
    c3 = eliminar(c3);
    c4 = eliminar(c4);
    aux1 = eliminar(aux1);
    aux2 = eliminar(aux2);
    cdr1[0] = eliminar(cdr1[0]);
    cdr1[1] = eliminar(cdr1[1]);
    cdr2[0] = eliminar(cdr2[0]);
    cdr2[1] = eliminar(cdr2[1]);
    return elimSobrantes(result);

  } else { // Caso si el largo debe ser pasado por reducir y conquistar o es sólo un paso de karatsuba
    if (p1->next && p2->next && def == 0) {// Caso solo para primer paso de karatsuba
      splitPolyK(p1, cdr1, k); // A(x)1*X^(2^(k-1)) && A(x)0
      splitPolyK(p2, cdr2, k); // B(x)1*X^(2^(k-1)) && B(x)0
      c1 = polCoefC(cdr1[0]->grd + cdr2[0]->grd);
      c1 = RyC(cdr1[0], cdr2[0], c1); //(A(x)1 * B(x)1)
      c2 = sumarPolinomios(c2, cdr1[0], 1);
      c2 = sumarPolinomios(c2, cdr1[1], 1);
      c3 = sumarPolinomios(c3, cdr2[0], 1);
      c3 = sumarPolinomios(c3, cdr2[1], 1);
      c4 = polCoefC(c2->grd + c3->grd);
      c4 = RyC(c2, c3, c4); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0))
      result = RyC(cdr1[1], cdr2[1], result); //(A(x)0 * B(x)0)
      c4 = sumarPolinomios(c4, c1, -1);
      c4 =
          sumarPolinomios(c4, result, -1); //((A(x)1 + A(x)0)*(B(x)1 + B(x)0)) -
                                           //(A(x)1 * B(x)1) - (A(x)0 * B(x)0)
      aux1 = polCoefC(l + c1->grd);
      aux1 = coefXPol(1, l, c1, aux1); //(A(x)1 * B(x)1)^(2^k)
      aux2 = polCoefC(k + c4->grd);
      aux2 = coefXPol(1, k, c4, aux2); // c4^(2^(k-1))
      result = sumarPolinomios(result, aux1, 1);
      result = sumarPolinomios(result, aux2, 1);
      c1 = eliminar(c1);
      c2 = eliminar(c2);
      c3 = eliminar(c3);
      c4 = eliminar(c4);
      aux1 = eliminar(aux1);
      aux2 = eliminar(aux2);
      cdr1[0] = eliminar(cdr1[0]);
      cdr1[1] = eliminar(cdr1[1]);
      cdr2[0] = eliminar(cdr2[0]);
      cdr2[1] = eliminar(cdr2[1]);
      return elimSobrantes(result);
    }
    return elimSobrantes(RyC(p1, p2, result));
  }
}


// FunciÃ³n que despliega un menÃº para el usuario

void menu(node *head1, node *head2){
    int opcion=0;
    long grdo =0;
    double time1=0.0;
    double time2=0.0;
    double time3=0.0;
    node *resultado;
    node *resultado2;
    node *poliref;
    do{

        printf("1. Multiplicar 2 polinomios Generados con Fuerza Bruta \n2. Multiplicar 2 Polinomios Generados con Reducir y Conquistar" 
          "\n3. Multiplicar 2 polinomios Generados con Dividir y Conquistar \n4. Multiplicar 2 polinomios generados con Karatsuba" 
          "\n5. Tiempo CPU de Karatsuba y Fuerza Bruta \n6. Comparar Resultados de polinomios \n7. opcion salir\n");
        scanf("%d", &opcion);//Se guarda la opción ingresada
        switch(opcion){
        case 1:
            printf("Ingresa el Grado de Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            resultado=multiplicarPolinomioFBrut(head1,head2);
            display(&resultado);
            resultado=eliminar(resultado);
            
            break;
        case 2:
            printf("Ingresa el Grado de los Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            poliref=polCoefC(head1->grd + head2->grd);
            resultado=RyC(head1,head2,poliref);
            display(&resultado);
            resultado=eliminar(resultado);
	    break;
	case 3:
            printf("Ingresa el Grado de los Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            resultado=MultDivYConq(head1,head2,grdo,grdo);
            display(&resultado);
            resultado=eliminar(resultado);
            break;
        case 4:

            printf("Ingresa el Grado de los Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            resultado=polCoefC(head1->grd + head2->grd);
            resultado=Karatsuba(head1, head2, head1->grd+1, head2->grd+1, 1);
            display(&resultado);
            resultado=eliminar(resultado);
            
            break;

        case 5:

            printf("Ingresa el Grado de Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            time1=clock();
            resultado2=multiplicarPolinomioFBrut(head1,head2); 
            time1=(clock() - time2)/CLOCKS_PER_SEC;
	    resultado=eliminar(resultado);
            resultado=polCoefC(head1->grd + head2->grd);
            time2=clock();
            resultado=Karatsuba(head1, head2, head1->grd+1, head2->grd+1, 1);
            time2=(clock() - time2)/CLOCKS_PER_SEC;

              printf("\nEl tiempo de ejecucion de la funcion por Fuerza bruta fue de "
             "%f \n",
             time1);
              printf("\nEl tiempo de ejecucion de la funcion por Karatsuba "
             "fue de %f \n",
             time2);
	      resultado2 = sumarPolinomios(resultado2, resultado, -1);
	      resultado=eliminar(resultado);
	      resultado2=eliminar(resultado2);
            
            break;

         case 6: 
            printf("Ingresa el Grado de Polinomio\n");
            scanf("%ld",&grdo);
            head1=eliminar(head1);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head2=eliminar(head2);//Eliminamos la memoria por si ya hay un polinomio creado en la lista
            head1=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            head2=generator(grdo);//Genera un polinomio de grado n con coeficientes aleatorios
            resultado=multiplicarPolinomioFBrut(head1,head2);
            resultado2 = polCoefC( head1->grd + head2->grd);
            resultado2 = Karatsuba(head1, head2, head1->grd+1, head2->grd+1, 1);
            poliref=sumarPolinomios(resultado, resultado2, -1);
	    printf("Diferencia entre multiplicacion clasica y karatsuba (si no hay diferencia no hay nada que imprimir) :");
            display(&poliref); //Si no hay diferencia no imprime nada
            resultado=eliminar(resultado);
            resultado2=eliminar(resultado2);
            break;

	case 7:
	  return;
        default:
            printf("Ingrese una opcion valida\n");
            break;

        }

    }while(opcion != 7);

}

int main() {
  srand(time(NULL)); // Se inicaliza la semilla de la funciÃ³n srand()
  node *head1 = NULL;
  node *head2 = NULL;
  node *P = NULL;
  int f = 1500;
  double t = 0.0;
  int op;
  printf("\n");
  menu(head1,head2);
  return 0;
}

