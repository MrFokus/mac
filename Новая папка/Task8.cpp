#include <iostream>

using namespace std;

int Rand(int f,int s,int i,int arr[][2]){
	
	for(int j=0;j<i;j++){
		if((arr[j][0]==f)&&(arr[j][1]==s)||(arr[j][0]==s)&&(arr[j][1]==f)){
			return 1;
			break;
		}
	}
	return 0;
}
void Task_8(){
	int arr[10][2];
	int f,s,counter=0,value,flag=0;
	for(int i=0;i<10;i++){
		int f=rand()%9+1;
		int s=rand()%9+1;
		flag=Rand(f,s,i,arr);
		if(flag==1){
			i--;
			flag=0;
			continue;
		}
		else{
			arr[i][0]=f;
			arr[i][1]=s;
		}

		
		cout<<f<<'x'<<s<<'=';
		cin>>value;
		if(value==f*s){
			counter++;
		}
		else{
			cout<<"Вы ошиблись! "<<f<<'x'<<s<<'='<<f*s<<endl;
		}
	}
	cout<<"Правильных ответов: "<<counter<<endl;
	if(counter==10){
		cout<<"Ваша оценка - отлично";
	}
	if((counter==9)||(counter==8)){
		cout<<"Ваша оценка - хорошо";
	}
	if((counter==7)||(counter==6)){
		cout<<"Ваша оценка - удовлетворительно";
	}
	if(counter<6){
		cout<<"Ваша оценка - плохо";
	}
}

int main(int argc, char *argv[]) {
	Task_8();
}