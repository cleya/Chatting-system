#include "json_comm.h"

json_comm::json_comm()
{}

bool json_comm::val_to_str(Json::Value &_val,std::string  &_str)
{
//#ifdef _OUT_STYLE
//	Json::StyledWriter _writer;
//else
	Json::FastWriter _writer;
//#endif	
	_str = _writer.write(_val);
	return 0;
}
bool json_comm::str_to_val(std::string &_str,Json::Value &_val)
{
	Json::Reader _reader;
	if(_reader.parse(_str,_val,false))
		return 0;
	else
		return 1;
}

json_comm::~json_comm()
{}
