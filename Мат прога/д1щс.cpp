#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand(time(0));
	int arr[20];
	for (int i=0; i<20; i++) {
		arr[i]=rand()%10;
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	bool stop=false;
	int valueStop=0;
	for (int j=0;stop==false;j++) {
		for (int i=j; i<20; i++) {
			if(arr[i]%2==0){
				int count=arr[j];
				arr[j]=arr[i];
				arr[i]=count;
				valueStop++;
				break;
				
			}
		}
		if(valueStop==0){
			stop=true;
		}
		valueStop=0;
	}
	for (int i=0; i<20; i++) {
			cout<<arr[i]<<" ";
	}
}