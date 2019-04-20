#ifndef _LOAD_H_
#define _LOAD_H_

#include "Header.h"

// 読み込むファイルの総数
#define FILENUM 300

// ゲージの幅
#define GAUGEWIDTH 300

struct Load
{
public:
	void DrawLoadingScreen();
	void Init();
	void NowLoading();
	bool end_flag = false;
private:
	// 画像ハンドル
	int GrHandle[FILENUM];
	// 読み込んでいる画像の番号
	int LoadingFile;

	int now_load = LoadGraph("data/title/NowLoading.png");
	double font_enlargement = 1.0;
	bool size_flag = false;
	Vector2 miffypos = VectorGet(1400.0f, 1000.0f);
};

#endif