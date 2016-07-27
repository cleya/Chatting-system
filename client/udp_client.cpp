#include"udp_client.h"
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<string>
#include<vector>



udp_client::udp_client(string _ip,short _port)
	:ip(_ip)
	,port(_port)
{
	sock = -1;
}

int udp_client::init_client()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(-1);
	}
//	cout<<"init_client"<<sock<<endl;
	return sock;
}

bool udp_client::recv_data(string &_msg)
{
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	struct sockaddr_in remote;
	socklen_t length = sizeof(remote);
	bzero(&remote,length);
	ssize_t size = recvfrom(this->sock,buf,sizeof(buf),0,(struct sockaddr*)&remote,&length);
	if(size < 0)
	{
		perror("recvfrom");
		return false;
	}
	else
	{
		buf[size] = '\0';
		_msg = buf;
		cout<<_msg<<endl;
		return true;
	}
}
bool udp_client::send_data(const std::string &_msg)
{
	struct sockaddr_in remote;
	socklen_t length = sizeof(remote);
	bzero(&remote,length);
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(ip.c_str());

	ssize_t size = sendto(this->sock,_msg.c_str(),_msg.size(),0,(struct sockaddr*)&remote,length);
	cout<<size<<endl;
	if(size < 0)
	{
	 	perror("sendto");
		return false;
	}
	else
		return true;;
}
bool udp_client::if_friend_exit(string& _info)
{
	vector<string>::iterator _iter = friend_list.begin();
	for(;_iter != friend_list.end();_iter++)
	{
		if(*_iter == _info)
		{
			return true;
		}
	}
	return false;
}
void udp_client::add_friend(string& _info)
{
	if(if_friend_exit(_info))
		return;
	else
		friend_list.push_back(_info);
}
void udp_client::del_friend(string& _info)
{
	if(if_friend_exit(_info))
	{
		vector<string>::iterator _iter = friend_list.begin();
		for(;_iter != friend_list.end();_iter++)
		{
			if(*_iter == _info)
			{
				friend_list.erase(_iter);
				return;
			}
		}
	}
    else
		return;

}
udp_client::~udp_client()
{
	if(this->sock != -1)
		close(sock);
}

//int main()
//{
//	struct sockaddr_in remote;
//	socklen_t len = sizeof(remote);
//	bzero(&remote,len);
//	remote.sin_family = AF_INET;
//	remote.sin_port = htons(8080);
//	inet_aton("127.0.0.1",&remote.sin_addr);


	
//	udp_client cli("127.0.0.1",8080);
//	cli.init_client();
//	char buf[1024];
//	string data;
//	while(1)
//	{
//		memset(buf,'\0',sizeof(buf));
//		ssize_t size = read(0,buf,sizeof(buf)-1);
//		if(size < 0)
//			perror("read");
//	    cli.send_data(data);
//		cli.recv_data(data);
//	}

//	return 0;
//}
