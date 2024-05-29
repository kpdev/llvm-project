// list.c
// Реализация базовых функций, связанных с обработкой
// однонаправленного кольцевого списка

#include <stdio.h>
#include <stdlib.h>
#include "ring-list.h"

// Начальная инициализация списка
void InitRingList(RingList* list) {
  list->tail = NULL;
  list->previous = NULL;
  list->current = NULL;
}

//------------------------------------------------------------------------------
// Добавление значения в хвост списка
void AppendRingList(RingList* list, Value* value) {
  Node* tmpNode = malloc(sizeof(Node));
  tmpNode->value = value;
  if(list->tail == 0)  // имеем пустой список
    tmpNode->next = tmpNode;  // Замыкает кольцо на себя
  else {
    tmpNode->next = (list->tail)->next;
    (list->tail)->next = tmpNode;
  }
  list->previous = list->tail;
  list->tail = tmpNode;
  list->current = tmpNode;
}

//------------------------------------------------------------------------------
// Удаление элемента из головы списка с его сохранением
Value* DeleteHeadOfRingList(RingList* list) {
  if(list->tail == NULL) return NULL; // Список пуст.
  Node* tmpNodePtr = list->tail->next;
  Value* value = tmpNodePtr->value;
  if(list->tail == list->tail->next) {
    // В списке один элемент. Список очищается
    list->tail = 0;
  } else { // Элементов не меньше двух
    list->tail->next = list->tail->next->next;
  }
  free(tmpNodePtr); // Удаление узла
  return value;
}

//------------------------------------------------------------------------------
// Удаление всех элементов списка (очистка от данных)
void EmptyRingList(RingList* list) {
  while(list->tail != NULL) {
    Value* value = DeleteHeadOfRingList(list);
    free(value);
  }
}

//------------------------------------------------------------------------------
// Вывод значения указанного элемента, из данного узла
void OutCurrentRingListValue(FILE* file, Value* value) {
  if(value == NULL) { // Элемент отсутствует
    fprintf(file, "Element is absent! ");
  } else {
    OutValue<value>(file);
  }
}

//------------------------------------------------------------------------------
// Вывод элементов списка в указанный файл, который
// должен быть предварително открыт
void OutRingListValues(FILE* file, RingList* list) {
  Node* tmpPtr;
  fprintf(file, "List content:\n");
  if(list->tail == NULL) {
    fprintf(file, "    List is empty.\n");
  } else {
    tmpPtr = list->tail;
    do {
      fprintf(file, "    ");
      OutCurrentRingListValue(file, tmpPtr->next->value);
      fprintf(file, "\n");
      tmpPtr = tmpPtr->next;
    } while(tmpPtr != list->tail);
  }
}
