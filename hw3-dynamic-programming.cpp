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
        f[i]=min(9,10-i+1)*f[i-1]; //���ǵ�i�����֣���min(9,10-i+1)��ѡ�� 
        g[i]=g[i-1]+f[i]; //��0~10^n�з��ϴ𰸵����������ۼ� 
    }
    return g[n];
}

int solve_opt(int n) {
	if(n>10)n=10;
    int f[2],g[2];
    f[0]=1;g[0]=1;
    for(int i=1;i<=n;i++){
    	//���ٿռ䣬����ͬsolve���� 
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
		//����10�ĳ��ݣ�pw��ʾiλ���ܹ������� 
		pw[i&1]=p-p/10;
		//��iλ���в�����Ҫ��Ĵ�����
		//����i-1λ���ظ��Ĵ�(��ʱ��iλ������ѡ)
		//��i-1λ�Ϸ��� (ʹ���Ϊ���Ϸ�ֻҪ������ѡ��i-1��������ѡһ��) 
		f[i&1]=f[(i&1)^1]*10+(pw[(i&1)^1]-f[(i&1)^1])*(i-1);
		 //��0~10^n�Ĵ��ۼ� 
		g[i&1]=g[(i&1)^1]+f[i&1];
	}
	//��0~nλ��������ȥ���Ϸ��𰸼�Ϊ���մ� 
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
