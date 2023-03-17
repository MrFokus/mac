create_matrix<-function(n){
  a<-matrix(runif(n*n),nrow=n,ncol=n)
  k<-3
  m<-(n-2)
  for (i in 1:m){
    for (j in k:n){
      a[j,i]<-0
      a[i,j]<-0
    }
    k<-k+1
  }
  b<-runif(n)
  v=array(1:n)
  u=array(1:n)
  x=array(1:n)
  print(v)
  print(u)
  print(x)
  u[1]<- ((b[1])/(a[1,1]))
  v[1]<-(-a[1,2]/a[1,1])
  m<-n-1
  for(i in 2:m){
    v[i]<-(-a[i,i+1])/(a[i,i]+a[i,i-1]*v[i-1])
    u[i]<-(b[i]-a[i,i-1]*u[i-1])/(a[i,i]+a[i,i-1]*v[i-1])
  }
  v[n]<-0
  u[n]<-(b[n]-a[n,n-1]*u[n-1])/(a[n,n]+a[n,n-1]*v[n-1])
  x[n]=u[n]
  m<-n-1
  for(i in m:1){
    x[i]=v[i]*x[i+1]+u[i]
  }
  print("Трёхдиагональная матрица")
  print(a)
  print("Итоговые значения матрицы")
  print(b)
  print("Итоговые значения x")
  print(x)
}
create_matrix(5)

#Защита
n = 5
a<-matrix(runif(n*n),nrow=n,ncol=n)
print(a)
for(i in 1:n){
  for(j in 1:n){
    a[i,j]=a[j,i]
  }
}
print(a)
k<-1
m<-(n-2)
for (i in 1:m){
  for (j in k:n){
    if(j!=i&a[i,j]!=0){
      a[i,j]=1/a[i,j]
    }
  }
  k<-k+1
}
print(a)
