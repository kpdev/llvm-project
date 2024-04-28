//==============================================================================
// main.c - содержит главную функцию,
// обеспечивающую простое тестирование
//==============================================================================

#include <stdio.h>

#include "container.h"
#include "figure-factory.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void ContainerInit(Container* c) ;
void ContainerClear(Container* c);
void ContainerIn(Container* c, FILE* ifst, FigureFactory* factory);
void ContainerOut(Container* c, FILE* ofst);

//------------------------------------------------------------------------------
int main() {
  // В демонстрационном примере данные для формирования семейств фигур
  // размещеены в конкретных файлов с явным указанием путей
  char simpleFigureFile[] = "../data/simple-input1.txt";
  char coordFigureFile[] = "../data/coord-input1.txt";
  char resultFigureFile[] = "../data/output1.txt";

  FILE* ifst_simple = fopen(simpleFigureFile, "r");
  FILE* ifst_coord = fopen(coordFigureFile, "r");
  FILE* ofst = fopen(resultFigureFile, "w");

  FigureFactory<simple> simpleFactory;
  FigureFactory<coord>  coordFactory;

  printf("Start\n");

  Container c;
  ContainerInit(&c);
  ContainerIn(&c, ifst_simple, &simpleFactory);
  fclose(ifst_simple);
  // ContainerOut(&c, stdout);
  fprintf(ofst, "Filled container.\n");
  ContainerOut(&c, ofst);
  SimpleContainerClear(&c);
  fprintf(ofst, "Empty container.\n");
  SimpleContainerOut(&c, ofst);

  ContainerIn(&c, ifst_coord, &coordFactory);
  fclose(ifst_coord);
  fprintf(ofst, "Filled container.\n");
  ContainerOut(&c, ofst);
  // fprintf(stdout, "Filled container.\n");
  ContainerOut(&c, stdout);
  ContainerClear(&c);
  fprintf(ofst, "Empty container.\n");
  ContainerOut(&c, ofst);
  fclose(ofst);

  printf("Stop\n");
  return 0;
}