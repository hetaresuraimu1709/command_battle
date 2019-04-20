#ifndef _Effect_H_
#define _Effect_H_

struct EffectBase
{
	int effectResource;
	int time;
	int playingEffect;
	Vector3 pos;
};

class Effect
{
public:
	Effect();
	~Effect();
	void Init();
	void Draw(EffectBase *effect, int max_count);
	int hoge_Handle;
	EffectBase warp;
    EffectBase enemy_die;
private:

};

#endif
