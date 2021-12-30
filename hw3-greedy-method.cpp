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
    sort(intervals.begin(),intervals.begin()+n,compare); //按照右端点从小到大进行排序 
    int cr=-0x7fffffff-1;
    int ans=0;
    for(int i=0;i<n;i++){ //贪心选取区间 
        if(intervals[i][0]>=cr){
            cr=intervals[i][1];//如果和已选区间不重叠，将其加入已选集合 
        }else{
            ans++; //否则忽略此区间，答案计数器增加 
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


