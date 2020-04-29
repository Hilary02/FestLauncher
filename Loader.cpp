#include "stdafx.h"
#include "Loader.h"

Loader::Loader(const FilePath& path) :foldername(path) {
}

Loader::~Loader()
{
}

Array<Game> Loader::LoadGames() {
	//�Q�[���t�H���_���̃f�B���N�g�����i�[
	Array<FilePath> folders = FileSystem::DirectoryContents(foldername,false);

	Array<Game> tmpGameList;
	for (unsigned int i = 0; i < folders.size(); i++) {
		Array<FilePath> files = FileSystem::DirectoryContents(folders[i]);
		Game tmpGame;

		tmpGame.exePath = SearchExePath(files);

		if (tmpGame.exePath.length() == 0) break; //���s������̂��Ȃ���Θb�ɂȂ�Ȃ�

		tmpGame.info = SearchInfo(files);
		tmpGame.img_banner = SearchBannerImg(files);
		tmpGame.img_operation = SearchOperationImg(files);
		tmpGame.screenshots = SearchSS(files);

		tmpGame.textFrame = SetTextFrame(tmpGame.info.frameImg);
		tmpGameList.push_back(tmpGame);
	}

	return tmpGameList;
}

//�����̗����C���O�̏����ň�ԍŏ��ɑ��݂���exe��ǂݍ��ށD
//config.exe�Ȃǂ���ɂ������ꍇ�C��ǂݍ��݂�����
FilePath Loader::SearchExePath(const Array<FilePath>& files) {
	FilePath exepath;
	for (const auto& file : files) {
		if (file.includes(U".exe") == true) {
			exepath = file;
			break;
		}
	}
	return exepath;
}

//���Ƃ�info.txt�����݂��Ȃ��Ă��G���[�͋N���Ȃ��D���C�A�E�g�͕ۏ؂��Ȃ�
Info Loader::SearchInfo(const Array<FilePath>& files) {
	Info info;
	TextReader reader;

	for (const auto& file : files) {
		String line;
		if (file.includes(U"info.txt") == true) {
			reader.open(file);
			reader.readLine(info.name);
			reader.readLine(info.summary);
			reader.readLine(info.frameImg);
			//reader.readLine(info.bannerColor);
			for (int i = 0; reader.readLine(line) && i < 3; i++) {	//�s�����݂���3�s�ȓ�
				info.explain += (line + U"\n");
			}
			break;
		}
	}
	return info;
}

//���s�̃����`����image��ǂݍ���ł��邽�߁C������ꎞ�I�ɓ��P���Ă���
//����ȊO�ɂ��摜�̓ǂݍ��݂����邽�߁C�Ӗ�����薾�m�ɂ�����
//TODO:banner�ɕς���\��
Texture Loader::SearchBannerImg(const Array<FilePath>& files) {
	FilePath tmpBanner;

	tmpBanner = U"./Design/noImg.png";
	for (const auto& file : files) {
		//if (file.includes(U"banner") == true) {
		if (file.includes(U"image") == true) {
			tmpBanner = file;
			break;
		}
	}

	return Texture(tmpBanner);
}

//��������摜��1�ǂݍ��ށD�摜�����݂��Ȃ��Ƃ��CnoImg�ƂȂ�
Texture Loader::SearchOperationImg(const Array<FilePath>& files) {
	FilePath tmpOpe;

	tmpOpe = U"./Design/noImg.png";
	for (const auto& file : files) {
		if (file.includes(U"operation") == true) {
			tmpOpe = file;
			break;
		}
	}

	return Texture(tmpOpe);
}

//�Љ�摜�𕡐��ǂݍ��ށD�摜�����݂��Ȃ��Ƃ��CnoImg1���݂̂ƂȂ�
Array<Texture> Loader::SearchSS(const Array<FilePath>& files) {
	Array<Texture> tmpTextures;
	for (const auto& file : files) {
		if (file.includes(U"screenshot") == true) {
			tmpTextures.push_back(Texture(file));
		}
	}
	if (tmpTextures.size() == 0) {
		FilePath tmp = U"./Design/noImg.png";
		tmpTextures.push_back(Texture(tmp));
	}
	return tmpTextures;
}

Texture Loader::SetTextFrame(const String& path) {
	FilePath folderpass = U"./Design";
	Array<FilePath> folders = FileSystem::DirectoryContents(folderpass);
	FilePath tmpFrame = U"./Design/redFrame.png";
	for (const auto& file : folders) {
		if (file.includes(path) == true) {
			tmpFrame = folderpass + U"/" + path;
		}
	}
	return Texture(tmpFrame);
}
