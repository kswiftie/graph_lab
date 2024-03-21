#include "..\\include\\draw_graph.hpp"
#include <iostream>

template <size_t w, size_t h>
void drawCircle(int x0, int y0, int radius, Pixel (&pixels)[w][h]) {
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while(y >= 0) {
        if (x0 + x >= 0 && y0 + y >= 0 && x0 + x < w && y0 + y < h)
		    pixels[x0 + x][y0 + y] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
            // drawLine(x0, y0, x0 + x, y0 + y, pixels);
        if (x0 + x >= 0 && y0 - y >= 0 && x0 + x < w && y0 - y < h)
            pixels[x0 + x][y0 - y] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
            // drawLine(x0, y0, x0 + x, y0 - y, pixels);
        if (x0 - x >= 0 && y0 + y >= 0 && x0 - x < w && y0 + y < h)
		    pixels[x0 - x][y0 + y] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
            // drawLine(x0, y0, x0 - x, y0 + y, pixels);
        if (x0 - x >= 0 && y0 - y >= 0 && x0 - x < w && y0 - y < h)
		    pixels[x0 - x][y0 - y] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
            // drawLine(x0, y0, x0 - x, y0 - y, pixels);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

template <size_t w, size_t h>
void drawLine(int x1, int y1, int x2, int y2, Pixel (&pixels)[w][h]) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    pixels[x2][y2] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
    while(x1 != x2 || y1 != y2) {
        pixels[x1][y1] = {static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0)};
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

template <size_t w, size_t h>
void drawNumber(int x0, int y0, int number, Pixel (&pixels)[w][h]) {
    // adding 1 to number here
    for (int x = 0; x < 12; ++x) {
        for (int y = 0; y < 12; ++y) {
            if (masks[number + 1][11 - x][y] == '1')
                pixels[x0 + x][y0 + y] = { '0', '0', '0' };
        }
    }
}

template <size_t w, size_t h>
void visualise_graph(int V, std::vector<Point>& points, Pixel (&pixels)[w][h], int radius, std::set <std::pair <int, int>> edges) {
    // count the number as a digit in the number of vertices
    int cnt_of_numbers = 0, V1 = V;
    while (V1 > 0) { V1 /= 10; ++cnt_of_numbers; }

    for (int q = 0; q < cnt_of_numbers; ++q) {
        int cur_iters = (q == 0) ? 0 : pow(10, q);
        for (int i = cur_iters; i < std::min(cur_iters * 10, V); ++i) {
            drawCircle(points[i].x, points[i].y, radius, pixels);

            int cur_num = i;
            // points[i].y - середина
            // 12 * (q + 1) + q - длина текста

            int startx = points[i].x - radius - 13, starty = points[i].y + (q + 1) * 6 + ((q + 1) / 2) - 12, signy = -1;

            if (startx < 0) startx = points[i].x + radius + 1;
            if (starty >= w) starty = w - 13;
            if (points[i].y - (q + 1) * 6 - ((q + 1) / 2) < 0)  { starty = 3; signy = 1; }

            for (int it = 0; it < q + 1; ++it) {
                drawNumber(startx, starty + signy * (it * 12 + ((it > 0) ? 1 : 0)), cur_num % 10, pixels);
                cur_num /= 10;
            }
        }
    }
    
    for (auto edge: edges) {
        if (edge.first == 45 || edge.second == 45) {
            std::cout << edge.first << " " << edge.second << "\n";
        }
        drawLine(round(points[edge.first].x), round(points[edge.first].y), round(points[edge.second].x), round(points[edge.second].y), pixels);
    }
}