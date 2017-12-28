arr=eval(input())
arr=list(arr)
dp=arr
for k in range(2,len(arr)) :
	dp[k]=min(dp[k-1]+arr[k],dp[k-2]+arr[k])
print(dp[len(dp)-1])

