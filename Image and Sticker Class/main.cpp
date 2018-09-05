#include "StickerSheet.h"
#include "Image.h"
#include <string>

using namespace std;

int main() {
	Image base_pic;
	base_pic.readFromFile("alma.png");
	Image sticker_on;
	sticker_on.readFromFile("IllinoisLogoFullColorRGB.png");
	Image sticker_tw;
	sticker_tw.readFromFile("IllinoisLogoReversedBlueRGB.png");
	Image sticker_th;
	sticker_th.readFromFile("IllinoisLogoReversedOrangeRGB.png");
	StickerSheet ss(base_pic,5);
	ss.addSticker(sticker_on,20,200);
	ss.addSticker(sticker_tw,650,40);
	ss.addSticker(sticker_th,800,400);
	ss.removeSticker(1);
	ss.addSticker(sticker_tw,650,40);
	Image result;
	result = ss.render();
	result.writeToFile("myImage.png");
  return 0;
}
