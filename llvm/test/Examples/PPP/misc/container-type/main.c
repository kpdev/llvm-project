// main.c
#include <stdio.h>
#include "array.h"
#include "ring-list.h"
#include "container.h"

// Подключение массива в качестве специализации
Container + <Array;>;
// Подключение кольцевого списка в качестве специализации
Container + <RingList;>;

typedef struct Int {int x;} Int;

// Добавление специализации в виде целочисленных значений
// Value + <int;>;
Value + <Int;>;

// Обработчик специализации для целочисленных значений
void OutValue<Value<Int>* value>(FILE* file) {
  fprintf(file, "value = %d", value->@x);
}
// void OutValue<Value<int>* value>(FILE* file) {
//   fprintf(file, "value = %d", value->@);
// }

int main(void) {
  //----------------------------------------------------------------------------
  // Использование в качестве контейнера массива
  //----------------------------------------------------------------------------

  // Формирование пустого контейнера
  struct Container<Array>  array;
  InitContainer<&array>();
  OutContainerValues<&array>(stdout);
  printf("\n");

  // Создание нового значения
  struct Value<Int> v1;
  v1.@x = 10;
  // OutValue<&v1>(stdout);

  // Динамическое создание нового элемента
  struct Value<Int>* pvInt;
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 20;
  struct Value* pv = pvInt;
  // OutValue<pv>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&array>(pv);
  OutContainerValues<&array>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 30;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&array>(pvInt);
  OutContainerValues<&array>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 40;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&array>(pvInt);
  OutContainerValues<&array>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = v1.@x;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&array>(pvInt);
  OutContainerValues<&array>(stdout);
  printf("\n");

  // Установка итератора на первй элемент и вывод его значения
  First<&array>();
  printf("First:");
  pv = CurrentItem<&array>();
  OutValue<pv>(stdout);
  // OutValue< CurrentItem<&array>() >(stdout);
  printf("\n\n");

  // Цикл по итераторам от первого до последнего элементов
  int count = 0;
  // _Bool b = IsDone<&array>();
  // while(!b) {
  while(!IsDone<&array>()) {
    printf("%d: ", count);
    pv = CurrentItem<&array>();
    OutValue<pv>(stdout);
    printf("\n");
    Next<&array>();
    ++count;
    // b = IsDone<&array>();
  }
  printf("\n");

  // Очистка контейнера
  EmptyContainer<&array>();
  OutContainerValues<&array>(stdout);
  printf("\n");

  //----------------------------------------------------------------------------
  // Использование в качестве контейнера однонаправленного кольцевого списка
  //----------------------------------------------------------------------------

  // Формирование пустого контейнера
  struct Container<RingList>  ringList;
  InitContainer<&ringList>();
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  // Создание нового значения
  // struct Value<Int> v1;
  v1.@x = 110;
  // OutValue<&v1>(stdout);

  // Динамическое создание нового элемента
  // struct Value<Int>* pvInt;
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 220;
  pv = pvInt;
  // OutValue<pv>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&ringList>(pv);
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 330;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&ringList>(pvInt);
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 440;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&ringList>(pvInt);
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = v1.@x;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в контейнер и вывод контейнера
  AppendContainer<&ringList>(pvInt);
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  // Установка итератора на первй элемент и вывод его значения
  First<&ringList>();
  printf("First:");
  pv = CurrentItem<&ringList>();
  OutValue<pv>(stdout);
  // OutValue< CurrentItem<&ringList>() >(stdout);
  printf("\n\n");

  // Цикл по итераторам от первого до последнего элементов
  count = 0;
  // _Bool b = IsDone<&ringList>();
  // while(!b) {
  while(!IsDone<&ringList>()) {
    printf("%d: ", count);
    pv = CurrentItem<&ringList>();
    OutValue<pv>(stdout);
    printf("\n");
    Next<&ringList>();
    ++count;
    // b = IsDone<&ringList>();
  }
  printf("\n");

  // Очистка контейнера
  EmptyContainer<&ringList>();
  OutContainerValues<&ringList>(stdout);
  printf("\n");

  return 0;
} // end main

