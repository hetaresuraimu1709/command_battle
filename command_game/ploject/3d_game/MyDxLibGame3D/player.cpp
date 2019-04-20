//player.cpp

//ヘッダー呼び出し
#include "Header.h"

//コンストラクタ
Player::Player(Memory memory)
{
    //ALLY_1_NAME
    {
        //キャラ名,アドレス先
        c_ally[0] = Status_Get(ALLY_1_NAME, "data/model/miffy/miffy_tool.pmx",
            //初期座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //初期バトル座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2 - 50, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //HP,MP,攻撃,防御,攻撃魔力,回復魔力,きようさ,すばやさ
            ALLY_1_FIRST_HP, ALLY_1_FIRST_MP, ALLY_1_FIRST_STR, ALLY_1_FIRST_DEF, ALLY_1_FIRST_MST, ALLY_1_FIRST_MHL, ALLY_1_FIRST_SKI, ALLY_1_FIRST_SPD, true);
        Inventory_Have_Get(c_ally[0].skill, memory.I_skill[memory.skill1], memory.I_skill[memory.skill2], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
        Inventory_Have_Get(c_ally[0].magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
        Inventory_Have_Get(c_ally[0].item, memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi]);
    }
    //ALLY_2_NAME
    {
        //キャラ名,アドレス先
        c_ally[1] = Status_Get(ALLY_2_NAME, "data/model/miffy/miffy_rood.pmx",
            //初期座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //初期バトル座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //HP,MP,攻撃,防御,攻撃魔力,回復魔力,きようさ,すばやさ
            ALLY_2_FIRST_HP, ALLY_2_FIRST_MP, ALLY_2_FIRST_STR, ALLY_2_FIRST_DEF, ALLY_2_FIRST_MST, ALLY_2_FIRST_MHL, ALLY_2_FIRST_SKI, ALLY_2_FIRST_SPD, true);
        Inventory_Have_Get(c_ally[1].skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
        Inventory_Have_Get(c_ally[1].magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
        Inventory_Have_Get(c_ally[1].item, memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi]);
    }
    //ALLY_3_NAME
    {
        //キャラ名,アドレス先
        c_ally[2] = Status_Get(ALLY_3_NAME, "data/model/miffy/miffy_sord.pmx",
            //初期座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //初期バトル座標
            VectorGet(50.0f * BATTLE_MAP_CHIP / 2 + 50, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2),
            //HP,MP,攻撃,防御,攻撃魔力,回復魔力,きようさ,すばやさ
            ALLY_3_FIRST_HP, ALLY_3_FIRST_MP, ALLY_3_FIRST_STR, ALLY_3_FIRST_DEF, ALLY_3_FIRST_MST, ALLY_3_FIRST_MHL, ALLY_3_FIRST_SKI, ALLY_3_FIRST_SPD, true);
        Inventory_Have_Get(c_ally[2].skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
        Inventory_Have_Get(c_ally[2].magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
        Inventory_Have_Get(c_ally[2].item, memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi], memory.I_item[memory.it_nasi]);
    }
	for (int i = 0; i < 3; i++)
	{
		// 走りアニメーションをアタッチ
		AnimAttachIndex[0] = MV1AttachAnim(c_ally[i].modelHandle, 0, -1, FALSE);
		AnimAttachIndex[1] = MV1AttachAnim(c_ally[i].modelHandle, 1, -1, FALSE);
		// 走りアニメーションの総時間を取得しておく
		AnimTotalTime[i] = MV1GetAttachAnimTotalTime(c_ally[i].modelHandle, AnimAttachIndex[i]);
		// アニメーション再生時間を初期化
		AnimNowTime = 0.f;
		MV1SetAttachAnimTime(c_ally[i].modelHandle, AnimAttachIndex[i], AnimNowTime);
	}
	hoge_chara = Status_Get("エラー！", "", VectorGet(0.0f, 0.0f, 0.0f), VectorGet(0.0f, 0.0f, 0.0f), -1, -1, -1, -1, -1, -1, -1, -1, false);
}

void Player::Init()
{
	now_anim = 0;
	dir_angle = 0;
	dir_angle_plas = 0;
	left_turn_flag = false;
	right_turn_flag = false;
	ahead_turn_flag = false;
	rear_turn_flag = false;
	ahead_left_turn_flag = false;
	ahead_right_turn_flag = false;
	rear_left_turn_flag = false;
	rear_right_turn_flag = false;
	jumpflag = false;
	keyflag = false;
	ahead_hit_flag = false;
	rear_hit_flag = false;
	left_hit_flag = false;
	right_hit_flag = false;
	warp_flag = false;
	jumppow = 0;
	vertical_dir = nodir;
	heng_dir = nodir;
	c_ally[0].vec = VectorGet(0.0f, 0.0f, 0.0f);
}

void Player::Turn_Reset()
{
	left_turn_flag = false;
	right_turn_flag = false;
	ahead_turn_flag = false;
	rear_turn_flag = false;
	ahead_left_turn_flag = false;
	ahead_right_turn_flag = false;
	rear_left_turn_flag = false;
	rear_right_turn_flag = false;
}

//動き
void Player::Move(Camera *camera,Map *map)
{
	AnimNowTime += 0.3f;
	// 上に進む処理
	if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED)
	{
		dir_angle = camera->HRotate;
		UpMove = Sub_Vector_Vector(c_ally[0].f_pos,camera->f_pos);//前へのベクトル取得
		UpMove = Vector_Normalize(UpMove);//正規化する
		UpMove = Mul_Vector_Scaler(UpMove, 1.0f);//移動速度調整
        c_ally[0].vec = Add_Vector_Vector(c_ally[0].vec, UpMove);//移動ベクトルに加算
		vertical_dir = ahead;
	}
	// 下に進む処理
	else if (getKey(KEY_INPUT_S) == KEY_STATE_PRESSED)
	{
		dir_angle = camera->HRotate;
		DownMove = Sub_Vector_Vector(c_ally[0].f_pos, camera->f_pos);//後ろベクトル取得
		DownMove = Mul_Vector_Scaler(DownMove, -1.0f);//前の逆だから反転させる
		DownMove = Vector_Normalize(DownMove);//正規化する
		DownMove = Mul_Vector_Scaler(DownMove, 1.0f);//移動速度調整
		c_ally[0].vec = Add_Vector_Vector(c_ally[0].vec, DownMove);//移動ベクトルに加算
		vertical_dir = rear;
	}
	// 右に進む処理
	if (getKey(KEY_INPUT_D) == KEY_STATE_PRESSED)
	{
		dir_angle = camera->HRotate;
		RightMove = Vector_Cross(camera->up, Sub_Vector_Vector(c_ally[0].f_pos, camera->f_pos));//右ベクトル取得
		RightMove = Vector_Normalize(RightMove);//正規化する
		RightMove = Mul_Vector_Scaler(RightMove, 1.0f);//移動速度調整
        c_ally[0].vec = Add_Vector_Vector(c_ally[0].vec, RightMove);//移動ベクトルに加算
		heng_dir = right;
	}
	// 左に進む処理
	else if (getKey(KEY_INPUT_A) == KEY_STATE_PRESSED)
	{
		dir_angle = camera->HRotate;
		LeftMove = Vector_Cross(Sub_Vector_Vector(c_ally[0].f_pos, camera->f_pos), camera->up);//左へのベクトル取得
		LeftMove = Vector_Normalize(LeftMove);//正規化
		LeftMove = Mul_Vector_Scaler(LeftMove, 1.0f);//移動速度調整
		c_ally[0].vec = Add_Vector_Vector(c_ally[0].vec, LeftMove);//移動ベクトルに加算
		heng_dir = left;
	}
    //上ボタンを離したとき
	if (getKey(KEY_INPUT_W) == KEY_STATE_PULLUP)
	{
		vertical_dir = nodir;
	}
    //下ボタンを離したとき
	else if (getKey(KEY_INPUT_S) == KEY_STATE_PULLUP)
	{
		vertical_dir = nodir;
	}
    //右ボタンを離したとき
	if (getKey(KEY_INPUT_D) == KEY_STATE_PULLUP)
	{
		heng_dir = nodir;
	}
    //左ボタンを離したとき
	if (getKey(KEY_INPUT_A) == KEY_STATE_PULLUP)
	{
		heng_dir = nodir;
	}
	if ((getKey(KEY_INPUT_SPACE) == KEY_STATE_PULLUP) && !keyflag && !jumpflag)//スペースキー
	{
		keyflag = true;
		jumpflag = true;
		jumppow = 3.0f;
	}
	else
	{
		keyflag = false;
	}

    if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_S) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_A) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_D) == KEY_STATE_PRESSED)
    {
        c_ally[0].vec = Vector_Normalize(c_ally[0].vec);//正規化
        c_ally[0].vec = Mul_Vector_Scaler(c_ally[0].vec, 1.0f);//移動速度調整
		switch (map->now_floor)
		{
		case 1:
			WallHit(*map, map->map_data_1);//壁に当たった時止めるように
			break;
		case 2:
			WallHit(*map, map->map_data_2);//壁に当たった時止めるように
			break;
		case 3:
			WallHit(*map, map->map_data_3);//壁に当たった時止めるように
			break;
		default:
			break;
		}
        c_ally[0].f_pos = Add_Vector_Vector(c_ally[0].f_pos, c_ally[0].vec);//座標に加算
    }
	
	if (jumpflag)
	{
		c_ally[0].f_pos.y += jumppow;
		jumppow -= GRAVITY;
		if (c_ally[0].f_pos.y < 0.0f)
		{
			c_ally[0].f_pos.y = 0.0f;
			jumpflag = false;
		}
	}

	if (warp_flag)
	{
		if (map->now_floor < 4)
		{
			map->now_floor++;
			camera->HRotate = 0;
			dir_angle_plas = 0;
			warp_flag = false;
			c_ally[0].f_pos = VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 0.0f, 50.0f * BATTLE_MAP_CHIP / 2);
			camera->f_pos = VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 15.f, 50.0f * BATTLE_MAP_CHIP / 2 - 30.f);
		}
	}
}

void Player::Turn()
{
	//キャラ回転のフラグを立てる
	for (int i = 0; i < ANIM_MAX; i++)
	{
		if (vertical_dir == ahead && heng_dir == nodir)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			ahead_turn_flag = true;
		}
		if (vertical_dir == rear && heng_dir == nodir)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			rear_turn_flag = true;
		}
		if (heng_dir == left && vertical_dir == nodir)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			left_turn_flag = true;
		}
		if (heng_dir == right && vertical_dir == nodir)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			right_turn_flag = true;
		}
		if (vertical_dir == ahead && heng_dir == right)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			ahead_right_turn_flag = true;
		}
		if (vertical_dir == ahead && heng_dir == left)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			ahead_left_turn_flag = true;
		}
		if (vertical_dir == rear && heng_dir == right)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			rear_right_turn_flag = true;
		}
		if (vertical_dir == rear && heng_dir == left)
		{
			Turn_Reset();
			AnimNowTime += 0.3f;
			rear_left_turn_flag = true;
		}
	}

	//キャラ回転の計算（ほかのキーが押されない限り、一回押したら押された方向に向くまで続く）
	if (ahead_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_AHEAD, vertical_dir_SPEED, ahead_turn_flag);
	}
	if (rear_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_REAR, vertical_dir_SPEED, rear_turn_flag);
	}
	if (left_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_LEFT, vertical_dir_SPEED, left_turn_flag);
	}
	if (right_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_RIGHT, vertical_dir_SPEED, right_turn_flag);
	}
	if (ahead_right_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_AHEAD + 45.f, vertical_dir_SPEED, ahead_right_turn_flag);
	}
	if (ahead_left_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_AHEAD - 45.f, vertical_dir_SPEED, ahead_left_turn_flag);
	}
	if (rear_right_turn_flag)
	{
		Turn_Around(dir_angle_plas, PLAYER_REAR - 45.f, vertical_dir_SPEED, rear_right_turn_flag);
	}
	if (rear_left_turn_flag)
	{
		Turn_Around(dir_angle_plas, 45.f, vertical_dir_SPEED, rear_left_turn_flag);
	}
	//printfDx("%f\n", dir_angle_plas);

	//プレイヤーを回転させるよう
	MV1SetRotationXYZ(c_ally[0].modelHandle, VGet(0.0f, dir_angle + (dir_angle_plas / (180.f / DX_PI_F)), 0.0f));
}

void WallHitBase(int map_number,Map map, int map_data[BATTLE_MAP_CHIP][BATTLE_MAP_CHIP], bool conditions, Vector3 pos, float *x_or_z, bool *hit_flag, int plasx1, int plasx2, int plasx3, int plasz1, int plasz2, int plasz3)
{
	if (conditions &&
		map.GetMapType( pos.x + plasx1, pos.z + plasz1, map_data, &map) == map_number &&
		(map.GetMapType(pos.x + plasx2, pos.z + plasz2, map_data, &map) == map_number ||
		map.GetMapType( pos.x + plasx3, pos.z + plasz3, map_data, &map) == map_number ))
	{
		if (map_number == 1)
		{
			*x_or_z -= *x_or_z;
		}
		*hit_flag = true;
	}
	else
	{
		*hit_flag = false;
	}
}

//壁の当たり判定
void Player::WallHit(Map map,int map_data[BATTLE_MAP_CHIP][BATTLE_MAP_CHIP])
{
	//前
	WallHitBase(1, map, map_data, c_ally[0].vec.z > 0, c_ally[0].f_pos, &c_ally[0].vec.z, &ahead_hit_flag, 25, 20, 30, 30, 30, 30);
	//後ろ
	WallHitBase(1, map, map_data, c_ally[0].vec.z < 0, c_ally[0].f_pos, &c_ally[0].vec.z, &rear_hit_flag, 25, 20, 30, 20, 20, 20);
	//左
	WallHitBase(1, map, map_data, c_ally[0].vec.x < 0, c_ally[0].f_pos, &c_ally[0].vec.x, &left_hit_flag, 20, 20, 20, 25, 20, 30);
	//右
	WallHitBase(1, map, map_data, c_ally[0].vec.x > 0, c_ally[0].f_pos, &c_ally[0].vec.x, &right_hit_flag, 30, 30, 30, 25, 20, 30);
	//前
	WallHitBase(2, map, map_data, true, c_ally[0].f_pos, &c_ally[0].vec.z, &warp_flag, 25, 20, 30, 30, 30, 30);
	//後ろ
	WallHitBase(2, map, map_data, true, c_ally[0].f_pos, &c_ally[0].vec.z, &warp_flag, 25, 20, 30, 20, 20, 20);
	//左
	WallHitBase(2, map, map_data, true, c_ally[0].f_pos, &c_ally[0].vec.x, &warp_flag, 20, 20, 20, 25, 20, 30);
	//右
	WallHitBase(2, map, map_data, true, c_ally[0].f_pos, &c_ally[0].vec.x, &warp_flag, 30, 30, 30, 25, 20, 30);
}

//敵との当たり判定
void Player::EnemyHit(int *scene, Enemy *enemy, Battle *battle, Camera *camera)
{
	if (enemy->on_flag)
	{
		for (int i = 0; i < ENEMY; i++)
		{
			//もし敵に接触したら
			if (Vector_Length(Sub_Vector_Vector(enemy->enemy[i].f_pos, c_ally[0].f_pos)) < 10)
			{
				enemy->enemy[i].f_pos = VectorGet(100.0f, 100.0f, 100.0f);
				//戦闘開始
				camera->Init();
				battle->Init(camera, this);
				battle->In(&c_ally[0], &c_ally[1], &c_ally[2], &enemy->enemy[i], &enemy->enemy[i], &enemy->enemy[i], &enemy->enemy[i]);
				*scene = s_battle;
			}
		}
	}
}

//加速しないように
void Player::VectorReset()
{
	c_ally[0].vec = VectorGet(0.0f, 0.0f, 0.0f);
}

//描画
void Player::Draw()
{
	//printfDx("%d\n", now_anim);
	// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
	if (AnimNowTime >= AnimTotalTime[now_anim])
	{
		// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
		AnimNowTime -= AnimTotalTime[now_anim];
	}
	// 新しいアニメーション再生時間をセット
	MV1SetAttachAnimTime(c_ally[0].modelHandle, AnimAttachIndex[now_anim], AnimNowTime);
	
	//棒立ちから歩きへアニメーション変換
	if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED ||
		getKey(KEY_INPUT_S) == KEY_STATE_PRESSED || 
		getKey(KEY_INPUT_A) == KEY_STATE_PRESSED || 
		getKey(KEY_INPUT_D) == KEY_STATE_PRESSED)
	{
		// ４番目のアニメーションから５番目のアニメーションに徐々に移行する
		for (Rate = 0.0f; Rate < 1.0f; Rate += 0.01f)
		{
			// 立っているアニメーションのブレンド率をセット
			MV1SetAttachAnimBlendRate(c_ally[0].modelHandle, AnimAttachIndex[1], 1.0f - Rate);

			// 手を前に出しているアニメーションのブレンド率をセット
			MV1SetAttachAnimBlendRate(c_ally[0].modelHandle, AnimAttachIndex[0], Rate);
		}
	}
	//歩きから棒立ちへアニメーション変換
	if (getKey(KEY_INPUT_W) == KEY_STATE_OFF &&
		getKey(KEY_INPUT_S) == KEY_STATE_OFF &&
		getKey(KEY_INPUT_A) == KEY_STATE_OFF &&
		getKey(KEY_INPUT_D) == KEY_STATE_OFF)
	{
		// ４番目のアニメーションから５番目のアニメーションに徐々に移行する
		for (Rate = 0.0f; Rate < 1.0f; Rate += 0.01f)
		{
			// 立っているアニメーションのブレンド率をセット
			MV1SetAttachAnimBlendRate(c_ally[0].modelHandle, AnimAttachIndex[0], 1.0f - Rate);

			// 手を前に出しているアニメーションのブレンド率をセット
			MV1SetAttachAnimBlendRate(c_ally[0].modelHandle, AnimAttachIndex[1], Rate);
		}
	}
	// ３Dモデルのポジション設定
	MV1SetPosition(c_ally[0].modelHandle, VGet(c_ally[0].f_pos.x, c_ally[0].f_pos.y, c_ally[0].f_pos.z));
	// プレイヤー描画.
	MV1DrawModel(c_ally[0].modelHandle);
}

void Player::BattleDraw(Battle battle)
{
	for (int i = 0; i < 3; i++)
	{
		// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
		if (AnimNowTime >= AnimTotalTime[now_anim])
		{
			// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
			AnimNowTime -= AnimTotalTime[now_anim];
		}
		// 新しいアニメーション再生時間をセット
		MV1SetAttachAnimTime(battle.m_ally[i].modelHandle, AnimAttachIndex[now_anim], AnimNowTime);

		//棒立ちから歩きへアニメーション変換
		if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED ||
			getKey(KEY_INPUT_S) == KEY_STATE_PRESSED ||
			getKey(KEY_INPUT_A) == KEY_STATE_PRESSED ||
			getKey(KEY_INPUT_D) == KEY_STATE_PRESSED)
		{
			for (Rate = 0.0f; Rate < 1.0f; Rate += 0.001f)
			{
				// 立っているアニメーションのブレンド率をセット
				MV1SetAttachAnimBlendRate(battle.m_ally[i].modelHandle, AnimAttachIndex[1], 1.0f - Rate);

				// 手を前に出しているアニメーションのブレンド率をセット
				MV1SetAttachAnimBlendRate(battle.m_ally[i].modelHandle, AnimAttachIndex[0], Rate);
				if (Rate == 0.99f)
				{
					now_anim = 0;
				}

			}
		}
		//歩きから棒立ちへアニメーション変換
		if (getKey(KEY_INPUT_W) == KEY_STATE_OFF &&
			getKey(KEY_INPUT_S) == KEY_STATE_OFF &&
			getKey(KEY_INPUT_A) == KEY_STATE_OFF &&
			getKey(KEY_INPUT_D) == KEY_STATE_OFF)
		{
			for (Rate = 0.0f; Rate < 1.0f; Rate += 0.001f)
			{
				// 立っているアニメーションのブレンド率をセット
				MV1SetAttachAnimBlendRate(battle.m_ally[i].modelHandle, AnimAttachIndex[0], 1.0f - Rate);

				// 手を前に出しているアニメーションのブレンド率をセット
				MV1SetAttachAnimBlendRate(battle.m_ally[i].modelHandle, AnimAttachIndex[1], Rate);
				if (Rate == 0.99f)
				{
					now_anim = 1;
				}
			}
		}

		// ３Dモデルのポジション設定
		MV1SetPosition(battle.m_ally[i].modelHandle, VGet(battle.m_ally[i].b_pos.x, battle.m_ally[i].b_pos.y, battle.m_ally[i].b_pos.z));
		// プレイヤー描画.
		MV1DrawModel(battle.m_ally[i].modelHandle);
	}
}

//デストラクタ
Player::~Player() {
	// プレイヤーを削除.
	//MV1DeleteModel(c_ally[0].modelHandle);
}