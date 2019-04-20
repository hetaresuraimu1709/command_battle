#ifndef _HEADER_H_
#define _HEADER_H_

#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <math.h>
#include <iostream>
#include <map>
#include "Define.h"
#include "Music.h"
#include "Player.h"
#include "Effect.h"
#include "Camera.h"
#include "Map.h"
#include "Inputkey.h"
#include "Enemy.h"
#include "Comment_string.h"
#include "Battle.h"
#include "Title.h"
#include "Memory.h"
#include "Npc.h"
#include "Window.h"
#include "Field.h"

void Turn_Around(float &now_dir, float max_dir, float speed_dir, bool &turn_flag);
Chara Status_Get(std::string chara_name, char *file_name, Vector3 f_pos, Vector3 b_pos, float hp, float mp, float pow, float def, float m_pow, float m_res, float ski, float spd, bool ally_or_enemy_flag);
Inventory Inventory_Have_Get(Inventory Inve[6], Inventory one, Inventory two, Inventory three, Inventory four, Inventory five, Inventory six);
Inventory Inventory_Get(int number, bool use_flag, int damage_bonus, int force, std::string name);
bool Enemy_notice(Vector3 pos1, Vector3 pos2);
void rotate(float *x, float *y, const float ang, const float mx, const float my);
void Command_Smooth(Vector2 *origin_vector, Vector2 goal_vector, float cut);
void Chara_Smooth(Vector3 *origin_vector, Vector3 goal_vector, float cut);
void Chara_turn_Smooth(Vector3 *origin_vector, Vector3 goal_vector, float cut);
Vector3 Map_On_Pos(Vector2 map_chip_size, Vector2 set_pos);
VECTOR Vector3_VECTOR_In(Vector3 vector);
Vector3 VECTOR_Vector3_In(VECTOR vector);
Vector3 VectorGet(float x, float y ,float z);
Vector2 VectorGet(float x, float y);
Vector3 Add_Vector_Vector(Vector3 &v1, Vector3 v2);
Vector2 Add_Vector_Vector(Vector2 &v1, Vector2 v2);
Vector3 Sub_Vector_Vector(Vector3 &v1, Vector3 v2);
Vector2 Sub_Vector_Vector(Vector2 &v1, Vector2 v2);
Vector3 Square_Vector(Vector3 &v);
Vector2 Square_Vector(Vector2 &v);
Vector3 Mul_Vector_Scaler(Vector3 &v, float s);
Vector2 Mul_Vector_Scaler(Vector2 &v, float s);
float Vector_Length(Vector3 v);
float Vector_Length(Vector2 v);
Vector3 Vector_Normalize(Vector3 v);
Vector2 Vector_Normalize(Vector2 v);
float Vector_Dot(Vector3 v1, Vector3 v2);
Vector3 Vector_Cross(Vector3 v1, Vector3 v2);
Vector3 Vector_Cross(Vector3 p1, Vector3 p2, Vector3 p3);

void Debug_Vector3_Pos(Vector3 *pos, Vector3 *center_point,float pos_speed, float cen_speed);//デバッグ用
#endif // _HEADER_H_