//npc.cpp

//ヘッダー呼び出し
#include "Header.h"

Npc::Npc()
{
}

Npc::~Npc()
{
}

Npc_base Npc_In(std::string name, char *filename, Vector3 pos, std::string line)
{
	Npc_base base;

	base.name = name;
	base.model = MV1LoadModel(filename);
	base.pos = pos;
	base.line = line;

	return base;
}

//初期化
void Npc::Init()
{
	for (int i = 0; i < 10; i++)
	{
		people[i] = Npc_In("ああああ", "data/model/miffy/miffy_tool.pmx", Map_On_Pos(VectorGet(MAP_CHIP, MAP_CHIP), VectorGet((float)(10.0f + i), 15.0f)), "あああああ");
	}
}

//更新プログラム
void Npc::Updata()
{

}

//描画
void Npc::Draw()
{
	//３Dモデルのポジション設定
	MV1SetPosition(people[0].model, VGet(people[0].pos.x, people[0].pos.y, people[0].pos.z));
	//プレイヤー描画
	MV1DrawModel(people[0].model);
}
