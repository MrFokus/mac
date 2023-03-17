n<- as.numeric(readline(promp="Input size of matrix"))
#В функции fir_step матрица приводится к трёх-диагональному виду
fir_step<-function(n){
  j=2
  Matr<-diag(round(runif(8, min=1, max=10),2) , nrow = n, ncol=n)
  n=n-1
  for(i in 1:n){
    Matr[i, j]<-round(runif(1, min=1, max=10),2)
    j=j+1
  }
  n=n+1
  j=1
  for(i in 2:n){
    Matr[i, j]<-round(runif(1, min=1, max=10),2)
    j=j+1
  }
  print(Matr)
  return(as.matrix(Matr))
}
sec_step<-function(Matr){
  vector_r<-matrix(round(runif(n, min=1, max=10),2), nrow=1, ncol=n) #"столбец" свободных членов
  print("столбец свободных членов")
  print(vector_r)
  vector_v<-matrix(nrow=1, ncol=n)
  vector_u<-matrix(nrow=1, ncol=n)
  vector_x<-matrix(nrow=1, ncol=n)
  for(i in 1:n){
    if(i==1){
      vector_u[1,1]=(vector_r[1,1]/Matr[1,1])
      vector_v[1,1]=(-Matr[1,2]/Matr[1,1])
    }
    else if(i==n){
      vector_v[1, n]=0
      vector_u[1, n]=(vector_r[1, n]-Matr[n,n-1]*vector_u[1, n-1])/(Matr[n,n]+Matr[n,n-1]*vector_v[1, n-1])
    }
    else{
      vector_v[1,i]=(-Matr[i, i+1])/(Matr[i,i]+Matr[i,i-1]*vector_v[1, i-1])
      vector_u[1,i]=(vector_r[1, i]-Matr[i,i-1]*vector_u[1,i-1])/(Matr[i,i]+Matr[i,i-1]*vector_v[1, i-1])
    }
  }
  vector_x[1, n]=vector_u[1, n]
  j=n
  j=j-1
  for(i in j: 1){
    vector_x[1, i]=vector_v[1, i]*vector_x[1, i+1]+vector_u[1, i]
  }
  vector_x2<-matrix(nrow=1, ncol=n)
  # for(i in 1: n){
  #   if(i==1){
  #     vector_x2[1,1]=Matr[1,1]*vector_x[1,1]+Matr[1,2]*vector_x[1,2]
  #   }
  #   else if(i==n){
  #     vector_x2[1,n]=Matr[3,2]*vector_x[1,2]+Matr[3,3]*vector_x[1,3]
  #   }
  #   else{
  #     vector_x2[1,2]=Matr[2,1]*vector_x[1,1]+Matr[2,2]*vector_x[1,2]+Matr[2,3]*vector_x[1,3]
  #   }
  # }
  ########
  print(Matr)
  print(vector_x)
  for(i in 1: n){
    for(j in 1:n){
      vector_x2[1,i]= vector_x2[1,i]+Matr[i,j]*vector_x[1,j]
    }
  }
  ########
  print("Проверка")
  print(vector_x2)
  return(as.matrix(vector_x))
}
matr<-fir_step(n) #вызов первой функции
sec_step(matr) #вызов второй функции
