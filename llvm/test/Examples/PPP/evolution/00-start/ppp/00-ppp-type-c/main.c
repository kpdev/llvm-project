//==============================================================================
// main.c - содержит главную функцию,
// обеспечивающую простое тестирование
//==============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "container.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void ContainerInit(Container* c) ;
void ContainerClear(Container* c);

void ContainerIn(Container* c, FILE* ifst) ;
void ContainerOut(Container* c, FILE* ofst) ;

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  if(argc !=3) {
    printf("incorrect command line!\nWaited: command infile outfile\n");
    return 1;
  }
  FILE* ifst = fopen(argv[1], "r");
  FILE* ofst = fopen(argv[2], "w");

  printf("Start\n");

  Container c;
  ContainerInit(&c);
  ContainerIn(&c, ifst);
  fclose(ifst);

  fprintf(ofst, "Filled container.\n");
  ContainerOut(&c, ofst);

  ContainerClear(&c);
  fprintf(ofst, "Empty container.\n");
  ContainerOut(&c, ofst);
  fclose(ofst);

  printf("Stop\n");
  return 0;
}

//------------------------------------------------------------------------------
// Инициализация контейнера
void ContainerInit(Container *c) {
  c->len = 0;
}

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
void ContainerClear(Container *c) {
  for(int i = 0; i < c->len; i++) {
    free(c->cont[i]);
  }
  ContainerInit(c);
}
