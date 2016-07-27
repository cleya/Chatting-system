#include"udp_data.h"

udp_data::udp_data()
{}
void udp_data::serialization(string &_out)
{
	Json::Value root;
	root["nickname"] = this->nickname;
	root["school"] = this->school;
	root["msg"] = this->msg;
	root["cmd"] = this->cmd;
	json.val_to_str(root,_out);
}
void udp_data::deserialization(string &_in)
{
	Json::Value root;
	json.str_to_val(_in,root);
	this->nickname = root["nickname"].asString();
	this->school = root["school"].asString();
	this->msg = root["msg"].asString();
	this->cmd = root["cmd"].asString();
}
udp_data::~udp_data()
{}
