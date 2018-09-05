#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  trav = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* tr,double to,Point st, PNG pn){
  trav = tr;
  tolerance = to;
  start.x = st.x;
  start.y = st.y;
  png = pn;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point curr;
  curr.x = ((*trav).peek()).x;
  curr.y = ((*trav).peek()).y;
  (*trav).pop();
  for(int i=1;i<=4;i++){
    int a; int b;
    if(i==1){a=1;b=0;}
    if(i==2){a=0;b=1;}
    if(i==3){a=-1;b=0;}
    if(i==4){a=0;b=-1;}
    int nextx = int(curr.x)+a; int nexty = int(curr.y)+b;
    if(nextx>=0 && nexty>=0 && nextx<=int(png.width())-1 && nexty<=int(png.height())-1){
      Point pt(nextx,nexty);
      HSLAPixel* pixel = png.getPixel(pt.x,pt.y);
      HSLAPixel* sta = png.getPixel(start.x,start.y);
      if(calculateDelta(*pixel,*sta) < tolerance){
        (*trav).add(pt);
      }
    }
  }

  if((*trav).empty()){trav=NULL;return *this;}

  while((*trav).visit((*trav).peek()) && !(*trav).empty()){
    (*trav).pop();
    if((*trav).empty()){break;}
  }

  if((*trav).empty()){trav=NULL;}

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if(trav==NULL || (*trav).empty()){return Point(0,0);}
  return (*trav).peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(other.trav == NULL){
    if(trav == NULL){return false;}
  }
  else{
    if(trav != NULL){
      if((*trav).empty() && (other.trav)->empty()){return false;}
      if(!(*trav).empty() && !((other.trav)->empty()) && (*trav).peek() == (other.trav)->peek()){return false;}
    }
  }
  return true;
}
