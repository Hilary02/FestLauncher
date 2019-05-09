#include "stdafx.h"
#include "TextFrame.h"

TextFrame::TextFrame()
{
}

TextFrame::TextFrame(FilePath texture) {
	//frame =  setFrame(texture);
}

//Texture TextFrame::setFrame(FilePath path){
//	FilePath foldername = L"./Launcher";
//	Array<FilePath> folders = FileSystem::DirectoryContents(L"./Launcher");
//	FilePath tmpFrame = L"./Launcher/redFrame.png";
//	for (const auto& file : folders) {
//		if (file.includes(path) == true) {
//			tmpFrame = foldername + path;
//		}
//	}
//	return Texture(tmpFrame);
//}

void TextFrame::draw(Point basePos, Size size) {
	const int w = frame.width / 3;
	const int h = frame.height / 3;
	const std::array<int, 3> width = { w, size.x - 2 * w, w };
	const std::array<int, 3> height = { h, size.y - 2 * h, h };
	Point p(basePos);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			frame({ w*x,h*y }, { w, h }).resize(width[x], height[y]).draw(p);
			p.x += width[x];
		}
		p.x = basePos.x;
		p.y += height[y];
	}
}

void TextFrame::draw(Point basePos, Size size, Texture frame){
	this->frame = frame;
	const int w = frame.width / 3;
	const int h = frame.height / 3;
	const std::array<int, 3> width = { w, size.x - 2 * w, w };
	const std::array<int, 3> height = { h, size.y - 2 * h, h };
	Point p(basePos);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			frame({ w*x,h*y }, { w, h }).resize(width[x], height[y]).draw(p);
			p.x += width[x];
		}
		p.x = basePos.x;
		p.y += height[y];
	}
}
