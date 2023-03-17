
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void Task1(){
	float a, b, c;
	cout << "Введите первое число - ";

	cin >> a;
	cout << "Введите второе число - ";
	cin >> b;
	cout<< "Сумма:"<<endl;
	c = a + b;
	cout<<c<<endl;
	cout<< "Разность:"<<endl;
	c = a - b;
	cout<<c<<endl;
	cout<< "Произведение:"<<endl;
	c = a * b;
	cout<<c<<endl;
	cout<< "Частное:"<<endl;
	c = a/b;
	cout<<c<<endl;
	cout<< "Среднее арифметическое:"<<endl;
	c = (a+b)/2;
	cout<<c<<endl;
}

void Task2(){
	int bread=3,sausage=4,kefir=2,cheese=5,command,milk=7,value;
	float price_bread=25.60,price_sausage=156.30,price_kefir=74.00,price_cheese=120.45,price_milk=65.68,itog;
	while(command!=0){
		cout<<"Доступно "<<bread<<" хлеба Цена: "<<price_bread<<endl;
		cout<<"Доступно "<<sausage<<" колбасы Цена: "<<price_sausage<<endl;
		cout<<"Доступно "<<kefir<<" кефира Цена: "<<price_kefir<<endl;
		cout<<"Доступно "<<cheese<<" сыра Цена: "<<price_cheese<<endl;
		cout<<"Доступно "<<milk<<" сыра Цена: "<<price_milk<<endl;
		cout<<"1 - хлеб"<<'\n'<<"2 - колбаса "<<'\n'<<"3 - кефир"<<'\n'<<"4 - сыр\n"<<"5 - молоко\n"<<'\n'<<"0 - выход"<<'\n'<<endl;
		
		cout<<"Введите товар "<<endl;
		cin>>command;
		if(command==1){
			cout<<"Введите количество"<<endl;
			cin>>value;
			if(value>bread){
				cout<<"Нет столько товара\n"<<endl;
			}
			else{
				bread-=value;
				itog+=price_bread*value;
				cout<<"Итог: "<<itog<<endl;
			}
		}
		if(command==2){
			cout<<"Введите количество"<<endl;
			cin>>value;
			if(value>sausage){
				cout<<"Нет столько товара"<<endl;
			}
			else{
				sausage-=value;
				itog+=price_sausage*value;
				cout<<"Итог: "<<itog<<endl;
			}
		}
		if(command==3){
			cout<<"Введите количество"<<endl;
			cin>>value;
			if(value>kefir){
				cout<<"Нет столько товара"<<endl;
			}
			else{
				kefir-=value;
				itog+=price_kefir*value;
				cout<<"Итог: "<<itog<<endl;
			}
		}
		if(command==4){
			cout<<"Введите количество"<<endl;
			cin>>value;
			if(value>cheese){
				cout<<"Нет столько товара"<<endl;
			}
			else{
				cheese-=value;
				itog+=price_cheese*value;
				cout<<"Итог: "<<itog<<endl;
			}
		}
		if(command==5){
			cout<<"Введите количество"<<endl;
			cin>>value;
			if(value>milk){
				cout<<"Нет столько товара"<<endl;
			}
			else{
				milk-=value;
				itog+=price_milk*value;
				cout<<"Итог: "<<itog<<endl;
			}
		}
	}
}
void Task3(){
	float x;
	cout<<"Введите длину стороны куба";
	cin>>x;
	float itog;
	itog=6*x*x;
	cout<<"Площадь поверхности куба: "<<itog<<endl;
	itog=x*x*x;
	cout<<"Объём куба: "<<itog<<endl;
	
}
void Task4(){
	int f_number,s_number,user_number,itog;
	cout<<"Введите первое число"<<endl;
	cin>>f_number;
	cout<<"Введите второе число"<<endl;
	cin>>s_number;
	itog=f_number*s_number;
	cout<<"Введите результат их произведения для проверки ваших знаний"<<endl;
	cin>>user_number;
	if(itog==user_number){
		cout<<"Поздравляю, это правильно. Произведение равно: "<<itog<<endl;
	}
	else {
		cout<<"К сожалению это не правильно. Произведение равно: "<<itog<<endl;
	}
}
void Task5(){
	int box=16, value;
	for(int i=0;box>0;i++){
		cout<<"Сколько загрузить ящиков в "<<i+1<<"-ю фуру?"<<endl;
		if(value>box){
			break;
		}
		else{
			cin>>value;
			box-=value;
			cout<<"Осталось "<<box<<" ящиков";
		}
	}
}
void Task6(){
	srand(time(NULL));
	int arr[50],x=2;
	for(int i=0;i<50;i++){
		while(x%2==0){
			x=rand()%100;
		}
		arr[i]=x;
		x=2;
		cout<<arr[i]<<endl;
	}
}
void Task7(){
	srand(time(NULL));
	string arr[28];
	int r,date;
	for(int i=0;i<28;i++){
		r=rand()%(6-0);
		if(r==0){
			arr[i]="Нет соревнований на этот день";
		}
		if(r==1){
			arr[i]="Соревнование по футболу";
		}
		if(r==2){
			arr[i]="Соревнование по баскетболу";
		}
		if(r==3){
			arr[i]="Соревнование по волейболу";
		}
		if(r==4){
			arr[i]="Соревнование по теннису";
		}
		if(r==5){
			arr[i]="Соревнование по шахматам";
		}
	}
	for(;;){
		cout<<"Введите дату [1-28] \nДля выхода введите -1\n"<<endl;
		cin>>date;
		if (date==-1){
			break;
		}
		else{
			cout<<arr[date-1]<<endl;
		}
		
	}

}
int main() {
	setlocale(LC_ALL, "rus");
	int command;
	for(;;){
		cout<<"Введите номер задачи для её выполнения \nДля выхода введите -1"<<endl;
		cin>>command;
		if(command==1){
			Task1();
		}
		if(command==2){
			Task2();
		}
		if(command==3){
			Task3();
		}
		if(command==4){
			Task4();
		}
		if(command==5){
			Task5();
		}
		if(command==6){
			Task6();
		}
		if(command==7){
			Task7();
		}
		if(command==-1){
			break;
		}
	}
}