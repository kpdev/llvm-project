// array.c
// Реализация базовых функций, связанных с обработкой
// однонаправленного кольцевого массива

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

// Начальная инициализация массива
void InitArray(Array* array) {
  array->len = 0;
  array->current = -1;
  for(int i = 0; i < maxLen; ++i) {
    array->value[i] = NULL;
  }
}

//------------------------------------------------------------------------------
// Добавление значения в хвост массива
void AppendArray(Array* array, Value* value) {
  if(array->len < maxLen) {
    array->value[array->len++] = value;
  } else {
    perror("Array Overflow\n");
    exit(-1);
  }
}

//------------------------------------------------------------------------------
// Удаление элемента из хвоста массива с его сохранением
Value* DeleteTailOfArray(Array* array) {
  if(array->len <= 0) {
    return NULL;   // элементы отсутствуют
  }
  Value* value = array->value[array->len];
  array->value[array->len--] = NULL;
  return value;
}

//------------------------------------------------------------------------------
// Удаление всех элементов массива (очистка от данных)
void EmptyArray(Array* array) {
  for(int i = 0; i < array->len; ++i) {
    free(array->value[i]);
  }
  array->len = 0;
}

//------------------------------------------------------------------------------
// Вывод значения указанного элемента, из данного узла
void OutCurrentArrayValue(FILE* file, Value* value) {
  if(value == NULL) { // Элемент отсутствует
    fprintf(file, "Element is absent! ");
  } else {
    OutValue<value>(file);
  }
}

//------------------------------------------------------------------------------
// Вывод элементов массива в указанный файл, который
// должен быть предварително открыт
void OutArrayValues(FILE* file, Array* array) {
  if(array->len == 0) {
    fprintf(file, "Empty Array of Values\n");
    return;
  }
  fprintf(file, "Array of Values is:\n");
  for(int i = 0; i < array->len; ++i) {
    fprintf(file, "    ");
    OutCurrentArrayValue(file, array->value[i]);
    fprintf(file, "\n");
  }
}
