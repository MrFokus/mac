arr=[20,10,6,6,1,5,3]
stop=False
valueStop=0;
i=2

while(stop==False):
	i+=1
	for j in range(0 , 7 , 1):
		if arr[i]%2==0:
			count=arr[j]
			arr[j]=arr[i]
			arr[i]=count
			valueStop+=1
			break
		if valueStop==0:
			stop=True
		else:
			valueStop=0
print(arr)