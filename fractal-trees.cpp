#include <fstream>
#include <iostream>
#include <cmath>
#include "screen.h"
using namespace std;

int main() {

  Screen screen;
  ofstream out("drawTree.ppm");
  const double sWidth = screen.windowWidth();
  const double sHeight = screen.windowHeight();
  // screen.transform(sWidth/2, sHeight);
  // screen.drawLine(Vec(0, 0), Vec(0, 2), out);
  screen.drawBranch(Vec(sWidth/2,sHeight), Vec(sWidth/2, sHeight - 100));
  screen.buildScreen(out);

}
