#pragma once
//#include "TextFrame.h"
#include <Siv3D.hpp>

/*
説明文の表示領域を定義する
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
	Rect rect;
	bool isCenterText = false;
	void drawFrame(Point basePos, Size size, Texture frame);
};