//
// Created by jason on 11/16/21.
//

#ifndef PROJECT_FINAL_CONSTANTS_H
#define PROJECT_FINAL_CONSTANTS_H

int MS_PER_CYCLE = 10000;
// GLuint GL_LIGHT


// which projection:
enum Projections
{
    ORTHO,
    PERSP
};

// which button:
enum ButtonVals
{
    RESET,
    QUIT
};

// TODO - Custom Views
// enum Views
// {
//     INSIDE,
//     OUTSIDE
// };


// NOTE: There are a lot of good reasons to use const variables instead
// of #define's.  However, Visual C++ does not allow a const variable
// to be used as an array size or as the case in a switch( ) statement.  So in
// the following, all constants are const variables except those which need to
// be array sizes or cases in switch( ) statements.  Those are #defines.

// title of these windows:
const char *WINDOWTITLE = { "OpenGL / Project Final -- Jason Brown" };
const char *GLUITITLE   = { "Texture Mapping" };

// what the glui package defines as true and false:
const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };

// the escape key:
#define ESCAPE		0x1b

// initial window size:
const int INIT_WINDOW_SIZE = { 600 };

// multiplication factors for input interaction:
//  (these are known from previous experience)
const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };

// minimum allowable scale factor:
const float MINSCALE = { 0.05f };

// scroll wheel button values:
const int SCROLL_WHEEL_UP   = { 3 };
const int SCROLL_WHEEL_DOWN = { 4 };

// equivalent mouse movement when we click a the scroll wheel:
const float SCROLL_WHEEL_CLICK_FACTOR = { 5. };

// active mouse buttons (or them together):
const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };

// fog parameters:
const GLfloat FOGCOLOR[4] = { .0, .0, .0, 1. };
const GLenum  FOGMODE     = { GL_LINEAR };
const GLfloat FOGDENSITY  = { 0.30f };
const GLfloat FOGSTART    = { 1.5 };
const GLfloat FOGEND      = { 4. };

// line width for the axes:
const GLfloat AXES_WIDTH   = { 3. };

#endif //PROJECT_FINAL_CONSTANTS_H
