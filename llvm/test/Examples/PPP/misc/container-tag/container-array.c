// container-array.c
// Реализация базовых функций, связанных с обработкой массива

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "container.h"

// Подключение массива в качестве специализации
Container + <vector: Array;>;

//==============================================================================
// Обработчики специализации для одномерного массива,
// выступающего в роли контейнера

// Начальная инициализация контейнера
void InitContainer<Container<vector> >* container>() {
  Array* array = &(container->@);
  InitArray(array);
}

// Добавление значения в хвост контейнера
void AppendContainer<Container<vector> >* container>(Value* value) {
  Array* array = &(container->@);
  AppendArray(array, value);
}

// Вывод элементов контейнера в указанный файл, который
// должен быть предварително открыт
void OutContainerValues<Container<vector> >* container>(FILE* file)  {
  Array* array = &(container->@);
  OutArrayValues(file, array);
}

// Удаление всех элементов из контейнера (очистка от данных)
void EmptyContainer<Container<vector> >* container>() {
  Array* array = &(container->@);
  EmptyArray(array);
}

//==============================================================================
// Дополнительно добавлены функции итератора из Design Patterns

//------------------------------------------------------------------------------
// Указатель на значение первого элемента контейнера
void First<Container<vector> >* container>() {
  Array* array = &(container->@);
  if(array->len == 0) {
    array->current = -1;
  } else {
    array->current = 0;
  }
}

//------------------------------------------------------------------------------
// Перевод указателя на значение следующего элемента контейнера
void Next<Container<vector> >* container>() {
  Array* array = &(container->@);
  if(array->len == 0) {
    array->current = -1;
  } ++(array->current);
}

//------------------------------------------------------------------------------
// Проверка выхода за последний элемент контейнера
_Bool IsDone<Container<vector> >* container>() {
  Array* array = &(container->@);
  if(array->current >= array->len) {
    array->current = array->len;
    return 1;
  }
  return 0;
}

//------------------------------------------------------------------------------
// Указатель на значение текущего элемента контейнера
Value* CurrentItem<Container<vector> >* container>() {
  Array* array = &(container->@);
  if((array->current >= 0) && (array->current < array->len)) {
    return array->value[array->current];
  }
  return NULL;
}
