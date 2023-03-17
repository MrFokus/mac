#include <iostream>
#include <math.h>

using namespace std;

float f_x(float x){
	float result=pow(x,4)-14*pow(x,3)+60*pow(x,2)-70*x;
	return result;
}
int main(int argc, char *argv[]) {
	float a=-2,b=3,x1,x2,f_x1,f_x2,L,e=0.001,delta=e/2;
	cout<<"                      "<<"x1"<<"        "<<"x2"<<"           "<<"f(x1)"<<"          "<<"f(x2)"<<endl;
	for(int i=0;abs(b-a)>=e;i++){
		x1=(a+b-delta)/2;
		x2=(a+b+delta)/2;
		cout<<"Номер итерации:"<<i+1<<"   ";
		cout<<"x1="<<trunc(x1 * 1000.0)/1000.0<<"   "<<"x2="<<trunc(x2 * 1000.0)/1000.0<<"       ";
		f_x1=f_x(x1);
		f_x2=f_x(x2);
		cout<<"f(x1)="<<trunc(f_x1 * 1000.0)/1000.0<<"   "<<"f(x2)="<<trunc(f_x2 * 1000.0)/1000.0;
		if(f_x1<f_x2){
			b=x2;
		}
		else {
			a=x1;
		}
		cout<<'\n';
	}
	
}