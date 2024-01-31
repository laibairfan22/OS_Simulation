#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
void *fun(void *arg)
{
  system("mpg123 ~/Desktop/OS-Project/prgs/song2.mp3");

  pthread_exit(NULL);
  return NULL;
}
using namespace std;
int main()
{
	pthread_t p1;
	pthread_create(&p1,NULL,fun,NULL);

	pthread_join(p1,NULL);

  return 0;
}