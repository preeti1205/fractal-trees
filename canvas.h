#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"
#include "vec.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// The class used for creating the canvas object. Graphics is drawn over the
// canvas. 
class Canvas {
public:
  Canvas(): width(500), height(500) {}

  int windowWidth() { return width; }
  int windowHeight() { return height; }

  //build the final canvas
  void buildCanvas(std::ofstream &out) {
    out << "P3\n" << width << std::endl << height << std::endl << "255\n" ;
    for(int y = 0; y < height; ++y) {
      for(int x = 0; x < width; ++x) {
        out << (int)pixel_col[x][y].r << std::endl;
        out << (int)pixel_col[x][y].g << std::endl;
        out << (int)pixel_col[x][y].b << std::endl;
      }
    }
  }

  // Bresenham's line algorithm  -- to draw a line approximation
  // Calculates the coordinates for an approximate line between two vectors on the canvas
  // and populates the Canvas:pixel_col array accordingly
  // Source: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  // Input:
  //        startP: Start vector
  //        endP  : End vector
  //        mag   : Length of the line
  // Return: void
  void createBranch(Vec startP, Vec endP, double mag) {
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
          pixel_col[yMid][x].g = mag*255;
          pixel_col[yMid][x].b = mag*200;
      }
      else
      {
          pixel_col[x][yMid].g = mag*255;
          pixel_col[x][yMid].b = mag*200;
      }
   
      error -= dy;
      if(error < 0)
      {
          yMid += ystep;
          error += dx;
      }
    }
  }

private:
  int width; 
  int height;
  Vec origin;
  Color pixel_col[500][500];
};

#endif
