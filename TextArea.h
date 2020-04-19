#pragma once
//#include "TextFrame.h"
#include <Siv3D.hpp>

/*
à–¾•¶‚Ì•\¦—Ìˆæ‚ğ’è‹`‚·‚é
*/
class TextArea {
public:
	TextArea();
	TextArea(Point pos, Size s, int fontsize, bool toggleCenter = false);
	~TextArea();
	void setPos(Point pos);
	void setSize(Size s);
	void draw(String text, Texture frame);
protected:
	Point pos;
	Size size;
	Font font;
	bool isCenterText = false;
	void drawFrame(Point basePos, Size size, Texture frame);
};