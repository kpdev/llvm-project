// main.c
#include <stdio.h>
// #include <ncurses.h>

#include "ring-list.h"

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
  // Формирование пустого списка
  RingList  list;
  InitRingList(&list);
  OutRingListValues(stdout, &list);

  // Создание нового значения
  struct Value<Int> v1;
  v1.@x = 10;
  // OutValue<&v1>(stdout);

  // Добавление элемента в список и вывод списка
  // AppendRingList(&list, &v1);
  // OutRingListValues(stdout, &list);

  // Динамическое создание нового элемента
  struct Value<Int>* pvInt;
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 20;
  struct Value* pv = pvInt;
  // OutValue<pv>(stdout);

  // Добавление элемента в список и вывод списка
  AppendRingList(&list, pv);
  OutRingListValues(stdout, &list);

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 30;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в список и вывод списка
  AppendRingList(&list, pvInt);
  OutRingListValues(stdout, &list);

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = 40;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в список и вывод списка
  AppendRingList(&list, pvInt);
  OutRingListValues(stdout, &list);

  // Динамическое создание нового элемента
  pvInt = create_spec<struct Value<struct Int> >();
  pvInt->@x = v1.@x;
  // OutValue<pvInt>(stdout);

  // Добавление элемента в список и вывод списка
  AppendRingList(&list, pvInt);
  OutRingListValues(stdout, &list);

  // Удаление элемента из головы списка
  pv = DeleteHeadOfRingList(&list);
  // OutValue<pv>(stdout);
  OutRingListValues(stdout, &list);

  // Очистка списка
  EmptyRingList(&list);
  OutRingListValues(stdout, &list);

  return 0;
} // end main

