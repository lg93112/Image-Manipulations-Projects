#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"

using namespace std;

class StickerSheet{
	public:
		StickerSheet(const Image &picture, unsigned max);
	  ~StickerSheet();
	  StickerSheet(const StickerSheet &other);
	  const StickerSheet& operator=(const StickerSheet &other);
	  void changeMaxStickers(unsigned max);
	  int addSticker(Image &sticker, unsigned x, unsigned y);
	  bool translate(unsigned index, unsigned x, unsigned y);
	  void removeSticker(unsigned index);
	  Image* getSticker(unsigned index) const;
	  Image render() const;

	private:
		Image* base_picture;
		Image** images;
		int* x_cord; int* y_cord;
		unsigned maximum;
		unsigned count;
		void _copy(const StickerSheet &other);
		void _destroy();
};

#endif