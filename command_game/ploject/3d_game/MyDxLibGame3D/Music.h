// Music.h
//メモリーのヘッダー
#ifndef _MUSIC_H_
#define _MUSIC_H_

struct BGM
{
	int intro;
	int loop;
	int volume;
	int volume_count;
	bool intro_flag;
	bool intro_end_flag;
	bool loop_flag;
};

class Music
{
public:
	Music();
	~Music();
	void cursor_enter();
	void cursor_move();
	void cursor_cancel();
	void title_enter();
	void title_cancel();
	void field_theme(int BGM_max_vol_plus);
	void title_theme(int BGM_max_vol_plus);
	void enemy_battle(int BGM_max_vol_plus);
	void boss_battle(int BGM_max_vol_plus);
	void field_theme_Stop();
	void title_theme_Stop();
	void enemy_battle_Stop();
	void boss_battle_Stop();
	void field_theme_flag_reset();
	void title_theme_flag_reset();
	void enemy_battle_flag_reset();
	void boss_battle_flag_reset();

private:
	int volume_max_bgm;
	int volume_max_se;
	int cursor_enter_se;
	int cursor_move_se;
	int cursor_cancel_se;
	int title_enter_se;
	int title_cancel_se;
	BGM field_theme_bgm;
	BGM title_theme_bgm;
	BGM enemy_battle_bgm;
	BGM boss_battle_bgm;
};

#endif //_MUSIC_H_