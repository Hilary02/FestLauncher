#pragma once
#include "Game.h"
#include "Loader.h"
#include "Button.h"
#include "TextArea.h"

/*
画像サイズを保管
*/
struct boxSize {
	int w;
	int h;
};

/*
ゲームのリストの保持や起動を行う．
プレイ履歴の管理もここ(予定)
*/
class Launcher {
public:
	Launcher(const FilePath& path);
	~Launcher();
	void update();
	void draw();

private:
	Loader loader;
	Array<Game> games;

	TextArea tb_title;
	TextArea tb_summary;
	TextArea tb_explain;

	Button btn_gameLaunsh;
	Button btn_viewPaper;
	Button btn_bannerPrev;
	Button btn_bannerNext;
	Button btn_operation;


	const Font debugFont;
	const boxSize bannerCenter = { 320, 240 };
	const boxSize bannerSub = { 240, 180 };
	int selectGame = 0;
	int selectImg = 0;
	int numGames;
	int numImgs;
	int numLoop(int next, int max);

	void checkKey();

	Optional<ProcessInfo> process;
	int playingCounter;
	int winW, winH;

	bool isShowingOptional = false;

	Shape s;
	TextWriter logWriter;

	Stopwatch stopwatch;
	const DateTime time;
};

