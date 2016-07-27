#include</usr/include/ncurses.h>
#include<string>
#include<string.h>
#include<iostream>
using namespace std;

class window
{
	public:
		window();
		void draw_header();
		void draw_input();
		void draw_output();
		void draw_friend_list();
		void put_str_to_win(WINDOW* _win,int _height,int _width,string _msg);
		
        void clear_win_line(WINDOW* _win,int begin,int num);
		void get_str_from_win(WINDOW* _win,string& _out);

		WINDOW* get_header(){return this->header;}
		WINDOW* get_input(){return this->input;}
		WINDOW* get_output(){return this->output;}
		WINDOW* get_friend_list(){return this->friend_list;}
		~window();
	private:
		WINDOW* header;
		WINDOW* input;
		WINDOW* output;
		WINDOW* friend_list;
};

