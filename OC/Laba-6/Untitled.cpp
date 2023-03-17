#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int G_D=5;
int R_D=20;
sem_t sem_rec_data;
sem_t sem_post_data;
pthread_t server;
pthread_t client;
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

struct Buffer{
  int data[50] = {0};
  int inputPoint = 0;
  int outputPoint = 0;
  int cl_data[50] = {0};
};

void printBuffer(Buffer * buffer){
  for(int value: buffer->data){

    if(value!=0)
      cout << value << " " ;
    else
      cout << value << " " ;

  } 
}

void printBufferCL(Buffer * buffer){
  for(int value: buffer->cl_data){
    
    if(value!=0)
      cout << value << " " ;
    else
      cout << value << " " ;
    
  } 
}

static void* serverThread(void* buffer){
  Buffer * buf = (Buffer *) buffer;
  
  for(int j = 0 ; j < 10 ; j++){

    for(int i = 0 ; i < G_D ; i++){
      if(i<=0){
        sem_wait(&sem_rec_data);
      } else {
        sem_trywait(&sem_rec_data);
      }
      if(buf->inputPoint==50){
        buf->inputPoint=0;
      }

      buf->data[buf->inputPoint] = rand() % 9 + 1;
      buf->inputPoint++;
    }

    pthread_mutex_lock(&mutx);
    cout << "Server" << endl;
    printBuffer(buf);
    cout << endl;
    pthread_mutex_unlock(&mutx);
    // if(j==9){
    //     for(int i=0 ; i < G_D+10 ; i++){
    //   sem_post(&sem_post_data);
    // }


    for(int i=0 ; i < G_D ; i++){
      sem_post(&sem_post_data);
    }

    }
    for(int i=0 ; i < 10 ; i++){
      sem_post(&sem_post_data);
    }
  pthread_exit(NULL);
}

static void * clientThread(void* buffer){
  Buffer * buf = (Buffer *) buffer;
  
  for(int j = 0 ; j < 3 ; j++){
    for(int i = 0 ; i < R_D ; i++){
      sem_wait(&sem_post_data);
      if(buf->outputPoint==50){
        buf->outputPoint=0;
      }
      buf->cl_data[buf->outputPoint] = buf->data[buf->outputPoint];
      buf->data[buf->outputPoint] = 0;
      buf->outputPoint++;
    }

    pthread_mutex_lock(&mutx);
    cout << "Client" << endl;
    printBufferCL(buf);
    cout << endl;
    pthread_mutex_unlock(&mutx);

    int currentValueRD;
    sem_getvalue(&sem_rec_data,&currentValueRD);
    if(currentValueRD < R_D){
      int sizeOfReqiuredData = R_D + currentValueRD;
      for(int i=0 ; i < sizeOfReqiuredData ; i++){
        sem_post(&sem_rec_data);
      }
    }


  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Buffer buffer;

  sem_init(&sem_rec_data,0,R_D);
  sem_init(&sem_post_data,0,0);
  pthread_create(&client,NULL,&clientThread,&buffer);
  pthread_create(&server,NULL,&serverThread,&buffer);

  pthread_join(server,NULL);
  pthread_join(client,NULL);
  sem_destroy(&sem_rec_data);
  sem_destroy(&sem_post_data);
  return 0;
}
