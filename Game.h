#pragma once
#include "TextFrame.h"
struct Info{
	String name;
	String summary;
	String frameImg;
	String explain;
};

/*
ƒQ[ƒ€‚Ìî•ñ‚ğŠi”[‚·‚éD
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