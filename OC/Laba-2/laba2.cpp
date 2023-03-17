#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>
 
int main(){
  pid_t pid = fork();
  if(pid == 0){
    printf("Forked!\n");
    int pf = open("a.txt", O_RDWR|O_CREAT); //вот сюда перенаправим вывод
    dup2(pf, STDOUT_FILENO); //клонируем файловый дескриптор, теперь он открыт одновременно в pf и stdout
     //вывод в pf нам не нужен, закрываем
    int a =execl("/Users/german/Desktop/OC/Laba-1/out","laba.cpp","../Laba-1/first.txt", "../Laba-1/last.txt", "4", "7", "10", NULL); //вызовем какую-нибудь стандартную утилиту
    std::cout<<a;
  }else if(pid < 0){
    fprintf(stderr, "Some error on fork\n");
    return -1;
  }
  printf("Success!\n");
  wait(NULL);//дожидаемся завершения
  printf("Done\n");
}