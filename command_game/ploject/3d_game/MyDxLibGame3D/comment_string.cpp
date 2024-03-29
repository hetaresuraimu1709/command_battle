#include "Header.h"
#include <list>

//********************************************************
// 関数群
//********************************************************
void Comment_string::word_insert(int col, std::string a, std::string i, std::string u, std::string e, std::string o, std::string A, std::string I, std::string U, std::string E, std::string O)
{
	word.insert(std::make_pair(a, &pos[col][0]));
	word.insert(std::make_pair(i, &pos[col][1]));
	word.insert(std::make_pair(u, &pos[col][2]));
	word.insert(std::make_pair(e, &pos[col][3]));
	word.insert(std::make_pair(o, &pos[col][4]));
	word.insert(std::make_pair(A, &pos[col][5]));
	word.insert(std::make_pair(I, &pos[col][6]));
	word.insert(std::make_pair(U, &pos[col][7]));
	word.insert(std::make_pair(E, &pos[col][8]));
	word.insert(std::make_pair(O, &pos[col][9]));
}

//********************************************************
// 画像読み込み
//********************************************************
Comment_string::Comment_string()
{
	comment_graph = LoadGraph("data/command/character_all3.png");
    comment_graph_orange = LoadGraph("data/command/character_all3_orange.png");
    comment_graph_red = LoadGraph("data/command/character_all3_red.png");
}

//********************************************************
// 画像デリート用（現在未使用）
//********************************************************
Comment_string::~Comment_string()
{
}

//********************************************************
// 初期化
//********************************************************
void Comment_string::Init()
{
	count = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			pos[i][j].u = (int)(j * STRING_SIZE_W);
			pos[i][j].v = (int)(i * STRING_SIZE_H);
			pos[i][j].w = (int)STRING_SIZE_W;
			pos[i][j].h = (int)STRING_SIZE_H;
		}
	}
	word_insert(0,  "あ", "い", "う", "え", "お", "ア", "イ", "ウ", "エ", "オ");
	word_insert(1,  "か", "き", "く", "け", "こ", "カ", "キ", "ク", "ケ", "コ");
	word_insert(2,  "さ", "し", "す", "せ", "そ", "サ", "シ", "ス", "セ", "ソ");
	word_insert(3,  "た", "ち", "つ", "て", "と", "タ", "チ", "ツ", "テ", "ト");
	word_insert(4,  "な", "に", "ぬ", "ね", "の", "ナ", "ニ", "ヌ", "ネ", "ノ");
	word_insert(5,  "は", "ひ", "ふ", "へ", "ほ", "ハ", "ヒ", "フ", "ヘ", "ホ");
	word_insert(6,  "ま", "み", "む", "め", "も", "マ", "ミ", "ム", "メ", "モ");
	word_insert(7,  "や", "ゐ", "ゆ", "ゑ", "よ", "ヤ", "ー", "ユ", "＋", "ヨ");
	word_insert(8,  "ら", "り", "る", "れ", "ろ", "ラ", "リ", "ル", "レ", "ロ");
	word_insert(9,  "わ", "を", "ん", "！", "？", "ワ", "ヲ", "ン", "、", "。");
	word_insert(10, "が", "ぎ", "ぐ", "げ", "ご", "ガ", "ギ", "グ", "ゲ", "ゴ");
	word_insert(11, "ざ", "じ", "ず", "ぜ", "ぞ", "ザ", "ジ", "ズ", "ゼ", "ゾ");
	word_insert(12, "だ", "ぢ", "づ", "で", "ど", "ダ", "ヂ", "ヅ", "デ", "ド");
	word_insert(13, "ば", "び", "ぶ", "べ", "ぼ", "バ", "ビ", "ブ", "ベ", "ボ");
	word_insert(14, "ぱ", "ぴ", "ぷ", "ぺ", "ぽ", "パ", "ピ", "プ", "ペ", "ポ");
	word_insert(15, "ぁ", "ぃ", "ぅ", "ぇ", "ぉ", "ァ", "ィ", "ゥ", "ェ", "ォ");
	word_insert(16, "ゃ", "（", "ゅ", "）", "ょ", "ャ", "／", "ュ", "・", "ョ");
	word_insert(17, "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ", "Ｉ", "Ｊ");
	word_insert(18, "Ｋ", "Ｌ", "Ｍ", "Ｎ", "Ｏ", "Ｐ", "Ｑ", "Ｒ", "Ｓ", "Ｔ");
	word_insert(19, "Ｕ", "Ｖ", "Ｗ", "Ｘ", "Ｙ", "Ｚ", "っ", "ッ", "＊", "　");
}

//********************************************************
// 描画
//********************************************************
void Comment_string::Draw(float x, float y, std::string comment)
{
    //文字数獲得（全角だから２分の１にする）
    std::size_t word_num = comment.size() / 2;
	// リストの個数分だけ書いていく
	for (size_t i = 0; i < word_num; i++)
	{
		auto tmpRect = word.find( std::string(comment.substr(i * 2, 2)));
		DrawRectGraph(
			(int)(x + (i * (STRING_SIZE_W - 5))),	// destX
			(int)y,									// destY
			tmpRect->second->u,						// srcX
			tmpRect->second->v,						// srcY
			tmpRect->second->w,						// w
			tmpRect->second->h,						// h
			comment_graph,							// handle
			true									// trans
		);
	}
}
void Comment_string::Draw_Orange(float x, float y, std::string comment)
{
    //文字数獲得（全角だから２分の１にする）
    std::size_t word_num = comment.size() / 2;
    // リストの個数分だけ書いていく
    for (size_t i = 0; i < word_num; i++)
    {
        auto tmpRect = word.find(std::string(comment.substr(i * 2, 2)));
        DrawRectGraph(
            (int)(x + (i * (STRING_SIZE_W - 5))),	// destX
            (int)y,									// destY
            tmpRect->second->u,						// srcX
            tmpRect->second->v,						// srcY
            tmpRect->second->w,						// w
            tmpRect->second->h,						// h
			comment_graph_orange,					// handle
            true									// trans
        );
    }
}
void Comment_string::Draw_Red(float x, float y, std::string comment)
{
    //文字数獲得（全角だから２分の１にする）
    std::size_t word_num = comment.size() / 2;
    // リストの個数分だけ書いていく
    for (size_t i = 0; i < word_num; i++)
    {
        auto tmpRect = word.find(std::string(comment.substr(i * 2, 2)));
        DrawRectGraph(
            (int)(x + (i * (STRING_SIZE_W - 5))),	// destX
            (int)y,									// destY
            tmpRect->second->u,						// srcX
            tmpRect->second->v,						// srcY
            tmpRect->second->w,						// w
            tmpRect->second->h,						// h
			comment_graph_red,						// handle
            true									// trans
        );
    }
}
