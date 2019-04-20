#include "Load.h"

// 読み込み画面描画関数
void Load::DrawLoadingScreen()
{
	// ゲージの全体を灰色で描画
	DrawBox(1200, 1050, 1200 + GAUGEWIDTH, 1075, GetColor(100, 0, 0), TRUE);

	// 現時点で読み込み終わっている分を白色で描画
	DrawBox(1200, 1050, 1200 + (LoadingFile * GAUGEWIDTH / FILENUM), 1075, GetColor(0, 255, 0), TRUE);
}

void Load::Init()
{
	end_flag = false;
	now_load = LoadGraph("data/title/NowLoading.png");
	font_enlargement = 1.0;
	size_flag = false;
	miffypos = VectorGet(1400.0f, 1000.0f);
}

void Load::NowLoading()
{
	if(!end_flag)
	{
		// 画面の初期化
		ClearDrawScreen();

		DrawRotaGraph(1600, 1030, font_enlargement, 0.0, now_load, true);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
}
