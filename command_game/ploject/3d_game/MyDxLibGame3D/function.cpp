#include"Header.h"

//向き変え
void Turn_Around(float &now_dir, float aim_dir, float speed_dir, bool &turn_flag)
{
	//正面から左に向くとき
	if (now_dir == PLAYER_REAR && (aim_dir == PLAYER_LEFT || aim_dir == PLAYER_LEFT - 45.f || aim_dir == PLAYER_LEFT + 45.f))
	{
		now_dir = 0;
	}
	//例外1
	if (aim_dir == PLAYER_REAR && (now_dir <= PLAYER_LEFT || now_dir <= PLAYER_LEFT - 45.f || now_dir <= PLAYER_LEFT + 45.f))
	{
		now_dir -= speed_dir;
		if (now_dir <= 0.f)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//例外2
	else if (aim_dir == PLAYER_RIGHT && now_dir <= 45.f)
	{
		now_dir -= speed_dir;
		if (now_dir <= -90.f)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//例外3
	else if (aim_dir == PLAYER_RIGHT + 45.f && (now_dir <= 45.f || now_dir <= PLAYER_LEFT))
	{
		now_dir -= speed_dir;
		if (now_dir <= -45.f)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//例外4
	else if (aim_dir == 45.f && (now_dir >= PLAYER_RIGHT + 45.f || now_dir >= PLAYER_RIGHT))
	{
		now_dir += speed_dir;
		if (now_dir >= PLAYER_REAR + 45.f)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//例外5
	else if (aim_dir == PLAYER_LEFT && (now_dir >= PLAYER_RIGHT + 45.f || now_dir >= PLAYER_RIGHT))
	{
		now_dir += speed_dir;
		if (now_dir >= PLAYER_REAR + PLAYER_LEFT)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//上から見て反時計回り
	else if (now_dir > aim_dir)
	{
		now_dir -= speed_dir;
		if (now_dir <= aim_dir)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
	//上から見て時計回り
	else if (now_dir < aim_dir)
	{
		now_dir += speed_dir;
		if (now_dir >= aim_dir)
		{
			now_dir = aim_dir;
			turn_flag = false;
		}
	}
}

//ステータス代入
Chara Status_Get(std::string chara_name, char *file_name, Vector3 f_pos, Vector3 b_pos,float hp, float mp, float pow, float def, float m_pow, float m_res, float ski, float spd, bool ally_or_enemy_flag)
{
	Chara name;
	name.modelHandle		= MV1LoadModel(file_name);
    name.name				= chara_name;
	name.name_origin		= chara_name;
    name.level              = 1;
	name.f_pos				= f_pos;
	name.b_pos				= b_pos;
	name.first_pos			= b_pos;
	name.max_hp				= hp;
	name.hp					= hp;
	name.max_mp				= mp;
	name.mp					= mp;
	name.pow				= pow;
	name.def				= def;
	name.m_pow				= m_pow;
	name.m_res				= m_res;
	name.ski				= ski;
	name.spd				= spd;
	name.ally_or_enemy_flag = ally_or_enemy_flag;
	//name.ally_or_enemy_flag = false;
	name.first_command_flag = false;
	for (int i = 0; i < KEY_1ST_MAX_COMMAND; i++)
	{
		name.first_behavior_flag[i] = false;
	}
	name.second_command_flag = false;
	for (int i = 0; i < KEY_2ND_MAX_COMMAND_Y * KEY_2ND_MAX_COMMAND_X; i++)
	{
		name.second_behavior_flag[i] = false;
	}
	name.magic_command_flag = false;
	for (int i = 0; i < KEY_3RD_MAX_COMMAND_Y; i++)
	{
		name.who_command_flag[i] = false;
	}
	name.turn_flag			= false;
	name.command_play_flag	= false;
	name.attack_flag		= false;
	name.set_flag			= false;
	name.chara_move_flag	= false;
	name.chara_move_flag2	= false;
	name.chara_move_flag3	= false;

	name.puls_pow			= 0;
	name.puls_def			= 0;
	name.puls_spd			= 0;

	name.damage_ones_flag	= false;

	return name;
}

//持ってるInventoryの中身を代入
Inventory Inventory_Have_Get(Inventory Inve[6], Inventory one, Inventory two, Inventory three, Inventory four, Inventory five, Inventory six)
{
	Inve[0] = one;
	Inve[1] = two;
	Inve[2] = three;
	Inve[3] = four;
	Inve[4] = five;
	Inve[5] = six;
	return *Inve;
}

//Inventoryの中身を代入
Inventory Inventory_Get(int number,bool use_flag,int damage_bonus,int force, std::string name)
{
	Inventory Inv;
	Inv.number = number;
	Inv.use_flag = use_flag;
	Inv.damage_bonus = damage_bonus;
	Inv.force = force;
	Inv.name = name;
	return Inv;
}

//エネミーの一定距離に入った時
bool Enemy_notice(Vector3 pos1, Vector3 pos2)
{
	bool flag = false;
	float f_between = 0;
	Vector3 v_between;
	v_between = Sub_Vector_Vector(pos1, pos2);
	f_between = Vector_Length(v_between);
	if (f_between < 0)
	{
		f_between *= -1;
	}
	if (f_between < ENEMY_NOTICE)
	{
		flag = true;
	}
	return flag;
}

// (camera_x,camera_z)の点を(player_x,player_z)を中心にang角回転する
void rotate(float *camera_x, float *camera_z, const float ang, const float player_x, const float player_z) {
	const float ox = *camera_x - player_x, oz = *camera_z - player_z;
	*camera_x = ox * cos(ang) + oz * sin(ang);
	*camera_z = -ox * sin(ang) + oz * cos(ang);
	*camera_x += player_x;
	*camera_z += player_z;
}

void Command_Smooth(Vector2 *origin_vector, Vector2 goal_vector, float cut)
{
    Vector2 sub_vector = Sub_Vector_Vector(goal_vector, *origin_vector);
    *origin_vector = Add_Vector_Vector(*origin_vector, Mul_Vector_Scaler(sub_vector, cut));
}

void Chara_Smooth(Vector3 *origin_vector, Vector3 goal_vector, float cut)
{
	Vector3 sub_vector = Vector_Normalize(Sub_Vector_Vector(goal_vector, *origin_vector));
	*origin_vector = Add_Vector_Vector(*origin_vector, Mul_Vector_Scaler(sub_vector, cut));
}

void Chara_turn_Smooth(Vector3 *origin_vector, Vector3 goal_vector, float cut)
{
	Vector3 sub_vector = Vector_Normalize(Sub_Vector_Vector(goal_vector, *origin_vector));
	*origin_vector = Sub_Vector_Vector(*origin_vector, Mul_Vector_Scaler(sub_vector, cut));
}

//マップのマス目でポジション決め（マスの中心にセット）
Vector3 Map_On_Pos(Vector2 map_chip_size, Vector2 set_pos)
{
	Vector3 pos;
	pos.x = map_chip_size.x / 2 + (map_chip_size.x * set_pos.x);
	pos.y = 0.0f;
	pos.z = map_chip_size.y / 2 + (map_chip_size.y * set_pos.y);
	return pos;
}

//Vector3型をVECTOR型に変換
VECTOR Vector3_VECTOR_In(Vector3 vector)
{
	VECTOR v;
	v.x = vector.x;
	v.y = vector.y;
	v.z = vector.z;
	return v;
}

//VECTOR型をVector3型に変換
Vector3 VECTOR_Vector3_In(VECTOR vector)
{
	Vector3 v;
	v.x = vector.x;
	v.y = vector.y;
	v.z = vector.z;
	return v;
}

//Vecto3型、Vecto2型を取得
Vector3 VectorGet(float x, float y, float z)
{
	Vector3 r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;
}
Vector2 VectorGet(float x, float y)
{
    Vector2 r;
    r.x = x;
    r.y = y;
    return r;
}

//（ベクトル）＋（ベクトル）
Vector3 Add_Vector_Vector(Vector3 &v1, Vector3 v2)
{
	Vector3 r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	return r;
}
Vector2 Add_Vector_Vector(Vector2 &v1, Vector2 v2)
{
    Vector2 r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

//（ベクトル）ー（ベクトル）
Vector3 Sub_Vector_Vector(Vector3 &v1, Vector3 v2)
{
	Vector3 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	return r;
}
Vector2 Sub_Vector_Vector(Vector2 &v1, Vector2 v2)
{
    Vector2 r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

Vector3 Square_Vector(Vector3 &v)
{
	Vector3 r;
	r.x = v.x * v.x;
	r.y = v.y * v.y;
	r.z = v.z * v.z;
	return r;
}
Vector2 Square_Vector(Vector2 &v)
{
    Vector2 r;
    r.x = v.x * v.x;
    r.y = v.y * v.y;
    return r;
}

//（ベクトル）×（スカラー）
Vector3 Mul_Vector_Scaler(Vector3 &v, float s)
{
	Vector3 r;
	r.x = v.x * s;
	r.y = v.y * s;
	r.z = v.z * s;
	return r;
}
Vector2 Mul_Vector_Scaler(Vector2 &v, float s)
{
    Vector2 r;
    r.x = v.x * s;
    r.y = v.y * s;
    return r;
}

//ベクトルの長さを獲得
float Vector_Length(Vector3 v)
{
	float l = sqrtf(v.x * v.x +
					v.y * v.y +
					v.z * v.z);
	return l;
}
float Vector_Length(Vector2 v)
{
    float l = sqrtf(v.x * v.x +
        v.y * v.y);
    return l;
}

//ベクトルを正規化
Vector3 Vector_Normalize(Vector3 v)
{
	float l = Vector_Length(v);
	Vector3 n;
	n.x = v.x / l;
	n.y = 0.0f;
	n.z = v.z / l;

	return n;
}
Vector2 Vector_Normalize(Vector2 v)
{
    float l = Vector_Length(v);
    Vector2 n;
    n.x = v.x / l;
    n.y = v.y / l;

    return n;
}

//ベクトル同士の内積
float Vector_Dot(Vector3 v1, Vector3 v2)
{
	float r;
	r = ((v1.x * v2.x) +
		(v1.y * v2.y) +
		(v1.z * v2.z)) /
		(Vector_Length(v1) *
		Vector_Length(v2));
	return r;
}

//ベクトル同士の外積
Vector3 Vector_Cross(Vector3 v1, Vector3 v2)
{
	Vector3 r;
	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = v1.z * v2.x - v1.x * v2.z;
	r.z = v1.x * v2.y - v1.y * v2.x;
	return r;
}

//３点からの外積
Vector3 Vector_Cross(Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 v1 = Sub_Vector_Vector(p2, p1);
	Vector3 v2 = Sub_Vector_Vector(p3, p2);

	return Vector_Cross(v1, v2);
}

//Vector3型用変数のポジションデバッグ用関数（一応カメラ用）
//（ｚ押しながら上下左右でvectorをｘｚ移動、ｘ押しながら上下でvectorをｙ移動、上下左右でcenter_pointをｘｚ移動、ｃ押しながら上下でcenter_pointをｙ移動）
void Debug_Vector3_Pos(Vector3 *vector, Vector3 *center_point, float pos_speed, float cen_speed)
{
	//デバッグ用
	if (getKey(KEY_INPUT_Z) == KEY_STATE_PRESSED && getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		vector->z += pos_speed;
	}
	if (getKey(KEY_INPUT_Z) == KEY_STATE_PRESSED && getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		vector->z -= pos_speed;
	}
	if (getKey(KEY_INPUT_Z) == KEY_STATE_PRESSED && getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
	{
		vector->x -= pos_speed;
	}
	if (getKey(KEY_INPUT_Z) == KEY_STATE_PRESSED && getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
	{
		vector->x += pos_speed;
	}
	if (getKey(KEY_INPUT_X) == KEY_STATE_PRESSED && getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		vector->y += pos_speed;
	}
	if (getKey(KEY_INPUT_X) == KEY_STATE_PRESSED && getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		vector->y -= pos_speed;
	}
	if (getKey(KEY_INPUT_C) != KEY_STATE_PRESSED && getKey(KEY_INPUT_Z) != KEY_STATE_PRESSED && getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		center_point->z += cen_speed;
	}
	if (getKey(KEY_INPUT_C) != KEY_STATE_PRESSED && getKey(KEY_INPUT_Z) != KEY_STATE_PRESSED && getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		center_point->z -= cen_speed;
	}
	if (getKey(KEY_INPUT_Z) != KEY_STATE_PRESSED && getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
	{
		center_point->x -= cen_speed;
	}
	if (getKey(KEY_INPUT_Z) != KEY_STATE_PRESSED && getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
	{
		center_point->x += cen_speed;
	}
	if (getKey(KEY_INPUT_C) == KEY_STATE_PRESSED && getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
	{
		center_point->y += cen_speed;
	}
	if (getKey(KEY_INPUT_C) == KEY_STATE_PRESSED && getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
	{
		center_point->y -= cen_speed;
	}
	printfDx("Pos　%f : %f : %f\nCen　%f : %f : %f\n", vector->x, vector->y, vector->z, center_point->x, center_point->y, center_point->z);
}