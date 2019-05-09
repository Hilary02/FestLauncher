#include "stdafx.h"
#include "Button.h"


Button::Button() {
}

Button::Button(Point pos, Size s, int r, int fontsize, String str) {
	this->pos =pos;
	size = s;
	font = Font(fontsize);
	text = str;
	base = RoundRect(pos, s, r);
	over = RoundRect(pos, s, r);
}


Button::~Button(){}

bool Button::leftClicked() {
	return this->base.leftClicked;
}

void Button::setPos(Point p) {
	pos = p;
	base.setPos(p);
	over.setPos(p);
}
void Button::setSize(Size s){
	size = s;
	base.setSize(s);
	over.setSize(s);
}


void Button::update() {
}

void Button::draw() {
	base.draw(Color(255, 255, 255));
	if (base.mouseOver) {
		over.draw(Color(255, 0, 0, 200));
	}
	font.drawCenter(text, Vec2(pos.x + size.x / 2, pos.y + size.y/ 2), Palette::Black);
}

//void Button::clickedAction() {
//}
