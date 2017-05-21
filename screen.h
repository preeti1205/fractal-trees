#ifndef SCREEN
#define SCREEN

#include "color.h"
#include "figures.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

//Todo : Change Screen to Canvas

class Screen {
public:
  Screen(): width(500), height(500) {}

  int windowWidth() { return width; }
  int windowHeight() { return height; }

  //build the final canvas
  void buildScreen(std::ofstream &out) {
    out << "P3\n" << width << std::endl << height << std::endl << "255\n" ;
    //Color pixel_col[height][width];
    for(int y = 0; y < height; ++y) {
      for(int x = 0; x < width; ++x) {
        out << (int)pixel_col[x][y].r << std::endl;
        out << (int)pixel_col[x][y].g << std::endl;
        out << (int)pixel_col[x][y].b << std::endl;
      }
    }
  }

  void translate(double x_, double y_) {
    origin.x += x_;
    origin.y += y_;
  }

  void rotate(double degrees) {
    // Todo:  add a case for negative angles
    double theta = (degrees * PI / 180.0);
    double cosVal = cos(theta);
    double sinVal = sin(theta);
    double newX = (origin.x)*cosVal - (origin.y)*sinVal;
    double newY = (origin.x)*sinVal - (origin.y)*cosVal;

  }

  //Bresenham's line algorithm  -- to draw a line approximation
  void drawBranch(Vec startP, Vec endP) {
    const bool slope = fabs(endP.y - startP.y) > fabs(endP.x - startP.x);

    if(slope) {
      std::swap(startP.x, startP.y);
      std::swap(endP.x, endP.y);
    }

    if(startP.x > endP.x) {
      std::swap(startP.x, endP.x);
      std::swap(startP.y, endP.y);
    }

    double dy = fabs(endP.y - startP.y);
    double dx = (endP.x - startP.x);

    float error = dx / 2.0f;
    const int ystep = (startP.y < endP.y) ? 1 : -1;
    int yMid = (int)startP.y;
   
    const int maxX = (int)endP.x;
    for(int x=(int)startP.x; x<maxX; ++x)
    {
      if(slope)
      {
          pixel_col[yMid][x].r = 255;
      }
      else
      {
          pixel_col[x][yMid].r = 255;
      }
   
      error -= dy;
      if(error < 0)
      {
          yMid += ystep;
          error += dx;
      }
    }
    // double D = 2*dy - dx;
    // int yMid = startP.y;

    // for(int x = startP.x; x < endP.x ; ++x) {
    //   pixel_col[yMid][x].r = 255;
    //   if ( D > 0 ) {
    //      yMid += 1;
    //      D -= 2*dx;
    //   }
    //   D += 2*dy ;
    // }
  }

private:
  int width; 
  int height;
  Vec origin;
  Color pixel_col[500][500];
};
#endif
