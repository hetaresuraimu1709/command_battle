//battle.cpp
#include "Header.h"

//************************************************************************
// 関数群
//************************************************************************

//カーソルキーの比較用
//(座標のXroY、終着点)
bool Cursor(float pos, float max) { return pos >= max - BOKASI && pos <= max + BOKASI; }

//確率関数
//(何パーセントか)
bool Battle::probability(int max) { return  rand_count % 100 <= max; }

//カーソルを動かすもの、上or下or右or左の１方向で上限も決めれる
//(カーソルの座標、どのキー押したか、カーソルがいける限界の座標、コマンドの数、１コマンド間のカーソルの移動量、長押しで動くようのカウント)
void Move_Cursor(float *key_pos, unsigned char key_code, float max, int command_max, float move, int *count, Music music)
{
	if (getKey(key_code) == KEY_STATE_PUSHDOWN)
	{
		music.cursor_move();
		if (!Cursor(*key_pos ,max))
		{
			*key_pos += move;
		}
		else if (Cursor(*key_pos, max))
		{
			*key_pos = max + (-move * (command_max - 1));
		}
	}
	else if (getKey(key_code) == KEY_STATE_PRESSED)
	{
		*count += 1;
		if (*count > 20)
		{
			music.cursor_move();
			if (!Cursor(*key_pos, max))
			{
				*key_pos += move;
			}
			else if (Cursor(*key_pos, max))
			{
				*key_pos = max + (-move * (command_max - 1));
			}
		}
	}
	else if (getKey(key_code) == KEY_STATE_PULLUP)
	{
		*count = 0;
	}
}

//Move_Cursorを上下or左右でまとめたもの
//(カーソルの座標、どのキー押したか１、どのキー押したか２、カーソルがいける限界の座標、コマンドの数、１コマンド間のカーソルの移動量、長押しで動くようのカウント１、長押しで動くようのカウント２)
void Set_Move_Cursor(float *key_pos, unsigned char key_code_1, unsigned char key_code_2, float max, int command_max, float move, int *count_1, int *count_2, Music music)
{
	Move_Cursor(key_pos, key_code_1, max,                              command_max, -move, count_1, music);
	Move_Cursor(key_pos, key_code_2, max + (move * (command_max - 1)), command_max, move,  count_2, music);
}

//カーソルにあったコマンドを入力するもの、入力後のカーソルの場所も指定する
//(今選択してるコマンドのカーソルの座標、次選択するコマンドのカーソルの座標、何番目のコマンドを決定したか、どの行動をしたか、カーソルがいける限界のY座標、１コマンド間のカーソルの移動量、コマンドの数、カーソルがいける限界のX座標、１コマンド間のカーソルの移動量、コマンドの数)
void Decide_Command(Vector2 key_pos_1, Vector2 *key_pos_2, bool *command_flag, bool *behavior_flag, float max_y, float move_y, int comand_y, float max_x, float move_x, int comand_x,Vector2 setpos, Music music)
{
	if (getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN && Cursor(key_pos_1.y, max_y + (move_y * comand_y))
													   && Cursor(key_pos_1.x, max_x + (move_x * comand_x)))
	{
		music.cursor_enter();
		*command_flag = true;
		*behavior_flag = true;
		*key_pos_2 = VectorGet(setpos.x, setpos.y);
	}
}

//ひとつ前のコマンドに戻るもの
//(どの行動をしたか、何番目のコマンドを決定したか、コマンドの数)
void Command_Back(bool *behavior_flag , bool *command_flag , int max_command, Music music)
{
	if (getKey(KEY_INPUT_BACK) == KEY_STATE_PUSHDOWN)
	{
		music.cursor_cancel();
		for (int i = 0; i < max_command; i++)
		{
			behavior_flag[i] = false;
		}
		*command_flag = false;
	}
}
//座標を一つ前に戻す（上とセットで使う）
//(コマンドの今の座標、コマンドの目指す座標、カーソルの今の座標、カーソルの目指す座標)
void Command_Pos_Reset(Vector2 *command_origin_pos, Vector2 command_goal_pos, Vector2 *key_origin_pos, Vector2 key_goal_pos)
{
	if (getKey(KEY_INPUT_BACK) == KEY_STATE_PUSHDOWN)
	{
		*command_origin_pos = command_goal_pos;
		*key_origin_pos = key_goal_pos;
	}
}

//入れた数字を描画するもの(２Ｄ)
//(数字の画像、描画したい数字、この数字を描画するｘ座標、ｙ座標)
void Count_Draw_2D(int *number_graph, int draw_count, float x, float y)
{
	if (draw_count < 10)
	{
		DrawGraph((int)x,                                (int)y, number_graph[draw_count],           TRUE);
	}
	else if (draw_count < 100)
	{
		DrawGraph((int)x,                                (int)y, number_graph[draw_count / 10],      TRUE);
		DrawGraph((int)(x + NUMBER_SIZE_X - 10),         (int)y, number_graph[draw_count % 10],      TRUE);
	}
	else if (draw_count < 1000)
	{
		DrawGraph((int)x,                                (int)y, number_graph[draw_count / 100],     TRUE);
		DrawGraph((int)(x + NUMBER_SIZE_X - 10),         (int)y, number_graph[draw_count / 10 % 10], TRUE);
		DrawGraph((int)(x + ((NUMBER_SIZE_X - 10) * 2)), (int)y, number_graph[draw_count % 10],      TRUE);
	}
}

//入れた数字を描画するもの(２Ｄ)（拡大率付き）
//(数字の画像、描画したい数字、この数字を描画するｘ座標、ｙ座標、拡大率)
void Count_Draw_2D(int *number_graph, int draw_count, float x, float y,float size_rate)
{
	if (draw_count < 10)
	{
		DrawRotaGraph((int)x, (int)y, size_rate, 0.0f, number_graph[draw_count], TRUE);
	}
	else if (draw_count < 100)
	{
		DrawRotaGraph((int)x, (int)y, size_rate, 0.0f, number_graph[draw_count / 10], TRUE);
		DrawRotaGraph((int)(x + ((NUMBER_SIZE_X - 10) * size_rate)), (int)y, size_rate, 0.0f, number_graph[draw_count % 10], TRUE);
	}
	else if (draw_count < 1000)
	{
		DrawRotaGraph((int)x, (int)y, size_rate, 0.0f, number_graph[draw_count / 100], TRUE);
		DrawRotaGraph((int)(x + ((NUMBER_SIZE_X - 10) * size_rate)), (int)y, size_rate, 0.0f, number_graph[draw_count / 10 % 10], TRUE);
		DrawRotaGraph((int)(x + (((NUMBER_SIZE_X - 10) * 2) * size_rate)), (int)y, size_rate, 0.0f, number_graph[draw_count % 10], TRUE);
	}
}

//入れた数字を描画するもの(３Ｄ)
//(数字の画像、描画したい数字、この数字を描画するｘ座標、ｙ座標)
void Count_Draw_3D(int *number_graph, int draw_count, float x, float y, float z)
{
	if (draw_count < 10)
	{
		DrawBillboard3D(VGet(x, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count], TRUE);
	}
	else if (draw_count < 100)
	{
		DrawBillboard3D(VGet(x + 2.5f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 10], TRUE);
		DrawBillboard3D(VGet(x - 2.5f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count % 10], TRUE);
	}
	else if (draw_count < 1000)
	{
		DrawBillboard3D(VGet(x + 5.0f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 100], TRUE);
		DrawBillboard3D(VGet(x , y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 10 % 10], TRUE);
		DrawBillboard3D(VGet(x - 5.0f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count % 10], TRUE);
	}
}

//敵の入れた数字を描画するもの(３Ｄ)
//(数字の画像、描画したい数字、この数字を描画するｘ座標、ｙ座標)
void Enemy_Count_Draw_3D(int *number_graph, int draw_count, float x, float y, float z)
{
	if (draw_count < 10)
	{
		DrawBillboard3D(VGet(x, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count], TRUE);
	}
	else if (draw_count < 100)
	{
		DrawBillboard3D(VGet(x - 2.5f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 10], TRUE);
		DrawBillboard3D(VGet(x + 2.5f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count % 10], TRUE);
	}
	else if (draw_count < 1000)
	{
		DrawBillboard3D(VGet(x - 5.0f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 100], TRUE);
		DrawBillboard3D(VGet(x, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count / 10 % 10], TRUE);
		DrawBillboard3D(VGet(x + 5.0f, y, z), 0.5f, 0.5f, 5.0f, 0.0f, number_graph[draw_count % 10], TRUE);
	}
}

//HPバーをつくる関数
void Set_HPber(float pos_x, float pos_y, float rate, int color)
{
	DrawBox((int)(pos_x - 7), (int)(pos_y - 7), (int)(pos_x + 157), (int)(pos_y + 37), GetColor(100, 100, 100), true);
	DrawBox((int)(pos_x - 5), (int)(pos_y - 5), (int)(pos_x + 155), (int)(pos_y + 35), GetColor(200, 200, 200), true);
	DrawBox((int)(pos_x), (int)(pos_y), (int)(pos_x + 150), (int)(pos_y + 30), GetColor(100, 0, 0), true);
	DrawBox((int)(pos_x), (int)(pos_y), (int)(pos_x + (150 * rate)), (int)(pos_y + 30), color, true);
	DrawBox((int)(pos_x), (int)(pos_y), (int)(pos_x + (150 * rate)), (int)(pos_y + 30), color, true);
}

//キーのアニメーション用
//(キーナンバー)
void Battle::Key_Anim(int number)
{
	if (anim_count % KEY_ANIM_LOAD == 0)
	{
		now_frame[number]++;
		if (now_frame[number] >= KEY_ANIM_FRAME)
		{
			now_frame[number] = 0;
		}
	}
}

//void Speed_adjustment(Chara *chara[], int chara_num)
//{
//	for (int i = 0; i < chara_num; i++)
//	{
//		if (i != chara_num - 1)
//		{
//			if (chara[i]->spd == chara[i + 1]->spd)
//			{
//				
//			}
//		}
//	}
//}

//誰が１番早かったかを見るもの
//(キャラ情報０～６)
Chara Battle::No_1_Speed_Get(Chara *speed0, Chara *speed1, Chara *speed2, Chara *speed3, Chara *speed4, Chara *speed5, Chara *speed6)
{
	Chara chara_hoge;
	chara_hoge = Status_Get("エラー！", "", VectorGet(0.0f, 0.0f, 0.0f), VectorGet(0.0f, 0.0f, 0.0f), -1, -1, -1, -1, -1, -1, -1, -1, false);
	Chara chara_base[7] = { *speed0,*speed1,*speed2,*speed3,*speed4,*speed5,*speed6 };
	for (int i = 0; i < 7; i++)
	{
		if (!chara_base[i].command_play_flag &&
			!chara_base[i].die_flag)
		{
			if (chara_base[i].spd + chara_base[i].puls_spd > chara_hoge.spd)
			{
				chara_hoge = chara_base[i];
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (!chara_base[i].command_play_flag &&
			!chara_base[i].die_flag)
		{
			if (chara_base[i].name == chara_hoge.name)
			{
				chara_base[i].command_play_flag = true;
				camera_flag[i] = true;
				return chara_base[i];
			}
		}
	}
	return chara_hoge;
}

//覚えてるじゅもん、とくぎ、持っているどうぐの文字を描画させるもの
//(味方のキャラ情報、プレイヤーの魔法か特技か道具か、魔法名、すべての魔法か特技か道具か)
void Battle::Have_Spell_Draw(Chara ally, int behavior,Inventory *ally_inv, Inventory *all_inv, Comment_string *comment)
{
	if (ally.second_behavior_flag[behavior])
	{
		for (int i = 0; i < KEY_MAGIC_MAX_COMMAND_X; i++)
		{
			for (int spell = 0; spell < SPELL_MAX; spell++)
			{
				if (ally_inv[i].number == spell)
				{
					//上の３つ
					comment->Draw((float)(command_pos[4].x + KEY_MAGIC_POS_X + 25.0f + (KEY_MAGIC_MOVE_X * i)),
								  (float)(command_pos[4].y + KEY_MAGIC_POS_Y - 10.0f),
								  all_inv[spell].name);
				}
				if (ally_inv[i + 3].number == spell)
				{
					//下の３つ
					comment->Draw((float)(command_pos[4].x + KEY_MAGIC_POS_X + 25.0f + (KEY_MAGIC_MOVE_X * i)),
								  (float)((command_pos[4].y + KEY_MAGIC_POS_Y - 10.0f) + KEY_MAGIC_MOVE_Y),
								  all_inv[spell].name);
				}
			}
		}
	}
}

//動きのフラグをリセットする
void Battle::Move_Flag_Reset()
{
	for (int i = 0; i < 3; i++)
	{
		m_ally[i].chara_move_flag = false;
	}
	for (int i = 0; i < 4; i++)
	{
		m_enemy[i].chara_move_flag = false;
	}
}

//フラグをすべてfalseにするもの
void Battle::Flag_Reset()
{
	//味方のフラグ
	for (int number = 0; number < 3; number++)
	{
		m_ally[number].first_command_flag			= false;
		for (int i = 0; i < KEY_1ST_MAX_COMMAND; i++)
		{
			m_ally[number].first_behavior_flag[i]	= false;
		}

		m_ally[number].second_command_flag			= false;
		for (int i = 0; i < (KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X); i++)
		{
			m_ally[number].second_behavior_flag[i]	= false;
		}

		m_ally[number].magic_command_flag			= false;
		for (int i = 0; i < (KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y); i++)
		{
			m_ally[number].magic[i].use_flag			= false;
			m_ally[number].skill[i].use_flag			= false;
			m_ally[number].item[i].use_flag			= false;
		}
		for (int i = 0; i < KEY_3RD_MAX_COMMAND_Y; i++)
		{
			m_ally[number].who_command_flag[i]		= false;
		}
		m_ally[number].turn_flag					= false;

		m_ally[number].command_play_flag			= false;
		m_ally[number].set_flag						= false;
		m_ally[number].chara_move_flag				= false;
		m_ally[number].chara_move_flag2				= false;
		m_ally[number].chara_move_flag3				= false;
	}
	//敵のフラグ
	for (int number = 0; number < 4; number++)
	{
		m_enemy[number].first_command_flag			= false;
		for (int i = 0; i < KEY_1ST_MAX_COMMAND; i++)
		{
			m_enemy[number].first_behavior_flag[i]	= false;
		}

		m_enemy[number].second_command_flag			= false;
		for (int i = 0; i < (KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X); i++)
		{
			m_enemy[number].second_behavior_flag[i] = false;
		}

		m_enemy[number].magic_command_flag			= false;
		for (int i = 0; i < (KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y); i++)
		{
			m_enemy[number].magic[i].use_flag			= false;
			m_enemy[number].skill[i].use_flag			= false;
			m_enemy[number].item[i].use_flag			= false;
		}
		for (int i = 0; i < KEY_3RD_MAX_COMMAND_Y; i++)
		{
			m_enemy[number].who_command_flag[i]		= false;
		}
		m_enemy[number].turn_flag					= false;

		m_enemy[number].command_play_flag			= false;
		m_enemy[number].set_flag					= false;
		m_enemy[number].chara_move_flag				= false;
		m_enemy[number].chara_move_flag2			= false;
		m_enemy[number].chara_move_flag3			= false;
	}
	for (int i = 0; i < 7; i++)
	{
		camera_flag[i]								= false;
		damege[i].damage							= 0;
		damege[i].critical_hit_flag					= false;
		damege[i].damege_once_flag					= false;
	}
}

//コマンド打ち込み処理
//(味方のだれか)
void Battle::Command(int number, Music music)
{
	//最初のコマンドのカーソルキー
	if (!m_ally[number].first_command_flag)
	{
		//キーのアニメーション用
		Key_Anim(0);
		//上下のコマンド移動（横には動かない）
		Set_Move_Cursor(&key_pos[0].y, KEY_INPUT_W, KEY_INPUT_S, KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y, KEY_1ST_MAX_COMMAND, KEY_1ST_MOVE_Y, &key_count[0], &key_count[1], music);
		//コマンドを一個前に戻す
		Command_Pos_Reset(&command_pos[2], VectorGet(KEY_1ST_COMMAND_X - 200.0f, KEY_1ST_COMMAND_Y), &key_pos[0], VectorGet(command_pos[2].x + KEY_1ST_POS_X, command_pos[2].y + KEY_1ST_POS_Y));
		if (m_ally[0].name != m_ally[number].name)
		{
			if (m_ally[number - 1].who_command_flag)
			{
				Command_Back(m_ally[number - 1].who_command_flag, &m_ally[number - 1].turn_flag, KEY_3RD_MAX_COMMAND_Y, music);
			}
			else if (m_ally[number - 1].second_behavior_flag)
			{
				Command_Back(m_ally[number - 1].second_behavior_flag, &m_ally[number - 1].turn_flag, KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X, music);
			}
			else if (m_ally[number - 1].first_behavior_flag)
			{
				Command_Back(m_ally[number - 1].first_behavior_flag, &m_ally[number - 1].turn_flag, KEY_1ST_MAX_COMMAND, music);
			}
		}
		//どれかコマンド押したら次へ
		for (int i = 0; i < KEY_1ST_MAX_COMMAND; i++)
		{
			//たたかうのとき
			if (i == 0)
			{
				Decide_Command(key_pos[0],
					&key_pos[1],
					&m_ally[number].first_command_flag,
					&m_ally[number].first_behavior_flag[0],
					KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y, KEY_1ST_MOVE_Y, 0,
					KEY_1ST_COMMAND_X + KEY_1ST_POS_X, 0, 0,
					VectorGet(KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y), music);
			}
			//みる、にげるのとき
			else
			{
				Decide_Command(key_pos[0],
					&key_pos[0],
					&m_ally[number].turn_flag,
					&m_ally[number].first_behavior_flag[i],
					KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y, KEY_1ST_MOVE_Y, i,
					KEY_1ST_COMMAND_X + KEY_1ST_POS_X, 0, 0,
					VectorGet(command_pos[2].x + KEY_1ST_POS_X, command_pos[2].y + KEY_1ST_POS_Y), music);
			}
		}
	}
	//２番目のコマンドのカーソルキー
	else if (m_ally[number].first_command_flag && !m_ally[number].second_command_flag)
	{
		//キーのアニメーション用
		Key_Anim(1);
		//上下左右のコマンド移動
		Set_Move_Cursor(&key_pos[1].y, KEY_INPUT_W, KEY_INPUT_S, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y, KEY_2ND_MAX_COMMAND_Y, KEY_2ND_MOVE_Y, &key_count[0], &key_count[1], music);
		Set_Move_Cursor(&key_pos[1].x, KEY_INPUT_A, KEY_INPUT_D, KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_MAX_COMMAND_X, KEY_2ND_MOVE_X, &key_count[2], &key_count[3], music);
		//コマンドを一個前に戻す
		Command_Pos_Reset(&command_pos[2], VectorGet(KEY_2ND_COMMAND_X, KEY_2ND_COMMAND_Y + 300.0f), &key_pos[1], VectorGet(KEY_1ST_COMMAND_X + KEY_1ST_POS_X, KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y));
		Command_Back(m_ally[number].first_behavior_flag, &m_ally[number].first_command_flag, KEY_1ST_MAX_COMMAND, music);
		//どれかコマンド押したら次へ
		for (int i = 0; i < KEY_2ND_MAX_COMMAND_X; i++)
		{
			for (int j = 0; j < KEY_2ND_MAX_COMMAND_Y; j++)
			{
				//ぼうぎょ、ためるのとき
				if (i == 0 && j == 1 || i == 2 && j == 1)
				{
					Decide_Command(key_pos[1],
						&key_pos[0],
						&m_ally[number].turn_flag,
						&m_ally[number].second_behavior_flag[i == 0 && j == 1 ? guard : sink ],
						KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y, KEY_2ND_MOVE_Y, j,
						KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_MOVE_X, i,
						VectorGet(command_pos[2].x + KEY_1ST_POS_X, command_pos[2].y + KEY_1ST_POS_Y), music);
				}
				//こうげき、じゅもん、とくぎ、どうぐのとき
				else
				{
					Decide_Command(key_pos[1],
						i == 0 && j == 0 ? &key_pos[2] : &key_pos[3],//攻撃の時はそのままcommand３へ、それ以外はインベントリを開く
						&m_ally[number].second_command_flag,
						&m_ally[number].second_behavior_flag[j == 0 ? i : i + KEY_2ND_MAX_COMMAND_X],
						KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y, KEY_2ND_MOVE_Y, j,
						KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_MOVE_X, i,
						i == 0 && j == 0 ? VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y) : VectorGet(KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y), music);
				}
			}
		}
	}
	//３番目のコマンドのカーソルキー
	else if (m_ally[number].second_command_flag && m_ally[number].second_behavior_flag[attack] || m_ally[number].magic_command_flag)
	{
		//キーのアニメーション用
		Key_Anim(2);
		//上下のコマンド移動
		Set_Move_Cursor(&key_pos[2].y, KEY_INPUT_W, KEY_INPUT_S, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y, KEY_3RD_MAX_COMMAND_Y, KEY_3RD_MOVE_Y, &key_count[0], &key_count[1], music);
		//コマンドを一個前に戻す
		Command_Pos_Reset(&command_pos[3], VectorGet(KEY_2ND_COMMAND_X, KEY_2ND_COMMAND_Y + 300.0f), &key_pos[2], VectorGet(KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y));
		if (!m_ally[number].magic_command_flag)
		{
			//前のコマンドでこうげきを選んでたとき
			Command_Back(m_ally[number].second_behavior_flag, &m_ally[number].second_command_flag, KEY_2ND_MAX_COMMAND_X * KEY_2ND_MAX_COMMAND_Y, music);
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				//前のコマンドでじゅもん、とくぎ、どうぐを選んでたとき
				Command_Back(&m_ally[number].magic[i].use_flag, &m_ally[number].magic_command_flag, KEY_MAGIC_MAX_COMMAND_X * KEY_MAGIC_MAX_COMMAND_Y, music);
			}
		}
		//どれかコマンド押したら次へ
		for (int i = 0; i < KEY_3RD_MAX_COMMAND_Y; i++)
		{
			Decide_Command(key_pos[2],
				&key_pos[0],
				&m_ally[number].turn_flag,
				&m_ally[number].who_command_flag[i],
				KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y, KEY_3RD_MOVE_Y, i,
				KEY_3RD_COMMAND_X + KEY_3RD_POS_X, 0, 0,
				VectorGet(command_pos[2].x + KEY_1ST_POS_X, command_pos[2].y + KEY_1ST_POS_Y), music);
		}
	}
	//魔法、特技、アイテムのコマンドのカーソルキー
	else if (m_ally[number].second_command_flag && !m_ally[number].magic_command_flag && !m_ally[number].second_behavior_flag[attack] && !m_ally[number].second_behavior_flag[guard] && !m_ally[number].second_behavior_flag[sink])
	{
		//キーのアニメーション用
		Key_Anim(3);
		//上下左右のコマンド移動
		Set_Move_Cursor(&key_pos[3].y, KEY_INPUT_W, KEY_INPUT_S, KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y, KEY_MAGIC_MAX_COMMAND_Y, KEY_MAGIC_MOVE_Y, &key_count[0], &key_count[1], music);
		Set_Move_Cursor(&key_pos[3].x, KEY_INPUT_A, KEY_INPUT_D, KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_MAX_COMMAND_X, KEY_MAGIC_MOVE_X, &key_count[2], &key_count[3], music);
		//コマンドを一個前に戻す
		Command_Pos_Reset(&command_pos[4], VectorGet(KEY_MAGIC_COMMAND_X, KEY_2ND_COMMAND_Y), &key_pos[3], VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y));
		Command_Back(m_ally[number].second_behavior_flag, &m_ally[number].second_command_flag, KEY_2ND_MAX_COMMAND_X * KEY_2ND_MAX_COMMAND_Y, music);
		//どれかコマンド押したら次へ
		for (int i = 0; i < KEY_MAGIC_MAX_COMMAND_X; i++)
		{
			for (int j = 0; j < KEY_MAGIC_MAX_COMMAND_Y; j++)
			{
				if (m_ally[number].second_behavior_flag[skill])
				{
					Decide_Command(key_pos[3],
						&key_pos[2],
						&m_ally[number].magic_command_flag,
						&m_ally[number].skill[j == 0 ? i : i + KEY_MAGIC_MAX_COMMAND_X].use_flag,
						KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y, KEY_MAGIC_MOVE_Y, j,
						KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_MOVE_X, i,
						VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y), music);
				}
				if (m_ally[number].second_behavior_flag[magic])
				{
					Decide_Command(key_pos[3],
						&key_pos[2],
						&m_ally[number].magic_command_flag,
						&m_ally[number].magic[j == 0 ? i : i + KEY_MAGIC_MAX_COMMAND_X].use_flag,
						KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y, KEY_MAGIC_MOVE_Y, j,
						KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_MOVE_X, i,
						VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y), music);
				}
				if (m_ally[number].second_behavior_flag[item])
				{
					Decide_Command(key_pos[3],
						&key_pos[2],
						&m_ally[number].magic_command_flag,
						&m_ally[number].item[j == 0 ? i : i + KEY_MAGIC_MAX_COMMAND_X].use_flag,
						KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y, KEY_MAGIC_MOVE_Y, j,
						KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_MOVE_X, i,
						VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y), music);
				}
			}
		}
	}
	if (m_ally[number].turn_flag && !reset_command_pos_flag)
	{
		Command_Smooth(&command_pos[3], VectorGet(KEY_2ND_COMMAND_X, KEY_2ND_COMMAND_Y + 300.0f), KEY_SPEED);
		Command_Smooth(&command_pos[4], VectorGet(KEY_MAGIC_COMMAND_X, KEY_MAGIC_COMMAND_Y), KEY_SPEED);
		Command_Smooth(&command_pos[5], VectorGet(KEY_3RD_COMMAND_X, KEY_3RD_COMMAND_Y + 300.0f), KEY_SPEED);
		Command_Smooth(&key_pos[1], VectorGet(KEY_1ST_COMMAND_X + KEY_1ST_POS_X, KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y), KEY_SPEED);
		Command_Smooth(&key_pos[2], VectorGet(KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y), KEY_SPEED);
		Command_Smooth(&key_pos[3], VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y), KEY_SPEED);
		if (Cursor(command_pos[3].y, KEY_2ND_COMMAND_Y + 300.0f))
		{
			reset_command_pos_flag = true;
		}
	}
}

//コマンド打ち込んでるときの描画
//(味方のだれか、フォント描画用、コマンドウィンドウ描画用)
void Battle::Command_Choice_Draw(int number, Comment_string *comment, Window *window, Memory *memory)
{
	std::size_t name_num;
	//コマンド座標移動
	if (!Cursor(command_pos[2].x, KEY_1ST_COMMAND_X))
	{
		Command_Smooth(&command_pos[2], VectorGet(KEY_1ST_COMMAND_X, KEY_1ST_COMMAND_Y), KEY_SPEED);
		Command_Smooth(&key_pos[0], VectorGet(KEY_1ST_COMMAND_X + KEY_1ST_POS_X, KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y), KEY_SPEED);
	}
	//名前枠と名前
	window->Command_Draw((float)command_pos[2].x, (float)(command_pos[2].y + NAME_COMMAND_Y), (float)NAME_COMMAND_SIZE_X, (float)NAME_COMMAND_SIZE_Y);
	comment->Draw((float)(command_pos[2].x + 15), (float)(command_pos[2].y + NAME_COMMAND_Y + 10), m_ally[number].name);
	//１つ目のコマンド
	window->Command_Draw(command_pos[2].x, command_pos[2].y, (float)KEY_1ST_COMMAND_SIZE_X, (float)KEY_1ST_COMMAND_SIZE_Y);
	//たたかう、みる、にげる
	for (int i = 0; i < 3; i++)
	{
		comment->Draw(command_pos[2].x + KEY_1ST_POS_X + 25.0f,
					  (command_pos[2].y + KEY_1ST_POS_Y - 10.0f) + (KEY_1ST_MOVE_Y*i),
					  first_behavior[i]);
	}
	//１つ目のコマンド用のカーソル
	DrawGraph((int)key_pos[0].x, (int)key_pos[0].y, key_graph[now_frame[0]], TRUE);
	//２つ目のコマンド
	if (m_ally[number].first_command_flag)
	{
		//コマンド座標移動
		if (!Cursor(command_pos[3].y, KEY_2ND_COMMAND_Y))
		{
			Command_Smooth(&command_pos[3], VectorGet(KEY_2ND_COMMAND_X, KEY_2ND_COMMAND_Y), KEY_SPEED);
			Command_Smooth(&key_pos[1], VectorGet(KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y), KEY_SPEED);
		}
		//前のコマンドを暗くする
		window->Command_Draw(command_pos[2].x, command_pos[2].y, (float)KEY_1ST_COMMAND_SIZE_X, (float)KEY_1ST_COMMAND_SIZE_Y);
		//２つ目のコマンド枠
		window->Command_Draw(command_pos[3].x, command_pos[3].y, (float)KEY_2ND_COMMAND_SIZE_X, (float)KEY_2ND_COMMAND_SIZE_Y);
		for (int i = 0; i < KEY_2ND_MAX_COMMAND_X; i++)
		{
			//こうげき、とくぎ、まほう
			comment->Draw(command_pos[3].x + KEY_2ND_POS_X + 25.0f + (KEY_2ND_MOVE_X * i),
						  command_pos[3].y + KEY_2ND_POS_Y - 10.0f,
						  second_behavior[i]);
			//ぼうぎょ、どうぐ、ためる
			comment->Draw(command_pos[3].x + KEY_2ND_POS_X + 25.0f + (KEY_2ND_MOVE_X * i),
						  command_pos[3].y + KEY_2ND_POS_Y - 10.0f + KEY_2ND_MOVE_Y,
						  second_behavior[i + 3]);
		}
		//２つ目のコマンド用のカーソル
		DrawGraph((int)key_pos[1].x, (int)key_pos[1].y, key_graph[now_frame[1]], TRUE);
	}
	//魔法等のコマンド
	if (m_ally[number].second_command_flag && !m_ally[number].second_behavior_flag[attack] && !m_ally[number].second_behavior_flag[guard] && !m_ally[number].second_behavior_flag[sink])
	{
		//コマンド座標移動
		if (!Cursor(command_pos[4].y, KEY_MAGIC_COMMAND_Y))
		{
			Command_Smooth(&command_pos[4], VectorGet(KEY_MAGIC_COMMAND_X, KEY_MAGIC_COMMAND_Y), KEY_SPEED);
			Command_Smooth(&key_pos[3], VectorGet(KEY_MAGIC_COMMAND_X + KEY_MAGIC_POS_X, KEY_MAGIC_COMMAND_Y + KEY_MAGIC_POS_Y), KEY_SPEED);
		}
		//前のコマンドを暗くする
		window->Command_Draw(command_pos[3].x, command_pos[3].y, (float)KEY_2ND_COMMAND_SIZE_X, (float)KEY_2ND_COMMAND_SIZE_Y);
		//魔法等のコマンド枠
		window->Command_Draw(command_pos[4].x, command_pos[4].y, (float)KEY_MAGIC_COMMAND_SIZE_X, (float)KEY_MAGIC_COMMAND_SIZE_Y);
		//覚えてる、持っているもの描画（何も覚えてなかった、持っていなかったら暗く＜なし＞と表示）
		Have_Spell_Draw(m_ally[number], skill, m_ally[number].skill, memory->I_skill, comment);
		Have_Spell_Draw(m_ally[number], magic, m_ally[number].magic, memory->I_spell, comment);
		Have_Spell_Draw(m_ally[number], item,  m_ally[number].item,  memory->I_item,  comment);
		//魔法等のコマンド用のカーソル
		DrawGraph((int)key_pos[3].x, (int)key_pos[3].y, key_graph[now_frame[3]], TRUE);
	}
	//３つ目のコマンド
	if (m_ally[number].second_command_flag && m_ally[number].second_behavior_flag[attack] || m_ally[number].magic_command_flag)
	{
		//コマンド座標移動
		if (!Cursor(command_pos[5].y, KEY_3RD_COMMAND_Y))
		{
			Command_Smooth(&command_pos[5], VectorGet(KEY_3RD_COMMAND_X, KEY_3RD_COMMAND_Y), KEY_SPEED);
			Command_Smooth(&key_pos[2], VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y), KEY_SPEED);
		}
		//前のコマンドでこうげきを選んでたら
		if (!m_ally[number].magic_command_flag)
		{
			//前のコマンドを暗くする
			window->Command_Draw(command_pos[3].x, command_pos[3].y, (float)KEY_2ND_COMMAND_SIZE_X, (float)KEY_2ND_COMMAND_SIZE_Y);
		}
		//前のコマンドでまほう、とくぎ、どうぐを選んでたら
		if (m_ally[number].magic_command_flag)
		{
			//前のコマンドを暗くする
			window->Command_Draw(command_pos[4].x, command_pos[4].y, (float)KEY_MAGIC_COMMAND_SIZE_X, (float)KEY_MAGIC_COMMAND_SIZE_Y);
		}
		//３つ目のコマンド
		window->Command_Draw(command_pos[5].x, command_pos[5].y, (float)KEY_3RD_COMMAND_SIZE_X, (float)KEY_3RD_COMMAND_SIZE_Y);
		//敵の名前
		for (int i = 0; i < 4; i++)
		{
			name_num = m_enemy[i].name.size() / 2;
			if (m_enemy[i].hp > 0)
			{
				comment->Draw(command_pos[5].x + KEY_3RD_POS_X + 20, command_pos[5].y + KEY_3RD_POS_Y + (KEY_3RD_MOVE_Y * i) - 10, m_enemy[i].name);
				Set_HPber((command_pos[5].x + KEY_3RD_POS_X + 15 + (name_num * 50)), (command_pos[5].y + KEY_3RD_POS_Y + (KEY_3RD_MOVE_Y * i)), m_enemy[i].hp / m_enemy[i].max_hp, GetColor(55, 255, 55));
				if (Cursor(key_pos[2].y, command_pos[5].y + KEY_3RD_POS_Y + (KEY_3RD_MOVE_Y * i)))
				{
					DrawBillboard3D(VGet(m_enemy[i].b_pos.x, m_enemy[i].b_pos.y + 10.0f, m_enemy[i].b_pos.z), 0.5f, 0.5f, 5.0f, (float)(-DX_PI / 2.0f), key_graph[now_frame[2]], TRUE);
				}
			}
		}
		//３つ目のコマンド用のカーソル
		DrawGraph((int)key_pos[2].x, (int)key_pos[2].y, key_graph[now_frame[2]], TRUE);
	}
}
//キャラの名前が同じならフラグをtrueにする
//(どこかからか入れられたキャラ情報、それと比べるキャラ情報)
void Chara_Name_Flager(Chara chara_case, Chara *origin)
{
    if (chara_case.name == origin->name || origin->die_flag)
	{
		origin->command_play_flag = true;
	}
}

//ダメージの大きさに応じて乱数をプラスする
//(バトル上にあるダメージ型)
void Battle::Damage_Adjustment(int *damege)
{
	if (*damege <= 0)
	{
		*damege = GetRand(1);
	}
	else if (*damege > 0 && *damege <= 50)
	{
		*damege = *damege + GetRand(5);
	}
	else if (*damege > 50 && *damege <= 100)
	{
		*damege = *damege + GetRand(20);
		*damege = *damege + GetRand(-10);
	}
	else if (*damege > 100 && *damege <= 200)
	{
		*damege = *damege + GetRand(40);
		*damege = *damege + GetRand(-20);
	}
	else if (*damege > 200 && *damege <= 400)
	{
		*damege = *damege + GetRand(80);
		*damege = *damege + GetRand(-40);
	}
	else if (*damege > 400 && *damege <= 999)
	{
		*damege = *damege + GetRand(100);
		*damege = *damege + GetRand(-50);
	}
	else if (*damege > 999)
	{
		*damege = 999;
	}
}

//ダメージ計算する
//(与える側のキャラ型、ダメージの元、追加したいダメージ、物理攻撃か否か)
void Battle::Damage_Calculation(Chara *chara_case, int damege_source, int damege_bonus, bool physics_flag)
{
	if (chara_case->ally_or_enemy_flag)
	{
        for (int i = 0; i < 3; i++)
        {
            if (chara_case->name == m_ally[i].name)
            {
				if (!damege[i].damege_once_flag)
				{
					if (!probability((int)(5 + (float)(chara_case->ski * 0.1f))))
					{
						if (physics_flag)
						{
							damege[i].damage = (int)(damege_source * 1.5f - ((chara_case->def + chara_case->puls_def) * 0.5f) + damege_bonus);
						}
						else if (!physics_flag)
						{
							damege[i].damage = (int)(damege_source * 1.5f - (chara_case->mp * 0.5f) + damege_bonus);
						}
					}
					else
					{
						damege[i].critical_hit_flag = true;
						damege[i].damage = (int)(damege_source * 1.5f + damege_bonus);
					}
					Damage_Adjustment(&damege[i].damage);
                    for (int j = 0; j < 4; j++)
                    {
                        if (chara_case->who_command_flag[j])
                        {
							if (m_enemy[j].second_behavior_flag[guard])
							{
								damege[i].damage /= 2;
							}
							m_enemy[j].hp -= damege[i].damage;
                            if (m_enemy[j].hp <= 0)
                            {
                                m_enemy[j].die_flag = true;
                            }
                        }
                    }
					damege[i].damege_once_flag = true;
				}
			}
		}
	}
	else
	{
        for (int i = 0; i < 4; i++)
        {
            if (chara_case->name == m_enemy[i].name)
            {
                if (!damege[i + 3].damege_once_flag)
                {
                    if (!probability((int)(5 + (float)(chara_case->ski * 0.1f))))
                    {
                        if (physics_flag)
                        {
                            damege[i + 3].damage = (int)(damege_source * 1.5f - ((chara_case->def + chara_case->puls_def) * 0.5f) + damege_bonus);
                        }
                        else if (!physics_flag)
                        {
                            damege[i + 3].damage = (int)(damege_source * 1.5f - (chara_case->mp * 0.5f) + damege_bonus);
                        }
                    }
                    else
                    {
                        damege[i + 3].critical_hit_flag = true;
                        damege[i + 3].damage = (int)(damege_source * 1.5f + damege_bonus);
                    }
                    Damage_Adjustment(&damege[i + 3].damage);
                    for (int j = 0; j < 3; j++)
                    {
                        if (chara_case->who_command_flag[j])
                        {
							if (m_ally[j].second_behavior_flag[guard])
							{
								damege[i].damage /= 2;
							}
                            m_ally[j].hp -= damege[i + 3].damage;
                            if (m_ally[j].hp <= 0)
                            {
                                m_ally[j].die_flag = true;
                            }
                        }
                    }
                    damege[i + 3].damege_once_flag = true;
                }
            }
        }
	}
}

//ダメージ計算などをまとめたもの
//(与える側のキャラ型、数字の描画ｘ座標、数字の描画ｙ座標、ダメージの元、追加したいダメージ、物理攻撃か否か)
void Battle::Damage_Calculation_Set(Comment_string *comment, Chara *chara_case, float command_x, float command_y, int damege_source, int damege_bonus, bool physics_flag)
{
	Damage_Calculation(chara_case, damege_source, damege_bonus, physics_flag);
	if (chara_case->ally_or_enemy_flag)
	{
		for (int i = 0; i < 3; i++)
		{
			if (chara_case->name == m_ally[i].name)
			{
				comment->Draw(command_x, command_y, "に");
				Count_Draw_2D(count_graph, damege[i].damage, command_x + 50, command_y);
				for (int z = 0; z < 4; z++)
				{
					if (chara_case->who_command_flag[z])
					{
						Count_Draw_3D(count_graph, damege[i].damage, m_enemy[z].b_pos.x, 10.0f,m_enemy[z].b_pos.z);
					}
				}
				for (int j = 1; j < 4; j++)
				{
					if (damege[i].damage < pow(10, j))
					{
						comment->Draw(command_x + STRING_SIZE_W * (j + 1), command_y, "のダメージ！");
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (chara_case->name == m_enemy[i].name)
			{
				comment->Draw(command_x, command_y, "に");
				Count_Draw_2D(count_graph, damege[i + 3].damage, command_x + 50, command_y);
				for (int z = 0; z < 3; z++)
				{
					if (chara_case->who_command_flag[z])
					{
						Enemy_Count_Draw_3D(count_graph, damege[i + 3].damage, m_ally[z].b_pos.x, 20.0f, m_ally[z].b_pos.z);
					}
				}
				for (int j = 1; j < 4; j++)
				{
					if (damege[i + 3].damage < pow(10, j))
					{
						comment->Draw(command_x + STRING_SIZE_W * (j + 1), command_y, "のダメージ！");
						break;
					}
				}
			}
		}
	}
}

//コマンド打ったあとの描画
//(フォント描画用、キャラ情報０～６、描画時間)
void Battle::Command_Play_Draw(Comment_string *comment,Chara *chara0, Chara *chara1, Chara *chara2, Chara *chara3, Chara *chara4, Chara *chara5, Chara *chara6,int count_max)
{
	Chara chara_case = No_1_Speed_Get(chara0, chara1, chara2, chara3, chara4, chara5, chara6);
	if (chara_case.command_play_flag)
	{	
		float command_x = (float)(FIRST_COMMAND_X + 300);
		float command_y = (float)(command_pos[0].y + 30);
		std::size_t name_num;
		if (!chara_case.chara_move_flag2)
		{
			comment->Draw(command_x, command_y, chara_case.name);
			name_num = chara_case.name.size() / 2;
		}
		else
		{
			if (chara_case.ally_or_enemy_flag)
			{
				for (int i = 0; i < 4; i++)
				{
                    if (chara_case.who_command_flag[i])
                    {
                        comment->Draw(command_x, command_y, m_enemy[i].name);
						name_num = m_enemy[i].name.size() / 2;
                    }
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
                    if (chara_case.who_command_flag[i])
                    {
                        comment->Draw(command_x, command_y, m_ally[i].name);
						name_num = m_ally[i].name.size() / 2;
                    }
				}
			}
		}
		if (chara_case.first_behavior_flag[see])
		{
			comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "はじっとみている。");
		}
		else if (chara_case.first_behavior_flag[escape])
		{
			comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "たちはにげだした！");
		}
		else if (chara_case.second_behavior_flag[attack])
		{
			if (!chara_case.chara_move_flag2)
			{
				comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "のこうげき！");
			}
			else
			{
				Damage_Calculation_Set(comment, &chara_case, command_x + (float)(name_num * STRING_SIZE_W), command_y, (int)chara_case.pow, 0, true);
			}
		}
		else if (chara_case.second_behavior_flag[guard])
		{
			comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "はみをまもっている。");
		}
		else if (chara_case.second_behavior_flag[sink])
		{
			comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "はテンションをためた！");
		}
		else if (chara_case.second_behavior_flag[skill] || chara_case.second_behavior_flag[magic] || chara_case.second_behavior_flag[item])
		{
			if (!chara_case.chara_move_flag2)
			{
				for (int i = 0; i < 6; i++)
				{
					if (chara_case.magic[i].use_flag)
					{
							comment->Draw(command_x + (float)(name_num * STRING_SIZE_W), command_y, "は");
							if (chara_case.second_behavior_flag[skill])
							{
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 100, command_y, chara_case.skill[i].name);
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 400, command_y, "をはなった！");
							}
							if (chara_case.second_behavior_flag[magic])
							{
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 100, command_y, chara_case.magic[i].name);
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 400, command_y, "をとなえた！");
							}
							if (chara_case.second_behavior_flag[item])
							{
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 100, command_y, chara_case.item[i].name);
								comment->Draw(command_x + (float)(name_num * STRING_SIZE_W) + 400, command_y, "をつかった！");
							}
						}
					}
				}
			else
			{
				Damage_Calculation_Set(comment, &chara_case, command_x + (float)(name_num * STRING_SIZE_W), command_y, (int)chara_case.pow, 0, false);
			}
		}
		command_play_count++;
		if (command_play_count > count_max)
		{
			Chara_Name_Flager(chara_case, chara0);
			Chara_Name_Flager(chara_case, chara1);
			Chara_Name_Flager(chara_case, chara2);
			Chara_Name_Flager(chara_case, chara3);
			Chara_Name_Flager(chara_case, chara4);
			Chara_Name_Flager(chara_case, chara5);
			Chara_Name_Flager(chara_case, chara6);
			command_play_count = 0;
			if (m_enemy[0].die_flag && m_enemy[1].die_flag && m_enemy[2].die_flag && m_enemy[3].die_flag)
			{
				end_flag = true;
			}
		}
	}
}

//狙った相手が倒されたとき、他の敵を攻撃するための関数
//(動くキャラ（味方）、だれに当たるか（敵）、敵の総数)
void Battle::Enemy_Kill_Next(Chara *chara, Chara *enemy, int enemy_num)
{
    for (int j = 0; j < enemy_num; j++)
    {
        if (chara->who_command_flag[j])
        {
            if (enemy[j].die_flag)
            {
                if (j < enemy_num - 1)
                {
                    chara->who_command_flag[j] = false;
                    chara->who_command_flag[j + 1] = true;
                }
                else
                {
                    chara->who_command_flag[j] = false;
                    chara->who_command_flag[0] = true;
                }
            }
        }
    }
}

//当たって帰ってくる処理
//(動くキャラ（味方）、だれに当たるか（敵）、動くためのフラグ２、動くためのフラグ３、敵の総数)
void Battle::Hit_And_Awey(Chara *chara, Chara *enemy, bool *chara_move_flag2, bool *chara_move_flag3, int enemy_num)
{
	for (int j = 0; j < enemy_num; j++)
	{
		if (chara->who_command_flag[j])
		{
	        if (!*chara_move_flag2)
	        {
                Enemy_Kill_Next(chara, enemy, enemy_num);
	        	float between = Vector_Length(Sub_Vector_Vector(chara->b_pos, enemy[j].b_pos));
	        	Chara_Smooth(&chara->b_pos, enemy[j].b_pos, 3.0f);
	        	if (Cursor(between, 0))
	        	{
	        		*chara_move_flag2 = true;
	        	}
	        }
	        else if (*chara_move_flag2 && !Cursor(chara->b_pos.z, chara->first_pos.z))
	        {
	        	Chara_turn_Smooth(&chara->b_pos, chara->first_pos, -3.0f);
	        	if (Cursor(chara->b_pos.z, chara->first_pos.z))
	        	{
	        		*chara_move_flag3 = true;
	        	}
	        }
		}
	}
}

//コマンド打った後の動き
//(動くキャラ（味方）、だれにあてたか（敵）、味方の総数、敵の総数)
void Battle::Playing_Move(Chara *ally, Chara *enemy, int ally_num, int enemy_num)
{
	for (int i = 0; i < ally_num; i++)
	{
		if (ally[i].chara_move_flag)
		{
			if (ally[i].first_behavior_flag[see])
			{
			}
			else if (ally[i].first_behavior_flag[escape])
			{
			}
			else if (ally[i].second_behavior_flag[attack])
			{
				Hit_And_Awey(&ally[i], enemy, &ally[i].chara_move_flag2, &ally[i].chara_move_flag3, enemy_num);
			}
			else if (ally[i].second_behavior_flag[guard])
			{
			}
			else if (ally[i].second_behavior_flag[sink])
			{
			}
			else if (ally[i].second_behavior_flag[skill] || ally[i].second_behavior_flag[magic] || ally[i].second_behavior_flag[item])
			{
				for (int j = 0; j < 6; j++)
				{
					if (ally[i].magic[j].use_flag)
					{
						if (ally[i].second_behavior_flag[skill])
						{
							Hit_And_Awey(&ally[i], enemy, &ally[i].chara_move_flag2, &ally[i].chara_move_flag3, enemy_num);
						}
						if (ally[i].second_behavior_flag[magic])
						{
							Hit_And_Awey(&ally[i], enemy, &ally[i].chara_move_flag2, &ally[i].chara_move_flag3, enemy_num);
						}
						if (ally[i].second_behavior_flag[item])
						{
							Hit_And_Awey(&ally[i], enemy, &ally[i].chara_move_flag2, &ally[i].chara_move_flag3, enemy_num);
						}
					}
				}
				if (ally[i].second_behavior_flag[skill])
				{
				}
				if (ally[i].second_behavior_flag[magic])
				{
				}
				if (ally[i].second_behavior_flag[item])
				{
				}
			}
		}
	}
}

void Battle::Command_Play_Move()
{
	if (m_ally[2].turn_flag)
	{
		if (command_play_count == 1)
		{
			for (int i = 0; i < 7; i++)
			{
				if (camera_flag[i] &&
					(i < 3 ? !m_ally[i].command_play_flag : !m_enemy[i - 3].command_play_flag))
				{
					Move_Flag_Reset();
					if (i < 3)
					{
						m_ally[i].chara_move_flag = true;
					}
					if (i >= 3)
					{
						m_enemy[i - 3].chara_move_flag = true;
					}
				}
			}
		}
		Playing_Move(m_ally, m_enemy, 3, 4);
		Playing_Move(m_enemy, m_ally, 4, 3);
		//printfDx("%d %d %d %d %d %d %d\n", chara_flag[0].chara_move_flag, chara_flag[1].chara_move_flag, chara_flag[2].chara_move_flag, chara_flag[3].chara_move_flag, chara_flag[4].chara_move_flag, chara_flag[5].chara_move_flag, chara_flag[6].chara_move_flag);
	}
}

//************************************************************************
// バトル突入時のキャラの代入
// (味方のキャラ情報１～３、敵のキャラ情報１～４)
//************************************************************************
void Battle::In(Chara *ally1, Chara *ally2, Chara *ally3, Chara *enemy1, Chara *enemy2, Chara *enemy3, Chara *enemy4)
{
    m_ally[0]  = *ally1;
    m_ally[1]  = *ally2;
    m_ally[2]  = *ally3;
    m_enemy[0] = *enemy1;
    m_enemy[1] = *enemy2;
    m_enemy[2] = *enemy3;
    m_enemy[3] = *enemy4;
    for (int i = 0; i < 3; i++)
    {
        MV1SetRotationXYZ(m_ally[i].modelHandle, VGet(0.0f, 0.0f, 0.0f));
        m_ally[i].attack_flag = false;
        m_ally[i].die_flag = false;
    }
    if (m_enemy[1].name == "エラー！")
    {
        m_enemy[0].b_pos = VectorGet(ENEMY_B_POS_X + 82, 0, ENEMY_B_POS_Y);
		m_enemy[0].attack_flag = false;
		m_enemy[0].die_flag = false;
		m_enemy[0].first_pos = m_enemy[0].b_pos;
    }
    else if (m_enemy[2].name == "エラー！")
    {
		m_enemy[0].b_pos = VectorGet(ENEMY_B_POS_X + 55, 0, ENEMY_B_POS_Y);
        m_enemy[1].b_pos = VectorGet(ENEMY_B_POS_X + (55 * 2), 0, ENEMY_B_POS_Y);
		for (int i = 0; i < 2; i++)
		{
			m_enemy[i].attack_flag = false;
			m_enemy[i].die_flag = false;
			m_enemy[i].first_pos = m_enemy[i].b_pos;
		}
		if (m_enemy[0].name == m_enemy[1].name)
		{
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[1].name = m_enemy[1].name + "Ｂ";
		}
    }
    else if (m_enemy[3].name == "エラー！")
    {
        m_enemy[0].b_pos = VectorGet(ENEMY_B_POS_X + 40, 0, 515);
        m_enemy[1].b_pos = VectorGet(ENEMY_B_POS_X + (40 * 2), 0, ENEMY_B_POS_Y);
        m_enemy[2].b_pos = VectorGet(ENEMY_B_POS_X + (40 * 3), 0, ENEMY_B_POS_Y);
		for (int i = 0; i < 3; i++)
		{
			m_enemy[i].attack_flag = false;
			m_enemy[i].die_flag = false;
			m_enemy[i].first_pos = m_enemy[i].b_pos;
		}
		if (m_enemy[0].name == m_enemy[1].name)
		{
			if (m_enemy[0].name == m_enemy[2].name)
			{
				m_enemy[2].name = m_enemy[2].name + "Ｃ";
			}
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[1].name = m_enemy[1].name + "Ｂ";
		}
		else if (m_enemy[0].name == m_enemy[2].name)
		{
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[2].name = m_enemy[2].name + "Ｂ";
		}
		else if (m_enemy[1].name == m_enemy[2].name)
		{
			m_enemy[1].name = m_enemy[1].name + "Ａ";
			m_enemy[2].name = m_enemy[2].name + "Ｂ";
		}
    }
    else
    {
        m_enemy[0].b_pos = VectorGet(ENEMY_B_POS_X + 33, 0, ENEMY_B_POS_Y);
        m_enemy[1].b_pos = VectorGet(ENEMY_B_POS_X + (33 * 2), 0, ENEMY_B_POS_Y);
        m_enemy[2].b_pos = VectorGet(ENEMY_B_POS_X + (33 * 3), 0, ENEMY_B_POS_Y);
        m_enemy[3].b_pos = VectorGet(ENEMY_B_POS_X + (33 * 4), 0, ENEMY_B_POS_Y);
		for (int i = 0; i < 4; i++)
		{
			m_enemy[i].attack_flag = false;
			m_enemy[i].die_flag = false;
			m_enemy[i].first_pos = m_enemy[i].b_pos;
		}
		if (m_enemy[0].name == m_enemy[1].name)
		{
			if (m_enemy[0].name == m_enemy[2].name)
			{
				if (m_enemy[0].name == m_enemy[3].name)
				{
					m_enemy[3].name = m_enemy[3].name + "Ｄ";
				}
				m_enemy[2].name = m_enemy[2].name + "Ｃ";
			}
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[1].name = m_enemy[1].name + "Ｂ";
		}
		else if (m_enemy[1].name == m_enemy[2].name)
		{
			if (m_enemy[1].name == m_enemy[3].name)
			{
				m_enemy[3].name = m_enemy[3].name + "Ｃ";
			}
			m_enemy[1].name = m_enemy[1].name + "Ａ";
			m_enemy[2].name = m_enemy[2].name + "Ｂ";
		}
		else if (m_enemy[0].name == m_enemy[2].name)
		{
			if (m_enemy[0].name == m_enemy[3].name)
			{
				m_enemy[3].name = m_enemy[3].name + "Ｃ";
			}
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[2].name = m_enemy[2].name + "Ｂ";
		}
		else if (m_enemy[0].name == m_enemy[1].name)
		{
			if (m_enemy[0].name == m_enemy[3].name)
			{
				m_enemy[3].name = m_enemy[3].name + "Ｃ";
			}
			m_enemy[0].name = m_enemy[0].name + "Ａ";
			m_enemy[1].name = m_enemy[1].name + "Ｂ";
		}
    }
}

//************************************************************************
// 画像読み込み
//************************************************************************
Battle::Battle()
{
	//コマンド枠
	{
		first_frame_graph    = LoadGraph("data/command/comment.png");
        status_command_graph = LoadGraph("data/command/command_status.png");
        name_command_graph   = LoadGraph("data/command/command_name.png");
        one_command_graph    = LoadGraph("data/command/command_1.png");
		two_command_graph    = LoadGraph("data/command/command_2.png");
		three_command_graph  = LoadGraph("data/command/command_3.png");
		magic_command_graph  = two_command_graph;
	}
	//カーソル
	LoadDivGraph("data/command/key.png", 8, 8, 1, 35, 25, key_graph);
	//数字
	LoadDivGraph("data/command/number.png",        NUMBER_MAX_X * NUMBER_MAX_Y, NUMBER_MAX_X, NUMBER_MAX_Y, (int)NUMBER_SIZE_X, (int)NUMBER_SIZE_Y, count_graph);
    LoadDivGraph("data/command/number_orange.png", NUMBER_MAX_X * NUMBER_MAX_Y, NUMBER_MAX_X, NUMBER_MAX_Y, (int)NUMBER_SIZE_X, (int)NUMBER_SIZE_Y, count_graph_orange);
    LoadDivGraph("data/command/number_red.png",    NUMBER_MAX_X * NUMBER_MAX_Y, NUMBER_MAX_X, NUMBER_MAX_Y, (int)NUMBER_SIZE_X, (int)NUMBER_SIZE_Y, count_graph_red);
	//たたかう、みる、にげる
	{
		first_behavior[battle] = "たたかう";
		first_behavior[see] = "みる";
		first_behavior[escape] = "にげる";
	}
	//こうげき、とくぎ、まほう、ぼうぎょ、どうぐ、ためる
	{
		second_behavior[attack] = "こうげき";
		second_behavior[skill] = "とくぎ";
		second_behavior[magic] = "まほう";
		second_behavior[guard] = "ぼうぎょ";
		second_behavior[item] = "どうぐ";
		second_behavior[sink] = "ためる";
	}
}

//************************************************************************
// 画像デリート用（現在未使用）
//************************************************************************
Battle::~Battle()
{

}


//************************************************************************
// 初期化
//************************************************************************
void Battle::Init(Camera *camera, Player *player)
{
	rand_count = 0;
	end_flag = false;
    for (int i = 0; i < 10; i++)
    {
        command_pos[i] = VectorGet(0, 0);
    }
    command_pos[0] = VectorGet(FIRST_COMMAND_X,			   FIRST_COMMAND_Y + 200.f);
	command_pos[1] = VectorGet(10.0f,                      -200.0f);
    command_pos[2] = VectorGet(KEY_1ST_COMMAND_X - 200.0f, KEY_1ST_COMMAND_Y);
	command_pos[3] = VectorGet(KEY_2ND_COMMAND_X,          KEY_2ND_COMMAND_Y + 300.0f);
	command_pos[4] = VectorGet(KEY_MAGIC_COMMAND_X,        KEY_2ND_COMMAND_Y);
	command_pos[5] = VectorGet(KEY_3RD_COMMAND_X,          KEY_3RD_COMMAND_Y + 300.0f);
	key_pos[0] = VectorGet(command_pos[2].x + KEY_1ST_POS_X,   command_pos[2].y + KEY_1ST_POS_Y);
	key_pos[1] = VectorGet(KEY_1ST_COMMAND_X + KEY_1ST_POS_X, KEY_1ST_COMMAND_Y + KEY_1ST_POS_Y);
	key_pos[2] = VectorGet(KEY_2ND_COMMAND_X + KEY_2ND_POS_X, KEY_2ND_COMMAND_Y + KEY_2ND_POS_Y);
	key_pos[3] = VectorGet(KEY_3RD_COMMAND_X + KEY_3RD_POS_X, KEY_3RD_COMMAND_Y + KEY_3RD_POS_Y);
	for (int i = 0; i < 4; i++)
	{
		key_count[i] = 0;
		key_move_pos[i] = 0.0f;
		now_frame[i] = 0;
	}
	anim_count = 0;
	first_count = 0;
    turn_count = 1;
	command_play_count = 0;
	reset_command_pos_flag = false;
	Flag_Reset();
	camera->Flag_Reset(*player);
}

//************************************************************************
// コマンドうち込み
// (プレイヤー、エネミー、カメラ)
//************************************************************************
void Battle::Commanding(Player *player, Enemy *enemy, Camera *camera, Map *map, Music music)
{
	enemy->Battle_AI(this);
	camera->Battle_Move(*player, *enemy, *this, map);
	//printfDx("%.1f\n",m_ally[0].b_pos.z);
	//コマンド終了してないとき
	if (!m_ally[2].turn_flag && first_count >= 100)
	{
		if (!m_ally[0].turn_flag)
		{
			Command(0, music);
		}
		else if (!m_ally[1].turn_flag)
		{
			Command(1, music);
		}
		else if (!m_ally[2].turn_flag)
		{
			Command(2, music);
		}
	}
}

//************************************************************************
// うったコマンドをもとに動かす
//************************************************************************
void Battle::Playing(Player *player, Enemy *enemy, Camera *camera)
{
	//コマンドうち終わったとき
	Command_Play_Move();
	if (m_ally[2].turn_flag)
	{
		Command_Smooth(&command_pos[0], VectorGet(FIRST_COMMAND_X, FIRST_COMMAND_Y), KEY_SPEED);
		if (m_ally[0].command_play_flag  &&
			m_ally[1].command_play_flag  &&
			m_ally[2].command_play_flag  &&
			m_enemy[0].command_play_flag &&
			m_enemy[1].command_play_flag &&
			m_enemy[2].command_play_flag &&
			m_enemy[3].command_play_flag)
		{
			Flag_Reset();
			camera->Flag_Reset(*player);
            turn_count++;
		}
	}
}
//************************************************************************
// 動きのプログラムのまとめ
//************************************************************************
void Battle::Updata(int *scene, Player *player, Enemy *enemy, Camera *camera, Map *map, Music *music)
{
	//敵がボスじゃなかったら
	if (m_enemy[0].name != BOSS_NAME)
	{
		//通常戦闘BGMをながす
		music->enemy_battle(0);
	}
	//敵がボスだったら
	else
	{
		//ボス戦BGMをながす
		music->boss_battle(0);
	}
	//戦闘が終わっていなかったら中の処理をする
	if (!end_flag)
	{
		//ランダム用カウント
		rand_count++;
		//コマンド打ち込み処理
		Commanding(player, enemy, camera, map, *music);
		//コマンド打った後の動き
		Playing(player, enemy, camera);
	}
	//戦闘が終わったら
	else
	{
		//メッセージコマンド枠を画面下側に移動
		Command_Smooth(&command_pos[0], VectorGet(FIRST_COMMAND_X, FIRST_COMMAND_Y), KEY_SPEED);
		//敵がボスじゃないとき
		if (m_enemy[0].name != BOSS_NAME)
		{
			//通常戦闘のBGMを止める
			music->enemy_battle_Stop();
		}
		//敵がボスのとき
		else
		{
			//ボス戦のBGMを止める
			music->boss_battle_Stop();
		}
		//決定キーを押したら
		if (getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN)
		{
			//キャラのステータス継承
			for (int i = 0; i < 3; i++)
			{
				player->c_ally[i] = m_ally[i];
			}
			//シーンをフィールドに戻す
			*scene = s_field;
		}
	}
}

//************************************************************************
// 描画
// (プレイヤー、エネミー、マップ、カメラ、フォントを描画させる用)
//************************************************************************
void Battle::Draw(int *scene, Player *player, Enemy *enemy, Map *map, Camera *camera, Comment_string *comment, Effect *effect, Music *music, Window *window, Memory *memory)
{
	//UI以外の描画処理（UIはこれの下に書く）
	map->Battle_Draw();
	player->BattleDraw(*this);
	enemy->Battle_Draw(*this, effect);

	if(!end_flag)
	{
		//アニメーション用カウント
		anim_count++;
		//ーーーーーー
		// UI
		//ーーーーーー
		//最初の～が現れたってやつ
		DrawGraph((int)command_pos[0].x, (int)command_pos[0].y, first_frame_graph, TRUE);
		if (first_count < 100 && camera->sight_point_flag[1] == true)
		{
		    Command_Smooth(&command_pos[0], VectorGet(FIRST_COMMAND_X, FIRST_COMMAND_Y), KEY_SPEED);
		    comment->Draw((float)(command_pos[0].x + 300), (float)(command_pos[0].y + 30), m_enemy[0].name_origin);
			std::size_t name_num = m_enemy[0].name_origin.size() / 2;
		    comment->Draw((float)(command_pos[0].x + 300 + (name_num * STRING_SIZE_W)), (float)(command_pos[0].y + 30), "たちがあらわれた！");
			first_count++;
		}
		//コマンド選択中に表示
		if (!m_ally[2].turn_flag && first_count >= 100)
		{
		    //コマンド枠をずらす
		    Command_Smooth(&command_pos[0], VectorGet(FIRST_COMMAND_X, FIRST_COMMAND_Y + 200), KEY_SPEED);
		    Command_Smooth(&command_pos[1], VectorGet(10.0f, 10.0f), KEY_SPEED);
		    //キャラのステータス
			window->Command_Draw(command_pos[1].x, command_pos[1].y, STATUS_COMMAND_SIZE_X, STATUS_COMMAND_SIZE_Y);
			//DrawGraph((int)command_pos[1].x, (int)command_pos[1].y, status_command_graph, TRUE);
			float rate = 0.8f;
			for (int i = 0; i < 3; i++)
			{
				Vector2 pos = VectorGet((float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70));
				Set_HPber(pos.x, pos.y + 70, m_ally[i].mp / m_ally[i].max_mp, GetColor(55, 55, 255));
		        if (m_ally[i].hp >= m_ally[i].max_hp * 0.3)
		        {
		            comment->Draw((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 10),  m_ally[i].name);
					comment->Draw((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 70),  "ＨＰ");
					comment->Draw((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 140), "ＭＰ");
					Set_HPber((float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70), m_ally[i].hp / m_ally[i].max_hp, GetColor(55, 255, 55));
		            Count_Draw_2D(count_graph, (int)m_ally[i].hp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70),  rate);
		            Count_Draw_2D(count_graph, (int)m_ally[i].mp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 140), rate);
		        }
		        else if (m_ally[i].hp < m_ally[i].max_hp * 0.3)
		        {
		            comment->Draw_Orange((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 10),  m_ally[i].name);
					comment->Draw_Orange((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 70),  "ＨＰ");
					comment->Draw_Orange((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 140), "ＭＰ");
					Set_HPber((float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70), m_ally[i].hp / m_ally[i].max_hp, GetColor(155, 155, 55));
					Count_Draw_2D(count_graph_orange, (int)m_ally[i].hp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70),  rate);
		            Count_Draw_2D(count_graph_orange, (int)m_ally[i].mp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 140), rate);
		        }
		        else if (m_ally[i].hp <= 0)
		        {
		            comment->Draw_Red((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 10),  m_ally[i].name);
					comment->Draw_Red((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 70),  "ＨＰ");
					comment->Draw_Red((float)(command_pos[1].x + 10 + (i * 290)), (float)(command_pos[1].y + 140), "ＭＰ");
					Set_HPber((float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70), m_ally[i].hp / m_ally[i].max_hp, GetColor(255, 55, 55));
		            Count_Draw_2D(count_graph_red, (int)m_ally[i].hp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 70),  rate);
		            Count_Draw_2D(count_graph_red, (int)m_ally[i].mp,     (float)(command_pos[1].x + 120 + (i * 290)), (float)(command_pos[1].y + 140), rate);
		        }
			}
		    //キャラのコマンド
			if (!m_ally[0].turn_flag)//１Ｐ
			{
				Command_Choice_Draw(0, comment, window, memory);
			}
			else if (!m_ally[1].turn_flag)//２Ｐ
			{
				Command_Choice_Draw(1, comment, window, memory);
			}
			else if (!m_ally[2].turn_flag)//３Ｐ
			{
				Command_Choice_Draw(2, comment, window, memory);
			}
		}
		if (m_ally[2].turn_flag)
		{
			Command_Play_Draw(comment, &m_ally[0], &m_ally[1], &m_ally[2], &m_enemy[0], &m_enemy[1], &m_enemy[2], &m_enemy[3], 150);
		}
		//printfDx("%.1f %.1f\n", key_pos[2].x, key_pos[2].y);
		//printfDx("%d %d %d %d %d %d %d\n", camera_flag[0], camera_flag[1], camera_flag[2], camera_flag[3], camera_flag[4], camera_flag[5], camera_flag[6]);
	}
	else
	{
		comment->Draw((float)(command_pos[0].x + 300), (float)(command_pos[0].y + 30), m_enemy[0].name);
		std::size_t name_num = m_enemy[0].name.size() / 2;
		comment->Draw((float)(command_pos[0].x + 300 + (name_num * STRING_SIZE_W)), (float)(command_pos[0].y + 30), "たちをやっつけた！");
	}
}
