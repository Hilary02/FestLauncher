#include "stdafx.h"
#include "TextArea.h"

TextArea::TextArea() {}

TextArea::TextArea(Point pos, Size s, int fontsize, bool toggleCenter) {
	this->pos = Point(pos);
	this->size = s;
	font = Font(fontsize);
	this->isCenterText = toggleCenter;
	rect = Rect(pos, size);
}

TextArea::~TextArea() {}

void TextArea::setPos(Point p) {
	this->pos = Point(p);
}

void TextArea::setSize(Size s) {
	this->size = s;
}

void TextArea::draw(String text, Texture frame) {
	drawFrame(pos, size, frame);	//ƒtƒŒ[ƒ€•`‰æ

	font(text).draw(rect, Palette::Black);
	//•¶š”ãŒÀ‚ğİ’è
	//unsigned int n = Min(font.drawableCharacters(text, size.x - 40), text.length);
	//int t = Max(1, (size.y - 10) / font.height());
	//String cuttedText = text.substr(0, n * t);
	//if (n != text.length) {
	//	cuttedText += U"...";
	//}
	//if (isCenterText) {
	//	font(cuttedText).draw(Vec2(pos.x + size.x / 2, pos.y + size.y / 2), Palette::Black);
	//}
	//else {
	//	font(cuttedText).draw(Vec2(pos.x + 10, pos.y + 10), Palette::Black);
	//}
}


void TextArea::drawFrame(Point basePos, Size size, Texture frame) {
	const int w = frame.width() / 3;
	int h = frame.height() / 3;
	const std::array<int, 3> width = { w, size.x - 2 * w, w };
	const std::array<int, 3> height = { h, size.y - 2 * h, h };
	Point p(basePos);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			frame({ w * x,h * y }, { w, h }).resized(width[x], height[y]).draw(p);
			p.x += width[x];
		}
		p.x = basePos.x;
		p.y += height[y];
	}
}