#ifndef __coord_rectangle__
#define __coord_rectangle__

//==============================================================================
// coord-rectangle.h - содержит описание прямоугольника
//==============================================================================

#include "coord-point.h"

//------------------------------------------------------------------------------
// прямоугольник
typedef struct CoordRectangle {
  Point top_left, down_right; // координаты верхнего и нижнего углов
} CoordRectangle;

#endif // __coord_rectangle__