//camera.cpp

//ヘッダー呼び出し
#include"Header.h"

Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(10.0000f, 1000.000f);
	f_pos = VectorGet(50.0f * BATTLE_MAP_CHIP / 2, 15.f, 50.0f * BATTLE_MAP_CHIP / 2 - 30.f);
	up = VectorGet(0.f, 1.f, 0.f);
	// カメラの回転値を初期化
	VRotate = 0.0f;
	HRotate = 0.0f;
	TRotate = 0.0f;
}

Camera::~Camera()
{

}

void Camera::Init()
{
	b_pos = VectorGet(725.0f, 20.0f, 500.0f);
	sight_point = VGet(825.0f, 20.0f, 700.0f);
	sight_point_flag[0] = false;
	sight_point_flag[1] = false;
	for (int i = 2; i < 20; i++)
	{
		sight_point_flag[i] = false;
	}
	for (int i = 0; i < 3; i++)
	{
		sight_point_flag2[i] = false;
	}
	turn_flag = false;
	reset_flag = false;
	reset_flag = false;
}

void Camera::Flag_Reset(Player &player)
{
	b_pos = VectorGet(player.c_ally[1].b_pos.x, 15.0f, player.c_ally[1].b_pos.z - 30.0f);
	for (int i = 2; i < 20; i++)
	{
		sight_point_flag[i] = false;
	}
	for (int i = 0; i < 3; i++)
	{
		sight_point_flag2[i] = false;
	}
	turn_flag = false;
}

void Camera::Sight_Point_Flag_Reset()
{
	for (int i = 7; i < 14; i++)
	{
		sight_point_flag[i] = false;
	}
	reset_flag = false;
	reset_flag = false;
}

void Move_Smooth(Vector3 *origin_vector, Vector3 goal_vector,float cut)
{
	Vector3 sub_vector = Sub_Vector_Vector(goal_vector, *origin_vector);
	*origin_vector = Add_Vector_Vector(*origin_vector, Mul_Vector_Scaler(sub_vector, cut));
}

void DX_Move_Smooth(VECTOR *origin_vector, Vector3 goal_vector, float cut)
{
	Vector3 hoge_v = VECTOR_Vector3_In(*origin_vector);
	Move_Smooth(&hoge_v, goal_vector, cut);
	*origin_vector = Vector3_VECTOR_In(hoge_v);
}


void Camera::Move(Player &player, Map *map)
{
	//前押したときにカメラが前向いてなかったら
	if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED)
	{
		//前に自動的に移動させたい
	}
	// カメラもキャラのベクトル分移動させる
    if (getKey(KEY_INPUT_W) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_S) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_A) == KEY_STATE_PRESSED ||
        getKey(KEY_INPUT_D) == KEY_STATE_PRESSED)
    {
        f_pos = Add_Vector_Vector(f_pos, player.c_ally[0].vec);//座標に加算
    }
    //printfDx("%f,%f,%f\n", player.c_ally[0].vec.x, player.c_ally[0].vec.y, player.c_ally[0].vec.z );

	// 左右キーでカメラをプレイヤー中心に横回転する
	if (getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
	{
		map->Cloud_M_Move();
		HRotate -= DX_PI_F / 90.0f;
		rotate(&f_pos.x, &f_pos.z, -DX_PI_F / 90.0f, player.c_ally[0].f_pos.x, player.c_ally[0].f_pos.z);//回転
	}
	if (getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
	{
		map->Cloud_P_Move();
		HRotate += DX_PI_F / 90.0f;
		rotate(&f_pos.x, &f_pos.z, +DX_PI_F / 90.0f, player.c_ally[0].f_pos.x, player.c_ally[0].f_pos.z);//回転
	}
	// 上下キーでカメラをプレイヤー中心に縦回転する

	//ライティング設定
	ChangeLightTypeDir(VGet(-1.0f, -1.0f, 1.0f));
	// ライトのアンビエントカラーを赤色に変更
	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 0.0f));

	MATERIALPARAM MatParam;

	MatParam.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// ディフューズカラーは白
	MatParam.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// アンビエントカラーは白( ライトのアンビエントカラーをそのまま反映する )
	MatParam.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// スペキュラカラーは無し
	MatParam.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// エミッシブカラー( 自己発光 )もなし
	MatParam.Power = 1.0f;									// スペキュラはないので０

	// マテリアルのパラメータをセット
	SetMaterialParam(MatParam);
	//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(f_pos.x, f_pos.y, f_pos.z), VGet(player.c_ally[0].f_pos.x, 15, player.c_ally[0].f_pos.z));
}

void Camera::Battle_Move(Player &player, Enemy &enemy, Battle &battle, Map *map)
{
	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	//SetCameraPositionAndTarget_UpVecY(VectorGet(0, 10, -20), VectorGet(0.0f, 10.0f, 0.0f));
	// 左シフトキーを押しているかどうかで処理を分岐
	// 左右キーでカメラをプレイヤー中心に横回転する
	//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	
	//カメラの動き
    if (getKey(KEY_INPUT_0) != KEY_STATE_PRESSED)
    {
		//初期位置
        if (!sight_point_flag[0])
        {
            sight_point_flag[0] = true;
            b_pos = VectorGet(725.0f, 20.0f, 500.0f);
            sight_point = VGet(825.0f, 20.0f, 700.0f);
        }
		//味方にカメラを向ける
        if (sight_point_flag[0] && !sight_point_flag[1])
        {
            Move_Smooth(&b_pos, VectorGet(670.0f, 15.0f, 580.0f), 0.1f);
            DX_Move_Smooth(&sight_point, VectorGet(540.0f, 20.0f, 810.0f), 0.1f);
            if (b_pos.y < 15.1f)
            {
                sight_point_flag[1] = true;
                b_pos = VectorGet(player.c_ally[1].b_pos.x, 30.0f, player.c_ally[1].b_pos.z - 30.0f);
                sight_point = VGet(player.c_ally[1].b_pos.x, 60.0f, player.c_ally[1].b_pos.z - 60.0f);
            }
        }
		//敵を見る
        if (sight_point_flag[1] && !sight_point_flag[2])
        {
            Move_Smooth(&b_pos, VectorGet(player.c_ally[1].b_pos.x, 15.0f, player.c_ally[1].b_pos.z - 30.0f), 0.1f);
            DX_Move_Smooth(&sight_point, VectorGet(player.c_ally[1].b_pos.x, 15.0f, player.c_ally[1].b_pos.z - 60.f), 0.1f);
            if (b_pos.y < 15.1f)
            {
                sight_point_flag[2] = true;
            }
        }
		//敵を見る(コマンド選択中)
        if (!sight_point_flag[3] && sight_point_flag[2] && battle.first_count >= 100)
        {
			sight_point = VGet(50.0f * BATTLE_MAP_CHIP / 2, 15.0f, 50.0f * BATTLE_MAP_CHIP / 2 - 60.f);
			if (b_pos.x < 615.0f)
			{
				turn_flag = true;
			}
			if (b_pos.x > 635.0f)
			{
				turn_flag = false;
			}
			if (turn_flag)
			{
				Move_Smooth(&b_pos, VectorGet(player.c_ally[1].b_pos.x + 15.0f, 15.f, player.c_ally[1].b_pos.z - 30.f), 0.01f);
			}
			else
			{
				Move_Smooth(&b_pos, VectorGet(player.c_ally[1].b_pos.x - 15.0f, 15.f, player.c_ally[1].b_pos.z - 30.f), 0.01f);
			}
			if (battle.m_ally[2].turn_flag)
			{
				sight_point_flag[3] = true;
			}
        }
		//playerを見る
		/*for (int i = 0; i < 3; i++)
		{
			if (sight_point_flag[i + 3] && !battle.m_ally[i].turn_flag && !sight_point_flag2[i])
			{
				DX_Move_Smooth(&sight_point, VectorGet(battle.m_ally[i].b_pos.x, 15.0f, battle.m_ally[i].b_pos.z), 0.1f);
				Move_Smooth(&b_pos, VectorGet(battle.m_ally[i].b_pos.x + ((i - 1)*15.0f), 30.f, battle.m_ally[i].b_pos.z + 30.f), 0.1f);
				if ((battle.m_ally[i].second_command_flag || battle.m_ally[i].magic_command_flag) && !sight_point_flag[i + 4])
				{
					sight_point_flag2[i] = true;
				}
			}
			if (sight_point_flag2[i])
			{
				Move_Smooth(&b_pos, VectorGet(player.c_ally[1].b_pos.x - 1.0f, 15.0f, player.c_ally[1].b_pos.z - 30.0f), 0.1f);
				DX_Move_Smooth(&sight_point, VectorGet(player.c_ally[1].b_pos.x, 15.0f, player.c_ally[1].b_pos.z - 60.f), 0.1f);
				if (battle.m_ally[i].turn_flag)
				{
					sight_point_flag2[i] = false;
					sight_point_flag[i + 4] = true;
				}
			}
			if (!battle.m_ally[2].turn_flag)
			{
				if (getKey(KEY_INPUT_BACK) == KEY_STATE_PUSHDOWN)
				{
					if (battle.m_ally[i].turn_flag)
					{
						sight_point_flag2[i] = true;
						sight_point_flag[i + 4] = false;
					}
					else if (!battle.m_ally[i].turn_flag && sight_point_flag2[i])
					{
						sight_point_flag2[i] = false;
					}
				}
			}
		}*/
		//コマンド打ち終わった時のカメラ操作
		if (battle.m_ally[2].turn_flag)
		{
			//最初だけ初期化
			if (battle.command_play_count == 1)
			{
				//フラグを初期化する
				for (int i = 0; i < 7; i++)
				{
					if (battle.camera_flag[i] &&
						(i < 3 ? !battle.m_ally[i].command_play_flag : !battle.m_enemy[i - 3].command_play_flag))
					{
						Sight_Point_Flag_Reset();
						sight_point_flag[i + 7] = true;
					}
				}
			}
			//味方（プレイヤー）
			for (int i = 0; i < 3; i++)
			{
				if (sight_point_flag[i + 7])
				{
					//動かない行動（魔法、道具以外）をしたとき
					if( battle.m_ally[i].first_behavior_flag[battle.see]	||
						battle.m_ally[i].second_behavior_flag[battle.guard] ||
						battle.m_ally[i].second_behavior_flag[battle.sink])
					{
						//初期場所設定
						if (!reset_flag)
						{
							//味方を正面からみつつ
							b_pos = VectorGet(battle.m_ally[i].b_pos.x, 20.0f, battle.m_ally[i].b_pos.z - 35.f);
							float camera_sight_x = battle.m_ally[i].b_pos.x;
							float camera_sight_z = battle.m_ally[i].b_pos.z;
							sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
							reset_flag = true;
						}
						//ゆっくり回転
						rotate(&b_pos.x, &b_pos.z, +DX_PI_F / 800.0f, battle.m_ally[i].b_pos.x, battle.m_ally[i].b_pos.z);
					}
					//魔法、道具を使った時
					else if (battle.m_ally[i].second_behavior_flag[battle.magic]||
							 battle.m_ally[i].second_behavior_flag[battle.item])
					{
						//初期場所設定
						if (!reset_flag)
						{
							//味方を正面からみつつ
							b_pos = VectorGet(battle.m_ally[i].b_pos.x, 15.0f, battle.m_ally[i].b_pos.z - 50.f);
							float camera_sight_x = battle.m_ally[i].b_pos.x;
							float camera_sight_z = battle.m_ally[i].b_pos.z;
							sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
							reset_flag = true;
						}
						if (battle.command_play_count < 50)
						{
							b_pos.z += 0.05f;
						}
						else
						{
							if (!ones_flag)
							{
								//味方を正面からみつつ
								b_pos = VectorGet(battle.m_ally[i].b_pos.x, 15.0f, battle.m_ally[i].b_pos.z + 10.f);
								for (int j = 0; j < 4; j++)
								{
									if (battle.m_ally[i].who_command_flag[j])
									{
										float camera_sight_x = battle.m_enemy[j].b_pos.x;
										float camera_sight_z = battle.m_enemy[j].b_pos.z;
										sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
									}
								}
								ones_flag = true;
							}

							b_pos.z += 0.05f;
						}
					}
					//その他
					else
					{
						for (int j = 0; j < 4; j++)
						{
							if (battle.m_ally[i].who_command_flag[j])
							{
								if (!battle.m_ally[i].chara_move_flag2)
								{
									b_pos = VectorGet(battle.m_ally[i].b_pos.x, 20.0f, battle.m_ally[i].b_pos.z + 35.f);
									float camera_sight_x = battle.m_enemy[j].b_pos.x;
									float camera_sight_z = battle.m_enemy[j].b_pos.z;
									sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
								}
								else
								{
									rotate(&b_pos.x, &b_pos.z, +DX_PI_F / 800.0f, battle.m_enemy[j].b_pos.x, battle.m_enemy[j].b_pos.z);//回転
								}
							}
						}
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (sight_point_flag[i + 10])
				{
					if (battle.m_enemy[i].first_behavior_flag[battle.see] ||
						battle.m_enemy[i].second_behavior_flag[battle.guard] ||
						battle.m_enemy[i].second_behavior_flag[battle.sink])
					{
						if (!reset_flag)
						{
							b_pos = VectorGet(battle.m_enemy[i].b_pos.x, 20.0f, battle.m_enemy[i].b_pos.z + 35.f);
							float camera_sight_x = battle.m_enemy[i].b_pos.x;
							float camera_sight_z = battle.m_enemy[i].b_pos.z;
							sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
							reset_flag = true;
						}
						rotate(&b_pos.x, &b_pos.z, +DX_PI_F / 800.0f, battle.m_enemy[i].b_pos.x, battle.m_enemy[i].b_pos.z);//回転
					}
					else
					{
						for (int j = 0; j < 3; j++)
						{
							if (battle.m_enemy[i].who_command_flag[j])
							{
								if (!battle.m_enemy[i].chara_move_flag2)
								{
									b_pos = VectorGet(battle.m_enemy[i].b_pos.x, 20.0f, battle.m_enemy[i].b_pos.z - 35.f);
									float camera_sight_x = battle.m_ally[j].b_pos.x;
									float camera_sight_z = battle.m_ally[j].b_pos.z;
									sight_point = VGet(camera_sight_x, 15.0f, camera_sight_z);
								}
								else
								{
									rotate(&b_pos.x, &b_pos.z, +DX_PI_F / 800.0f, battle.m_ally[j].b_pos.x, battle.m_ally[j].b_pos.z);//回転
								}
							}
						}
					}
				}
			}
		}
    }

	//ライティング設定
	ChangeLightTypeDir(VGet(-1.0f, -1.0f, 1.0f));
	// ライトのアンビエントカラーを赤色に変更
	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 0.0f));

	MATERIALPARAM MatParam;

	MatParam.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// ディフューズカラーは白
	MatParam.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// アンビエントカラーは白( ライトのアンビエントカラーをそのまま反映する )
	MatParam.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// スペキュラカラーは無し
	MatParam.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// エミッシブカラー( 自己発光 )もなし
	MatParam.Power = 1.0f;									// スペキュラはないので０

	// マテリアルのパラメータをセット
	SetMaterialParam(MatParam);
	//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(b_pos.x, b_pos.y, b_pos.z), sight_point);

	//デバッグ
    if (getKey(KEY_INPUT_0) == KEY_STATE_PRESSED)
    {
        if (getKey(KEY_INPUT_1) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_ally[0].b_pos.x, 15, battle.m_ally[0].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_ally[0].b_pos.x, 15.f, battle.m_ally[0].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_2) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_ally[1].b_pos.x, 15, battle.m_ally[1].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_ally[1].b_pos.x, 15.f, battle.m_ally[1].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_3) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_ally[2].b_pos.x, 15, battle.m_ally[2].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_ally[2].b_pos.x, 15.f, battle.m_ally[2].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_4) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_enemy[0].b_pos.x, 15, battle.m_enemy[0].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_enemy[0].b_pos.x, 15.f, battle.m_enemy[0].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_5) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_enemy[1].b_pos.x, 15, battle.m_enemy[1].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_enemy[1].b_pos.x, 15.f, battle.m_enemy[1].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_6) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_enemy[2].b_pos.x, 15, battle.m_enemy[2].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_enemy[2].b_pos.x, 15.f, battle.m_enemy[2].b_pos.z - 30.f), 0.3f);
        }
        if (getKey(KEY_INPUT_7) == KEY_STATE_PRESSED)
        {
            DX_Move_Smooth(&sight_point, VectorGet(battle.m_enemy[3].b_pos.x, 15, battle.m_enemy[3].b_pos.z), 0.3f);
            Move_Smooth(&b_pos, VectorGet(battle.m_enemy[3].b_pos.x, 15.f, battle.m_enemy[3].b_pos.z - 30.f), 0.3f);
        }
    }
	//Vector3 hoge_v = VECTOR_Vector3_In(sight_point);
	//Debug_Vector3_Pos(&battle.m_enemy[0].b_pos, &hoge_v, 1.0f,10.0f);
	//sight_point = Vector3_VECTOR_In(hoge_v);
}