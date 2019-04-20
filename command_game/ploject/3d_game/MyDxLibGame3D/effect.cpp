#include "Header.h"

Effect::Effect()
{
	warp.effectResource = LoadEffekseerEffect("data/effect/warp.efk");
    enemy_die.effectResource = LoadEffekseerEffect("data/effect/warp.efk");
	hoge_Handle = LoadGraph("data/command/keycursor.png");
}

Effect::~Effect()
{
}

void Effect::Init()
{
	warp.time = 0;
	warp.pos = VectorGet(50.0f * 12, 0.0f, 50.0f * 21);
	warp.playingEffect = -1;
    enemy_die.time = 0;
    enemy_die.pos = VectorGet(0.0f, 0.0f, 0.0f);
    enemy_die.playingEffect = -1;
}

void Effect::Draw(EffectBase *effect, int max_count)
{

	DrawGraph(-100, -100, hoge_Handle, true);

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	// 定期的にエフェクトを再生する
	if (effect->time % max_count == 0)
	{
		// エフェクトを再生する。
		effect->playingEffect = PlayEffekseer3DEffect(effect->effectResource);
	}
	SetPosPlayingEffekseer3DEffect(effect->playingEffect, effect->pos.x, effect->pos.y, effect->pos.z);
	effect->time++;
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}
