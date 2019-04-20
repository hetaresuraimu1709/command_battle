// Title.h
//タイトルのヘッダー
#ifndef _TITLE_H_
#define _TITLE_H_

struct Graph
{
	int graph;//画像データ
	Vector2 pos;//position
	float enl;//拡大率
	bool flag;//拡大率いじるためのフラグ
};

class Title
{
public:
	Title();//コンストラクタ
	~Title();//デストラクタ
	void Move(int *scene, Music *music, bool *game_end_flag);//動き
	void Draw(Comment_string *comment, Music *music);//描画
private:
	Graph main_title;
	Graph title_back;
	Graph command;
	Graph miffy[3];
	Graph suraimu[2];
	int cursor_graph[8];
	int anim_count;
	int anim_frame;
	Vector2 gamestart_pos;
	Vector2 cursor_pos;
};

class End
{
public:
	End();//コンストラクタ
	~End();//デストラクタ
	void Move(int *scene);//動き
	void Draw(Comment_string *comment, Music *music);//描画
};

#endif // _TITLE_H_