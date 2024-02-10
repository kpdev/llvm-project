//==============================================================================
// figures-input.c - функция содания ввода всех альтернативных фигур.
// Реализована как централизованная. Единственная, требующая модификации
// при вводе данных. Но можно тоже сделать эволюционно расширяемой.
//==============================================================================

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "figure.h"
#include "figure-rectangle.h"
#include "figure-triangle.h"

#define create_spec(VarName, ...)                \
  {                                              \
    __VA_ARGS__ tmp;                             \
    VarName = malloc(sizeof(__VA_ARGS__));       \
    memcpy(VarName, &tmp, sizeof(__VA_ARGS__));  \
  }

//------------------------------------------------------------------------------
// Ввод параметров одноф из фигур из файла
struct Figure* FigureCreateAndIn(FILE* ifst) {
  struct Figure *sp;
  int k;
  fscanf(ifst, "%d", &(k));
  switch(k) {
  case 1:
    // sp = malloc(sizeof(Figure<Rectangle>));
    // Далее нужно сформировать признак. Наверное спец. функция...
    create_spec(sp, struct Figure<struct Rectangle>); // Создание и инициализация
    break;
  case 2:
    // sp = malloc(sizeof(Figure<Triangle>));
    // Далее нужно сформировать признак. Наверное спец. функция...
    create_spec(sp, struct Figure<struct Triangle>); // Создание и инициализация
    break;
  default:
    printf("INIT ERROR [IDX: %d]\n", k);
    return 0;
  }
  FigureInput<sp>(ifst);
  return sp;
}
