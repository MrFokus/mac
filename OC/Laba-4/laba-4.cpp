#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
 
//размеры матриц
#define N 5
#define M 5
 
//специальная структура для данных потока
typedef struct{
	int rowN; //номер обрабатываемой строки
	int rowSize; 
	int Max;
	int Min;
	//размер строки
	int** resArr;

} pthrData;
void* threadFunc(void* thread_data){
	
	//получаем структуру с данными
	pthrData *data = (pthrData*) thread_data;
	for(int i = 0; i < data->rowSize; i++){
		data->resArr[data->rowN][i] = rand()%10;
	}
	return NULL;
}
void* MaxElement(void* thread_data){
	int* output = new int[2];
	int** data = (int**)thread_data;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(data[i][j]>=data[0][0]){
				data[0][0]=data[i][j];
			}
		}
	}
	output[0]=data[0][0];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(data[i][j]<=data[0][0]){
				data[0][0]=data[i][j];
			}
		}
	}
	output[1]=data[0][0];

	return (void*)output;
}

int main(){
	//выделяем память под двумерные массивы
	int** resultMatrix = (int**) malloc(N * sizeof(int*));
 
	//выделяем память под элементы матриц
	for(int i = 0; i < M; i++){

		resultMatrix[i] = (int*) malloc(M * sizeof(int));
	}
	//выделяем память под массив идентификаторов потоков
	pthread_t* threads = (pthread_t*) malloc(N+1 * sizeof(pthread_t));
	//сколько потоков - столько и структур с потоковых данных
	pthrData* threadData = (pthrData*) malloc(N * sizeof(pthrData));
 
	//инициализируем структуры потоков
	for(int i = 0; i < N; i++){
		threadData[i].rowN = i;
		threadData[i].rowSize = M;
		threadData[i].resArr = resultMatrix;
 
		//запускаем поток
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}
	//ожидаем выполнение всех потоков
	
	for(int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);
	for(int i = 0; i < N; i++){
		std::cout<<'\n';
		for(int j = 0; j < N; j++){
			std::cout<<"  "<<resultMatrix[i][j];
		}
	}
	pthread_t t1;
	pthrData Date;
	void* res;
	pthread_create(&t1, NULL, MaxElement, resultMatrix);
	pthread_join(t1, &res);
	int* output=new int[2];
	output=(int*)res;
	std::cout<<'\n'<<(output[0])<<std::endl;
	std::cout<<(output[1])<<std::endl;
	//освобождаем память
	free(threads);
	free(threadData);
	for(int i = 0; i < N; i++){

		free(resultMatrix[i]);
	}

	free(resultMatrix);
	return 0;
}