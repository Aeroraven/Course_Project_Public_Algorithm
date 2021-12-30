
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
using namespace std;

template <class T> inline T Min(const T& a, const T& b) {
	return (a < b) ? a : b;
}
int locker_solve(char* srcString, char* destString) {
	int len = strlen(srcString);
	//f[i][j][k]表示srcString和destString的前i个字符串相等，第i+1位上移j，第i+2位上移k的最小移动代价
	//其中0<=j<10，0<=k<10
	//由于DP转移式中，f[i][j][k]不会使用f[i-4]及之前的状态，故本处对数组第一维进行滚动，减小空间复杂度
	//注释用g[i][j][k]表示滚动前的f数组
	int f[4][10][10];
	//将f[i][j][k]全置为INF
	const int INF = 1 << (sizeof(int) * 8 - 2);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				f[i][j][k] = INF;
			}
		}
	}
	//处理第一位字符(初始条件)
	int t1 = 0;
	int t2;
	int t3;
	int p, q;
	f[0][0][0] = 0;
	//此时考虑后2位数向上移动的状态，若第二位上移i,则第三位可以上移j，0<=j<=i
	//该情况代价为i
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= i; j++) {
			f[0][i][j] = i;
		}
	}
	//此时考虑后2位数向下移动的状态，若第二位下移i,则第三位可以下移j，i<=j<=0
	//该情况代价为-i。简化处理，将i,j对10取余
	for (int i = 5; i <= 10; i++) {
		for (int j = i; j <= 10; j++) {
			f[0][i % 10][j % 10] = 10 - i;
		}
	}
	//处理后续的数位
	for (int i = 0; i < len; i++) {
		//对于i非零的情况，由于滚动数组f[i][j][k]此时存储的值实际上对应于g[i-4][j][k]
		//故需要先将其置为INF
		if (i != 0) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					f[i & 3][j][k] = INF;
				}
			}
		}
		//情况1：转动i-2,i-1和i三位数字，即 #xx[x]**,[x]表示第i为数字，x为要转动的数字，#为已经相同的数字
		if (i - 3 >= 0) {
			t1 = (-srcString[i] + destString[i] + 10) % 10;
			t2 = (-srcString[i - 1] + destString[i - 1] + 10) % 10;
			t3 = (-srcString[i - 2] + destString[i - 2] + 10) % 10;
			p = (t2 - t1 + 20) % 10;
			q = (t3 - t1 + 20) % 10;
			//状态转移1.1：g[i][0][0]=Min(g[i][0][0],g[i-1][q][p]+cost) 转动上三位数字至第i位相同的最小代价
			// 
			//	其中t1=dest[i]-src[i] (mod 10) 表示第i位与目标的差
			//	cost=Min(10-t1,t1) 表示使得第i位相同时，选择上移和下移的最小代价
			//	q=(dest[i-1]-src[i-1]-t1) (mod 10) 表示进行该状态转移时，为了移动后第i位相等，第i-1位需要提前上移的单位
			//  p=(dest[i-2]-src[i-2]-t1) (mod 10) 表示进行该状态转移时，为了移动后第i位相等，第i-2位需要提前上移的单位
			f[i & 3][0][0] = Min(f[i & 3][0][0], f[(i + 1) & 3][q][p] + Min(10 - t1, t1));

			//状态转移1.2：g[i][j][j]=Min(g[i][j][j],g[i][0][0]+cost) 完成1.1步骤后，使得后两位数上移j的最小代价
			for (int j = 0; j < 10; j++) {
				f[i & 3][j][j] = Min(f[i & 3][j][j], f[i & 3][0][0] + Min(10 - j, j));
			}
		}
		//情况2：(a)转动i-1和i两位数字，使得第i位及以前相同，即 ##x[x]**
		//		 (b)转动i-1,i和i+1三位数字，使得第i位及以前相同，即##x[x]x*
		if (i - 2 >= 0) {
			for (int j = 0; j < 10; j++) {
				//t1表示第i位目标位和当前位的差 t1=(dest[i]-src[i]) (mod 10)
				t1 = (destString[i] - srcString[i] - j + 20) % 10;
				p = (destString[i - 1] - srcString[i - 1] - t1 + 20) % 10;

				//状态转移2.1：g[i][k][0]=Min(g[i-2][p][j]+cost,g[i][k][0]) 情况(a)(b)的转移方程，且向下转动
				//此时第i位向下转动m=(10-t1)位，此时第i+1位可以选择向下转动[0,m]位
				// cost=10-t1表示移动代价
				// j表示第i位之前一定提前上移的位数
				// p=(dest[i-1]-src[i-1]-t1) (mod 10) 表示进行该状态转移时，为了移动后第i位相等，第i-1位需要提前上移的单位
				if (t1 > 10 - t1) { 
					for (int k = t1; k <= 10; k++) {
						f[i & 3][k % 10][0] = Min(f[(i + 2) & 3][p][j] + 10 - t1, f[i & 3][k % 10][0]);
					}
				}
				//状态转移2.2：g[i][k][0]=Min(g[i-2][p][j]+cost,g[i][k][0]) 情况(a)(b)的转移方程，且向上转动
				//此时第i位向上转动m=t1位，此时第i+1位可以选择向下转动[0,t1]位
				// cost=t1表示转移代价
				else {
					for (int k = 0; k <= t1; k++) {
						f[i & 3][k][0] = Min(f[(i + 2) & 3][p][j] + t1, f[i & 3][k][0]);
					}
				}
			}

		}
		//情况3：(a)仅转动第i位数字，使得前i位数字相同，即 ###[x]**
		//		 (b)转动第i、i+1位数字，使得前i位数字相同，即 ###[x]x*
		//		 (c)转动第i、i+1和i+2位数字，使得前i位数字相同，即###[x]xx
		if (i - 1 >= 0) {
			for (int j = 0; j < 10; j++) {
				//t1表示第i位目标位和当前位的差 t1=(dest[i]-src[i]) (mod 10)
				t1 = (destString[i] - srcString[i] - j + 20) % 10;
				
				for (int k = 0; k < 10; k++) {
					//状态转移3.1：g[i][y][m] = Min(g[i][y][m],g[i-1][j][k]+cost) 向上移动的转移方程
					//cost=t1 表示向上移动的次数(代价)
					//j表示被转移状态中，第i位已经上移的位数
					//k表示被转移状态中，第i+1位已经上移的位数
					//l表示第i+1位可以上移的位数，由于第i位已经上移t1个单位，故第i+1位上移单位不超过t1
					//m表示第i+2位可以上移的位数，由于第i+1位已经上移l个单位，故i+2位上移单位不超过l
					//y表示当前状态中，第i+1位在上移l个单位和前置状态上移k个单位后，相较于src，上移的位数 y=k+l (mod10)
					if (t1 < 5) {
						for (int l = 0; l <= t1; l++) {
							for (int m = 0; m <= l; m++) {
								f[i & 3][(k + l) % 10][m] = Min(f[i & 3][(k + l) % 10][m], f[(i + 3) & 3][j][k] + t1);
							}
						}
					}
					//状态转移3.2：g[i][y][m] = Min(g[i][y][m],g[i-1][j][k]+cost) 向下移动的转移方程
					//cost=10-t1 表示向上移动的次数(代价)
					else { 
						for (int l = t1; l <= 10; l++) {
							for (int m = l; m <= 10; m++) {
								f[i & 3][(k + l) % 10][m % 10] = Min(f[i & 3][(k + l) % 10][m % 10], f[(i + 3) & 3][j][k] + 10 - t1);
							}
						}
					}
				}
			}
		}
		//情况4：基于完成情况1\2\3后，对后两位进行的移动
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				t1 = (j - k + 10) % 10;
				f[i & 3][j][0] = Min(f[i & 3][j][0], f[i & 3][k][0] + Min(10 - t1, t1));
			}
			//状态转移4：g[i][j][k]=Min(g[i][j][k],g[i][l][t2]+cost) 
			//	在第i位前相同，第i+1位上移l，第i+2位上移t2的情况下，上/下移cost单位后的结果
			// t1=(j-l) (mod 10) 表示第i+1位在被转移状态和转移后上移次数差
			// t2=(k-t1) (mod 10) 表示确定t1的情况下，第i+2位在本次上移前，已经在被转移状态中上移的位数
			// cost=Min(10-t1,t1) 表示从上移和下移中选择代价小者进行状态转移
			for (int k = 0; k < 10; k++) {
				for (int l = 0; l < 10; l++) {
					t1 = (j - l + 10) % 10;
					t2 = (k - t1 + 10) % 10;
					f[i & 3][j][k] = Min(f[i & 3][j][k], f[i & 3][l][t2] + Min(10 - t1, t1));
				}
			}
		}
	}
	//取最小值作为答案
	int ans = INT_MAX;
	for (int i2 = 0; i2 < 10; i2++) {
		for (int j = 0; j < 10; j++) {
			ans = Min(ans, f[(len - 1) & 3][i2][j]);
		}
	}
	return ans;
}

int main() {
	const int MAXN = 1020;
	char a[MAXN], b[MAXN];
	for (int i = 0; i < MAXN; i++)a[i] = b[i] = '0';
	while (cin >> (a+1) >> (b + 1)) {
		int ans = locker_solve(a, b);
		cout << ans << endl;
		break;
	}
	return 0;
}
