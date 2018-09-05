#include <string>
#include "mp1.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;
using namespace std;

void rotate(std::string inputFile, std::string outputFile) {
     // Load in.png
     PNG* input = new PNG();
     input->readFromFile(inputFile);
     unsigned width = input->width();
     unsigned height = input->height();
     // Create out.png
     PNG* output = new PNG(width, height);
     // Go over the whole image and rotate
     unsigned H = (height+1)/2;
     unsigned W = (width+1)/2;
     // Rotate up and down
     for(unsigned x=0; x<width; x++){
	for(unsigned y=0; y<H; y++){
	   unsigned opposite = (height%2 == 0) ? (y+1+(H-(y+1))*2) : (y+2+(H-(y+2))*2);
	   HSLAPixel* InOpposite =  input->getPixel(x,opposite);
	   HSLAPixel* InCurrent = input->getPixel(x,y);
	   HSLAPixel* OutCurrent = output->getPixel(x,y);
	   HSLAPixel* OutOpposite = output->getPixel(x,opposite);
	   OutCurrent->h = InOpposite->h; OutCurrent->s = InOpposite->s;
	   OutCurrent->l = InOpposite->l; OutCurrent->a = InOpposite->a; 
	   OutOpposite->h = InCurrent->h; OutOpposite->s = InCurrent->s;
	   OutOpposite->l = InCurrent->l; OutOpposite->a = InCurrent->a; 
	}
    }
    // Rotate left and right
    PNG* newinput = new PNG();
    *newinput = *output;
    for(unsigned y=0; y<height; y++){
	for(unsigned x=0; x<W; x++){
	   unsigned opposite = (width%2 == 0) ? (x+1+(W-(x+1))*2) : (x+2+(W-(x+2))*2);
	   HSLAPixel* InOpposite =  newinput->getPixel(opposite,y);
	   HSLAPixel* InCurrent = newinput->getPixel(x,y);
	   HSLAPixel* OutCurrent = output->getPixel(x,y);
	   HSLAPixel* OutOpposite = output->getPixel(opposite,y);
	   OutCurrent->h = InOpposite->h; OutCurrent->s = InOpposite->s;
	   OutCurrent->l = InOpposite->l; OutCurrent->a = InOpposite->a; 
	   OutOpposite->h = InCurrent->h; OutOpposite->s = InCurrent->s;
	   OutOpposite->l = InCurrent->l; OutOpposite->a = InCurrent->a; 
	}
    }
    // Save the output file
    output->writeToFile(outputFile);
    // Clean up memory
    delete input; input = NULL;
    delete output; output =NULL;
}
