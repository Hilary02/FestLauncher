#pragma once

class TextFrame {
private:
	Texture frame;	//�t���[���摜
	s3d::Point pos_m;			//�`��̍�����W
	Size size_m;				//�`��T�C�Y
	int width;					//�摜�T�C�Y
	int height;
public:
	TextFrame();
	TextFrame(FilePath texture);
	//Texture setFrame(FilePath path);
	// �`��
	void draw(Point basePos, Size size);
	void draw(Point basePos, Size size,Texture frame);

};

