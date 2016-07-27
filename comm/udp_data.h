#pragma once

#include<iostream>
#include"json/json.h"
#include"json_comm.h"
using namespace std;

class udp_data
{
	public:
		udp_data();
		void serialization(string &_out);
		void deserialization(string &_in);
	
		void set_nickname(string& _nickname){nickname = _nickname;}
		void set_school(string& _school){school = _school;}
		void set_msg(string& _msg){msg = _msg;}
		void set_cmd(string& _cmd){cmd = cmd;}

		void get_nickname(string& _nickname)	{_nickname = this->nickname;}
		void get_school(string& _school)	{_school = this->school;}
		void get_msg(string& _msg)	{_msg = this->msg;}
		void get_cmd(string& _cmd)	{_cmd = this->cmd;}
		~udp_data();
	private:
		json_comm json;
		string nickname;
		string school;
		string msg;
		string cmd;
};


