//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "Header.h"
#include "Load.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(1920, 1080, 16);
	SetWindowSizeExtendRate(0.5, 0.5);

	//描画先を裏画面に変更する。
	SetDrawScreen(DX_SCREEN_BACK);

	// DirectX9,11を使用するようにする。(エフェクシア用)
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	// 生成と初期化
	Load load;
	load.Init();
	load.NowLoading();
	Title *c_title = new Title();
	End *c_end = new End();
	Memory *c_memory = new Memory();
	Player *c_player = new Player(*c_memory);
	c_player->Init();
	Camera *c_camera = new Camera();
	c_camera->Init();
	Map *c_map = new Map();
	c_map->Init();
	Enemy *c_enemy = new Enemy(*c_memory);
	Comment_string *c_string = new Comment_string();
	c_string->Init();
	Effect *c_effect = new Effect();
	c_effect->Init();
	Battle *c_battle = new Battle();
	c_battle->Init(c_camera, c_player);
	Music *c_music = new Music();
	Window *c_window = new Window();
	//Npc *c_npc = new Npc();
	//c_npc->Init();
	int scene = s_title;
	bool game_end_flag = false;
	load.end_flag = true;
	c_map->now_floor = 1;

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !game_end_flag)
	{
		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();

		//キーをとるためのやつ
		updateKey();

		//*********************
		// 動き、当たり判定等
		//*********************
		//タイトル
		switch (scene)
		{
		case s_title:
			c_title->Move(&scene, c_music, &game_end_flag);
			break;
		case s_field:
			//c_npc->Updata();
			c_player->Move(c_camera, c_map);
			c_player->Turn();
			c_enemy->Move(*c_map, *c_player);
			c_player->EnemyHit(&scene, c_enemy, c_battle, c_camera);
			c_camera->Move(*c_player, c_map);
			c_player->VectorReset();
			break;
		case s_battle:
			c_battle->Updata(&scene, c_player, c_enemy, c_camera, c_map, c_music);
			/*c_battle->Commanding(c_player, c_enemy, c_camera, c_map,*c_music);
			c_battle->Playing(c_player, c_enemy, c_camera);*/
			break;
		case s_end:
			c_end->Move(&scene);
			break;
		default:
			break;
		}

		

		// 画面を初期化する
		ClearDrawScreen();
		//*********
		// 描画
		//*********
		//タイトル
		switch (scene)
		{
		case s_title:
			c_music->field_theme_Stop();
			c_title->Draw(c_string, c_music);
			break;
		case s_field:
			//c_npc->Draw();
			c_music->field_theme(0);
			c_map->Field_Draw(c_effect);
			c_player->Draw();
			c_enemy->Draw(*c_map);
			c_effect->Draw(&c_effect->warp, 1500000000);
			break;
		case s_battle:
			c_music->field_theme_Stop();
			c_battle->Draw(&scene, c_player, c_enemy, c_map, c_camera, c_string, c_effect, c_music, c_window, c_memory);
			break;
		case s_end:
			c_music->field_theme_Stop();
			c_end->Draw(c_string, c_music);
			break;
		default:
			break;
		}
		
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}
	//それぞれを解放
	delete c_player;
	delete c_enemy;
	delete c_camera;
	delete c_map;
	delete c_battle;
	delete c_string;

	// Effekseerを終了する。
	Effkseer_End();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}