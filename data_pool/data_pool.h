#pragma once

#include<iostream>
#include<semaphore.h>
#include<string>
#include<vector>
using namespace std;

#define POOL_SIZE 512

class data_pool
{
public:
	data_pool(int _size = POOL_SIZE);
	bool get_data(string& _out);
	bool put_data(string& _in);
	~data_pool();
private:
	int start;
	int end;
	int pool_size;
	vector<string> pool;
	sem_t producer;
	sem_t consumer;

};
