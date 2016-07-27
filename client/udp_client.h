#pragma once

#include<iostream>
#include<vector>
using namespace std;

class udp_client
{
	public:
		udp_client(string _ip,short _port);
		int init_client();
        bool recv_data(string &_msg);
        bool send_data(const string &_msg);
		bool if_friend_exit(string& _info);
		void add_friend(string& _info);
		void del_friend(string& _info);
		vector<string>  get_friend_list() {return this->friend_list;}
		~udp_client();
	private:
		int sock;
		string ip;
		short port;
		vector<string> friend_list;
};
