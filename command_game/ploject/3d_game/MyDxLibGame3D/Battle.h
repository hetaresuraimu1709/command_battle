//Battle.h
#ifndef _BATTLE_H_
#define _BATTLE_H_

class Window;

struct Damege
{
	int damage;				//battleでのダメージを入れるとこ
	bool critical_hit_flag;	//会心の一撃かどうかのフラグ
	bool damege_once_flag;	//ダメージ計算を一回だけするためのフラグ
};

class Battle
{
public:
	Battle();
	~Battle();
	void Init(Camera *camera, Player *player);//初期化
    void In(Chara *ally1, Chara *ally2, Chara *ally3, Chara *enemy1, Chara *enemy2, Chara *enemy3, Chara *enemy4);//キャラ代入
	void Commanding(Player *player, Enemy *enemy, Camera *camera, Map *map, Music music);//味方それぞれのやつを動かす
	void Playing(Player *player, Enemy *enemy, Camera *camera);
	void Updata(int *scene, Player *player, Enemy *enemy, Camera *camera, Map *map, Music *music);
	void Draw(int *scene, Player *player, Enemy *enemy, Map *map, Camera *camera, Comment_string *comment, Effect *effect, Music *music, Window *window, Memory *memory);//描画
	bool probability(int max);
	void Flag_Reset();//フラグリセット用
	void Move_Flag_Reset();

	enum first_command
	{
		battle,//戦う
		see,//見る
		escape,//逃げる
	};
	enum second_command
	{
		attack,//攻撃
		skill,//特技
		magic,//魔法
		guard,//防御
		item,//道具
		sink,//溜める
	};

	int first_count;//最初のやつを表示させる時間
	int command_play_count;//打ったコマンドをplayしてるときに表示させる時間
	bool camera_flag[7];//だれが行動してるかをカメラで判別するためのフラグ
    int turn_count;//現在なんターン目か
	Damege damege[7];

    Chara m_ally[3];//味方を入れるところ
    Chara m_enemy[4];//敵を入れるところ
private:
	//battleでしか使わない関数
	void Have_Spell_Draw(Chara ally, int behavior, Inventory *ally_inv, Inventory *all_inv, Comment_string *comment);
	void Command(int number, Music music);//コマンドうち込み
	void Key_Anim(int number);
	Chara No_1_Speed_Get(Chara *speed0, Chara *speed1, Chara *speed2, Chara *speed3, Chara *speed4, Chara *speed5, Chara *speed6);
	void Command_Play_Move();//コマンド打ったあとの動き
	void Command_Play_Draw(Comment_string *comment, Chara *chara0, Chara *chara1, Chara *chara2, Chara *chara3, Chara *chara4, Chara *chara5, Chara *chara6, int count_max);//コマンド打ったあとの描画
	void Command_Choice_Draw(int number, Comment_string *comment, Window *window, Memory *memory);//コマンド選択中の描画
    void Enemy_Kill_Next(Chara *chara, Chara *enemy, int enemy_num);
	void Hit_And_Awey(Chara *chara, Chara *enemy, bool *chara_move_flag2, bool *chara_move_flag3, int enemy_num);
	void Playing_Move(Chara *ally, Chara *enemy, int ally_num, int enemy_num);
	void Damage_Adjustment(int *damege);
	void Damage_Calculation(Chara *chara_case, int damege_source, int damege_bonus, bool physics_flag);
	void Damage_Calculation_Set(Comment_string *comment, Chara *chara_case, float command_x, float command_y, int damege_source, int damege_bonus, bool physics_flag);
	//battleでしか使わない変数
	std::string first_behavior[KEY_1ST_MAX_COMMAND];							//たたかう、みる、にげる
	std::string second_behavior[KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X];	//こうげき、とくぎ、まほう、ぼうぎょ、どうぐ、ためる
	Vector2 key_pos[4];															//カーソルの座標
	Vector2 command_word_pos[9];												//たたかう等の文字の座標
    Vector2 command_pos[10];													//コマンド枠の座標
	float key_move_pos[4];														//カーソルの移動座標
	bool reset_command_pos_flag;												//コマンドを元に戻したかのフラグ
	bool reset_command_pos_flag2;												//コマンドを元に戻したかのフラグ
	int key_graph[8];															//カーソルの画像
	int anim_count;																//アニメーションのためのカウント
	int now_frame[4];															//アニメーションのためのフレーム
	int first_frame_graph;														//最初の文字枠
    int name_command_graph;														//１つ目のコマンドの上に表示させる名前用の枠
    int status_command_graph;													//ステータスのコマンド枠
	int one_command_graph;														//１つ目のコマンド枠
	int two_command_graph;														//２つ目のコマンド枠
	int three_command_graph;													//３つ目のコマンド枠
	int magic_command_graph;													//魔法等のコマンド枠
	int count_graph[10];														//数字の画像
    int count_graph_orange[10];													//数字の画像
    int count_graph_red[10];													//数字の画像
	int key_count[4];															//長押し
    int rand_count;                                                             //ランダムで使うようの変数
	bool end_flag;
};

#endif // _BATTLE_H_