#include "Header.h"

Memory::Memory()
{
    //まほう
    {
        I_spell[0]  = Inventory_Get(sp_nasi, false, 0,	mu,		"スペルなし");       //魔法無し
        I_spell[1]  = Inventory_Get(spell1,  false, 10,	firen,	"フィレン");         //火属性魔法（小）
        I_spell[2]  = Inventory_Get(spell2,  false, 30, firen,	"フィレイヤ");       //火属性魔法（中）
        I_spell[3]  = Inventory_Get(spell3,  false, 100,firen,	"フィレムーア");     //火属性魔法（大）
        I_spell[4]  = Inventory_Get(spell4,  false, 10, rofs,	"ロフス");           //氷属性魔法（小）
        I_spell[5]  = Inventory_Get(spell5,  false, 30, rofs,	"ロフスィン");       //氷属性魔法（中）
        I_spell[6]  = Inventory_Get(spell6,  false, 100,rofs,	"ロブスーン");       //氷属性魔法（大）
        I_spell[7]  = Inventory_Get(spell7,  false, 10,	alre,	"アーレ");           //風属性魔法（小）
        I_spell[8]  = Inventory_Get(spell8,  false, 30, alre,	"エアーレ");         //風属性魔法（中）
        I_spell[9]  = Inventory_Get(spell9,  false, 100,alre,	"エアリガレ");       //風属性魔法（大）
        I_spell[10] = Inventory_Get(spell10, false, 0,	mu,		"フォーズ");         //攻撃力バフ魔法
        I_spell[11] = Inventory_Get(spell11, false, 0,	mu,		"フォール");         //攻撃力デバフ魔法
        I_spell[12] = Inventory_Get(spell12, false, 0,	mu,		"ガーヅ");           //防御力バフ魔法
        I_spell[13] = Inventory_Get(spell13, false, 0,	mu,		"ガール");           //防御力デバフ魔法
        I_spell[14] = Inventory_Get(spell14, false, 0,	mu,		"スピーズ");         //素早さバフ魔法
        I_spell[15] = Inventory_Get(spell15, false, 0,	mu,		"スピール");         //素早さデバフ魔法
    }
    //とくぎ
    {
        I_skill[0]  = Inventory_Get(sk_nasi, false, 0,	mu,		"スキルなし");       //スキル無し
        I_skill[1]  = Inventory_Get(skill1,  false, 0,  alre,	"なぎはらい");       //範囲攻撃
        I_skill[2]  = Inventory_Get(skill2,  false, 0,	mu,		"いっせん");         //当たれば会心
        I_skill[3]  = Inventory_Get(skill3,  false, 0,	mu,		"めつぶし");         //相手の攻撃が２ターン当たらなくなる
        I_skill[4]  = Inventory_Get(skill4,  false, 0,	mu,		"くちふさぎ");       //相手の魔法が２ターン唱えられなくなる
        I_skill[5]  = Inventory_Get(skill5,  false, 0,	mu,		"ちょうはつ");       //相手の敵意を自分一人に寄せる
        I_skill[6]  = Inventory_Get(skill6,  false, 0,	mu,		"たいあたり");       //防御力依存のダメージ、相手は１ターン行動不能
        I_skill[7]  = Inventory_Get(skill7,  false, 0,	mu,		"みねうち");         //手加減して攻撃、１は必ず与える
        I_skill[8]  = Inventory_Get(skill8,  false, 0,	mu,		"おたけび");         //敵全体を１ターン行動不能（確率）、寝てる人がいたら起きる
        I_skill[9]  = Inventory_Get(skill9,  false, 0,	mu,		"てあて");           //味方一人のHPを小～中回復
        I_skill[10] = Inventory_Get(skill10, false, 0,	mu,		"はっする");         //味方全体のHPを小回復
        I_skill[11] = Inventory_Get(skill11, false, 0,	mu,		"ひろいぐい");       //５０％の確率でHP,MP中回復、５０％の確率で状態異常をくらいつつHP小回復
        I_skill[12] = Inventory_Get(skill12, false, 0,	mu,		"そせいじゅつ");     //味方一人を蘇生（確率）
        I_skill[13] = Inventory_Get(skill13, false, 0,	mu,		"あらりょうじ");     //ダメージを食らうが状態異常回復
        I_skill[14] = Inventory_Get(skill14, false, 0,	mu,		"おやすみ");         //３ターンの間睡眠状態になるがHP,MPが回復していく
        I_skill[15] = Inventory_Get(skill15, false, 0,	mu,		"まんじ");           //バイブスが上がる（３回連続で成功するとバイブスが有頂天になって敵をせん滅）
    }
    //どうぐ
    {
        I_item[0]  = Inventory_Get(it_nasi, false, 0,	mu,	"アイテムなし");       //アイテム無し
        I_item[1]  = Inventory_Get(item1,   false, 0,	mu,	"カットバン");         //味方一人のHPを中回復
        I_item[2]  = Inventory_Get(item2,   false, 0,	mu,	"ほうたい");           //味方一人のHPを大回復
        I_item[3]  = Inventory_Get(item3,   false, 0,	mu,	"ポーション");         //味方一人のHPを完全回復
        I_item[4]  = Inventory_Get(item4,   false, 0,	mu,	"おこう");             //味方全体のHP,MPを小回復
        I_item[5]  = Inventory_Get(item5,   false, 0,	mu,	"ミネラルすい");       //味方一人のMPを中回復
        I_item[6]  = Inventory_Get(item6,   false, 0,	mu,	"ブルーブル");         //味方一人のMPを大回復
        I_item[7]  = Inventory_Get(item7,   false, 0,	mu,	"おべんとう");         //味方一人のHP,MPを小回復、３回使える
        I_item[8]  = Inventory_Get(item8,   false, 0,	mu,	"けむりだま");         //戦闘から確実に逃げれる
        I_item[9]  = Inventory_Get(item9,   false, 0,	mu,	"");
        I_item[10] = Inventory_Get(item10,  false, 0,	mu,	"アイテム");
        I_item[11] = Inventory_Get(item11,  false, 0,	mu,	"アイテム");
        I_item[12] = Inventory_Get(item12,  false, 0,	mu,	"アイテム");
        I_item[13] = Inventory_Get(item13,  false, 0,	mu,	"アイテム");
        I_item[14] = Inventory_Get(item14,  false, 0,	mu,	"アイテム");
        I_item[15] = Inventory_Get(item15,  false, 0,	mu,	"アイテム");
    }
}

Memory::~Memory()
{
}

void Memory::UseSpell(Battle *battle, Chara *chara)
{
	for (int i = 0; i < KEY_MAGIC_MAX_COMMAND_X; i++)
	{
		for (int j = 0; j < KEY_MAGIC_MAX_COMMAND_Y; j++)
		{
			Inventory inv_case = chara->magic[j == 0 ? i : i + KEY_MAGIC_MAX_COMMAND_X];
			if (inv_case.use_flag)
			{
				if (inv_case.name == "フィレン")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "フィレイヤ")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "フィレムーア")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "ロフス")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "ロフスィン")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "ロブスーン")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "アーレ")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "エアーレ")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "エアリガレ")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "フォーズ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "フォール")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "ガーヅ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "ガール")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "スピーズ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "スピール")
				{
					chara->mp -= 2;
				}
			}
		}
	}
}

void Memory::UseSkill(Battle *battle, Chara *chara)
{
	for (int i = 0; i < KEY_MAGIC_MAX_COMMAND_X; i++)
	{
		for (int j = 0; j < KEY_MAGIC_MAX_COMMAND_Y; j++)
		{
			Inventory inv_case = chara->skill[j == 0 ? i : i + KEY_MAGIC_MAX_COMMAND_X];
			if (inv_case.use_flag)
			{
				if (inv_case.name == "なぎはらい")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "いっせん")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "めつぶし")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "くちふさぎ")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "ちょうはつ")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "たいあたり")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "みねうち")
				{
					chara->mp -= 3;
				}
				if (inv_case.name == "おたけび")
				{
					chara->mp -= 5;
				}
				if (inv_case.name == "てあて")
				{
					chara->mp -= 10;
				}
				if (inv_case.name == "はっする")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "ひろいぐい")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "そせいじゅつ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "あらりょうじ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "おやすみ")
				{
					chara->mp -= 2;
				}
				if (inv_case.name == "まんじ")
				{
					chara->mp -= 2;
				}
			}
		}
	}
}

void Memory::UseItem(Battle *battle, Chara *chara)
{
}
