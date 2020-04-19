#include <Siv3D.hpp>
#include "Launcher.h"

void correctWindowSize() {
	int minW = 1200;
	int minH = 600;
	Size windowSize = Window::ClientSize();
	int w = windowSize.x;
	int h = windowSize.y;

	if (w < minW) w = minW;
	if (h < minH) h = minH;
	Window::Resize(w, h);
}

void Main() {
	Window::Resize(1200, 600);				//ウィンドウサイズ初期化
	Scene::SetBackground(Palette::Gray);

	Window::SetTitle(L"GameLauncher");
	Window::SetStyle(WindowStyle::Sizable); //サイズ可変

	const FilePath homeDirectory = FileSystem::CurrentDirectory();

	if (!FileSystem::IsDirectory(U"./Game")) System::Exit();	//存在しなければ終了
	Launcher launcher(U"./Game");		//ランチャークラスの生成・同時に読み込み

	while (System::Update()) {
		correctWindowSize();	//最小ウィンドウサイズへの修正
		launcher.update();
		launcher.draw();

		// カーソルの位置を表示
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
	}
}
