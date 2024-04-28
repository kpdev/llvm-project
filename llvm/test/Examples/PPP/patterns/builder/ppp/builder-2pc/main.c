//==============================================================================
// main.c - содержит главную функцию,
// обеспечивающую простое тестирование
//==============================================================================

#include <stdio.h>

#include "builder.h"
#include "figure-container.h"

//------------------------------------------------------------------------------
int main() {
  // В демонстрационном примере данные для формирования семейств фигур
  // размещены в конкретных файлах с явным указанием путей
  char resultFigureFile[] = "../data/output1.txt";
  FILE* ofst = fopen(resultFigureFile, "w");

  FigureContainer container;
  FigureContainerInit(&container);

  Builder<SimpleBuilder> simpleBuilder;
  simpleBuilder.@container = &container;

  Builder<CounterBuilder> counterBuilder;
  counterBuilder.@rectanglesCounter = 0
  counterBuilder.@trianglesCounter = 0

  std::cout << "Start\n";

  AppliqueCollector(ofst, &simpleBuilder);
  ResultOut<&simpleBuilder>(ofst);
  FigureContainerClear(&container);

  AppliqueCollector(ofst, &counterBuilder);
  ResultOut<&counterBuilder>(ofst);

  printf("Stop\n");
  return 0;
}