#ifndef _COMMENT_STRING_H_
#define _COMMENT_STRING_H_
struct Rect
{
	int u;
	int v;
	int w;
	int h;
};

class Comment_string
{
public:
	typedef std::map<std::string, Rect*, std::less<> > StringMap;
	Rect pos[20][10];
	StringMap word;
	int comment_graph;
    int comment_graph_orange;
    int comment_graph_red;
	int count;
	Comment_string();
	~Comment_string();
	void Init();
	void Draw(float x, float y, std::string comment);
    void Draw_Orange(float x, float y, std::string comment);
    void Draw_Red(float x, float y, std::string comment);
	void word_insert(int col, std::string a, std::string i, std::string u, std::string e, std::string o, std::string A, std::string I, std::string U, std::string E, std::string O);
};



#endif // _COMMENT_STRING_H_