
#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
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
  q.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator it(this,tol,st,pn);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(!visit(point)){q.push(point);}
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point pop = q.front();
  q.pop();
  int x = int(pop.x); int y = int(pop.y);
  Matrix[x][y] = 1;
  return pop;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(q.empty()){return true;}
  return false;
}

bool BFS::visit(Point p){
  int x = int(p.x); int y = int(p.y);
  if(Matrix[x][y]==1){return true;}
  return false;
}
