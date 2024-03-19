#include "..\\include\\draw_graph.hpp"

template <size_t h, size_t w>
void drawCircle(int x0, int y0, int radius, Pixel (&pixels)[h][w]) {
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

template <size_t h, size_t w>
void drawLine(int x1, int y1, int x2, int y2, Pixel (&pixels)[h][w]) {
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