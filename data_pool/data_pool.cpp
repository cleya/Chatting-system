#include"data_pool.h"

data_pool::data_pool(int _size)
	:pool_size(_size) ,pool(_size)
{
	start = 0;
	end = 0;
	sem_init(&producer,0,_size);
	sem_init(&consumer,0,0);
}
bool data_pool::get_data(string& _out)
{
	sem_wait(&consumer);  //consumer-
	_out = pool[end];
	sem_post(&producer);
	end = (++end)%pool_size;

}
bool data_pool::put_data(string& _in)
{
	sem_wait(&producer);  //producer-
	pool[start] = _in;
	sem_post(&consumer);
	start = (++start)%pool_size;

}
data_pool::~data_pool()
{
	sem_destroy(&producer);
	sem_destroy(&consumer);
}
