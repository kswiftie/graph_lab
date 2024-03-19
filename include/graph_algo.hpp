#ifndef GRAPH_ALGO_HPP
#define GRAPH_ALGO_HPP

#include <set>
#include <vector>
#include "field_structs.hpp"
#include "math.hpp"

void fruchtermanReingold(std::vector<Point>& points, std::set <int> *graph, double L, int V, int numIterations);

void scale_graph(std::vector<Point>& points, int V, int height, int width);

#endif