// Memory.h
//メモリーのヘッダー
#ifndef _MEMORY_H_
#define _MEMORY_H_

class Memory
{
public:
    Memory();
    ~Memory();
    Inventory I_spell[SPELL_MAX], I_skill[SKILL_MAX], I_item[ITEM_MAX];
    enum spell
    {
        sp_nasi,//何も入ってない
        spell1,//火属性（小）
        spell2,//火属性（中）
        spell3,//火属性（大）
        spell4,//水属性（小）
        spell5,//水属性（中）
        spell6,//水属性（大）
        spell7,//風属性（小）
        spell8,//風属性（中）
        spell9,//風属性（大）
        spell10,//光属性（小）
        spell11,//光属性（中）
        spell12,//光属性（大）
        spell13,//闇属性（小）
        spell14,//闇属性（中）
        spell15,//闇属性（大）
    };

    enum skill
    {
        sk_nasi,
        skill1,
        skill2,
        skill3,
        skill4,
        skill5,
        skill6,
        skill7,
        skill8,
        skill9,
        skill10,
        skill11,
        skill12,
        skill13,
        skill14,
        skill15,
    };

    enum item
    {
        it_nasi,
        item1,
        item2,
        item3,
        item4,
        item5,
        item6,
        item7,
        item8,
        item9,
        item10,
        item11,
        item12,
        item13,
        item14,
        item15,
    };

	enum force
	{
		mu = 0,		//属性なし
		firen = 1,	//火属性
		rofs = 2,	//氷属性
		alre = 3	//風属性
	};

    void UseSpell(Battle *battle, Chara *chara);
    void UseSkill(Battle *battle, Chara *chara);
    void UseItem(Battle *battle, Chara *chara);
private:

};

#endif // _MEMORY_H_
