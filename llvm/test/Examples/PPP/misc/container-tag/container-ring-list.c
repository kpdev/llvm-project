// container-ring-list.c
// Реализация базовых функций, связанных с обработкой
// однонаправленного кольцевого списка

#include <stdio.h>
#include <stdlib.h>
#include "ring-list.h"
#include "container.h"

// Подключение кольцевого списка в качестве специализации
Container + <rlist: RingList;>;

//==============================================================================
// Обработчики специализации для одномерного массива,
// выступающего в роли контейнера

// Начальная инициализация контейнера
void InitContainer<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  InitRingList(ringList);
}

// Добавление значения в хвост контейнера
void AppendContainer<Container<rlist> >* container>(Value* value) {
  RingList* ringList = &(container->@);
  AppendRingList(ringList, value);
}

// Вывод элементов контейнера в указанный файл, который
// должен быть предварително открыт
void OutContainerValues<Container<rlist> >* container>(FILE* file)  {
  RingList* ringList = &(container->@);
  OutRingListValues(file, ringList);
}

// Удаление всех элементов из контейнера (очистка от данных)
void EmptyContainer<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  EmptyRingList(ringList);
}

//==============================================================================
// Дополнительно добавлены функции итератора из Design Patterns

//------------------------------------------------------------------------------
// Указатель на значение первого элемента контейнера
void First<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  if(ringList->tail == NULL) {
    ringList->previous = NULL;
    ringList->current = NULL;
  } else {
    ringList->current = ringList->tail->next;
    ringList->previous = ringList->tail;
  }
}

//------------------------------------------------------------------------------
// Перевод указателя на значение следующего элемента контейнера
void Next<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  if(ringList->tail == NULL) {
    ringList->current = NULL;
    ringList->current = NULL;
  } else {
    ringList->previous = ringList->current;
    ringList->current = ringList->current->next;
  }
  // Контроль перехода с последнего элемента на первый
  if(ringList->current == ringList->tail->next) {
    ringList->previous = NULL;
  }
}

//------------------------------------------------------------------------------
// Проверка выхода за последний элемент контейнера
_Bool IsDone<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  // Текущим стал первый, а предыдущий сбросился в NULL
  if((ringList->current == ringList->tail->next)
      && (ringList->previous == NULL)) {
    return 1;
  } else {
    return 0;
  }
}

//------------------------------------------------------------------------------
// Указатель на значение текущего элемента контейнера
Value* CurrentItem<Container<rlist> >* container>() {
  RingList* ringList = &(container->@);
  if(ringList->current == NULL) {
    return NULL;
  } else {
    return ringList->current->value;
  }
}
