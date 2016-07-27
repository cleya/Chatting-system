#include"udp_server.h"
#include"udp_data.h"
#include<string>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>

udp_server::udp_server(char* _ip,short _port)
	:ip(_ip) ,port(_port) 
{
	sock = -1;
}
udp_server::~udp_server()
{
	if(sock != -1)
		close(sock);
}
void udp_server::init_server()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in local;
	bzero(&local,sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	if(ip == "")
	{
		local.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
//		inet_aton(_ip,&local.sin_addr);
		local.sin_addr.s_addr = inet_addr(ip.c_str());
//		inet_pton(AF_INET,_ip,&local.sin_addr);


	if( bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0 )
	{
		perror("bind");
		exit(1);
	}

}


bool udp_server::recv_data(string &_msg)
{
	struct sockaddr_in client;
	socklen_t length = sizeof(client);
	bzero(&client,length);
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	ssize_t size = recvfrom(this->sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&length);
	if(size < 0)
	{
		perror("recvfrom");
		return false;
	}
	else
	{
		buf[size] = '\0';
		_msg = buf;
		pool.put_data(_msg);
		add_user(client);
		del_user(client,_msg);
		return true;
	}
}

bool udp_server::send_data(const string &_msg,const struct sockaddr_in &_client,const socklen_t &_length)
{
	ssize_t size = sendto(this->sock,_msg.c_str(),_msg.size(),0,(struct sockaddr*)&_client,_length);
	if(size < 0)
	{
		perror("sendto");
		return false;
	}
	else
		return true;
}

void udp_server::broadcast()
{
	string _data;
	pool.get_data(_data);
	map<string,struct sockaddr_in>::iterator _iter;
	for(_iter = online_user.begin();_iter != online_user.end();_iter++)
	{
		send_data(_data,_iter->second,sizeof(_iter->second));
	}
}

void udp_server::add_user(struct sockaddr_in& client)
{
	string _ip = inet_ntoa(client.sin_addr);
	online_user[_ip] = client;
}

void udp_server::del_user(struct sockaddr_in& client,string& out)
{
	udp_data data;
	data.deserialization(out);
	string cmd;
	data.get_cmd(cmd);
	if(cmd == "quit")
	{
		string _ip = inet_ntoa(client.sin_addr);
		online_user.erase(_ip);
	}
}
