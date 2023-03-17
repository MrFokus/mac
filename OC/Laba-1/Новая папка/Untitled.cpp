#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include  <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    int fd_f = open(argv[1], O_RDONLY);
    size_t count=10;
    int n=0;
    off_t size_n = lseek(fd_f, 0, SEEK_END); 
    lseek(fd_f, 0, SEEK_SET);
    char buff[size_n+1];
    ssize_t numRead = read(fd_f, buff, size_n);
    char newbuff[size_n];
    int newbuff_size=-1;
    
    for(int i=0; i<size_n;i++){
        if(buff[i]=='\n'){
            n++;
        }
        if((n==atoi(argv[3])-1)||(n==atoi(argv[4])-1)||(n==atoi(argv[5])-1)||(n==atoi(argv[6])-1)){
            i++;
            newbuff_size++;
            while(buff[i]!='\n'){
                newbuff[newbuff_size]=buff[i];
                i++;
                newbuff_size++;
            }
            newbuff[newbuff_size]='\n';
            i=i-1;
        }
    }
    cout<<newbuff;
    int fd_l = open(argv[2], O_RDWR);
    off_t curr = lseek(fd_l, 0, SEEK_CUR);
    ssize_t numWrite = write(fd_l, newbuff, newbuff_size);
    close(fd_f);
    close(fd_l);
}