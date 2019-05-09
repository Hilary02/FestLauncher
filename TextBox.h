#pragma once
#include "TextFrame.h"
/*
à–¾•¶‚Ì•\¦—Ìˆæ‚ğ’è‹`‚·‚é
*/
class TextBox{
public:
	TextBox();
	TextBox(Point pos, Size s, int fontsize, bool toggleCenter = false);
	~TextBox();
	void setPos(Point pos);
	void setSize(Size s);
	void draw(String text, Texture frame);
protected:
	Point pos;
	Size size;
	Font font;
	bool isCenterText;
	void drawFrame(Point basePos, Size size, Texture frame);
};