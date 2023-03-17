#include <iostream>
#include <pthread.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define QUEUE_SIZE 5
#define COUNT_CLIENTS 7
#define FILE_NAME "shared_memory"
#define LINE_SIZE 12
using namespace std;
sem_t sQueue;
sem_t sHandleQuery;
sem_t sReadResponse;
pthread_mutex_t mAccess = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mComeInToQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mStdoutAccess = PTHREAD_MUTEX_INITIALIZER;

struct Query{
  char line[LINE_SIZE]={0};
  char subline[LINE_SIZE]={0};
  int response=0;
  
  Query(char line[LINE_SIZE],char subline[LINE_SIZE],int response){
    for(int i=0;i < LINE_SIZE ; i++){
      this->line[i] = line[i];
      this->subline[i] = subline[i];
    }
    this->response = response;
  }
};

int
getSharedBlock(std::string fileName){
  key_t key;
  key = ftok(fileName.c_str(),0);

  return shmget(key,1*sizeof(Query),IPC_CREAT | 0666);
}

void *
attachMemoryBlock(int blockId){
  if(blockId==-1){
    return NULL;
  }

  void* result;
  result=(void*)shmat(blockId,NULL,0);
  if(result == (void*)-1){
    return NULL;
  }

  return result;
}

void
detachMemoryBlock(void* block){
  shmdt(block);
}

void
destroyMemoryBlock(int blockId){
  shmctl(blockId,IPC_RMID,NULL);
}

int
performQueryToServer(std::string line, std::string subline){
    return 1;
}

int
indexLastSubline(std::string line,std::string subline){
  int lastIndex=-1;
  int isSub=true;
  for(int i=0; i < line.length() ; i++){
    for(int j=0; j < subline.length(); j++){
      if(i+j >= line.length()){
        isSub=false;
        break;
      }
      if(line[i+j]!=subline[j]){
        isSub=false;
        break;
      }
    }
    if(isSub){
      lastIndex=i;
    }
    isSub=true;
  }

  return lastIndex;
}

static void *
serverThread(void* something){
  int i=0;
  while(i<5){
    sem_wait(&sHandleQuery);
    system("sleep 0");
    int blockId;
    Query* shm;
    blockId = getSharedBlock(FILE_NAME);
    shm = (Query*) attachMemoryBlock(blockId);
    shm->response = indexLastSubline(shm->line, shm->subline);
    detachMemoryBlock(shm);
    sem_post(&sReadResponse);
    i++;
  }
  pthread_exit(NULL);
}

static void *
clientThread(void* arg){
  int countFreePlaces;
  Query* passedQuery=(Query*) arg;
  sem_getvalue(&sQueue,&countFreePlaces);

  pthread_mutex_lock(&mComeInToQueue);
  if(!countFreePlaces){
    pthread_mutex_lock(&mStdoutAccess);
    std::cout <<"CLIENT{"<< std::endl;
    std::cout <<"    line: " << passedQuery->line << std::endl;
    std::cout <<"    subline: " << passedQuery->subline << std::endl;
    std::cout <<"    response: error: the queue is full" << std::endl;
    std::cout <<"}"<< std::endl << std::endl;
    pthread_mutex_unlock(&mStdoutAccess);
    pthread_mutex_unlock(&mComeInToQueue);
    pthread_exit(NULL);
  } else{
    sem_wait(&sQueue);
    pthread_mutex_unlock(&mComeInToQueue);
  }


  pthread_mutex_lock(&mAccess);
  int blockId;
  Query* shm;

  blockId = getSharedBlock(FILE_NAME);
  shm = (Query*) attachMemoryBlock(blockId);
  for(int i = 0 ; i < LINE_SIZE ; i++){
    shm->line[i]=passedQuery->line[i];
    shm->subline[i]=passedQuery->subline[i];
  }
  sem_post(&sHandleQuery);
  sem_wait(&sReadResponse);
  pthread_mutex_lock(&mStdoutAccess);
  std::cout <<"CLIENT{";
  std::cout <<"    line: " << shm->line;
  std::cout <<"    subline: " << shm->subline;
  std::cout <<"    response: " << shm->response;
  std::cout <<"}"<< std::endl;
  pthread_mutex_unlock(&mStdoutAccess);
  detachMemoryBlock(shm);
  destroyMemoryBlock(blockId);
  pthread_mutex_unlock(&mAccess);

  pthread_exit(NULL);
}

int
main() {
  pthread_t serverPid;
  pthread_t clientPids[COUNT_CLIENTS];

  Query queryes[7]={
    {"i love c++","love",0},
    {"fbgdebd","b",0},
    {"","gdhb",0},
    {"ttty jjf ssss","s",0},
    {"aa cc aacc","cc",0},
    {"v","v",0},
    {"ttttt","tt",0}
  };
  


  sem_init(&sQueue,0,QUEUE_SIZE);
  sem_init(&sHandleQuery,0,0);
  sem_init(&sReadResponse,0,0);

  pthread_create(&serverPid,NULL,&serverThread,NULL);
  for(int i=0 ; i < COUNT_CLIENTS ; i++){
    pthread_create(&clientPids[i],NULL,&clientThread,(void*)&queryes[i]);
  }

  for(int i =0 ; i < COUNT_CLIENTS ; i++){
    pthread_join(clientPids[i],NULL);
  }

  pthread_join(serverPid,NULL);

  sem_destroy(&sQueue);
  sem_destroy(&sHandleQuery);
  sem_destroy(&sReadResponse);
}
