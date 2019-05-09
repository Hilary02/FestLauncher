#pragma once
#include "Game.h"
class Loader
{
public:
	Loader(const FilePath& path);
	~Loader();

	/*ディレクトリ仕様
	ディレクトリ名の昇順で読み込まれる
	必要なファイル
	.
	(必須)
	⎿ *.exe         実行されるファイル
	⎿ info.txt      右に表示するタイトル・サブ列・紹介文などの情報を記述
	(任意)
	⎿ banner.*      メニュー画面左に表示する画像(Siv3Dが読み込める形式で)
	⎿ screenshot.*  メニュー右に表示する画像(複数枚でもよい)
	⎿ operation.*   操作説明用の画像(1枚)
	*/
	Array<Game> LoadGames();

private:
	FilePath foldername;
	FilePath SearchExePath(const Array<FilePath>& files);
	Info SearchInfo(const Array<FilePath>& files);
	Texture SearchBannerImg(const Array<FilePath>& files);
	Texture SearchOperationImg(const Array<FilePath>& files);
	Array<Texture> SearchSS(const Array<FilePath>& files);

	Texture SetTextFrame(const String& path);
	//Color setColor(const String& color);
};

