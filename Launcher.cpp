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
	tb_title = TextArea({ 420,30 }, { 510, 55 }, 27, true);
	tb_summary = TextArea({ 420,90 }, { 510, 40 }, 18, true);
	tb_explain = TextArea({ 420,490 }, { 510, 140 }, 20, false);
	btn_gameLaunsh = Button({ 980,350 }, { 200, 100 }, 5, 20, U"Z：スタート!");
	btn_viewPaper = Button({ 980,190 }, { 200, 100 }, 5, 20, U"X：操作説明");
	btn_bannerPrev = Button({ 88,Window::ClientSize().y / 4 - 90 - 32 }, { bannerSub.w + 4, bannerSub.h + 4 }, 0, 1, U"");
	btn_bannerNext = Button({ 88,Window::ClientSize().y * 3 / 4 - 90 + 28 }, { bannerSub.w + 4, bannerSub.h + 4 }, 0, 1, U"");


	if (FileSystem::IsFile(U"Design/log.txt")) {
		logWriter = TextWriter(U"Design/log.txt", OpenMode::Append);
		logWriter.writeln(time.format(U"HH:mm:ss") + U",ランチャー起動,0");
	}
	else {
		logWriter = TextWriter(U"Design/log.txt");
		logWriter.writeln(time.format(U"HH:mm:ss") + U",ファイル作成,0");
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
		btn_operation.setSize({ Window::ClientSize().x - 20, Window::ClientSize().y - 20 });
		if (KeyX.down() || Gamepad(0).buttons[2].pressed || btn_operation.leftClicked()) {
			isShowingOptional = false;
		}
	}
	else {
		/*キー監視とかここ*/
		checkKey();
	}

	winW = Window::ClientSize().x;
	winH = Window::ClientSize().y;

	tb_title.setSize({ winW - 440, 55 });
	tb_summary.setSize({ winW - 440, 45 });
	tb_explain.setPos({ 420, winH - 150 });
	tb_explain.setSize({ winW - 440, 140 });

	btn_gameLaunsh.setPos({ winW - 260, winH / 2 + 15 });
	btn_viewPaper.setPos({ winW - 260, winH / 2 - 115 });
	btn_gameLaunsh.update();
	btn_viewPaper.update();

	btn_bannerPrev.setPos({ 88,Window::ClientSize().y / 4 - 90 - 32 });
	btn_bannerNext.setPos({ 88,Window::ClientSize().y * 3 / 4 - 90 + 28 });

}

void Launcher::draw() {
	/*描画はここ*/
	//左側バナー画像
	//Rect(88, Window::ClientSize().y / 4 - 90 - 32, bannerSub.w + 4, bannerSub.h + 4).draw(Palette::Blue);
	btn_bannerPrev.draw();
	games[numLoop(selectGame - 1, numGames)].img_banner.resized(bannerSub.w, bannerSub.h).draw(90, Window::ClientSize().y / 4 - 90 - 30);

	//Rect(88, Window::ClientSize().y * 3 / 4 - 90 + 28, bannerSub.w + 4, bannerSub.h + 4).draw(Palette::Red);
	btn_bannerNext.draw();
	games[numLoop(selectGame + 1, numGames)].img_banner.resized(bannerSub.w, bannerSub.h).draw(90, Window::ClientSize().y * 3 / 4 - 90 + 30);

	Rect(48, Window::ClientSize().y / 2 - 122, bannerCenter.w + 4, bannerCenter.h + 4).draw();
	games[selectGame].img_banner.resized(bannerCenter.w, bannerCenter.h).draw(50, Window::ClientSize().y / 2 - 120);

	debugFont(ToString(selectGame + 1) + U"/" + ToString(numGames)).draw(Vec2(10, Window::ClientSize().y - 50));

	//画像と説明文との境界線
	Line(400, 0, 400, Window::ClientSize().y).draw(5);
	Line(406, 0, 406, Window::ClientSize().y).draw(2);

	//説明文の表示
	tb_title.draw(games[selectGame].info.name, games[selectGame].textFrame);
	tb_summary.draw(games[selectGame].info.summary, games[selectGame].textFrame);
	tb_explain.draw(games[selectGame].info.explain, games[selectGame].textFrame);
	btn_viewPaper.draw();
	btn_gameLaunsh.draw();

	games[selectGame].screenshots[selectImg].resized(bannerCenter.w, bannerCenter.h).draw(460, winH / 2 - 120);

	debugFont(ToString(selectImg + 1) + U"/" + ToString(numImgs)).draw(Vec2(800, winH / 2 + 90));

	if (isShowingOptional) {
		btn_operation.draw();
		double amp = Min((Window::ClientSize().x - 40) / 4, (Window::ClientSize().y - 40) / 3);
		int w = (int)(4 * amp);
		int h = (int)(3 * amp);
		Rect(18, 18, Window::ClientSize().x - 36, Window::ClientSize().y - 36).draw({ 128,0,128,255 });
		games[selectGame].img_operation.resized(w, h).draw((Window::ClientSize().x - w) / 2, (Window::ClientSize().y - h) / 2);

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
			logWriter.writeln(time.format(U"HH:mm:ss,") + games[selectGame].info.name + U"," + ToString(stopwatch.s()));
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
	if (KeyDown.pressed || Gamepad(0).povDown.pressed || btn_bannerNext.leftClicked()) {
		selectGame = numLoop(selectGame + 1, numGames);
		numImgs = games[selectGame].screenshots.size();
		selectImg = 0;
	}
	if (KeyUp.pressed || Gamepad(0).povUp.pressed || btn_bannerPrev.leftClicked()) {
		selectGame = numLoop(selectGame - 1, numGames);
		numImgs = games[selectGame].screenshots.size();
		selectImg = 0;
	}
	if (KeyLeft.pressed || Gamepad(0).povLeft.pressed) {
		selectImg = numLoop(selectImg + 1, numImgs);
	}
	if (KeyRight.pressed || Gamepad(0).povRight.pressed) {
		selectImg = numLoop(selectImg - 1, numImgs);
	}

	//padのボタンは0オリジンなのでそこに注意
	if (KeyX.pressed || Gamepad(0).buttons[2].pressed || btn_viewPaper.leftClicked()) {

		isShowingOptional = true;
		btn_operation = Button({ 10,10 }, { Window::ClientSize().x - 20, Window::ClientSize().y - 20 }, 0, 1, U"");
	}

	if (KeyZ.pressed || Gamepad(0).buttons[3].pressed || btn_gameLaunsh.leftClicked()) {
		process = Process::Spawn(games[selectGame].exePath);
		playingCounter = 0;
		stopwatch.start();
	}
}
