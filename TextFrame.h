#pragma once

class TextFrame {
private:
	Texture frame;	//フレーム画像
	s3d::Point pos_m;			//描画の左上座標
	Size size_m;				//描画サイズ
	int width;					//画像サイズ
	int height;
public:
	TextFrame();
	TextFrame(FilePath texture);
	//Texture setFrame(FilePath path);
	// 描画
	void draw(Point basePos, Size size);
	void draw(Point basePos, Size size,Texture frame);

};

