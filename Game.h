#pragma once
#include "TextFrame.h"
struct Info{
	String name;
	String summary;
	String frameImg;
	String explain;
};

/*
ゲームの情報を格納する．
*/
class Game {
public:
	FilePath exePath;
	Info info;
	Texture img_banner;
	Texture textFrame;
	Texture img_operation;
	Array<Texture> screenshots;
};