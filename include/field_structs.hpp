#ifndef FIELD_STRUCTS_HPP
#define FIELD_STRUCTS_HPP

#pragma pack(push, 1)
struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};
struct Point {
    double x, y;
};
#pragma pack(pop)

#endif