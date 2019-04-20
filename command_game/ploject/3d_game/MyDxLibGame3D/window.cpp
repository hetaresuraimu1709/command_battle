#include "Header.h"

Window::Window()
{
	//コマンド背景画像をインストール！！
	window_back_graph = LoadGraph("data/command/window_back.png");
}

Window::~Window()
{
}

void Window::Command_Draw(float pos_x, float pos_y, float size_x, float size_y)
{
	//描画ブレンドモードをアルファブレンド（５０％）にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	//ウィンドウの背景
	DrawExtendGraph((int)pos_x, (int)pos_y, (int)(pos_x + size_x), (int)(pos_y + size_y), window_back_graph, true);
	//ウィンドウの外枠
	DrawBox((int)pos_x, (int)pos_y, (int)(pos_x + size_x), (int)(pos_y + COMMAND_WINDOW_LINE_SIZE), GetColor(255, 255, 255), true);//上
	DrawBox((int)pos_x, (int)(pos_y + size_y - COMMAND_WINDOW_LINE_SIZE), (int)(pos_x + size_x), (int)(pos_y + size_y), GetColor(255, 255, 255), true);//下
	DrawBox((int)pos_x, (int)(pos_y + COMMAND_WINDOW_LINE_SIZE), (int)(pos_x + COMMAND_WINDOW_LINE_SIZE), (int)(pos_y + size_y - COMMAND_WINDOW_LINE_SIZE), GetColor(255, 255, 255), true);//左
	DrawBox((int)(pos_x + size_x - COMMAND_WINDOW_LINE_SIZE), (int)(pos_y + COMMAND_WINDOW_LINE_SIZE), (int)(pos_x + size_x), (int)(pos_y + size_y - COMMAND_WINDOW_LINE_SIZE), GetColor(255, 255, 255), true);//右
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//変更前
////描画ブレンドモードをアルファブレンド（５０％）にする
//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
////ウィンドウの背景
//DrawExtendGraph((int)pos_x, (int)pos_y, (int)(pos_x + size_x), (int)(pos_y + size_y), window_back_graph, true);
////ウィンドウの外枠
//DrawBox((int)pos_x, (int)pos_y, (int)(pos_x + COMMAND_WINDOW_LINE_SIZE), (int)(pos_y + size_y), GetColor(255, 255, 255), true);//左
//DrawBox((int)pos_x, (int)pos_y, (int)(pos_x + size_x), (int)(pos_y + COMMAND_WINDOW_LINE_SIZE), GetColor(255, 255, 255), true);//上
//DrawBox((int)pos_x, (int)(pos_y + size_y - COMMAND_WINDOW_LINE_SIZE), (int)(pos_x + size_x), (int)(pos_y + size_y), GetColor(255, 255, 255), true);//下
//DrawBox((int)(pos_x + size_x - COMMAND_WINDOW_LINE_SIZE), (int)pos_y, (int)(pos_x + size_x), (int)(pos_y + size_y), GetColor(255, 255, 255), true);//右
//																																				   // 描画ブレンドモードをノーブレンドにする
//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);