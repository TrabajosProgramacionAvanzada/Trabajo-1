#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodeP {
  /*
    Estructura linked list que permite almacenar coeficiente y grado
    de un polinomio de la forma a(x)=(asub(n-1)*bsub(n-1))xexp(n-1)+A(x)
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
  node *aux;
  node *nNode = malloc(sizeof(node)); // Crear nodo temporal y asignar memoria
  nNode->coef = coef;                 // Asignar coef a coef
  nNode->grd = grd;                   // Asignar el grado

  if (*head == NULL || (*head)->grd < grd) {
    nNode->next = *head; // Apuntar a head
    *head = nNode;       // Igualaron head al nodo temporal.
  } else {
    aux = (*head);
    while (aux->next != NULL && (long)aux->next->grd > (long)nNode->grd) {
      aux = aux->next;
    }
    nNode->next = aux->next;
    aux->next = nNode;
  }
}

// Funcion copia
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
  node *temp;            // Crear nodo temporal
  temp = *head;          // Igualar el nodo temporal a nuestra head
  while (temp != NULL) { // Mientras el nodo temporal sea distinto de NULL
    if (temp->coef > 0 &&
        temp->grd == 0) { // Si el coeficiente es mayor que cero
      printf(" %ld x^%ld ", temp->coef, temp->grd); // Imprime con un signo mas.
    } else if (temp->coef > 0) {                    // Sino
      printf("+ %ld x^%ld ", temp->coef,
             temp->grd); // Imprime con un signo menos.
    } else {
      printf(" %ld x^%ld ", temp->coef, temp->grd);
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
  for (i = grado; i >= 0; i--) { // Iterar desde el mayor al menor. para de esta
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
  for (i = grds; i >= 0;
       i--) { // Se recorre desde el grado 0 al grado mÃ¡ximo dado "grds"
    scanf("%ld", &coef); // Se pide el coeficiente del polinomio
    if (coef != 0) {
      push(&head, coef, i); // Luego se une a la lista
    }
  }
  return head;
}

// Funcion que suma dos polinomios
node *sumarPolinomios(node *p1, node *p2) {
  node *pFinal =
      NULL; // Puntero nodo, vacio, que contendra la suma de dos polinomios.
  while (p1 && p2) {
    if (p1->grd == p2->grd) {
      push(&pFinal, p1->coef + p2->coef, p1->grd); // Inserta la suma en pFinal;
      p1 = p1->next;
      p2 = p2->next;
    } else if (p1->grd > p2->grd) {
      push(&pFinal, p1->coef, p1->grd);
      p1 = p1->next;
    } else if (p2->grd > p1->grd) {
      push(&pFinal, p2->coef, p2->grd);
      p2 = p2->next;
    }
  }
  if (p1 != NULL) {
    while (p1 != NULL) {
      push(&pFinal, p1->coef, p1->grd);
      p1 = p1->next;
    }
  }
  if (p2 != NULL) {
    while (p2 != NULL) {
      push(&pFinal, p2->coef, p2->grd);
      p2 = p2->next;
    }
  }
  return pFinal;
}
// Funcion que resta dos polinomios
node *restaPolinomios(node *p1, node *p2) {
  node *pFinal = NULL;
  while (p1 != NULL && p2 != NULL) {
    if (p1->grd == p2->grd) {
      push(&pFinal, p2->coef, p1->grd);
      p1 = p1->next;
      p2 = p2->next;
    } else if (p1->grd > p2->grd) {
      push(&pFinal, p1->coef, p1->grd);
      p1 = p1->next;
    } else if (p2->grd > p1->grd) {
      push(&pFinal, (p2->coef) * -1, p2->grd);
      p2 = p2->next;
    }
  }
  if (p1 != NULL) {
    while (p1 != NULL) {
      push(&pFinal, p1->coef, p1->grd);
      p1 = p1->next;
    }
  }
  if (p2 != NULL) {
    while (p2 != NULL) {
      push(&pFinal, (p2->coef) * -1, p2->grd);
      p2 = p2->next;
    }
  }
  return pFinal;
}
node *multiplicarPolinomio(node *p1, node *p2) {
  node *cP1 = NULL;
  node *rMult = NULL;
  cP1 = p1;
  while (p2 != NULL) {
    while (cP1 != NULL) {
      push(&rMult, (long)(cP1->coef) * (long)(p2->coef),
           (cP1->grd) + (p2->grd));
      cP1 = cP1->next;
    }
    p2 = p2->next;
    cP1 = p1;
  }
  return rMult;
}
node *sumagrdIguales(node *p) {
  long n = 0;
  node *final = NULL;
  while (p->next != NULL) {
    if (p->grd == p->next->grd) {
      n = n + (p->coef + p->next->coef);
    } else {
      if (n > 0) {
        push(&final, n, p->grd);
        n = 0;
      } else {
        push(&final, p->coef, p->grd);
      }
    }
    p = p->next;
  }
  push(&final, p->coef, p->grd);
  return final;
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

// FunciÃ³n que despliega un menÃº para el usuario
void menu(node *head1, node *head2) {
  int opcion = 0;
  long grdo1 = 0;
  long grdo2 = 0;
  node *aux = NULL;
  do {

    printf("1. sumar dos polinomios generados \n2. restar dos polinomios "
           "generados \n3. copiar un polinomio ingresado \n4. opcion sair\n");
    scanf("%d", &opcion); // Se guarda la opciÃ³n ingresada
    switch (opcion) {
    case 1:
      scanf("%ld", &grdo1);
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(
          grdo1); // Genera un polinomio de grado n con coeficientes aleatorios
      head2 = generator(grdo2);
      display(&head1);
      display(&head2);
      printf("\n+--------------------------------------------------------------"
             "--------\n");
      aux = sumarPolinomios(head1, head2);
      head2 = eliminar(head2);
      head2 = copy(aux);
      display(&head2);
      break;
    case 2:
      scanf("%ld", &grdo1);
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(
          grdo1); // Genera un polinomio de grado n con coeficientes aleatorios
      head2 = generator(grdo2);
      display(&head1);
      display(&head2);
      printf("\n-  "
             "-----------------------------------------------------------------"
             "-----\n");
      aux = restaPolinomios(head1, head2);
      head2 = eliminar(head2);
      head2 = copy(aux);
      display(&head2);
      break;
    case 3:
      scanf("%ld", &grdo1);
      head1 = eliminar(head1); // Paso anÃ¡logo al "case 1"
      head2 = eliminar(head2);
      aux = eliminar(aux);
      head1 = ingresar_plinomio(grdo1); // Pide el polinomio al usuario
      head2 = copy(head1);
      aux = copy(head2);
      printf("\nEl polinomio ingresado:\n");
      display(&head1);
      printf("\nEl polinomio copiado:\n");
      display(&aux);
      break;
    case 4:
      break;
      head1 = eliminar(head1); // Elimina la memoria antes de cerrar el programa
      head2 = eliminar(head2);
      aux = eliminar(aux);
      break;
    default:
      printf("Ingrese una opcion valida\n");
      break;
    }

  } while (opcion != 4);
}

int main() {
  srand(time(NULL)); // Se inicaliza la semilla de la funciÃ³n srand()
  node *head1 = NULL;
  node *head2 = NULL;
  node *head3 = NULL;
  node *P = NULL;
  int exp = 0;
  // menu(head1, head2);
  head1 = generator(500);
  head2 = generator(500);
  head3 = generator(500);
  display(&head1);
  display(&head2);
  display(&head3);
  P = multiplicarPolinomio(head1, head2);
  eliminar(head1);
  eliminar(head2);
  display(&P);
  P = sumagrdIguales(P);
  display(&P);
  P = multiplicarPolinomio(P, head3);
  display(&P);
  eliminar(head3);
  P = sumagrdIguales(P);
  display(&P);
  eliminar(P);
  return 0;
}
