#include "..\\include\\create_image.hpp"

template <size_t w, size_t h>
void fill_field(Pixel (&pixels)[w][h]) {
    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            pixels[x][y] = {static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255)};
        }    
    }
}