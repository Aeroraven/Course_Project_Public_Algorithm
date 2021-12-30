#include <iostream>
#include <cstdio>
#include <vector> 
void solve(int n, int k)
{
	std::vector<int> ans;
	//std::cout << "[";
	bool is_first_number = true; //����Ƿ��ǵ�һ����������֣������ж��Ƿ��������
	k = (k < 0) ? -k : k; //ȡk�ľ���ֵ����ֹ����kΪ��ֵ����
	if (n > 1) //n=1,0����ʱ���޴𰸣�����Ҫ�ų�
	{
		char* digit_stack = new char[n+1]; //�����Ѿ��ŷźõ���λ��ջ
		digit_stack[n] = '\0';//����ַ�������
		int* digit_stack_assist = new int[n]; //digit_stack�ĸ���ջ�����ڱ��������λ��״̬
		for (int i = 1; i <= 9; i++)
		{
			int stack_top = -1; //ջ��ָ�룬ջ��Ԫ�ص��±�
			digit_stack[++stack_top] = i + '0'; //����һλ���ַ���ջ��
			digit_stack_assist[stack_top] = 0;
			while (stack_top + 1) //ջ�ǿյ�ʱ�򣬼������в���
			{
				if (stack_top == n-1) //���ջ��СΪn����˵���Ѿ�����һ���Ϸ��Ĵ𰸣��������
				{
					if (is_first_number) //����ǵ�һ�����֣����������
					{
						is_first_number = false;
					}
					else
					{
						std::cout << ",";
					}
					//std::cout << digit_stack;//�����
					printf("%s",digit_stack);
					//ans.push_back(dans);
					stack_top--;
					continue;
				}
				/*
					����ջ������digit_stack[stack_top],����һ����λ��ֵ�������������k=0����һ�����)��
					���һΪ��digit_stack[stack_top]-k
					�����Ϊ��digit_stack[stack_top]+k

					ջdigit_stack_assist���ڱ��ջ������Ҫ��������һ�������
					A. digit_stack_assist[stack_top]Ϊ0ʱ����ʾ�����1��Ϊ����״̬��������
					B. digit_stack_assist[stack_top]Ϊ1ʱ����ʾ�����2��Ϊ����״̬�������������1�Ѿ����������
					C. digit_stack_assist[stack_top]Ϊ2ʱ����ʾ�����1��2����ɣ���Ҫ���л��ݣ�����ջ��

					��digit_stack[stack_top]-k<digit_stack[stack_top]+k�����ȴ������1���Ա�֤������)
				*/
				switch (digit_stack_assist[stack_top])
				{
					case 0:
						digit_stack_assist[stack_top] = 1 + (k == 0); //������1�������
						if (digit_stack[stack_top] - k >= '0')
						{
							digit_stack[stack_top +  1] = digit_stack[stack_top] - k; //����һ��λΪ��ǰ(ջ��)��λ-k
							digit_stack_assist[++stack_top] = 0;
						}
						continue;
					case 1:
						digit_stack_assist[stack_top] = 2;
						if (digit_stack[stack_top]  + k <= '9')
						{
							digit_stack[stack_top + 1] = digit_stack[stack_top] + k;  //����һ��λΪ��ǰ(ջ��)��λ+k
							digit_stack_assist[++stack_top] = 0;
						}
						continue;
					case 2:
						stack_top--; //���1�����2���Ѿ����
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
