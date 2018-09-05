#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

using namespace std;

Image::Image():PNG(){}

Image::Image(unsigned int w, unsigned int h):PNG(w,h){}

void Image::lighten(){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double lum = (this->getPixel(x,y))->l + 0.1;
      (this->getPixel(x,y))->l = (lum > 1) ? 1 : lum;
    }
  } 
}

void Image::lighten(double amount){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double lum = (this->getPixel(x,y))->l + amount;
      (this->getPixel(x,y))->l = (lum > 1) ? 1 : lum;
    }
  } 
}

void Image::darken(){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double lum = (this->getPixel(x,y))->l - 0.1;
      (this->getPixel(x,y))->l = (lum <0) ? 0 : lum;
    }
  }
}

void Image::darken(double amount){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double lum = (this->getPixel(x,y))->l - amount;
      (this->getPixel(x,y))->l = (lum < 0 ) ? 0 : lum;
    }
  }
}

void Image::saturate(){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double sat = (this->getPixel(x,y))->s + 0.1;
      (this->getPixel(x,y))->s = (sat > 1) ? 1 : sat;
    }
  } 
}

void Image::saturate(double amount){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double sat = (this->getPixel(x,y))->s + amount;
      (this->getPixel(x,y))->s = (sat > 1) ? 1 : sat;
    }
  } 
}

void Image::desaturate(){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double sat = (this->getPixel(x,y))->s -0.1;
      (this->getPixel(x,y))->s = (sat <0) ? 0 : sat;
    }
  }
}

void Image::desaturate(double amount){
  for(unsigned int x=0;x<this->width();x++){
    for(unsigned int y=0;y<this->height();y++){
      double sat = (this->getPixel(x,y))->s - amount;
      (this->getPixel(x,y))->s = (sat <0) ? 0 : sat;
    }
  }
}

void Image::grayscale(){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel* pixel = this->getPixel(x, y);
      pixel->s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      double hue = (this->getPixel(x,y))->h + degrees;
      hue = (hue > 360) ? (hue-360) : hue;
      hue = (hue < 0) ? (360+hue) : hue;
      (this->getPixel(x,y))->h = hue;
    }
  }
}

void Image::illinify(){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel* pixel = this->getPixel(x, y);
      double orange = abs((pixel->h)-11.0);
      orange = (orange > 180.0) ? (360.0 - orange) : orange;
      double blue = abs((pixel->h)-216.0);
      blue = (blue > 180.0) ? (360.0 - blue) : blue;
      pixel->h = (orange < blue) ? 11.0 : 216.0;
    }
  }
}

void Image::scale(double factor){
  unsigned int oldwidth = this->width();
	unsigned int oldheight = this->height();
	unsigned int newwidth = int(oldwidth * factor);
	unsigned int newheight = int(oldheight * factor);
	HSLAPixel* oldPixel = new HSLAPixel[oldwidth*oldheight];
	for(unsigned int x = 0; x < oldwidth; x++){
		for (unsigned int y = 0; y < oldheight; y++){
			oldPixel[x + y * oldwidth] = *(this->getPixel(x,y));
		}
	}
	this->resize(newwidth,newheight);
	for(unsigned int x = 0; x < newwidth; x++){
		for (unsigned int y = 0; y < newheight; y++){
			HSLAPixel* newPixel = this->getPixel(x,y);
			int oldx = int(x/factor);
			int oldy = int(y/factor);
			int old = oldx + oldy * oldwidth;
			newPixel->h = oldPixel[old].h;
			newPixel->s = oldPixel[old].s;
			newPixel->l = oldPixel[old].l;
			newPixel->a = oldPixel[old].a;
		}
	}
  delete []oldPixel; oldPixel = NULL;
}

void Image::scale(unsigned w, unsigned h){
	unsigned int oldwidth = this->width();
	unsigned int oldheight = this->height();
  double old_a = double(oldheight)/double(oldwidth);
	double new_a = double(h)/double(w);
	unsigned int newwidth = (old_a > new_a) ? int(h/old_a) : w;
	unsigned int newheight = (old_a > new_a) ? h : int(w * old_a);
	HSLAPixel* oldPixel = new HSLAPixel[oldwidth*oldheight];
	for(unsigned int x = 0; x < oldwidth; x++){
		for (unsigned int y = 0; y < oldheight; y++){
			oldPixel[x + y * oldwidth] = *(this->getPixel(x,y));
		}
	}
	this->resize(newwidth,newheight);
	for(unsigned int x = 0; x < newwidth; x++){
		for (unsigned int y = 0; y < newheight; y++){
			HSLAPixel* newPixel = this->getPixel(x,y);
			int oldx = (x * oldwidth)/newwidth;
			int oldy = (y * oldheight)/newheight;
			int old = oldx + oldy * oldwidth;
			newPixel->h = oldPixel[old].h;
			newPixel->s = oldPixel[old].s;
			newPixel->l = oldPixel[old].l;
			newPixel->a = oldPixel[old].a;
		}
	}
    delete []oldPixel; oldPixel = NULL;
}
