#include <iostream>
#include <algorithm> 
#include <cstdlib>
#include <ctime> 
#include <vector>
using namespace std;
struct interval{
	int l,r;
	bool operator<(const interval& p)const {
		return r<p.r;
	}
};
static bool compare(const vector<int>&p,const vector<int>& q){
    return p[1]<q[1];
}
int calculate(vector<vector<int>>& intervals) {
    int n=intervals.size();
    sort(intervals.begin(),intervals.begin()+n,compare); //�����Ҷ˵��С����������� 
    int cr=-0x7fffffff-1;
    int ans=0;
    for(int i=0;i<n;i++){ //̰��ѡȡ���� 
        if(intervals[i][0]>=cr){
            cr=intervals[i][1];//�������ѡ���䲻�ص������������ѡ���� 
        }else{
            ans++; //������Դ����䣬�𰸼��������� 
        }
    }
    return ans;
}

int main(){
	vector<vector<int>> a;
	int l,r;
	while(1){
		cin>>l>>r;
		if(cin.eof())
			break;
		a.push_back({l,r});
	}
	int ans=calculate(a);
	cout<<ans;
	return 0;
}


