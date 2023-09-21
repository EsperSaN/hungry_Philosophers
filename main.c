#include <sys/time.h>
#include <stdio.h>
long get_time()
{
	struct timeval t;
	gettimeofday(&t,NULL);
	return ((t.tv_usec / 1000) + (t.tv_sec * 1000));
}

int main()
{
	while(1)
	{
		printf("[%llu]\n", get_time());
	}
}