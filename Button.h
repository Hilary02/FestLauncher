#pragma once

class Button{
public:
	Button();
	Button(Point pos, Size s,int r, int fontsize,String str);
	~Button();
	bool leftClicked();
	void setPos(Point pos);
	void setSize(Size s);
	void update();
	void draw();
	//void clickedAction();
private:
	Point pos;
	Size size;
	Font font;
	String text;
	RoundRect base;
	RoundRect over;
};