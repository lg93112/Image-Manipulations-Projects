#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <cmath>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */

MyColorPicker::MyColorPicker(unsigned stx,unsigned sty){
  start.x = stx;
  start.y = sty;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  int d = int(sqrt((start.x-x)*(start.x-x)+(start.y-y)*(start.y-y)));
  if(d%6==0){HSLAPixel yellow0(60,1,0.97);return yellow0;}
  if(d%6==1){HSLAPixel yellow1(57,1,0.91);return yellow1;}
  if(d%6==2){HSLAPixel yellow2(60,1,0.5);return yellow2;}
  if(d%6==3){HSLAPixel yellow3(56,1,0.5);return yellow3;}
  if(d%6==4){HSLAPixel yellow4(52,1,0.5);return yellow4;}
  if(d%6==5){HSLAPixel yellow5(56,0.82,0.59);return yellow5;}
  return HSLAPixel();
}
