#ifndef COLOR
#define COLOR

// Defines the colors for entities in canvas.
struct Color {
    Color(): r(0), g(0), b(0) {}
    Color(double red, double green, double blue): r(red), g(green), b(blue) {}

    Color operator*(const double scale) {
      return Color(r*scale, g*scale, b*scale);
    }

    Color operator+(Color mix) {
      return Color( (r + mix.r)/2, (g + mix.g)/2, (b + mix.b)/2);
    }

    double r, g, b;
};
#endif
