#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>
 
int main(){
  pid_t pid1 = fork();//создаём процесс

  if(pid1 == 0){
    printf("Forked!\n");
    int pf1 = open("proc1.txt", O_RDWR); //вот сюда перенаправим вывод
    system("cd /Users/german/Desktop/OC/Laba-2");//вызовем какую-нибудь стандартную утилиту
    system("g++ proc1.cpp -o proc1");
    dup2(pf1, STDOUT_FILENO);//клонируем файловый дескриптор, теперь он открыт одновременно в pf и stdout
    execl("./proc1"," ","first", NULL);
  }else if(pid1 < 0){
    fprintf(stderr, "Some error on fork\n");
    return -1;
  }
  pid_t pid2 = fork();//создаём процесс
  if(pid2 == 0){
    printf("Forked!\n");
    system("cd /Users/german/Desktop/OC/Laba-2");//bash
    int pf2 = open("proc2.txt", O_RDWR);
    dup2(pf2, STDOUT_FILENO);//перенаправляем вывод
    int pf3 = open("a.txt", O_RDONLY);
    dup2(pf3, STDIN_FILENO);//перенаправляем ввод
    system("g++ proc2.cpp -o proc2");
    execl("./proc2"," ","second", NULL);
    
  }else 
    if(pid2 < 0){
      fprintf(stderr, "Some error on fork\n");
      return -1;
    }
  pid_t pid5 = fork();//создаём процесс
  if(pid5 == 0){
    system("ls > a.txt");
    
  }else 
    if(pid5 < 0){
      fprintf(stderr, "Some error on fork\n");
      return -1;
    }
  
  
  printf("Success!\n");
  wait(NULL);//дожидаемся завершения
  wait(NULL);//дожидаемся завершения
  pid_t pid3 = fork();//создаём процесс
  if(pid3 == 0){
    printf("Forked!\n");
    system("cd /Users/german/Desktop/OC/Laba-2"); //bash
    int pf4 = open("proc2.txt", O_RDWR);
    int pf3 = open("a.txt", O_RDONLY);
    dup2(pf3, STDIN_FILENO); //перенаправляем ввод
    system("g++ proc3.cpp -o proc3"); //создаём файл out
    execl("./proc3"," ","third", NULL);
    
  }else if(pid3 < 0){
    fprintf(stderr, "Some error on fork\n");
    return -1;
  }
  wait(NULL);
  printf("Done\n");
}