#include "stdafx.h"
#include "Launcher.h"

Launcher::Launcher(const FilePath& path) :
	loader(path),
	time(DateTime::Now()),
	debugFont(25) {
	//リソース読み込み
	games = loader.LoadGames();	//この時点でゲームリストは確定
	numGames = games.size();
	numImgs = games[selectGame].screenshots.size();

	//                   [左上座標] , {サイズ},フォントサイズ,文字を中央に書くか
	tb_title = TextBox({ 420,30 }, { 510, 55 }, 27, true);
	tb_summary = TextBox({ 420,90 }, { 510, 40 }, 18, true);
	tb_explain = TextBox({ 420,490 }, { 510, 140 }, 20, false);
	btn_gameLaunsh = Button({ 980,350 }, { 200, 100 }, 5, 20, L"Z：スタート!");
	btn_viewPaper = Button({ 980,190 }, { 200, 100 }, 5, 20, L"X：操作説明");
	btn_bannerPrev = Button({ 88,Window::Height() / 4 - 90 - 32 }, { bannerSub.w + 4, bannerSub.h + 4 }, 0, 1, L"");
	btn_bannerNext = Button({ 88,Window::Height() * 3 / 4 - 90 + 28 }, { bannerSub.w + 4, bannerSub.h + 4 }, 0, 1, L"");


	if (FileSystem::IsFile(L"Design/log.txt")) {
		logWriter = TextWriter(L"Design/log.txt", OpenMode::Append);
		logWriter.writeln(time.format(L"HH:mm:ss") + L",ランチャー起動,0");
	}
	else {
		logWriter = TextWriter(L"Design/log.txt");
		logWriter.writeln(time.format(L"HH:mm:ss") + L",ファイル作成,0");
	}
}

Launcher::~Launcher() {
	logWriter.close();
}


void Launcher::update() {
	/**
	 * @fn
	 * ここに関数の説明を書く
	 * @brief 要約説明
	 * @param (引数名) 引数の説明
	 * @param (引数名) 引数の説明
	 * @return 戻り値の説明
	 * @sa 参照すべき関数を書けばリンクが貼れる
	 * @detail 詳細な説明
	 */

	if (isShowingOptional) {
		//btn_operation.update();
		btn_operation.setSize({ Window::Width() - 20, Window::Height() - 20 });
		if (Input::KeyX.clicked || Gamepad(0).button(2).clicked || btn_operation.leftClicked()) {
			isShowingOptional = false;
		}
	}
	else {
		/*キー監視とかここ*/
		checkKey();
	}

	winW = Window::Width();
	winH = Window::Height();

	tb_title.setSize({ winW - 440, 55 });
	tb_summary.setSize({ winW - 440, 45 });
	tb_explain.setPos({ 420, winH - 150 });
	tb_explain.setSize({ winW - 440, 140 });

	btn_gameLaunsh.setPos({ winW - 260, winH / 2 + 15 });
	btn_viewPaper.setPos({ winW - 260, winH / 2 - 115 });
	btn_gameLaunsh.update();
	btn_viewPaper.update();

	btn_bannerPrev.setPos({ 88,Window::Height() / 4 - 90 - 32 });
	btn_bannerNext.setPos({ 88,Window::Height() * 3 / 4 - 90 + 28 });

}

void Launcher::draw() {
	/*描画はここ*/
	//左側バナー画像
	//Rect(88, Window::Height() / 4 - 90 - 32, bannerSub.w + 4, bannerSub.h + 4).draw(Palette::Blue);
	btn_bannerPrev.draw();
	games[numLoop(selectGame - 1, numGames)].img_banner.resize(bannerSub.w, bannerSub.h).draw(90, Window::Height() / 4 - 90 - 30);

	//Rect(88, Window::Height() * 3 / 4 - 90 + 28, bannerSub.w + 4, bannerSub.h + 4).draw(Palette::Red);
	btn_bannerNext.draw();
	games[numLoop(selectGame + 1, numGames)].img_banner.resize(bannerSub.w, bannerSub.h).draw(90, Window::Height() * 3 / 4 - 90 + 30);

	Rect(48, Window::Height() / 2 - 122, bannerCenter.w + 4, bannerCenter.h + 4).draw();
	games[selectGame].img_banner.resize(bannerCenter.w, bannerCenter.h).draw(50, Window::Height() / 2 - 120);

	debugFont.draw(ToString(selectGame + 1) + L"/" + ToString(numGames), Vec2(10, Window::Height() - 50));

	//画像と説明文との境界線
	Line(400, 0, 400, Window::Height()).draw(5);
	Line(406, 0, 406, Window::Height()).draw(2);

	//説明文の表示
	tb_title.draw(games[selectGame].info.name, games[selectGame].textFrame);
	tb_summary.draw(games[selectGame].info.summary, games[selectGame].textFrame);
	tb_explain.draw(games[selectGame].info.explain, games[selectGame].textFrame);
	btn_viewPaper.draw();
	btn_gameLaunsh.draw();

	games[selectGame].screenshots[selectImg].resize(bannerCenter.w, bannerCenter.h).draw(460, winH / 2 - 120);

	debugFont.draw(ToString(selectImg + 1) + L"/" + ToString(numImgs), { 800, winH / 2 + 90 });

	if (isShowingOptional) {
		btn_operation.draw();
		double amp = Min((Window::Width() - 40) / 4, (Window::Height() - 40) / 3);
		int w = (int)(4 * amp);
		int h = (int)(3 * amp);
		Rect(18, 18, Window::Width() - 36, Window::Height() - 36).draw({ 128,0,128,255 });
		games[selectGame].img_operation.resize(w, h).draw((Window::Width() - w) / 2, (Window::Height() - h) / 2);

	}





	//実行中ならば最少化&カウンタ回す
	if (process) {
		if (process->isRunning()) {
			//Window::Minimize();
			playingCounter++;
		}
		else {
			//Window::Restore();
			process = none;
			logWriter.writeln(time.format(L"HH:mm:ss,") + games[selectGame].info.name + L"," + ToString(stopwatch.s()));
			stopwatch.reset();
		}
	}
}

/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
int Launcher::numLoop(int next, int max) {
	if (next >= max) return 0;
	if (next < 0) return max - 1;
	return next;
}

void Launcher::checkKey() {
	if (Input::KeyDown.clicked || Gamepad(0).povBackward.clicked || btn_bannerNext.leftClicked()) {
		selectGame = numLoop(selectGame + 1, numGames);
		numImgs = games[selectGame].screenshots.size();
		selectImg = 0;
	}
	if (Input::KeyUp.clicked || Gamepad(0).povForward.clicked || btn_bannerPrev.leftClicked()) {
		selectGame = numLoop(selectGame - 1, numGames);
		numImgs = games[selectGame].screenshots.size();
		selectImg = 0;
	}
	if (Input::KeyLeft.clicked || Gamepad(0).povLeft.clicked) {
		selectImg = numLoop(selectImg + 1, numImgs);
	}
	if (Input::KeyRight.clicked || Gamepad(0).povRight.clicked) {
		selectImg = numLoop(selectImg - 1, numImgs);
	}

	//padのボタンは0オリジンなのでそこに注意
	if (Input::KeyX.clicked || Gamepad(0).button(2).clicked || btn_viewPaper.leftClicked()) {

		isShowingOptional = true;
		btn_operation = Button({ 10,10 }, { Window::Width() - 20, Window::Height() - 20 }, 0, 1, L"");
	}

	if (Input::KeyZ.clicked || Gamepad(0).button(3).clicked || btn_gameLaunsh.leftClicked()) {
		process = System::CreateProcess(games[selectGame].exePath);
		playingCounter = 0;
		stopwatch.start();
	}
}
