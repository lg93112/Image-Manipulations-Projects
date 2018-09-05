#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
	maximum = max; 
	count = 0;
	x_cord = new int[maximum-1]; 
	y_cord = new int[maximum-1];
	images = new Image*[maximum-1];
	base_picture = new Image(picture);
}

StickerSheet::~StickerSheet(){
	_destroy();
}

void StickerSheet::_copy(const StickerSheet &other){
	this->maximum = other.maximum;
	this->count = other.count;
	this->x_cord = new int[maximum-1];
	this->y_cord = new int[maximum-1];
	this->images = new Image*[maximum-1];
	this->base_picture = new Image(*(other.base_picture));
	for(unsigned i=0;i<count;i++){
		x_cord[i] = other.x_cord[i];
		y_cord[i] = other.y_cord[i];
		images[i] = new Image(*(other.images[i]));
	} 
}

void StickerSheet::_destroy(){
	for(unsigned i=0;i<count;i++){
		delete images[i]; images[i] = NULL;
	}
	delete []images; images = NULL;
	delete []x_cord; x_cord = NULL;
	delete []y_cord; y_cord = NULL;
	delete base_picture; base_picture = NULL;
}

StickerSheet::StickerSheet(const StickerSheet &other){
	_copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
	if(this == &other){return *this;}
	_destroy();
	_copy(other);
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
	Image** newimages = new Image*[max-1];
	int* newx_cord = new int[max-1];
	int* newy_cord = new int[max-1];
	count = (count<max)? count : max;
	for(unsigned i=0;i<count;i++){
		newimages[i] = images[i];
		newx_cord[i] = this->x_cord[i];
		newy_cord[i] = this->y_cord[i];
	}
	delete []images; images = NULL;
	delete []x_cord; x_cord = NULL;
	delete []y_cord; y_cord = NULL;
	this->maximum = max;
	this->images = newimages;
	this->x_cord = newx_cord;
	this->y_cord = newy_cord;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
	unsigned int lowest = count;
	for(unsigned i=0;i<count;i++){
		if(images[i] == NULL){lowest = i; break;}
	}
	if(lowest == maximum){return -1;}
	images[lowest] = new Image(sticker);
	x_cord[lowest] = x;
	y_cord[lowest] = y;
	count = (lowest==count) ? (count+1) : count;
	return lowest;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
	if( index>= count || images[index] == NULL ){return false;}
	x_cord[index] = x;
	y_cord[index] = y;
	return true;
}

void StickerSheet::removeSticker(unsigned index){
	delete images[index]; images[index] = NULL;
	x_cord[index] = 0; y_cord[index] = 0;
}

Image* StickerSheet::getSticker(unsigned index) const {
	if(index>=count){return NULL;}
	return images[index];
}

Image StickerSheet::render() const {

	Image rendered = *base_picture;

	for(unsigned k=0;k<count;k++){
		if(images[k]!=NULL){
			int width = images[k]->width();
		  int height = images[k]->height();
		  int x = x_cord[k]; int y = y_cord[k];

		  int x_extra = x+width-(rendered.width());
		  int y_extra = y+height-(rendered.height());
		  x_extra = (x_extra>0) ? x_extra:0;
		  y_extra = (y_extra>0) ? y_extra:0;
		  if(x_extra>0 || y_extra>0){
			  Image* extension = new Image(rendered.width()+x_extra,rendered.height()+y_extra);
			  for(unsigned int i=0;i<rendered.width();i++){
				  for(unsigned int j=0;j<rendered.height();j++){
					  HSLAPixel* rptr = rendered.getPixel(i,j);
					  HSLAPixel* eptr = extension->getPixel(i,j);
					  eptr->h = rptr->h; eptr->s = rptr->s;
					  eptr->l = rptr->l; eptr->a = rptr->a;
				  }
			  }
			  rendered = *extension;
			  delete extension; extension = NULL;
		  } 

		  for(int i=0;i<width;i++){
			  for(int j=0;j<height;j++){
				  HSLAPixel* pixelst = images[k]->getPixel(i,j);
				  if(pixelst->a != 0){
					  HSLAPixel* pixelsh = rendered.getPixel(x+i,y+j);
					  pixelsh->h = pixelst->h; pixelsh->l = pixelst->l;
				    pixelsh->s = pixelst->s; pixelsh->a =pixelst->a;
				  }	
			  }
		  }
		}
	}
	return rendered;

}
