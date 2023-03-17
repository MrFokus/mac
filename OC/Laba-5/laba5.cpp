#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
static char buff[20];
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

char gen_random() {
	static const char alphanum[] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int i=rand()%50;
	return alphanum[i];
}

static void * threadFunc(void *arg)
{
	usleep(100000);
	srand(time(0));
	
	int i,j,s;
	int position=*((int*)arg);
	for(j=0;j<20;j++){
		s = pthread_mutex_lock(&mtx);
		
			for(i=position*5-5;i<position*5;i++){
				char ch=gen_random();
				buff[j] = ch;
		}
		s = pthread_mutex_unlock(&mtx);
	}
	return NULL;
}
static void * WriteBuff(void *arg)
{
	int s;
		s = pthread_mutex_lock(&mtx);
		cout<<buff<<endl;
		s = pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc, char *argv[])
{
	for (int i=0;i<20;i++) {
		buff[i]='\0';
	}
	int position=rand()%4;
	pthread_t r1, r2, w1, w2,w3,w4;
	int s, arr[4]={-1,-1,-1,-1},flag=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			arr[j]=-1;
		}
		flag=0;
		for(;flag!=4;){
			position=rand()%4;
			if(arr[position]==-1){
				s = pthread_create(&r1, NULL, threadFunc, &position);
				flag++;
				arr[position]=position;
			}
			else
				continue;
			position=rand()%4;
			if(arr[position]==-1){
				s = pthread_create(&r2, NULL, threadFunc,&position);
				flag++;
				arr[position]=position;
			}
			
		}
		
		s = pthread_join(r1, NULL);
		s = pthread_join(r2, NULL);
		s = pthread_create(&w1, NULL, WriteBuff, NULL);
		s = pthread_create(&w2, NULL, WriteBuff, NULL);
		s = pthread_create(&w3, NULL, WriteBuff, NULL);
		s = pthread_create(&w4, NULL, WriteBuff, NULL);
		s = pthread_join(w1, NULL);
		s = pthread_join(w2, NULL);
		s = pthread_join(w3, NULL);
		s = pthread_join(w4, NULL);
		
		
	}
}
