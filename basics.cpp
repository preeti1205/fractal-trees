#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
  double x, y, z;
  Point(double a, double b, double c) : x(a), y(b), z(c) {}
  Point operator-(Point &p) const {
    return Point(x - p.x, y - p.y, z - p.z);
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
  bool intersect(Ray ray, double &t) {
    Point o = ray.origin;
    Point d = ray.dir;
    Point oc = o - center;
    double b = 2*dot(oc, d);
    double c = dot(oc, oc) - radius*radius;
    double disc = b*b - 4*c;
    if(disc < 0) return false;
    else {
      disc = sqrt(disc);
      double t0 = - b - disc;
      double t1 = -b + disc;
      t = t0 < t1 ? t0 : t1;
      return true;
    }
  }
};

struct Color {
  double r,g, b;
  Color(): r(0), g(0), b(0) {}
  Color(double red, double green, double blue): r(red), g(green), b(blue) {}
};

int main() {
    const int width = 500;
    const int height = 500;

    ofstream out("out.ppm");
    out << "P3\n" << width << endl << height << endl << "255\n" ;
    Color pixel_col[height][width];
    Color white(255, 255, 255);
    Sphere sphere(Point(width/2, height/2, 80), 80);

    for(int y = 0; y < height; ++y ) {
      for(int x = 0; x < width; ++x) {
          //send a ray
          Ray ray(Point(x, y, 0), Point(0, 0, 1));
          double t = 20000;

          if (sphere.intersect(ray, t)) {
            pixel_col[y][x] = white;

          }
          out << pixel_col[y][x].r << endl;
          out << pixel_col[y][x].g << endl;
          out << pixel_col[y][x].b << endl;
      }
    }
}
