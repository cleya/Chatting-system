#pragma once

#include<iostream>
#include<map>
#include"data_pool.h"
using namespace std;

class udp_server
{
	public:
		udp_server(char* _ip,short _port);
		void init_server();
		bool recv_data(string &_msg);
		bool send_data(const string &_msg,const struct sockaddr_in &_client,const socklen_t &_length);
		void broadcast();
		~udp_server();
	private:
		void add_user(struct sockaddr_in& client);
		void del_user(struct sockaddr_in& client,string& out);
	private:
		std::string ip;
		short port;
		int sock;
		data_pool pool;
		map<string,struct sockaddr_in>online_user;
};
