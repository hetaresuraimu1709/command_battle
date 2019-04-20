//Window.h
#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window
{
public:
	Window();
	~Window();
	void Command_Draw(float pos_x, float pos_y,float size_x,float size_y);
private:

	int window_back_graph;
	int window_line_graph;
};

#endif // _WINDOW_H_