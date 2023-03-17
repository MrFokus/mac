#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include  <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    cout<<"im child"<<argv[0];
    int fd_f = open(argv[1], O_RDONLY);
    size_t count=10;
    int n=0;
    string arg[3] = {argv[3], argv[4],argv[5]};
    off_t size_n = lseek(fd_f,0, SEEK_END); 
    lseek(fd_f, 0, SEEK_SET);
    char buff[size_n+1];
    ssize_t numRead = read(fd_f, buff, size_n);
    char newbuff[size_n];
    int newbuff_size=0;
    for (int i=0, currentline=1; i<size_n; i++) {
        if(currentline==stoi(arg[0])||currentline==stoi(arg[1])||currentline==stoi(arg[2])){
            newbuff[newbuff_size]=buff[i];
            newbuff_size++;
        }
        if(buff[i]=='\n'){
            currentline++;
        }
    }
    int fd_l = open(argv[2], O_RDWR| O_CREAT);
    off_t curr = lseek(fd_l, 0, SEEK_END);
    ssize_t numWrite = write(fd_l, newbuff, newbuff_size);
    close(fd_f);
    chmod(argv[2], S_IRUSR | S_IWUSR);
    close(fd_l);
}