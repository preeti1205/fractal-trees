#ifndef FIGURES
#define FIGURES
#include <cmath>
#define PI 3.14159265

class Vec {
public:
  Vec(): x(0), y(0) {}
  Vec(double a, double b): x(a), y(b) {}

  // Vec operator+(Vec p) const {
  //   return Vec(x + p.x, y + p.y);
  // }
  // Vec operator-(Vec p) const {
  //   return Vec(x - p.x, y - p.y);
  // }
  // Vec operator*(const double scale) const {
  //   return Vec(scale*x, scale*y);
  // }
  // Vec operator/(const double scale) const {
  //   return Vec(x/scale, y/scale);
  // }

  void add(Vec p) {
    x += p.x;
    y += p.y;
  }

  void sub(Vec p) {
    x -= p.x;
    y -= p.y;
  }

  void multiply(double scale) {
    x = scale*x;
    y = scale*y;
  }
  void div(double scale) {
    x = x/scale;
    y = y/scale;
  }

  float mag() {
    return sqrt(x*x + y*y);
  }
  void normalize() {
    float magnitude = mag();
    if(magnitude != 0) {
       div(magnitude);
    }
  }

// private:
  double x, y;
};

class Branch {
public:
  Branch(Vec pt, int d, double len): startVec(pt), dir(d), length(len) {}
private:
  Vec startVec;
  Vec endVec;
  int dir;
  double length;
};

#endif
