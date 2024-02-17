//==============================================================================
// main.cpp - содержит главную функцию,
// обеспечивающую простое тестирование
//==============================================================================

#include <iostream>
#include <fstream>

#include "container.h"

//------------------------------------------------------------------------------
// Сигнатуры требуемых функций можно тоже подключить через
// заголовочный файл. Но, для простоты, можно и так описать.
void Init(container &c) ;
void Clear(container &c);

void In(container &c, std::ifstream &ifst) ;
void Out(container &c, std::ofstream &ofst) ;

//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  if(argc !=3) {
    std::cout << "incorrect command line!"
            " Waited: command infile outfile" << "\n";
    return 1;
  }
  std::ifstream ifst(argv[1]);
  std::ofstream ofst(argv[2]);

  std::cout << "Start\n";

  container c;
  Init(c);
  In(c, ifst);

  ofst << "Filled container.\n";
  Out(c, ofst);

  Clear(c);
    ofst << "Empty container.\n";
  Out(c, ofst);

  std::cout << "Stop\n";
  return 0;
}