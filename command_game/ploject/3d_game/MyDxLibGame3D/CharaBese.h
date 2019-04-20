#ifndef _CHARABESE_H_
#define _CHARABESE_H_

struct Inventory
{
	int number;
	bool use_flag;
	std::string name;
	int damage_bonus;
	int force;
};

class Chara
{
public:
	Vector3 f_pos;				//フィールド座標
	Vector3 b_pos;				//バトル座標
	Vector3 vec;				//移動ベクトル
	Vector3 first_pos;			//バトルの初期ポジション
    std::string name;			//名前
	std::string name_origin;	//名前
	int modelHandle;			//画像
    int level;					//レベル
	float max_hp;				//体力の最大値
	float hp;					//体力
	float max_mp;				//魔力の最大値
	float mp;					//魔力
	float pow;					//攻撃力
	float def;					//防御力
	float m_pow;				//攻撃魔力
	float m_res;				//回復魔力
	float ski;					//器用さ
	float spd;					//素早さ
	bool ally_or_enemy_flag;//味方か敵かのフラグ＜true→味方　false→敵＞
	//最初のコマンドフラグ
	bool first_command_flag;//最初のコマンドを打ったかどうかのフラグ
	bool first_behavior_flag[KEY_1ST_MAX_COMMAND];//最初のコマンド
	//２番目のコマンドフラグ
	bool second_command_flag;//２番目のコマンドを打ったかどうかのフラグ
	bool second_behavior_flag[KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X];//最初のコマンド
	//どの魔法を使うか
	bool magic_command_flag;//２番目のコマンドを打ったかどうかのフラグ
	//だれを狙ったか
	bool who_command_flag[KEY_3RD_MAX_COMMAND_Y];
	
	Inventory magic[KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y];//魔法
	Inventory skill[KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y];//特技
	Inventory item[KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y];//道具

	//コマンドうち終わりのフラグ
	bool turn_flag;

	bool command_play_flag;	//コマンドの行動をやったかどうかのフラグ
	bool attack_flag;		//攻撃したかどうかのフラグ

	bool set_flag;
	bool chara_move_flag;	//コマンド打った後のキャラを動かすためのフラグ
	bool chara_move_flag2;	//コマンド打った後のキャラを動かすためのフラグ
	bool chara_move_flag3;	//コマンド打った後のキャラを動きを止めるためのフラグ

    bool die_flag;          //HPが０になった時のフラグ

	int puls_pow;			//バフデバフで増えたり減ったりする分の攻撃力
	int puls_def;			//バフデバフで増えたり減ったりする分の防御力
	int puls_spd;			//バフデバフで増えたり減ったりする分の素早さ

	bool damage_ones_flag;

	int damage_move_y;
};

#endif // _CHARABESE_H_