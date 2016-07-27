#include"window.h"

window::window()
	:header(NULL),input(NULL),output(NULL),friend_list(NULL)
{
	initscr();
}
void window::put_str_to_win(WINDOW* _win,int _height,int _width,string _msg)
{
	mvwaddstr(_win,_height,_width,_msg.c_str());
}
void window::get_str_from_win(WINDOW* _win,string& _out)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(_win,buf,sizeof(buf));
	_out = buf;
}
void window::clear_win_line(WINDOW* _win,int begin,int num)
{
	while(num-- > 0)
	{
		wmove(_win,begin++,0);
		wclrtoeol(_win);
	}
}
void window::draw_header()
{
	int _y = 0;
	int _x = 0;
	int _height = LINES/5;
	int _width = COLS;
	this->header = newwin(_height,_width,_y,_x);
	box(header,0,0);
	wrefresh(header);
}
void window::draw_friend_list()
{
	int _y = LINES/5;
	int _x = 0;
	int _height = 3*LINES/5;
	int _width = COLS/2;
	this->friend_list = newwin(_height,_width,_y,_x);
	box(friend_list,0,0);
	wrefresh(friend_list);
}
void window::draw_output()
{
	int _y = LINES/5;
	int _x = COLS/2;
	int _height = 3*LINES/5;
	int _width = COLS/2;
	this->output = newwin(_height,_width,_y,_x);
	box(input,0,0);
	wrefresh(output);
}
void window::draw_input()
{
	int _y = 4*LINES/5;
	int _x = 0;
	int _height = LINES/5;
	int _width = COLS;
	this->input = newwin(_height,_width,_y,_x);
	box(input,0,0);
	wrefresh(input);
}
window::~window()
{
	delwin(header);
	delwin(input);
	delwin(output);
	delwin(friend_list);
	endwin();
}

