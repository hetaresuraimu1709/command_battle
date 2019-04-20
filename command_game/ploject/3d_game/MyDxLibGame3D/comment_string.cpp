#include "Header.h"
#include <list>

//********************************************************
// ŠÖ”ŒQ
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
// ‰æ‘œ“Ç‚İ‚İ
//********************************************************
Comment_string::Comment_string()
{
	comment_graph = LoadGraph("data/command/character_all3.png");
    comment_graph_orange = LoadGraph("data/command/character_all3_orange.png");
    comment_graph_red = LoadGraph("data/command/character_all3_red.png");
}

//********************************************************
// ‰æ‘œƒfƒŠ[ƒg—piŒ»İ–¢g—pj
//********************************************************
Comment_string::~Comment_string()
{
}

//********************************************************
// ‰Šú‰»
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
	word_insert(0,  "‚ ", "‚¢", "‚¤", "‚¦", "‚¨", "ƒA", "ƒC", "ƒE", "ƒG", "ƒI");
	word_insert(1,  "‚©", "‚«", "‚­", "‚¯", "‚±", "ƒJ", "ƒL", "ƒN", "ƒP", "ƒR");
	word_insert(2,  "‚³", "‚µ", "‚·", "‚¹", "‚»", "ƒT", "ƒV", "ƒX", "ƒZ", "ƒ\");
	word_insert(3,  "‚½", "‚¿", "‚Â", "‚Ä", "‚Æ", "ƒ^", "ƒ`", "ƒc", "ƒe", "ƒg");
	word_insert(4,  "‚È", "‚É", "‚Ê", "‚Ë", "‚Ì", "ƒi", "ƒj", "ƒk", "ƒl", "ƒm");
	word_insert(5,  "‚Í", "‚Ğ", "‚Ó", "‚Ö", "‚Ù", "ƒn", "ƒq", "ƒt", "ƒw", "ƒz");
	word_insert(6,  "‚Ü", "‚İ", "‚Ş", "‚ß", "‚à", "ƒ}", "ƒ~", "ƒ€", "ƒ", "ƒ‚");
	word_insert(7,  "‚â", "‚î", "‚ä", "‚ï", "‚æ", "ƒ„", "[", "ƒ†", "{", "ƒˆ");
	word_insert(8,  "‚ç", "‚è", "‚é", "‚ê", "‚ë", "ƒ‰", "ƒŠ", "ƒ‹", "ƒŒ", "ƒ");
	word_insert(9,  "‚í", "‚ğ", "‚ñ", "I", "H", "ƒ", "ƒ’", "ƒ“", "A", "B");
	word_insert(10, "‚ª", "‚¬", "‚®", "‚°", "‚²", "ƒK", "ƒM", "ƒO", "ƒQ", "ƒS");
	word_insert(11, "‚´", "‚¶", "‚¸", "‚º", "‚¼", "ƒU", "ƒW", "ƒY", "ƒ[", "ƒ]");
	word_insert(12, "‚¾", "‚À", "‚Ã", "‚Å", "‚Ç", "ƒ_", "ƒa", "ƒd", "ƒf", "ƒh");
	word_insert(13, "‚Î", "‚Ñ", "‚Ô", "‚×", "‚Ú", "ƒo", "ƒr", "ƒu", "ƒx", "ƒ{");
	word_insert(14, "‚Ï", "‚Ò", "‚Õ", "‚Ø", "‚Û", "ƒp", "ƒs", "ƒv", "ƒy", "ƒ|");
	word_insert(15, "‚Ÿ", "‚¡", "‚£", "‚¥", "‚§", "ƒ@", "ƒB", "ƒD", "ƒF", "ƒH");
	word_insert(16, "‚á", "i", "‚ã", "j", "‚å", "ƒƒ", "^", "ƒ…", "E", "ƒ‡");
	word_insert(17, "‚`", "‚a", "‚b", "‚c", "‚d", "‚e", "‚f", "‚g", "‚h", "‚i");
	word_insert(18, "‚j", "‚k", "‚l", "‚m", "‚n", "‚o", "‚p", "‚q", "‚r", "‚s");
	word_insert(19, "‚t", "‚u", "‚v", "‚w", "‚x", "‚y", "‚Á", "ƒb", "–", "@");
}

//********************************************************
// •`‰æ
//********************************************************
void Comment_string::Draw(float x, float y, std::string comment)
{
    //•¶š”Šl“¾i‘SŠp‚¾‚©‚ç‚Q•ª‚Ì‚P‚É‚·‚éj
    std::size_t word_num = comment.size() / 2;
	// ƒŠƒXƒg‚ÌŒÂ”•ª‚¾‚¯‘‚¢‚Ä‚¢‚­
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
    //•¶š”Šl“¾i‘SŠp‚¾‚©‚ç‚Q•ª‚Ì‚P‚É‚·‚éj
    std::size_t word_num = comment.size() / 2;
    // ƒŠƒXƒg‚ÌŒÂ”•ª‚¾‚¯‘‚¢‚Ä‚¢‚­
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
    //•¶š”Šl“¾i‘SŠp‚¾‚©‚ç‚Q•ª‚Ì‚P‚É‚·‚éj
    std::size_t word_num = comment.size() / 2;
    // ƒŠƒXƒg‚ÌŒÂ”•ª‚¾‚¯‘‚¢‚Ä‚¢‚­
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
