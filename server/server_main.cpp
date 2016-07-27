#include"udp_server.h"
#include<stdlib.h>
void* consumer_run(void* arg)
{
	udp_server* ser_p = (udp_server*)arg;
	for(;;)
	{
		ser_p->broadcast();
	}
}
void* producter_run(void* arg)
{

	udp_server* ser_p = (udp_server*)arg;
	string msg;
	for(;;)
	{
		ser_p->recv_data(msg);
		cout<<msg<<endl;
	}
	return NULL;
}
void Usage(char* _proc)
{
	cout<<"usage:"<<_proc<<" [IP] [PORT]"<<endl;
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return -1;
	}
	char* _ip = argv[1];
	short _port = atoi(argv[2]);
//	daemon(0,0);
	udp_server ser(_ip,_port);
	ser.init_server();

	pthread_t consumer, producter;
	pthread_create(&consumer, NULL, consumer_run, (void*)&ser);
	pthread_create(&producter, NULL, producter_run, (void*)&ser);
	pthread_join(consumer, NULL);
	pthread_join(producter, NULL);
	return 0;
}
