#include <fstream>
#include <iostream>
#include <cmath>
#include "canvas.h"
using namespace std;

// Recursive function that will populate the Canvas::pixel_col of the canvas at each level
void createTree(Canvas &canv, Vec rootA, Vec rootB, const double angle ) {
	Vec dir = rootB - rootA;
	int magni = dir.mag();
	if(magni < 5) return;
	canv.createBranch(rootA, rootB, magni);
	dir.scale(0.75);
  	Vec rightEnd = dir.rotate(angle);
  	Vec leftEnd = dir.rotate(-1*angle);
  	createTree(canv, rootB, rightEnd + rootB, angle );
  	createTree(canv, rootB, leftEnd + rootB, angle );
}

int main() {

  Canvas canvas;
  double degrees;
  const double sWidth = canvas.windowWidth();
  const double sHeight = canvas.windowHeight();
  cout << "Enter an angle between 0 to 90 degrees: ";
  cin >> degrees;
  Vec rootA(sWidth/2,sHeight);
  Vec rootB(sWidth/2, sHeight - 100);
  createTree(canvas, rootA, rootB, degrees);
  ofstream out("Tree.ppm");
  canvas.buildCanvas(out);

}
