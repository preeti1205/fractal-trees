#include <fstream>
#include <iostream>
#include <cmath>
#include "color.h"
using namespace std;

class Point {
public:
  double x, y, z;
  Point(): x(0), y(0), z(0) {}
  Point(double a, double b, double c) : x(a), y(b), z(c) {}
  Point operator-(Point p) const {
    return Point(x - p.x, y - p.y, z - p.z);
  }

  Point operator+(Point p) const {
    return Point(x + p.x, y + p.y, z + p.z);
  }

  Point operator*(const double scale) const {
    return Point(scale*x, scale*y, scale*z);
  }

  Point operator/(const double scale) const {
    return Point(x/scale, y/scale, z/scale);
  }

  Point normalize() {
    double mag = sqrt(x*x + y*y + z*z);
    return Point(x/mag, y/mag, z/mag);
  }
};

class Ray {
public:
  Point origin;
  Point dir;
  Ray(Point o, Point d) : origin(o), dir(d) {}
};

double dot(Point p1, Point p2) {
  return (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z);
}

class Sphere {
public:
  Point center;
  double radius;
  Sphere(Point ctr, double r) : center(ctr), radius(r) {}

  Point getNormal(Point pi) {
    return (center - pi)/ radius;
  }

  bool intersect(Ray ray, double &t) {
    Point o = ray.origin;
    Point d = ray.dir;
    Point oc = o - center;   //vector between center and point in consideration
    double b = 2*dot(oc, d);
    double c = dot(oc, oc) - radius*radius;
    double disc = b*b - 4*c;
    if(disc < 0) return false;
    else {
      disc = sqrt(disc);
      double t0 = - b - disc;
      double t1 = - b + disc;
      t = t0 < t1 ? t0 : t1;
      return true;
    }
  }
};

int main() {
    const int width = 500;
    const int height = 500;

    ofstream out("out.ppm");
    out << "P3\n" << width << endl << height << endl << "255\n" ;  //for creating a ppm bitmap with max color value 255
    Color pixel_col[height][width];
    Color white(255, 255, 255);
    Color red(255, 0, 0);

    Sphere sphere(Point(width/2, height/2, 80), 80);
    Sphere light(Point(width/2, 0, 80), 1);

    for(int y = 0; y < height; ++y ) {
      for(int x = 0; x < width; ++x) {
          //send a ray
          Ray ray(Point(x, y, 0), Point(0, 0, 1));
          double t = 20000;

          if (sphere.intersect(ray, t)) {
            Point pi = ray.origin + (ray.dir*t);
            Point L = light.center - pi;
            Point N = sphere.getNormal(pi);
            double dt = dot(L.normalize(), N.normalize());
            // pixel_col[y][x] = white;

            pixel_col[y][x] = red + (white*dt);
            if (pixel_col[y][x].r < 0) pixel_col[y][x].r = 0;
            if (pixel_col[y][x].g < 0) pixel_col[y][x].g = 0;
            if (pixel_col[y][x].b < 0) pixel_col[y][x].b = 0;
            if (pixel_col[y][x].r > 255) pixel_col[y][x].r = 255;
            if (pixel_col[y][x].g > 255) pixel_col[y][x].g = 255;
            if (pixel_col[y][x].b > 255) pixel_col[y][x].b = 255;


          }
          out << (int)pixel_col[y][x].r << endl;
          out << (int)pixel_col[y][x].g << endl;
          out << (int)pixel_col[y][x].b << endl;
      }
    }
}
