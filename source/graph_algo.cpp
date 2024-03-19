#include "..\\include\\graph_algo.hpp"
#include "math.cpp"

void fruchtermanReingold(std::vector<Point>& points, std::set <int> *graph, double L, int V, int numIterations) {
    // algo start
    for (int it = 0; it < numIterations; ++it) {
        double temperature = 1.0 / (V + (it + 1));
        std::vector <Point> moment = points;
        // repulsion force
        for (int i = 0; i < V; ++i) {
            for (int u = 0; u < V && u != i; ++u) {
                    double dist = distance(points[i], points[u]);
                    double repulsion = -1.0 * temperature * L * L / dist;
                    moment[i].x += repulsion * (points[u].x - points[i].x) / dist;
                    moment[i].y += repulsion * (points[u].y - points[i].y) / dist;
            }
        }
        // attractive force
        for (int i = 0; i < V; ++i) {
            for (int u: graph[i]) {
                    double dist = distance(points[i], points[u]);
                    double attractive = 1.0 * temperature * dist * dist / L;
                    moment[i].x += attractive * (points[u].x - points[i].x) / dist;
                    moment[i].y += attractive * (points[u].y - points[i].y) / dist;
            }
        }

        // update vertex coordinates
        for (int i = 0; i < V; ++i) {
            points[i].x = moment[i].x;
            points[i].y = moment[i].y;
        }
    }
}

void scale_graph(std::vector<Point>& points, int V, int height, int width) {
    double minX = points[0].x, minY = points[0].y, maxX = points[0].x, maxY = points[0].y;
    for (int i = 0; i < V; ++i) {
        minX = std::min(minX, points[i].x);
        minY = std::min(minY, points[i].y);
        maxX = std::max(maxX, points[i].x);
        maxY = std::max(maxY, points[i].y);
    }
    double cf_x = (double)(width - 20) / (maxX - minX), cf_y = (double)(height - 20) / (maxY - minY);
    for (int i = 0; i < V; ++i) {
        points[i].x *= cf_x;
        points[i].y *= cf_y;
    }
    minX = points[0].x; minY = points[0].y; maxX = points[0].x; maxY = points[0].y;
    for (int i = 0; i < V; ++i) {
        minX = std::min(minX, points[i].x);
        minY = std::min(minY, points[i].y);
        maxX = std::max(maxX, points[i].x);
        maxY = std::max(maxY, points[i].y);
    }
    for (int i = 0; i < V; ++i) {
        points[i].x -= minX;
        points[i].y -= minY;
        points[i].x += 10.0; // radius * 2
        points[i].y += 10.0; // radius * 2
    }
}
