#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#ifndef PROJECT_FINAL_UTILS_H
#define PROJECT_FINAL_UTILS_H

#include <vector>

#define GLM_FORCE_RADIANS
#include "../glm/vec2.hpp"
#include "../glm/vec3.hpp"
#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/matrix_inverse.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "constants.h"

// read a BMP file into a Texture:
#define _USE_MATH_DEFINES
  #include <math.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #define VERBOSE		false
  #define BMP_MAGIC_NUMBER	0x4d42

  #ifndef BI_RGB
  #define BI_RGB			0
  #define BI_RLE8			1
  #define BI_RLE4			2
#endif


// Custom struct to store 3 element vectors
typedef struct {
    float x, y, z;
} Vec3;

typedef std::vector<Vec3> vector;

void			Axes( float );
unsigned char *	BmpToTexture( char *, int *, int * );
void			HsvRgb( float[3], float [3] );
int				ReadInt( FILE * );
short			ReadShort( FILE * );

void			Cross(float[3], float[3], float[3]);
float			Dot(float [3], float [3]);
float			Unit(float [3], float [3]);


// bmp file header:
struct bmfh
{
    short bfType;		// BMP_MAGIC_NUMBER = "BM"
    int bfSize;		// size of this file in bytes
    short bfReserved1;
    short bfReserved2;
    int bfOffBytes;		// # bytes to get to the start of the per-pixel data
} FileHeader;

// bmp info header:
struct bmih
{
    int biSize;		// info header size, should be 40
    int biWidth;		// image width
    int biHeight;		// image height
    short biPlanes;		// #color planes, should be 1
    short biBitCount;	// #bits/pixel, should be 1, 4, 8, 16, 24, 32
    int biCompression;	// BI_RGB, BI_RLE4, BI_RLE8
    int biSizeImage;
    int biXPixelsPerMeter;
    int biYPixelsPerMeter;
    int biClrUsed;		// # colors in the palette
    int biClrImportant;
} InfoHeader;

// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
        0.f, 1.f, 0.f, 1.f
};

static float xy[ ] = {
        -.5f, .5f, .5f, -.5f
};

static int xorder[ ] = {
        1, 2, -3, 4
};

static float yx[ ] = {
        0.f, 0.f, -.5f, .5f
};

static float yy[ ] = {
        0.f, .6f, 1.f, 1.f
};

static int yorder[ ] = {
        1, 2, 3, -2, 4
};

static float zx[ ] = {
        1.f, 0.f, 1.f, 0.f, .25f, .75f
};

static float zy[ ] = {
        .5f, .5f, -.5f, -.5f, 0.f, 0.f
};

static int zorder[ ] = {
        1, 2, 3, 4, -5, 6
};

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

void
Axes( float length )
{
  glBegin( GL_LINE_STRIP );
  glVertex3f( length, 0., 0. );
  glVertex3f( 0., 0., 0. );
  glVertex3f( 0., length, 0. );
  glEnd( );
  glBegin( GL_LINE_STRIP );
  glVertex3f( 0., 0., 0. );
  glVertex3f( 0., 0., length );
  glEnd( );

  float fact = LENFRAC * length;
  float base = BASEFRAC * length;

  glBegin( GL_LINE_STRIP );
  for( int i = 0; i < 4; i++ )
  {
    int j = xorder[i];
    if( j < 0 )
    {

      glEnd( );
      glBegin( GL_LINE_STRIP );
      j = -j;
    }
    j--;
    glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
  }
  glEnd( );

  glBegin( GL_LINE_STRIP );
  for( int i = 0; i < 5; i++ )
  {
    int j = yorder[i];
    if( j < 0 )
    {

      glEnd( );
      glBegin( GL_LINE_STRIP );
      j = -j;
    }
    j--;
    glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
  }
  glEnd( );

  glBegin( GL_LINE_STRIP );
  for( int i = 0; i < 6; i++ )
  {
    int j = zorder[i];
    if( j < 0 )
    {

      glEnd( );
      glBegin( GL_LINE_STRIP );
      j = -j;
    }
    j--;
    glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
  }
  glEnd( );

}

// read a BMP file into a Texture:
unsigned char *
BmpToTexture( char *filename, int *width, int *height )
{
  FILE *fp;
#ifdef _WIN32
  errno_t err = fopen_s( &fp, filename, "rb" );
        if( err != 0 )
        {
		fprintf( stderr, "Cannot open Bmp file '%s'\n", filename );
		return NULL;
        }
#else
  fp = fopen( filename, "rb" );
  if( fp == NULL )
  {
    fprintf( stderr, "Cannot open Bmp file '%s'\n", filename );
    return NULL;
  }
#endif

  FileHeader.bfType = ReadShort( fp );


  // if bfType is not BMP_MAGIC_NUMBER, the file is not a bmp:

  if( VERBOSE ) fprintf( stderr, "FileHeader.bfType = 0x%0x = \"%c%c\"\n",
                         FileHeader.bfType, FileHeader.bfType&0xff, (FileHeader.bfType>>8)&0xff );
  if( FileHeader.bfType != BMP_MAGIC_NUMBER )
  {
    fprintf( stderr, "Wrong type of file: 0x%0x\n", FileHeader.bfType );
    fclose( fp );
    return NULL;
  }


  FileHeader.bfSize = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "FileHeader.bfSize = %d\n", FileHeader.bfSize );

  FileHeader.bfReserved1 = ReadShort( fp );
  FileHeader.bfReserved2 = ReadShort( fp );

  FileHeader.bfOffBytes = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "FileHeader.bfOffBytes = %d\n", FileHeader.bfOffBytes );


  InfoHeader.biSize = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biSize = %d\n", InfoHeader.biSize );
  InfoHeader.biWidth = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biWidth = %d\n", InfoHeader.biWidth );
  InfoHeader.biHeight = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biHeight = %d\n", InfoHeader.biHeight );

  const int nums = InfoHeader.biWidth;
  const int numt = InfoHeader.biHeight;

  InfoHeader.biPlanes = ReadShort( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biPlanes = %d\n", InfoHeader.biPlanes );

  InfoHeader.biBitCount = ReadShort( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biBitCount = %d\n", InfoHeader.biBitCount );

  InfoHeader.biCompression = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biCompression = %d\n", InfoHeader.biCompression );

  InfoHeader.biSizeImage = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biSizeImage = %d\n", InfoHeader.biSizeImage );

  InfoHeader.biXPixelsPerMeter = ReadInt( fp );
  InfoHeader.biYPixelsPerMeter = ReadInt( fp );

  InfoHeader.biClrUsed = ReadInt( fp );
  if( VERBOSE )	fprintf( stderr, "InfoHeader.biClrUsed = %d\n", InfoHeader.biClrUsed );

  InfoHeader.biClrImportant = ReadInt( fp );


  // fprintf( stderr, "Image size found: %d x %d\n", ImageWidth, ImageHeight );


  // pixels will be stored bottom-to-top, left-to-right:
  unsigned char *texture = new unsigned char[ 3 * nums * numt ];
  if( texture == NULL )
  {
    fprintf( stderr, "Cannot allocate the texture array!\n" );
    return NULL;
  }

  // extra padding bytes:

  int requiredRowSizeInBytes = 4 * ( ( InfoHeader.biBitCount*InfoHeader.biWidth + 31 ) / 32 );
  if( VERBOSE )	fprintf( stderr, "requiredRowSizeInBytes = %d\n", requiredRowSizeInBytes );

  int myRowSizeInBytes = ( InfoHeader.biBitCount*InfoHeader.biWidth + 7 ) / 8;
  if( VERBOSE )	fprintf( stderr, "myRowSizeInBytes = %d\n", myRowSizeInBytes );

  int oldNumExtra =  4*(( (3*InfoHeader.biWidth)+3)/4) - 3*InfoHeader.biWidth;
  if( VERBOSE )	fprintf( stderr, "Old NumExtra padding = %d\n", oldNumExtra );

  int numExtra = requiredRowSizeInBytes - myRowSizeInBytes;
  if( VERBOSE )	fprintf( stderr, "New NumExtra padding = %d\n", numExtra );


  // this function does not support compression:

  if( InfoHeader.biCompression != 0 )
  {
    fprintf( stderr, "Wrong type of image compression: %d\n", InfoHeader.biCompression );
    fclose( fp );
    return NULL;
  }


  // we can handle 24 bits of direct color:
  if( InfoHeader.biBitCount == 24 )
  {
    rewind( fp );
    fseek( fp, FileHeader.bfOffBytes, SEEK_SET );
    int t;
    unsigned char *tp;
    for( t = 0, tp = texture; t < numt; t++ )
    {
      for( int s = 0; s < nums; s++, tp += 3 )
      {
        *(tp+2) = fgetc( fp );		// b
        *(tp+1) = fgetc( fp );		// g
        *(tp+0) = fgetc( fp );		// r
      }

      for( int e = 0; e < numExtra; e++ )
      {
        fgetc( fp );
      }
    }
  }

  // we can also handle 8 bits of indirect color:
  if( InfoHeader.biBitCount == 8 && InfoHeader.biClrUsed == 256 )
  {
    struct rgba32
    {
        unsigned char r, g, b, a;
    };
    struct rgba32 *colorTable = new struct rgba32[ InfoHeader.biClrUsed ];

    rewind( fp );
    fseek( fp, sizeof(struct bmfh) + InfoHeader.biSize - 2, SEEK_SET );
    for( int c = 0; c < InfoHeader.biClrUsed; c++ )
    {
      colorTable[c].r = fgetc( fp );
      colorTable[c].g = fgetc( fp );
      colorTable[c].b = fgetc( fp );
      colorTable[c].a = fgetc( fp );
      if( VERBOSE )	fprintf( stderr, "%4d:\t0x%02x\t0x%02x\t0x%02x\t0x%02x\n",
                              c, colorTable[c].r, colorTable[c].g, colorTable[c].b, colorTable[c].a );
    }

    rewind( fp );
    fseek( fp, FileHeader.bfOffBytes, SEEK_SET );
    int t;
    unsigned char *tp;
    for( t = 0, tp = texture; t < numt; t++ )
    {
      for( int s = 0; s < nums; s++, tp += 3 )
      {
        int index = fgetc( fp );
        *(tp+0) = colorTable[index].r;	// r
        *(tp+1) = colorTable[index].g;	// g
        *(tp+2) = colorTable[index].b;	// b
      }

      for( int e = 0; e < numExtra; e++ )
      {
        fgetc( fp );
      }
    }

    delete[ ] colorTable;
  }

  fclose( fp );

  *width = nums;
  *height = numt;
  return texture;
}

int
ReadInt( FILE *fp )
{
  const unsigned char b0 = fgetc( fp );
  const unsigned char b1 = fgetc( fp );
  const unsigned char b2 = fgetc( fp );
  const unsigned char b3 = fgetc( fp );
  return ( b3 << 24 )  |  ( b2 << 16 )  |  ( b1 << 8 )  |  b0;
}

short
ReadShort( FILE *fp )
{
  const unsigned char b0 = fgetc( fp );
  const unsigned char b1 = fgetc( fp );
  return ( b1 << 8 )  |  b0;
}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
  // guarantee valid input:

  float h = hsv[0] / 60.f;
  while( h >= 6. )	h -= 6.;
  while( h <  0. ) 	h += 6.;

  float s = hsv[1];
  if( s < 0. )
    s = 0.;
  if( s > 1. )
    s = 1.;

  float v = hsv[2];
  if( v < 0. )
    v = 0.;
  if( v > 1. )
    v = 1.;

  // if sat==0, then is a gray:

  if( s == 0.0 )
  {
    rgb[0] = rgb[1] = rgb[2] = v;
    return;
  }

  // get an rgb from the hue itself:

  float i = (float)floor( h );
  float f = h - i;
  float p = v * ( 1.f - s );
  float q = v * ( 1.f - s*f );
  float t = v * ( 1.f - ( s * (1.f-f) ) );

  float r=0., g=0., b=0.;			// red, green, blue
  switch( (int) i )
  {
    case 0:
      r = v;	g = t;	b = p;
      break;

    case 1:
      r = q;	g = v;	b = p;
      break;

    case 2:
      r = p;	g = v;	b = t;
      break;

    case 3:
      r = p;	g = q;	b = v;
      break;

    case 4:
      r = t;	g = p;	b = v;
      break;

    case 5:
      r = v;	g = p;	b = q;
      break;
  }


  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
}

float
Dot(float v1[3], float v2[3])
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}




float White[ ] = { 1.,1.,1.,1. };

// utility to create an array from 3 separate values:
float * Array3( float a, float b, float c )
{
  static float array[4];

  array[0] = a;
  array[1] = b;
  array[2] = c;
  array[3] = 1.;   // Set to 1 on purpose
  return array;
}

// utility to create an array from a multiplier and an array:
float * MulArray3( float factor, float array0[3] )
{
  static float array[4];

  array[0] = factor * array0[0];
  array[1] = factor * array0[1];
  array[2] = factor * array0[2];
  array[3] = 1.;   // Set to 1 on purpose
  return array;
}

//************************************************
// LIGHTING
//************************************************


void SetMaterial( float r, float g, float b, float shininess )
{
  // Back-facing = gray
  glMaterialfv( GL_BACK, GL_EMISSION, Array3( 0., 0., 0. ) );
  glMaterialfv( GL_BACK, GL_AMBIENT, MulArray3( .4f, White ) );
  glMaterialfv( GL_BACK, GL_DIFFUSE, MulArray3( 1., White ) );
  glMaterialfv( GL_BACK, GL_SPECULAR, Array3( 0., 0., 0. ) );
  glMaterialf ( GL_BACK, GL_SHININESS, 2.f );

  // Front-facing = (r, g, b)
  glMaterialfv( GL_FRONT, GL_EMISSION, Array3( 0., 0., 0. ) );
  glMaterialfv( GL_FRONT, GL_AMBIENT, Array3( r, g, b ) );
  glMaterialfv( GL_FRONT, GL_DIFFUSE, Array3( r, g, b ) );
  glMaterialfv( GL_FRONT, GL_SPECULAR, MulArray3( .8f, White ) );
  glMaterialf ( GL_FRONT, GL_SHININESS, shininess );
}



// 'ilight' would be GL_LIGHT0 for example

void SetPointLight( int ilight, float x, float y, float z, float r, float g, float b )
{
  glLightfv( ilight, GL_POSITION, Array3( x, y, z ) );
  glLightfv( ilight, GL_AMBIENT, Array3( 0., 0., 0. ) );
  glLightfv( ilight, GL_DIFFUSE, Array3( r, g, b ) );
  glLightfv( ilight, GL_SPECULAR, Array3( r, g, b ) );
  glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
  glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
  glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
  // glLightf ( ilight, GL_CONSTANT_ATTENUATION, 0. );
  // glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
  // glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 1. );
  glEnable( ilight );
}

void SetSpotLight( int ilight, float x, float y, float z, float xdir, float ydir, float zdir, float r, float g, float b )
{
  glLightfv( ilight, GL_POSITION, Array3( x, y, z ) );
  glLightfv( ilight, GL_SPOT_DIRECTION, Array3(xdir,ydir,zdir) );
  glLightf( ilight, GL_SPOT_EXPONENT, 1. );
  glLightf( ilight, GL_SPOT_CUTOFF, 45. );
  glLightfv( ilight, GL_AMBIENT, Array3( 0., 0., 0. ) );
  glLightfv( ilight, GL_DIFFUSE, Array3( r, g, b ) );
  glLightfv( ilight, GL_SPECULAR, Array3( r, g, b ) );
  glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
  glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
  glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
  // glLightf ( ilight, GL_CONSTANT_ATTENUATION, 0. );
  // glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
  // glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 1. );
  glEnable( ilight );
}

#endif //PROJECT_FINAL_UTILS_H
#pragma clang diagnostic pop