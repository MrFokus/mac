#include <iostream>
using namespace std;


void task3(){
	for(;;){
		int command;
		cin>>command;
		int tmp=0, value=0;
		char str[1024];
			cin.getline(str,1024);
			for(int i=0;str[i]!='\0';i++){
				if(str[i]!=' '){
					value++;
				}
				else{
					if(value>tmp){
						tmp=value;
					}
					value=0;
				}
			}
		
			if(value>tmp){
				tmp=value;
			}
			cout<<tmp;
	}
}

int main(int argc, char *argv[]) {
	task3();
}