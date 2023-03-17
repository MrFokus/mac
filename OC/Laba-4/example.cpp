#include <pthread.h>
#include <iostream>
#include <string.h>

static void * threadFunc(void* arg)
{
 char *s = (char *) arg;
 printf("%s", s);
 return (void *) strlen(s);
}
int
main(int argc, char *argv[])
{
 char a[]="Hello world\n";
 pthread_t t1;
 void *res;
 int s;
 s = pthread_create(&t1, NULL, threadFunc,&a);
 printf("Message from main()\n");
 s = pthread_join(t1, &res);
 printf("Thread returned %ld\n", (long) res);
 exit(EXIT_SUCCESS);
}