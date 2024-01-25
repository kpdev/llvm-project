#pragma once

struct Circle { int r; };
struct Rectangle { int w, h; };
struct Figure { unsigned color; } < struct Circle; struct Rectangle; >;

void printRectangle();
void printCircle();


void PrintFigure<struct Figure* f>();
