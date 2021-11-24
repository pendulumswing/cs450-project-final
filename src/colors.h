//
// Created by jason on 10/9/21.
//


#ifndef PROJECT_3_COLORS_H
#define PROJECT_3_COLORS_H

#include <vector>

typedef struct {
    float r, g, b;
} Rgb;

typedef std::vector<Rgb> rgb3;

typedef struct {
    float r, g, b, a;
} Rgba;

typedef std::vector<Rgba> rgb4;

// the color numbers:
// this order must match the radio button order

enum Colors {
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE,
    BLACK,
    LIGHTBLUE,
    LIGHTRED,
    LIGHTGREEN,
    OFFWHITE,
    BLUEGRAY,
    PINK,
    ORANGE,
    GRAY10,
    GRAY20,
    GRAY30,
    GRAY40,
    GRAY50,
    GRAY60,
    GRAY70,
    GRAY80,
    GRAY90,
};

char *ColorNames[] =
        {
                (char *) "Red",
                (char *) "Yellow",
                (char *) "Green",
                (char *) "Cyan",
                (char *) "Blue",
                (char *) "Magenta",
                (char *) "White",
                (char *) "Black",
                (char *) "Light Blue",
                (char *) "Light Red",
                (char *) "Light Green",
                (char *) "Off White",
                (char *) "Blue Gray",
                (char *) "Pink",
                (char *) "Orange",
                (char *) "Gray-10",
                (char *) "Gray-20",
                (char *) "Gray-30",
                (char *) "Gray-40",
                (char *) "Gray-50",
                (char *) "Gray-60",
                (char *) "Gray-70",
                (char *) "Gray-80",
                (char *) "Gray-90",
        };

// the color definitions:
// this order must match the menu order

const GLfloat Colors[][3] =
        {
                {1.,    0.,    0.},           // red
                {1.,    1.,    0.},           // yellow
                {0.,    1.,    0.},           // green
                {0.,    1.,    1.},           // cyan
                {0.,    0.,    1.},           // blue
                {1.,    0.,    1.},           // magenta
                {1.,    1.,    1.},           // white
                {0.,    0.,    0.},           // black
                {0.584, 0.831, 0.858},        // lightblue
                {0.898, 0.435, 0.380},        // lightred
                {0.839, 0.925, 0.537},        // lightgreen
                {0.992, 0.988, 0.890},        // offwhite
                {0.290, 0.415, 0.509},        // bluegray
                {0.980, 0.682, 0.870},        // pink
                {0.7,   0.5,   0.1 },         // orange
                {0.9,   0.9,   0.9},          // gray10
                {0.8,   0.8,   0.8},          // gray20
                {0.7,   0.7,   0.7},          // gray30
                {0.6,   0.6,   0.6},          // gray40
                {0.5,   0.5,   0.5},          // gray50
                {0.4,   0.4,   0.4},          // gray60
                {0.3,   0.3,   0.3},          // gray70
                {0.2,   0.2,   0.2},          // gray80
                {0.1,   0.1,   0.1},          // gray90
        };

Rgb SetColor( int Color ) {
  Rgb color = {Colors[Color][0], Colors[Color][1], Colors[Color][2] };
  return color;
}

Rgba SetColorWithAlpha( int Color, float Alpha=1.0f ) {
  Rgba color = {Colors[Color][0], Colors[Color][1], Colors[Color][2], Alpha };
  return color;
}

#endif //PROJECT_3_COLORS_H
