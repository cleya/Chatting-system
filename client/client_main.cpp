#include<iostream>
#include<pthread.h>
#include<stdlib.h>   //atoi() exit()
#include"../window/window.h"
#include"udp_client.h"
#include"udp_data.h"
#include<strstream>
using namespace std;

static window win;

udp_client cli("127.0.0.1",8080);

static udp_data data;

void* header_run(void* arg)
{
	int _x =1;
	string _msg = "Welcome to chatting system";
	win.draw_header();
	WINDOW* _h = win.get_header();
	while(1)
	{
	    int _height,_width;
	    getmaxyx(_h,_height,_width);
		win.clear_win_line(_h,_height/2,1);
		win.put_str_to_win(_h,_height/2,_x++,_msg);
		if(_x >= COLS - _msg.size())
			_x = 1;
		sleep(1);
		box(_h,0,0);
		wrefresh(_h);
	}
}
void* input_run(void* arg)
{
	int y = 1,x = 5;
	string msg = "please enter:";
	win.draw_input();
	WINDOW* i = win.get_input();
	//getmaxyx(i,height,width);
	string input;
	string none = "NONE";
	string quit = "QUIT";
	while(1)
	{
		input="";
		win.put_str_to_win(i,y,x,msg);
		box(i,0,0);
		wrefresh(i);
		win.get_str_from_win(i,input);
		if(input == "quit")
		{
			data.set_msg(none);
			data.set_cmd(quit);

			string json_msg;
			data.serialization(json_msg);
			cli.send_data(json_msg);
			exit(0);
		}
		data.set_msg(input);
		string json_msg;
		data.serialization(json_msg);
		cli.send_data(json_msg);
	    int height,width;
		getmaxyx(i,height,width);
		win.clear_win_line(i,1,height-1);
		usleep(100000);
	}
}

void* output_run(void* arg)
{
	string msg,nickname,school,mesg,cmd;
	int height,width;
	int x= 5,y = 0;
	win.draw_output();
	WINDOW* o = win.get_output();
	getmaxyx(o,height,width);
	udp_data data;
	while(1)
	{
		y++;
		y %= height;
		if(y == 0)
		{
			win.clear_win_line(o,1,height-1);
			continue;
		}
		box(o,0,0);
		wrefresh(o);
		ssize_t size = cli.recv_data(msg);
		if(size > 0)
		{
			data.deserialization(msg);
			data.get_nickname(nickname);
			data.get_school(school);
			data.get_msg(mesg);
			data.get_cmd(cmd);

			string output = "[";
			output += nickname;
			output += "/";
			output += school;
			output += "]$";
			output += mesg;

			win.put_str_to_win(o,y,x,output);
			string friend_info = nickname + "/" +school;
			if(cmd == "QUIT")
				cli.del_friend(friend_info);
			else
				cli.add_friend(friend_info);
			
		}
		box(o,0,0);
		wrefresh(o);
	}
}
void* friend_list_run(void* arg)
{
	string msg = "hello";
	win.draw_friend_list();
	WINDOW* l = win.get_friend_list();
	int x = 2;
	while(1)
	{
	    int height,width;
	    getmaxyx(l,height,width);
		vector<string> vec = cli.get_friend_list();
		int friend_num = vec.size();
		int page = height - 3;
		int page_num = friend_num / page;
		int page_mode = friend_num % page;
		if(page_mode > 0)
			page_num++;

		strstream ss;
		string str_page_num;
		ss<<page_num;
		ss>>str_page_num;

		string out_page;
		box(l,0,0);
		wrefresh(l);

		string info;

		for(int i = 0;i < page_num;i++)
		{
			string str_i;
			strstream ssi;
			ssi<<i+1;
			ssi>>str_i;

			out_page = str_i+"/"+str_page_num;
			win.clear_win_line(l,height-2,1);
			win.put_str_to_win(l,height-2,width/2,out_page);

			int y = 0;
			for(int j = 0; j < page;j++)
			{
				y++;
				y %= height -3;
				int index = i*page + j;
				if(index < friend_num)
				{
					info = vec[index];
					if(y == 0)
					{
						wrefresh(l);
						sleep(3);
						win.clear_win_line(l,1,height-4);
						continue;
					}
					win.put_str_to_win(l,y,x,info);
				}
				else
					break;
			}
		}
	}
		sleep(5);

}
//void get_opt(int argc,char* argv[])
//{
//	char* opt_str = "hi:p:";
//	int ch;
//	int flag = 0;
//	while(ch = getopt(argc,argv,opt_str) != -1)
//	{
//		switch(ch)
//		{
//			case 'h':
//				usage();
//				exit(1);
//				break;
//			case 'i':
//				flag++;
//				string _ip = optarg;
//				cli.set_ip(_ip);
//				break;
//			case 'p':
//				flag++;
//				int _p = atoi(optarg);
//				cli.set_port((unsigned short int)_p);
//				break;
//		}
//	}
//	if(flag != 2)
//	{
//		usage();
//		exit(1);
//	}
//}

void Usage(const char* proc)
{
	cout <<"Usage:"<<proc<<"[remote_ip] [remote_port]" <<endl;
}


int main()
{
//	get_opt(argc,argv);
//	if(argc != 3)
//	{
//		Usage(argv[0]);
//		exit(1);
//	}
//	string ip = argv[1];
//	short port = atoi(argv[2]);
    cli.init_client();
	string nickname;
	string school;
	cout<<"please enter your nickname: ";
	fflush(stdout);
	cin>>nickname;
	cout<<endl;
	cout<<"please enter your school: ";
	fflush(stdout);
	cin>>school;

	data.set_nickname(nickname);
	data.set_school(school);

	pthread_t header,input,output,friend_list;
	pthread_create(&header,NULL,header_run,NULL);
	pthread_create(&input,NULL,input_run,NULL);
	pthread_create(&output,NULL,output_run,NULL);
	pthread_create(&friend_list,NULL,friend_list_run,NULL);

	pthread_join(header,NULL);
	pthread_join(input,NULL);
	pthread_join(output,NULL);
	pthread_join(friend_list,NULL);

	return 0;
}
