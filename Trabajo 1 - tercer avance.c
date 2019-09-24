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
  node *aux = NULL;
  node *aux1 = NULL;
  node *nNode = NULL;
  nNode = (node *)malloc(sizeof(node)); // Crear nodo temporal y asignar memoria
  nNode->coef = coef;                 // Asignar coef a coef
  nNode->grd = grd;                   // Asignar el grado
  if (*head == NULL || (*head)->grd < grd) {
    nNode->next = *head; // Apuntar a head
    *head = nNode;       // Igualaron head al nodo temporal
  } else {
    aux = (*head);
    while (aux != NULL && (long)aux->grd > grd) {
      aux1 = aux;
      aux = aux->next;
    }
    if (aux != NULL && (long)aux->grd == grd) {
      aux->coef = aux->coef + coef;
      free(nNode);
      return;
    }
    nNode->next = aux1->next;
    aux1->next = nNode;
    free(aux);
  }
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

node *multiplicarPolinomioFBrut(node *p1, node *p2) { // Función a fuerza bruta
  node *cP1 = NULL;
  node *rMult = NULL;
  cP1 = p1;
  while (p2 != NULL) {    // Se itera en el segundo polinomio
    while (cP1 != NULL) { // Se le multiplica cada término del segundo polinomio
                          // al primer polinomio
      push(&rMult, (long)(cP1->coef) * (long)(p2->coef),
           (cP1->grd) + (p2->grd)); // Se ingresa a una pila nueva
      cP1 = cP1->next;
    }
    p2 = p2->next; // Se avanza
    cP1 = p1;
  }
  return rMult;
}



node *multiplicarPolinomioRyConc(
    node *p1, node *p2) { // Reducir y conquistar a(x) = a(n-1)X^(n-1) + A(x)
                          // b(x) = b(n-1)X^(n-1) + B(x)
  node *rMult = NULL;
  node *aux = NULL; //a*b
  node *aux1 = NULL;
  node *aux2 =
      NULL; //(aX^n + A(x)) * (bX^n + B(x)) = abX^2n + aB(x) + bA(x) + A(x)B(x)
  node *a = NULL; //aX^n
  node *b = NULL;//bX^n
  push(&a, p1->coef, p1->grd);
  push(&b, p2->coef, p2->grd);
  aux = multiplicarPolinomioFBrut(a, b);
  if (p1->next && p2->next) {
    aux1 = multiplicarPolinomioFBrut(a, p2->next);
    aux2 = multiplicarPolinomioFBrut(b, p1->next);
    rMult = sumarPolinomios(
        sumarPolinomios(sumarPolinomios(aux, aux1),
                       aux2),
        multiplicarPolinomioRyConc(
            p1->next,
            p2->next)); // Sé que está desordenado pero es la searación en
                        // cuatro sumas, la anterior expuesta en aux, (an-1 .
                        // B(x) + bn-1 . A(x))xn-1) y la multiplicación restante
                        // (A(x) . B(x))
  } else {
    if (p1->next) { // Se remplaza a p2->next por aux2 (1X^0)
      rMult = sumarPolinomios(
          aux, multiplicarPolinomioFBrut(aux2, p1->next));
    } else {
      if (p2->next) { // Se remplaza a p->next por aux2 (1X^0)
        rMult = sumarPolinomios(
				aux, multiplicarPolinomioFBrut(aux1, p2->next));
      } else { // Se remplaza a p1->next y p2->next por aux2 (1X^0) y se corta
               // la recursión reemplazando la llamada en la suma con aux1 (0X^0)
               // CASO BASE!!!
        rMult = aux;
      }
    }
  }
  return rMult;
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

    printf("\n1. sumar dos polinomios generados \n2. restar dos polinomios "
           "generados \n3. copiar un polinomio ingresado\n4. multiplicar dos "
           "polinomios generados  \n5. opcion sair\n");
    scanf("%d", &opcion); // Se guarda la opción ingresada
    switch (opcion) {
    case 1:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(
          grdo1); // Genera un polinomio de grado n con coeficientes aleatorios
      head2 = generator(grdo2);
      printf("\nEl primer polinomio generado:\n\n");
      display(&head1);
      printf("\nEl segundo polinomio generado:\n\n");
      display(&head2);
      printf("\n+--------------------------------------------------------------"
             "--------\n\n");
      aux = sumarPolinomios(head1, head2);
      head2 = eliminar(head2);
      head2 = copy(aux);
      display(&head2);
      break;
    case 2:
      printf("\nIngrese el grado maximo del primer polinomio: ");
      scanf("%ld", &grdo1);
      printf("\nIngrese el grado maximo del segundo polinomio: ");
      scanf("%ld", &grdo2);
      aux = eliminar(aux);
      head1 = eliminar(head1); // Eliminamos la memoria por si ya hay un
                               // polinomio creado en la lista
      head2 = eliminar(head2);
      head1 = generator(
          grdo1); // Genera un polinomio de grado n con coeficientes aleatorios
      head2 = generator(grdo2);
      printf("\nEl primer polinomio generado:\n\n");
      display(&head1);
      printf("\nEl segundo polinomio generado:\n\n");
      display(&head2);
      printf("\n-  "
             "-----------------------------------------------------------------"
             "-----\n\n");
      aux = restaPolinomios(head1, head2);
      head2 = eliminar(head2);
      head2 = copy(aux);
      display(&head2);
      break;
    case 3:
      printf("\nIngrese el grado maximo del polinomio: ");
      scanf("%ld", &grdo1);
      head1 = eliminar(head1); // Paso anÃ¡logo al "case 1"
      head2 = eliminar(head2);
      aux = eliminar(aux);
      head1 = ingresar_plinomio(grdo1); // Pide el polinomio al usuario
      head2 = copy(head1);
      printf("\nEl polinomio ingresado:\n");
      display(&head1);
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
      head1 = generator(
          grdo1); // Genera un polinomio de grado n con coeficientes aleatorios
      head2 = generator(grdo2);
      printf("\nEl primer polinomio generado:\n\n");
      display(&head1);
      printf("\nEl segundo polinomio generado:\n\n");
      display(&head2);
      printf("\nx  "
             "-----------------------------------------------------------------"
             "-----\n\n");
      aux = multiplicarPolinomioRyConc(head1, head2);
      head1 = eliminar(head1);
      head2 = eliminar(head2);
      display(&aux);
      aux = eliminar(aux);
      break;
    case 5:
      break;
      head1 = eliminar(head1); // Elimina la memoria antes de cerrar el programa
      head2 = eliminar(head2);
      aux = eliminar(aux);
      break;
    default:
      printf("Ingrese una opcion valida\n");
      break;
    }

  } while (opcion != 5);
}

int main() {
  srand(time(NULL)); // Se inicaliza la semilla de la funciÃ³n srand()
  node *head1 = NULL;
  node *head2 = NULL;
  node *P = NULL;
  push(&head1, 1, 2);
  push(&head1, 1, 1);
  display(&head1);
  push(&head2, 1, 2);
  push(&head2, 1, 1);
  display(&head2);
  //P = multiplicarPolinomioRyConc(head1, head2);
  //display(&P);
  //P = eliminar(P);
  P = multiplicarPolinomioFBrut(head1, head2);
  display(&P);
  P = eliminar(P);
  //menu(head1, head2);
  return 0;
}
