//Npc.h
#ifndef _NPC_H_
#define _NPC_H_

struct Npc_base
{
	std::string name;
	int model;
	Vector3 pos;
	std::string line;
};

class Npc
{
public:
	Npc();
	~Npc();
	void Init();
	void Updata();
	void Draw();
private:
	Npc_base people[10];
};

#endif//_NPC_H_
