//------------------------------------------------------------------------------
// input-figures.c - функция ввода параметров фигур из файлов
//------------------------------------------------------------------------------

#include <stdio.h>
#include "figure-container.h"
#include "simple-creator.h"

//------------------------------------------------------------------------------
// Ввод параметров обобщенной фигуры из стандартного потока ввода
// Для создания фигур используется фабричный метод
void FigureCreateAndIn(FILE* ifst, FigureContainer* pfc) {
  SimpleCreator<rect>  rectangleCreator;
  SimpleCreator<trian> triangleCreator;
  Figure* pf;
  int k;
  while(!ifst.eof())
  {
    ifst >> k;
    switch(k) {
    case 1:
      pf = CreateFigure<&rectangleCreator>();
      break;
    case 2:
      pf = CreateFigure<&triangleCreator>();
      break;
    default:
      printf("Incorrect key of figure!!!\n");
      exit(-1);
    }
    pf->InData(ifst);
    pfc->Append(pf);
  }
}
