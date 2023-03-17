#include <iostream>
#include <math.h>
#include <locale>
using namespace std;
float alpha=2,betta=2,epsilant=0.0001;
float valueFunc(float * x1){
	float f=pow(x1[0]-2,2)+pow(x1[1]-5,2)+pow(x1[2]+2,4);
	return f;
}
void print(float * x1){
	cout<<"(";
	for(int j=0;j<3;j++){
		if(j!=2)
			cout<<x1[j]<<", ";
		else
			cout<<x1[j];
	}
	cout<<")"<<endl;
}
void sl(float* x1,float* x0){
	int i;
	for(i=0;i<3;i++){
		x1[i]=x0[i];	}
}

void exploratory_search(float *x0,float* x1,float h){
	int i,flag=0;
	sl(x1,x0);
	for(i=0;i<3;i++){
		if(h>epsilant){
			switch (flag) {
				case 0:
					x1[i]+=h;
					if(valueFunc(x0)>valueFunc(x1)){
						flag=0;
						print(x1);
						cout<<"H= "<<h<<" f(x1)= "<<valueFunc(x1)<<"  <  f(x0)= "<<valueFunc(x0)<<" -> \033[1;32mУдачно\033[0m"<<endl;
						continue;
					}
					else{
						flag=1;
						cout<<"H= "<<h<<" f(x1)= "<<valueFunc(x1)<<"  >  f(x0)= "<<valueFunc(x0)<<" -> \033[1;31mНеудачно\033[0m"<<endl;
						print(x1);
						x1[i]-=h;
						
											}
				case 1:
					x1[i]-=h;
					if(valueFunc(x0)>valueFunc(x1)){
						flag=0;
						print(x1);
						cout<<"H= "<<h<<" f(x1)= "<<valueFunc(x1)<<"  <  f(x0)= "<<valueFunc(x0)<<" -> \033[1;32mУдачно\033[0m"<<endl;
						continue;
					}
					else{
						print(x1);
						cout<<"H= "<<h<<" f(x1)= "<<valueFunc(x1)<<"  >  f(x0)= "<<valueFunc(x0)<<" -> \033[1;31mНеудачно\033[0m"<<endl;
						x1[i]+=h;
						h=h/alpha;
						flag=0;
						i=0;
					}
			}
		}
		else break;
	}
}
float* search_obr(float* x1,float* x0,float b){
	int i,arr[3];
	float* x_2=new float[3];
	for(i=0;i<3;i++){
		x_2[i]=x1[i]+b*(x1[i]-x0[i]);
	}
	return x_2;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"rus");
	float h=1, x0[3]={4,-2,-3},znach,flag=0;
	float* x1 = new float[3];
	float* x2 = new float[3];
	cout<<"    H = "<<h<<", Альфа = "<<alpha<<", Бетта = "<<betta<<endl;
	for(int i=0;flag==0;i++){
		cout<<"\033[1;36mНомер итерации\033[0m "<<i+1<<endl<<endl;
		cout<<"  Исследующий поиск"<<endl;
		exploratory_search(x0,x1,h);
		cout<<"    X0 = ";
		print(x0);
		cout<<"    X1 = ";
		print(x1);
		znach=valueFunc(x0);
		cout<<"    F(x0) = "<<znach<<endl;
		znach=valueFunc(x1);
		cout<<"    F(x1) = "<<znach<<endl;
		x2=search_obr(x1, x0,betta);
		if(valueFunc(x2)>valueFunc(x1)){
			cout<<"\033[1;31mИсследование не удалось\033[0m\n"<<endl;
			cout<<"    X2 = ";
			print(x2);
			znach=valueFunc(x1);
			cout<<"    F(x1) = "<<znach<<endl;
			znach=valueFunc(x2);
			cout<<"    F(x2) = "<<znach<<endl;
			cout<<"  Новая базисная точка: ";
			print(x1);
			sl(x0,x1);
			cout<<endl;
			
		}
		else{
			cout<<"\033[1;32mИсследование удалось\033[0m\n"<<endl;
			cout<<"    X2 = ";
			print(x2);
			znach=valueFunc(x1);
			cout<<"    F(x1) = "<<znach<<endl;
			znach=valueFunc(x2);
			cout<<"    F(x2) = "<<znach<<endl;
			cout<<"  Новая базисная точка: ";
			print(x2);
			sl(x0,x2);
			cout<<endl;
			if(valueFunc(x2)<=0.0001){
				flag=1;
			}
		}
	}
	
}