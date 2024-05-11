//==============================================================================
// main.c - содержит главную функцию,
// обеспечивающую простое тестирование
//==============================================================================

#include <stdio.h>
#include "figure-container.h"

//------------------------------------------------------------------------------
// Прототип функии ввода всех фигур
void FigureCreateAndIn(FILE* ifst, FigureContainer* pfc);

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  if(argc !=3) {
    printf("incorrect command line! Wated: command infile outfile\n");
    return 1;
  }

  FILE* ifst = fopen(argv[1], "r");
  FILE* ofst = fopen(argv[2], "w");

  printf("Start\n");

  FigureContainer c;
  FigureContainerInit(&c);

  FigureCreateAndIn(ifst, &c);
  fclose(ifst);

  fprintf(stdout, "Filled container.\n");
  FigureContainerOut(&c, stdout);

  fprintf(ofst, "Filled container.\n");
  FigureContainerOut(&c, ofst);

  FigureContainerClear(&c);

  fprintf(stdout, "Empty container.\n");
  FigureContainerOut(&c, stdout);

  fprintf(ofst, "Empty container.\n");
  FigureContainerOut(&c, ofst);

  fclose(ofst);
  printf("Stop\n");
  return 0;
}