//
// Created by jason on 10/11/21.
//

#ifndef PROJECT_3_OBJECTS_H
#define PROJECT_3_OBJECTS_H

#include "utils.h"
#include "colors.h"

class Objects {

public:
    // Objects();
    GLuint circleList() {
      // Create a strange circle object (Project 1)
      GLuint CircleList = glGenLists(1);
      float sRadius = 0.8f;
      int sColor = PINK;
      int sColor2 = LIGHTRED;
      int sColor3 = OFFWHITE;
      int vColor = LIGHTBLUE;
      int vColor2 = LIGHTGREEN;
      Vec3 sCenter = {0., 0., 0.};
      float sZ = 0.f;
      int numSegs = 30;
      float sDang = 2. * M_PI / (float) (numSegs);
      float sAng = 0;
      float vRadius = 0.1f;
      float vDang = 2. * M_PI / (float) (numSegs);
      float vAng = 0;
      float vZ = 0.8f;
      Vec3 vCenter;

      vector sCircle;
      sCircle.
      push_back( sCenter );
      for(
      int i = 0;
      i <=
      numSegs;
      i++ )
      {
        Vec3 sTemp = {sRadius * cos(sAng), sRadius * sin(sAng), 0.};
        sCircle.
                push_back(sTemp);
        sAng +=
                sDang;
      }

      glNewList( CircleList, GL_COMPILE
      );

      // Main Circle
      glBegin( GL_TRIANGLE_FAN );

      glVertex3f( sCenter
      .x, sCenter.y, sCenter.z );

      glColor3f( Colors[sColor][0], Colors[sColor][1], Colors[sColor][2]
      );
      for (
      vector::iterator it = sCircle.begin();
      it != sCircle.

      end();

      ++it)
      {
        Vec3 temp = *it;
        glVertex3f(temp
                           .x, temp.y, temp.z);
      }

      glEnd();

      // Border Cones
      int count = 0;
      for (
      vector::iterator it = ++sCircle.begin();
      it != sCircle.

      end();

      ++it)
      {
        Vec3 vCenter = *it;

        // Cone top
        glBegin( GL_TRIANGLE_FAN );

        if (count % 2 == 0) {
          glColor3f( Colors[vColor][0], Colors[vColor][1], Colors[vColor][2]
          );
        } else {
          glColor3f( Colors[vColor2][0], Colors[vColor][1], Colors[vColor2][2]
          );
        }

        glVertex3f( vCenter
                            .x, vCenter.y, vCenter.z );    // Center
        for(
                int j = 0;
                j<numSegs;
                j++ )
        {
          glVertex3f(vRadius
                     *
                     cos(vAng)
                     + vCenter.x,
                     vRadius *sin(vAng)
                     + vCenter.y, vZ);
          vAng +=
                  vDang;
        }

        glEnd();

        // Cone base
        glBegin( GL_TRIANGLE_FAN );

        if (count % 2 == 0) {
          glColor3f( Colors[vColor][0], Colors[vColor][1], Colors[vColor][2]
          );
        } else {
          glColor3f( Colors[vColor2][0], Colors[vColor][1], Colors[vColor2][2]
          );
        }

        glVertex3f( vCenter
                            .x, vCenter.y, vZ );    // Center
        for(
                int j = 0;
                j<numSegs;
                j++ )
        {
          glVertex3f(vRadius
                     *
                     cos(vAng)
                     + vCenter.x,
                     vRadius *sin(vAng)
                     + vCenter.y, vZ);
          vAng +=
                  vDang;
        }

        glEnd();

        vDang = 2. * M_PI / (float) (numSegs - 1);
        vAng = 0;
        count++;
      }
      count = 0;

      // Secondary Circle
      glBegin( GL_TRIANGLE_FAN );

      float zOffset = 0.7f;

      glVertex3f( sCenter
      .x, sCenter.y, zOffset );

      glColor3f( Colors[sColor2][0], Colors[sColor2][1], Colors[sColor2][2]
      );
      for (
      vector::iterator it = sCircle.begin();
      it != sCircle.

      end();

      ++it)
      {
        Vec3 temp = *it;
        glVertex3f(temp
                           .x, temp.y, zOffset);
      }

      glEnd();


      float z3Offset = 0.8f;
      float scaleFactor = 0.04f;
      float colorOffset = 0.0f;


      for (
      int i = 0;
      i < 8; i++)
      {
        // Tertiary Circle
        glBegin( GL_TRIANGLE_FAN );

        z3Offset += 0.1f;
        scaleFactor += 0.05f;
        colorOffset -= 0.02f;


        glColor3f( Colors[sColor3][0]
                   + colorOffset * 3, Colors[sColor3][1] + colorOffset * 2, Colors[sColor3][2] + colorOffset);
        glVertex3f( sCenter
                            .x, sCenter.y, z3Offset );
        for (
                vector::iterator it = sCircle.begin();
                it != sCircle.

                        end();

                ++it)
        {
          Vec3 temp = *it;
          glVertex3f(temp
                             .
                                     x *scaleFactor, temp
                                                             .
                                                                     y *scaleFactor, z3Offset
          );
        }

        glEnd();

      }

      glEndList();
      return CircleList;
    };

    // Plane
    GLuint planeList( float size = 100.f, int color = GRAY30, float height = -1.f ) {
      // Create a Plane
      GLuint PlaneList = glGenLists( 1 );
      float pSize = size;
      float pHeight = height;
      int pColor = color;
      glNewList( PlaneList, GL_COMPILE );
        glPushMatrix( );
          glBegin( GL_QUADS );

            glColor3f( Colors[pColor][0], Colors[pColor][1], Colors[pColor][2] );
            glVertex3f( -pSize, pHeight, -pSize );
            glVertex3f( -pSize, pHeight,  pSize );
            glVertex3f(  pSize, pHeight,  pSize );
            glVertex3f(  pSize, pHeight, -pSize );

          glEnd( );
        glPopMatrix();
      glEndList( );

      return PlaneList;
    }


    // Helicopter Body
    GLuint helicopter() {
      #include "heli.550"

      GLuint HeliBodyList = glGenLists( 1 );
      glNewList( HeliBodyList, GL_COMPILE );

      int i;
      struct point *p0, *p1, *p2;
      struct tri *tp;
      float p01[3], p02[3], n[3];

      glPushMatrix( );
      glTranslatef( 0., -1., 0. );
      glRotatef(  97.,   0., 1., 0. );
      glRotatef( -15.,   0., 0., 1. );
      glBegin( GL_TRIANGLES );
      for( i=0, tp = Helitris; i < Helintris; i++, tp++ )
      {
        p0 = &Helipoints[ tp->p0 ];
        p1 = &Helipoints[ tp->p1 ];
        p2 = &Helipoints[ tp->p2 ];

        // fake "lighting" from above:

        p01[0] = p1->x - p0->x;
        p01[1] = p1->y - p0->y;
        p01[2] = p1->z - p0->z;
        p02[0] = p2->x - p0->x;
        p02[1] = p2->y - p0->y;
        p02[2] = p2->z - p0->z;
        Cross( p01, p02, n );
        Unit( n, n );
        n[1] = fabs( n[1] );
        n[1] += .25;
        if( n[1] > 1. )
          n[1] = 1.;
        // glColor3f( 0., n[1], 0. );
        glColor3f( Colors[LIGHTRED][0] * n[1], Colors[LIGHTRED][1] * n[1], Colors[LIGHTRED][2] * n[1] );

        glVertex3f( p0->x, p0->y, p0->z );
        glVertex3f( p1->x, p1->y, p1->z );
        glVertex3f( p2->x, p2->y, p2->z );
      }
      glEnd( );
      glPopMatrix( );

      glEndList( );

      return HeliBodyList;
    }

    // HELICOPTER BLADES
    GLuint heliBlades() {
      float n[3];


      GLuint BladeList = glGenLists( 1 );
      glNewList( BladeList, GL_COMPILE );

      glPushMatrix( );
      // blade parameters:

        #define BLADE_RADIUS		1.0
        #define BLADE_WIDTH		 	0.4

        // draw the helicopter blade with radius BLADE_RADIUS and
        //	width BLADE_WIDTH centered at (0.,0.,0.) in the XY plane

        glBegin( GL_TRIANGLES );
          glColor3f( Colors[LIGHTBLUE][0] * n[1], Colors[LIGHTBLUE][1] * n[1], Colors[LIGHTBLUE][2] * n[1] );
          glVertex2f(  BLADE_RADIUS,  BLADE_WIDTH/2. );
          glVertex2f(  0., 0. );
          glVertex2f(  BLADE_RADIUS, -BLADE_WIDTH/2. );

          glVertex2f( -BLADE_RADIUS, -BLADE_WIDTH/2. );
          glVertex2f(  0., 0. );
          glVertex2f( -BLADE_RADIUS,  BLADE_WIDTH/2. );
        glEnd( );
      glPopMatrix( );

      glEndList( );

      return BladeList;
    };


    // CUBE
    GLuint cube(float size = 2.f) {
      float dx = size / 2.f;
      float dy = size / 2.f;
      float dz = size / 2.f;

      GLuint CubeList = glGenLists( 1 );
      glNewList( CubeList, GL_COMPILE );

        glPushMatrix( );

          glBegin( GL_QUADS );
            glColor3f( 0., 0., 1. );
            glVertex3f( -dx, -dy,  dz );
            glVertex3f(  dx, -dy,  dz );
            glVertex3f(  dx,  dy,  dz );
            glVertex3f( -dx,  dy,  dz );

            glVertex3f( -dx, -dy, -dz );
            glVertex3f( -dx,  dy, -dz );
            glVertex3f(  dx,  dy, -dz );
            glVertex3f(  dx, -dy, -dz );

            glColor3f( 1., 0., 0. );
            glVertex3f(  dx, -dy,  dz );
            glVertex3f(  dx, -dy, -dz );
            glVertex3f(  dx,  dy, -dz );
            glVertex3f(  dx,  dy,  dz );

            glVertex3f( -dx, -dy,  dz );
            glVertex3f( -dx,  dy,  dz );
            glVertex3f( -dx,  dy, -dz );
            glVertex3f( -dx, -dy, -dz );

            glColor3f( 0., 1., 0. );
            glVertex3f( -dx,  dy,  dz );
            glVertex3f(  dx,  dy,  dz );
            glVertex3f(  dx,  dy, -dz );
            glVertex3f( -dx,  dy, -dz );

            glVertex3f( -dx, -dy,  dz );
            glVertex3f( -dx, -dy, -dz );
            glVertex3f(  dx, -dy, -dz );
            glVertex3f(  dx, -dy,  dz );
          glEnd( );
        glPopMatrix( );

      glEndList( );
      return CubeList;
    }


};

#endif //PROJECT_3_OBJECTS_H
