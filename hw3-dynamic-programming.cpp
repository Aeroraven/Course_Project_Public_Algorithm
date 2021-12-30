#include <iostream>
#include <algorithm> 
#include <cstdlib>
#include <ctime> 
#include <vector>
using namespace std;

int solve(int n) {
	if(n>10)n=10;
    int f[20],g[20];
    f[0]=1;g[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=min(9,10-i+1)*f[i-1]; //考虑第i个数字，有min(9,10-i+1)种选择 
        g[i]=g[i-1]+f[i]; //将0~10^n中符合答案的总数进行累加 
    }
    return g[n];
}

int solve_opt(int n) {
	if(n>10)n=10;
    int f[2],g[2];
    f[0]=1;g[0]=1;
    for(int i=1;i<=n;i++){
    	//减少空间，其余同solve函数 
        f[i&1]=min(9,10-i+1)*f[(i&1)^1];
        g[i&1]=g[(i&1)^1]+f[i&1];
    }
    return g[n&1];
}


int solve_rev(int n){
	if(n>10)n=10;
	int pw[2],f[2],g[2],p;
	pw[0]=1,p=1,f[0]=0,g[0]=0;
	for(int i=1;i<=n;i++){
		p*=10;
		//处理10的乘幂，pw表示i位数总共的数量 
		pw[i&1]=p-p/10;
		//求i位数中不符合要求的答案数量
		//包括i-1位含重复的答案(此时第i位可以任选)
		//和i-1位合法答案 (使其变为不合法只要从其已选的i-1个数中任选一个) 
		f[i&1]=f[(i&1)^1]*10+(pw[(i&1)^1]-f[(i&1)^1])*(i-1);
		 //将0~10^n的答案累加 
		g[i&1]=g[(i&1)^1]+f[i&1];
	}
	//用0~n位数总数减去不合法答案即为最终答案 
	return p-g[n&1];
}

int main(){
	int n,ans;
	cin>>n;
	ans=solve_opt(n);
	cout<<ans;
	ans=solve(n);
	return 0;
}
