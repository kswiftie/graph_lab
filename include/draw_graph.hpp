#ifndef DRAW_GRAPH_HPP
#define DRAW_GRAPH_HPP

#include <stdlib.h>
#include "field_structs.hpp"

template <size_t w, size_t h>
void drawCircle(int x0, int y0, int radius, Pixel (&pixels)[w][h]);

template <size_t w, size_t h>
void drawLine(int x1, int y1, int x2, int y2, Pixel (&pixels)[w][h]);

#endif