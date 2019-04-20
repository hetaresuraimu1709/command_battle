#include"Header.h"

Enemy::Enemy(Memory memory)
{
	for (int i = 0; i < ENEMY; i++)
	{
		notice_flag[i] = false;
		notice_count[i] = 0;
		move_count[i] = 0;
	}
	on_flag = false;
	//エネミーのステータス代入           名前               アドレス先								  フィールド														戦闘                HP   MP    攻撃   防御  攻魔 回魔 きようさ すばやさ
	enemy[suraimu] = Status_Get(       "スライム"		,"data/model/enemy/suraimu1/suraimu.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet(10, 15)), VectorGet(0, 0, 0), 20,    0,   10,     5,  10,   0,     50,     5, false);
	enemy[suraimubesu] = Status_Get(   "スライムベス"	,"data/model/enemy/suraimu2/suraimu.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet(11, 15)), VectorGet(0, 0, 0), 30,   10,   15,     5,  10,   0,     30,     4, false);
	enemy[metarusuraimu] = Status_Get( "メタルスライム"	,"data/model/enemy/suraimu4/suraimu.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet(12, 15)), VectorGet(0, 0, 0),  3, 2500,    3,  2500,  10,   0,     10,   700, false);
	enemy[raimusuraimu] = Status_Get(  "ライムスライム"	,"data/model/enemy/suraimu3/suraimu.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet(13, 15)), VectorGet(0, 0, 0), 15,   10,    5,    20,   0,  20,     50,     3, false);
	enemy[remonsuraimu] = Status_Get(  "レモンスライム"	,"data/model/enemy/suraimu5/suraimu.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet(14, 15)), VectorGet(0, 0, 0), 20,    0,   10,     5,  10,   0,     50,     2, false);
	Inventory_Have_Get(enemy[suraimu].		skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
	Inventory_Have_Get(enemy[suraimubesu].	skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
	Inventory_Have_Get(enemy[metarusuraimu].skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
	Inventory_Have_Get(enemy[raimusuraimu].	skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
	Inventory_Have_Get(enemy[remonsuraimu].	skill, memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi], memory.I_skill[memory.sk_nasi]);
	Inventory_Have_Get(enemy[suraimu].		magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
	Inventory_Have_Get(enemy[suraimubesu].	magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
	Inventory_Have_Get(enemy[metarusuraimu].magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
	Inventory_Have_Get(enemy[raimusuraimu].	magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
	Inventory_Have_Get(enemy[remonsuraimu].	magic, memory.I_spell[memory.spell1], memory.I_spell[memory.spell4], memory.I_spell[memory.spell7], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi], memory.I_spell[memory.sp_nasi]);
}

Enemy::~Enemy()
{
}

void Enemy::Turn_Reset()
{
}
void Enemy::Battle_AI(Battle *battle)
{
	for (int i = 0; i < 4; i++)
	{
		if (battle->m_enemy[i].name_origin == "スライム")
		{
			battle->m_enemy[i].second_behavior_flag[battle->attack] = true;
			battle->m_enemy[i].who_command_flag[0] = true;
        }
        if (battle->m_enemy[i].name_origin == "スライムベス")
        {
			battle->m_enemy[i].second_behavior_flag[battle->attack] = true;
			battle->m_enemy[i].who_command_flag[1] = true;
        }
        if (battle->m_enemy[i].name_origin == "メタルスライム")
        {
			battle->m_enemy[i].second_behavior_flag[battle->attack] = true;
			battle->m_enemy[i].who_command_flag[2] = true;
		}
        if (battle->m_enemy[i].name_origin == "ライムスライム")
        {
			battle->m_enemy[i].second_behavior_flag[battle->attack] = true;
			battle->m_enemy[i].who_command_flag[0] = true;
        }
        if (battle->m_enemy[i].name_origin == "レモンスライム")
        {
			battle->m_enemy[i].second_behavior_flag[battle->attack] = true;
			battle->m_enemy[i].who_command_flag[1] = true;
        }
     }
}

void Enemy::Move(Map map, Player player)
{
	if (map.now_floor > 0)
	{
		on_flag = true;
		for (int i = 0; i < ENEMY; i++)
		{
			if (Enemy_notice(player.c_ally[0].f_pos, enemy[i].f_pos))
			{
				notice_flag[i] = true;
			}
			if (notice_flag[i])
			{
				enemy[i].vec = Sub_Vector_Vector(enemy[i].f_pos, player.c_ally[0].f_pos);
				enemy[i].vec = Vector_Normalize(enemy[i].vec);
				enemy[i].vec = Mul_Vector_Scaler(enemy[i].vec, -0.5);
				enemy[i].f_pos = Add_Vector_Vector(enemy[i].f_pos, enemy[i].vec);
				notice_count[i]++;
				if (notice_count[i] > 300)
				{
					notice_count[i] = 0;
					notice_flag[i] = false;
				}
			}
			if (!notice_flag[i])
			{
				if (move_count[i] < 200)
				{
					enemy[i].vec = Vector_Normalize(enemy[i].vec);
					enemy[i].vec = Mul_Vector_Scaler(enemy[i].vec, 1);
					enemy[i].f_pos = Add_Vector_Vector(enemy[i].f_pos, enemy[i].vec);
				}
				else if (move_count[i] > 400)
				{
					enemy[i].vec = Vector_Normalize(enemy[i].vec);
					enemy[i].vec = Mul_Vector_Scaler(enemy[i].vec, -1);
					enemy[i].f_pos = Add_Vector_Vector(enemy[i].f_pos, enemy[i].vec);
					if (move_count[i] > 600)
					{
						move_count[i] = 0;
					}
				}
				move_count[i]++;
			}
		}
	}
	else
	{
		on_flag = false;
	}
}

void Enemy::Draw(Map map)
{
	if(map.now_floor > 0)
	{
		for (int i = 0; i < ENEMY; i++)
		{
			MV1DrawModel(enemy[i].modelHandle);
			MV1SetPosition(enemy[i].modelHandle, VGet(enemy[i].f_pos.x, enemy[i].f_pos.y, enemy[i].f_pos.z));
		}
	}
}

void Enemy::Battle_Draw(Battle battle, Effect *effect)
{
    for (int i = 0; i < ENEMY; i++)
    {
		if (battle.m_enemy[i].hp > 0)
		{
			MV1DrawModel(battle.m_enemy[i].modelHandle);
			MV1SetPosition(battle.m_enemy[i].modelHandle, VGet(battle.m_enemy[i].b_pos.x, battle.m_enemy[i].b_pos.y, battle.m_enemy[i].b_pos.z));
			MV1SetRotationXYZ(battle.m_enemy[i].modelHandle, VGet(0.0f, DX_PI_F, 0.0f));
		}
		else if (battle.m_enemy[i].die_flag)
		{
           /* effect->enemy_die.pos = enemy[i].b_pos;
            effect->Draw(&effect->enemy_die, 150);*/
			/*MV1DrawModel(battle.m_enemy[i].modelHandle);
			MV1SetPosition(battle.m_enemy[i].modelHandle, VGet(battle.m_enemy[i].b_pos.x, battle.m_enemy[i].b_pos.y, battle.m_enemy[i].b_pos.z));
			MV1SetRotationXYZ(battle.m_enemy[i].modelHandle, VGet(0.0f, DX_PI_F, 0.0f));*/
		}
    }
}
