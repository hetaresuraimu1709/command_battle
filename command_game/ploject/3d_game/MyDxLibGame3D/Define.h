//Define.h

#ifndef _DEFINE_H_
#define _DEFINE_H_

//画面サイズ
#define SCREEN_W 1920
#define SCREEN_H 1080

//キャラの初期ステータス
#define ALLY_1_NAME     "クラミ"
#define ALLY_1_FIRST_HP  50
#define ALLY_1_FIRST_MP  5
#define ALLY_1_FIRST_STR 30
#define ALLY_1_FIRST_DEF 45
#define ALLY_1_FIRST_MST 5
#define ALLY_1_FIRST_MHL 5
#define ALLY_1_FIRST_SKI 15
#define ALLY_1_FIRST_SPD 10
#define ALLY_2_NAME      "ルカリ"
#define ALLY_2_FIRST_HP  25
#define ALLY_2_FIRST_MP  50
#define ALLY_2_FIRST_STR 5
#define ALLY_2_FIRST_DEF 10
#define ALLY_2_FIRST_MST 50
#define ALLY_2_FIRST_MHL 20
#define ALLY_2_FIRST_SKI 50
#define ALLY_2_FIRST_SPD 15
#define ALLY_3_NAME      "バブミ"
#define ALLY_3_FIRST_HP  10
#define ALLY_3_FIRST_MP  40
#define ALLY_3_FIRST_STR 10
#define ALLY_3_FIRST_DEF 50
#define ALLY_3_FIRST_MST 15
#define ALLY_3_FIRST_MHL 50
#define ALLY_3_FIRST_SKI 10
#define ALLY_3_FIRST_SPD 50

//キャラの動き関係
#define GRAVITY 0.3f//重力
#define vertical_dir_SPEED 20.f//
#define PLAYER_REAR 360.f//前
#define PLAYER_LEFT 90.f//左
#define PLAYER_AHEAD 180.f//後ろ
#define PLAYER_RIGHT 270.f//右
#define ANIM_MAX 3//０：棒立ち、１：歩く、２：走る
//マップ関係
#define MAP_CHIP 50//マップの縦横サイズ
#define BATTLE_MAP_CHIP 25//バトルマップの縦横サイズ
#define MAP_BLOCK_SIZE 50.f//マップチップ一つ一つの縦横サイズ

//敵関係
#define ENEMY 5//敵の種類数
#define BOSS_NAME "ドラゴン"
#define ENEMY_NOTICE 100.f
#define ENEMY_B_POS_X 545
#define ENEMY_B_POS_Y 530

//＊コマンド関係＊
//キー
#define KEY_ANIM_LOAD 2
#define KEY_ANIM_FRAME 8
//最初のヤツ
#define FIRST_COMMAND_X 27.5f
#define FIRST_COMMAND_Y SCREEN_H - 110 - 10
//ステータスウィンドウ
#define STATUS_COMMAND_SIZE_X 907
#define STATUS_COMMAND_SIZE_Y 215
//一つ目
#define KEY_1ST_COMMAND_SIZE_X 224
#define KEY_1ST_COMMAND_SIZE_Y 240
#define KEY_1ST_COMMAND_X 20
#define KEY_1ST_COMMAND_Y SCREEN_H - KEY_1ST_COMMAND_SIZE_Y - 50
#define KEY_1ST_POS_X 5
#define KEY_1ST_POS_Y 40
#define KEY_1ST_MOVE_Y 70.0f
#define KEY_1ST_MAX_COMMAND 3
//名前のやつ
#define NAME_COMMAND_SIZE_X 224
#define NAME_COMMAND_SIZE_Y 70
#define NAME_COMMAND_X 20
#define NAME_COMMAND_Y -71
//二つ目
#define KEY_2ND_COMMAND_SIZE_X 700
#define KEY_2ND_COMMAND_SIZE_Y 229
#define KEY_2ND_COMMAND_X KEY_1ST_COMMAND_X + KEY_1ST_COMMAND_SIZE_X + 20
#define KEY_2ND_COMMAND_Y SCREEN_H - KEY_1ST_COMMAND_SIZE_Y - 50
#define KEY_2ND_POS_X 10
#define KEY_2ND_POS_Y 40
#define KEY_2ND_MOVE_X 230.0f
#define KEY_2ND_MOVE_Y 120.0f
#define KEY_2ND_MAX_COMMAND_X 3
#define KEY_2ND_MAX_COMMAND_Y 2
//三つ目
#define KEY_3RD_COMMAND_SIZE_X 761
#define KEY_3RD_COMMAND_SIZE_Y 229
#define KEY_3RD_COMMAND_X KEY_2ND_COMMAND_X + KEY_2ND_COMMAND_SIZE_X + 20
#define KEY_3RD_COMMAND_Y SCREEN_H - KEY_1ST_COMMAND_SIZE_Y - 50
#define KEY_3RD_POS_X 30
#define KEY_3RD_POS_Y 20
#define KEY_3RD_MOVE_X 200.0f
#define KEY_3RD_MOVE_Y 55.0f
#define KEY_3RD_MAX_COMMAND_Y 4
//魔法コマンド
#define KEY_MAGIC_COMMAND_SIZE_X 1000
#define KEY_MAGIC_COMMAND_SIZE_Y 229
#define KEY_MAGIC_COMMAND_X KEY_2ND_COMMAND_X
#define KEY_MAGIC_COMMAND_Y KEY_2ND_COMMAND_Y - KEY_1ST_COMMAND_SIZE_Y - 10
#define KEY_MAGIC_POS_X 30
#define KEY_MAGIC_POS_Y 40
#define KEY_MAGIC_MOVE_X 300.0f
#define KEY_MAGIC_MOVE_Y 120.0f
#define KEY_MAGIC_MAX_COMMAND_X 3
#define KEY_MAGIC_MAX_COMMAND_Y 2
//コマンドが動くスピード
#define KEY_SPEED 0.8f

//数字関係
#define NUMBER_MAX_X 10
#define NUMBER_MAX_Y 1
#define NUMBER_SIZE_X 50.0f
#define NUMBER_SIZE_Y 50.0f

//文字関係
#define STRING_SIZE_W 50
#define STRING_SIZE_H 50
#define STRING_NUM 200
#define STRING_XNUM 10
#define STRING_YNUM 20

//魔法の最大数
#define SPELL_MAX 16
#define SKILL_MAX 16
#define ITEM_MAX 16

//音楽関係
#define BGM_VOL_THROW 0

//ぼかし
#define BOKASI 3.0f

//コマンドウィンドウの枠
#define COMMAND_WINDOW_LINE_SIZE 10

struct Vector3
{
	float x, y, z;
};

struct Vector2
{
    float x, y;
};

struct Point
{
	float x, y, z;
};
enum
{
	nodir,//どこもなし
	left,//左
	right,//右
	ahead,//前方
	rear,//後方
};

enum scene
{
	s_title,//タイトル画面
	s_field,//フィールド画面
	s_battle,//バトル画面
	s_end,//エンディング
};

#endif
