#pragma once

#include<iostream>
#include"json/json.h"
#include<string>
using namespace std;

class json_comm
{
	public:
		json_comm();
		bool val_to_str(Json::Value& _val,std::string& _str);
		bool str_to_val(std::string& _str,Json::Value& _val);
		~json_comm();
};
