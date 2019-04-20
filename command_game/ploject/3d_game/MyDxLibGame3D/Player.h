//Player.h
//プレイヤーのヘッダー
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CharaBese.h"

class Map;
class Enemy;
class Camera;
class Battle;
class Memory;

class Player
{
public:
	int ShadowMapHandle;
	int run_animation;
	int AnimAttachIndex[ANIM_MAX];
	float Rate;
	float jumppow;
	float AnimTotalTime[ANIM_MAX];
	float AnimNowTime;
	int now_anim;//現在のアニメーション
	float dir_angle;//キャラの向いている角度
	float dir_angle_plas;//向いてる向きに加算
	int vertical_dir;//前後の向き
	int heng_dir;//左右の向き
	bool left_turn_flag;
	bool right_turn_flag;
	bool ahead_turn_flag;
	bool rear_turn_flag;
	bool ahead_left_turn_flag;
	bool ahead_right_turn_flag;
	bool rear_left_turn_flag;
	bool rear_right_turn_flag;
	bool jumpflag;
	bool keyflag;
	bool ahead_hit_flag;
	bool rear_hit_flag;
	bool left_hit_flag;
	bool right_hit_flag;
	bool warp_flag;
	Vector3 pos,vec;//座標
	Vector3 UpMove;//W移動のベクトル
	Vector3 DownMove;//S移動
	Vector3 LeftMove;//A移動
	Vector3 RightMove;//D移動
	Chara c_ally[3];
	Chara hoge_chara;
	Player(Memory memory);//コンストラクタ
	~Player();//デストラクタ
	void Init();
	void Turn_Reset();
	void Move(Camera *camera,Map *map);//動き
	void Turn();
	void WallHit(Map map, int map_data[BATTLE_MAP_CHIP][BATTLE_MAP_CHIP]);
	void EnemyHit(int *scene, Enemy *enemy, Battle *battle, Camera *camera);
	void VectorReset();
	void Draw();//描画
	void BattleDraw(Battle battle);
};
#endif // _PLAYER_H_