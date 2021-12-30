#include <iostream>
#include <cstdio>
#include <vector> 
void solve(int n, int k)
{
	std::vector<int> ans;
	//std::cout << "[";
	bool is_first_number = true; //标记是否是第一个输出的数字，用于判断是否输出逗号
	k = (k < 0) ? -k : k; //取k的绝对值，防止输入k为负值出错
	if (n > 1) //n=1,0或负数时，无答案，故需要排除
	{
		char* digit_stack = new char[n+1]; //储存已经排放好的数位的栈
		digit_stack[n] = '\0';//标记字符串结束
		int* digit_stack_assist = new int[n]; //digit_stack的辅助栈，用于标记所在数位的状态
		for (int i = 1; i <= 9; i++)
		{
			int stack_top = -1; //栈顶指针，栈顶元素的下标
			digit_stack[++stack_top] = i + '0'; //将第一位数字放入栈中
			digit_stack_assist[stack_top] = 0;
			while (stack_top + 1) //栈非空的时候，继续进行操作
			{
				if (stack_top == n-1) //如果栈大小为n，则说明已经存在一个合法的答案，进行输出
				{
					if (is_first_number) //如果是第一个数字，不输出逗号
					{
						is_first_number = false;
					}
					else
					{
						std::cout << ",";
					}
					//std::cout << digit_stack;//输出答案
					printf("%s",digit_stack);
					//ans.push_back(dans);
					stack_top--;
					continue;
				}
				/*
					对于栈顶数字digit_stack[stack_top],其下一个数位的值仅有两种情况（k=0仅有一种情况)：
					情况一为：digit_stack[stack_top]-k
					情况二为：digit_stack[stack_top]+k

					栈digit_stack_assist用于标记栈顶数字要搜索的下一种情况：
					A. digit_stack_assist[stack_top]为0时，表示对情况1作为后续状态进行搜索
					B. digit_stack_assist[stack_top]为1时，表示对情况2作为后续状态进行搜索（情况1已经完成搜索）
					C. digit_stack_assist[stack_top]为2时，表示对情况1和2均完成，需要进行回溯（即退栈）

					（digit_stack[stack_top]-k<digit_stack[stack_top]+k，故先处理情况1可以保证有序性)
				*/
				switch (digit_stack_assist[stack_top])
				{
					case 0:
						digit_stack_assist[stack_top] = 1 + (k == 0); //标记情况1搜索完成
						if (digit_stack[stack_top] - k >= '0')
						{
							digit_stack[stack_top +  1] = digit_stack[stack_top] - k; //置下一数位为当前(栈顶)数位-k
							digit_stack_assist[++stack_top] = 0;
						}
						continue;
					case 1:
						digit_stack_assist[stack_top] = 2;
						if (digit_stack[stack_top]  + k <= '9')
						{
							digit_stack[stack_top + 1] = digit_stack[stack_top] + k;  //置下一数位为当前(栈顶)数位+k
							digit_stack_assist[++stack_top] = 0;
						}
						continue;
					case 2:
						stack_top--; //情况1和情况2均已经完成
						break;
				}
			}
		}
		delete[] digit_stack;
		delete[] digit_stack_assist;
	}
	//std::cout << "]";
}

int main()
{
	int n, k;
	std::cin >> n >> k;
	solve(n, k);
	return 0;
}
