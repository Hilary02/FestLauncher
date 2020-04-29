#include "stdafx.h"
#include "Loader.h"

Loader::Loader(const FilePath& path) :foldername(path) {
}

Loader::~Loader()
{
}

Array<Game> Loader::LoadGames() {
	//ゲームフォルダ内のディレクトリを格納
	Array<FilePath> folders = FileSystem::DirectoryContents(foldername,false);

	Array<Game> tmpGameList;
	for (unsigned int i = 0; i < folders.size(); i++) {
		Array<FilePath> files = FileSystem::DirectoryContents(folders[i]);
		Game tmpGame;

		tmpGame.exePath = SearchExePath(files);

		if (tmpGame.exePath.length() == 0) break; //実行するものがなければ話にならない

		tmpGame.info = SearchInfo(files);
		tmpGame.img_banner = SearchBannerImg(files);
		tmpGame.img_operation = SearchOperationImg(files);
		tmpGame.screenshots = SearchSS(files);

		tmpGame.textFrame = SetTextFrame(tmpGame.info.frameImg);
		tmpGameList.push_back(tmpGame);
	}

	return tmpGameList;
}

//処理の流れ上，名前の昇順で一番最初に存在するexeを読み込む．
//config.exeなどが先にあった場合，誤読み込みをする
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

//たとえinfo.txtが存在しなくてもエラーは起きない．レイアウトは保証しない
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
			for (int i = 0; reader.readLine(line) && i < 3; i++) {	//行が存在かつ3行以内
				info.explain += (line + U"\n");
			}
			break;
		}
	}
	return info;
}

//現行のランチャはimageを読み込んでいるため，それを一時的に踏襲している
//これ以外にも画像の読み込みをするため，意味をより明確にしたい
//TODO:bannerに変える予定
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

//操作説明画像を1つ読み込む．画像が存在しないとき，noImgとなる
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

//紹介画像を複数読み込む．画像が存在しないとき，noImg1枚のみとなる
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
