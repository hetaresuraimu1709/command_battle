#include "Header.h"

BGM Get_BGM(int intro, int loop,bool intro_flag, bool intro_end_flag,bool loop_flag)
{
	BGM bgm;
	bgm.intro = intro;
	bgm.loop = loop;
	bgm.volume = 50;
	bgm.volume_count = 0;
	bgm.intro_flag = intro_flag;
	bgm.intro_end_flag = intro_end_flag;
	bgm.loop_flag = loop_flag;
	return bgm;
}

Music::Music()
{
	cursor_enter_se	 = LoadSoundMem("data/sound/SE/cursor_enter.mp3");
	cursor_move_se	 = LoadSoundMem("data/sound/SE/cursor_move.mp3");
	cursor_cancel_se = LoadSoundMem("data/sound/SE/cursor_cancel.mp3");
	title_enter_se = LoadSoundMem("data/sound/SE/enter.mp3");
	title_cancel_se = LoadSoundMem("data/sound/SE/cancel.mp3");
	field_theme_bgm  = Get_BGM(0,														LoadSoundMem("data/sound/BGM/field.mp3"),				true,  true,  false);
	title_theme_bgm  = Get_BGM(LoadSoundMem("data/sound/BGM/title_theme/intro.mp3"),	LoadSoundMem("data/sound/BGM/title_theme/loop.mp3"),	false, false, false);
	enemy_battle_bgm = Get_BGM(LoadSoundMem("data/sound/BGM/enemy_battle/intro.mp3"),	LoadSoundMem("data/sound/BGM/enemy_battle/loop.mp3"),	false, false, false);
	boss_battle_bgm  = Get_BGM(LoadSoundMem("data/sound/BGM/boss_battle/intro.mp3"),	LoadSoundMem("data/sound/BGM/boss_battle/loop.mp3"),	false, false, false);
	volume_max_bgm = 155;
	volume_max_se = 155;
}

Music::~Music()
{
}

void BGM_Stop(BGM *bgm)
{
	if (!bgm->intro_end_flag)
	{
		StopSoundMem(bgm->intro);
	}
	else
	{
		StopSoundMem(bgm->loop);
	}
}

void BGM_Play(BGM *bgm, int BGM_max_vol)
{
	if (bgm->volume < BGM_max_vol)
	{
		bgm->volume_count++;
		if (bgm->volume_count > BGM_VOL_THROW)
		{
			bgm->volume++;
			bgm->volume_count = 0;
		}
		ChangeVolumeSoundMem(bgm->volume, bgm->intro);
		ChangeVolumeSoundMem(bgm->volume, bgm->loop);
	}
	if (!bgm->intro_flag)
	{
		PlaySoundMem(bgm->intro, DX_PLAYTYPE_BACK);
		bgm->intro_flag = true;
	}
	if(bgm->intro_end_flag && !bgm->loop_flag)
	{
		PlaySoundMem(bgm->loop, DX_PLAYTYPE_LOOP);
		bgm->loop_flag = true;
	}
	if (!CheckSoundMem(bgm->intro))
	{
		bgm->intro_end_flag = true;
	}
	if (bgm->intro_end_flag && !CheckSoundMem(bgm->loop))
	{
		bgm->loop_flag = false;
	}
}

void Music::cursor_enter()
{
	ChangeVolumeSoundMem(volume_max_se, cursor_enter_se);
	PlaySoundMem(cursor_enter_se, DX_PLAYTYPE_BACK);
}

void Music::cursor_move()
{
	ChangeVolumeSoundMem(volume_max_se, cursor_move_se);
	PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK);
}

void Music::cursor_cancel()
{
	ChangeVolumeSoundMem(volume_max_se, cursor_cancel_se);
	PlaySoundMem(cursor_cancel_se, DX_PLAYTYPE_BACK);
}

void Music::title_enter()
{
	ChangeVolumeSoundMem(volume_max_se, title_enter_se);
	PlaySoundMem(title_enter_se, DX_PLAYTYPE_BACK);
}

void Music::title_cancel()
{
	ChangeVolumeSoundMem(volume_max_se, title_cancel_se);
	PlaySoundMem(title_cancel_se, DX_PLAYTYPE_BACK);
}

void Music::field_theme(int BGM_max_vol_plus)
{
	BGM_Play(&field_theme_bgm, volume_max_bgm + BGM_max_vol_plus);
}

void Music::title_theme(int BGM_max_vol_plus)
{
	BGM_Play(&title_theme_bgm, volume_max_bgm + BGM_max_vol_plus);
}

void Music::enemy_battle(int BGM_max_vol_plus)
{
	BGM_Play(&enemy_battle_bgm, volume_max_bgm + BGM_max_vol_plus);
}

void Music::boss_battle(int BGM_max_vol_plus)
{
	BGM_Play(&boss_battle_bgm, volume_max_bgm + BGM_max_vol_plus);
}

void Music::field_theme_Stop()
{
	BGM_Stop(&field_theme_bgm);
}

void Music::title_theme_Stop()
{
	BGM_Stop(&title_theme_bgm);
}

void Music::enemy_battle_Stop()
{
	BGM_Stop(&enemy_battle_bgm);
}

void Music::boss_battle_Stop()
{
	BGM_Stop(&boss_battle_bgm);
}

void Music::field_theme_flag_reset()
{
	field_theme_bgm.intro_flag = false;
	field_theme_bgm.intro_end_flag = false;
}

void Music::title_theme_flag_reset()
{
	title_theme_bgm.intro_flag = false;
	title_theme_bgm.intro_end_flag = false;
}

void Music::enemy_battle_flag_reset()
{
	enemy_battle_bgm.intro_flag = false;
	enemy_battle_bgm.intro_end_flag = false;
}

void Music::boss_battle_flag_reset()
{
	boss_battle_bgm.intro_flag = false;
	boss_battle_bgm.intro_end_flag = false;
}
