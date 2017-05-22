#ifndef VEC_H
#define VEC_H
#include <cmath>
#define PI 3.14159265

// Implementation of the Vector struct
// Vector is defined by one point on the canvas (its direction is
// obtained by drawing a line from the origin to the point)
struct Vec {
  double x, y;
  Vec(): x(0), y(0) {}
  Vec(double a, double b): x(a), y(b) {}

  Vec operator+(const Vec& p) {
    return Vec(x + p.x, y + p.y);
  }
  Vec operator-(const Vec& p) {
    return Vec(x - p.x, y - p.y);
  }

  // Add a vector to the current vector
  // Input:
  //        p: Vector to be added to the current vector
  // Return: void
  void add(const Vec& p) {
    x += p.x;
    y += p.y;
  }

  // Subtract a vector to the current vector
  // Input:
  //        p: Vector to be subtracted from the current vector
  // Return: void
  void sub(const Vec& p) {
    x -= p.x;
    y -= p.y;
  }

  // Scales the vector by a factor
  // Input: 
  //        factor: Factor by which the vector has to be scaled
  // Returns: void
  void scale(double factor) {
    x = factor*x;
    y = factor*y;
  }

  // Returns the magnitude of the vector
  // Return:
  //        magnitude of the current vector
  float mag() {
    return sqrt(x*x + y*y);
  }

  // Normalize the vector by dividing it with its magnitude
  void normalize() {
    float magnitude = mag();
    if(magnitude != 0) {
       scale(1/magnitude);
    }
  }

  // Rotate the vector by a degree angle (clockwise)
  // Input:
  //        degrees: Degree angle by which to rotate the vector
  // Return:
  //        new rotated vector
  Vec rotate(double degrees) {
    double theta = (degrees * PI / 180.0);
    double cosVal = cos(theta);
    double sinVal = sin(theta);
    double newX = x*cosVal - y*sinVal;
    double newY = x*sinVal + y*cosVal;
    return Vec(newX, newY);

  }

};

#endif
