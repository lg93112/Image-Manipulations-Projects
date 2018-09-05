#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <list>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pn = png;
  st.x = start.x;
  st.y = start.y;
  tol = tolerance;
  int m = int(png.width());
  int n = int(png.height());
  for(int i=0;i<m;i++){
    vector<int> v(n,0);
    Matrix.push_back(v);
  }
  s.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator it(this,tol,st,pn);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(!visit(point)){s.push(point);}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = s.top();
  s.pop();
  int x = int(top.x); int y = int(top.y);
  Matrix[x][y] = 1;
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(s.empty()){return true;}
  return false;
}

bool DFS::visit(Point p){
  int x = int(p.x); int y = int(p.y);
  if(Matrix[x][y]==1){return true;}
  return false;
}
