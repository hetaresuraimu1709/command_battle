//Camera.h
//カメラのヘッダー
#ifndef _CAMERA_H_
#define _CAMERA_H_

class Player;

class Camera
{
public:

	Vector3 f_pos,b_pos,up;//座標
	VECTOR sight_point;
	float VRotate, HRotate, TRotate;
	bool turn_flag;
    bool sight_point_flag[20];
	bool sight_point_flag2[3];
	bool ones_flag;
	bool reset_flag;
	Camera();//コンストラクタ
	~Camera();//デストラクタ
	void Init();
	void Flag_Reset(Player &player);
	void Sight_Point_Flag_Reset();
	void Move(Player &player, Map *map);//動き
	void Battle_Move(Player &player, Enemy &enemy, Battle &battle, Map *map);
};
#endif // _camera_H_