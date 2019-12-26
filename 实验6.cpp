#include <iostream>
#include<iomanip>
#include<cstring>
using namespace std;
template<class T>
class arraystack//����һ��ջ��ʵ����Ҫ�ļ������� 
{
public:
	arraystack(int a = 10);
	~arraystack() { delete[]stack; }
	bool empty() { return stacktop == -1; }// ͨ���ж�ջ���ı���Ƿ�Ϊ-1�ж�ջ�Ƿ�Ϊ�� 
	int size() { return stacktop + 1; }//���ջ�Ĵ�С 
	T& top();//�õ���ʱ��ջ��Ԫ�� 
	void pop();//ɾ����ʱ��ջ��Ԫ�� 
	void push(const T& theelement);//��ջ������һ��Ԫ�� 


private:
	int stacktop;
	int arraylength;
	T* stack;
};

template<class T>
arraystack<T>::arraystack(int a)
{
	arraylength = a;
	stacktop = -1;
	stack = new T[arraylength];
}

template<class T>
T& arraystack<T>::top()
{
	return stack[stacktop];
}

template<class T>
void arraystack<T>::pop()
{
	stack[stacktop].~T();
	stacktop--;
}

template<class T>
void arraystack<T>::push(const T& theelement)
{
	if (stacktop == arraylength - 1)//�ж�����ʱ���ٵ�����ռ�������������ռ� 
	{
		T* temp = new T[arraylength * 2];
		copy(stack, stack + arraylength, temp);
		delete[]stack;
		stack= temp;
		arraylength = 2 * arraylength;
	}
	stacktop++;
	stack[stacktop] = theelement;
	
}

int main()
{
	int n;
	cin >> n;
	char b[1];
	cin.getline(b, 1);//�����̵�����n����Ļس��� 
	for (int i = 0; i < n; i++)
	{
		arraystack<double> mynumber;//������һ��ջ�������洢������ 
		arraystack<double> myoperator;//�����ڶ���ջ�������洢����������� 
		char a[2000];
		cin.getline(a, 2000,'\n');//������ʽ 
		for (int j = 0; j<strlen(a); j++)
		{
			if (a[j] >= 48 && a[j] <= 57)//�ж������λ���ַ������֣��������������һ��ջ 
				mynumber.push(a[j]-48);
			else
			{
				if (a[j] == 40) myoperator.push(a[j]);//���ַ��ǣ���������������ڶ���ջ 
				else if (a[j] == 43||a[j]==45)//����+�Ż���-�ţ�����Ҫ��һ���жϴ�ʱ�Ƿ�Ϊ��ջ 
				{
					if (myoperator.size() == 0)
						myoperator.push(a[j]);
					else
					{
						/*if(myoperator.top()==45|| myoperator.top() == 42|| myoperator.top() == 47)*/
						if (myoperator.top() ==40 )//����Ϊ�գ����һ���ж�ջ��Ԫ����ʲô���������Ƚ����ȼ� 
							myoperator.push(a[j]);
						else
						{
							double temp1 = myoperator.top();
							myoperator.pop();
							double temp2 = mynumber.top();//ȡ����һ��ջ������������ 
							mynumber.pop();
							double temp3 = mynumber.top();
							mynumber.pop();
							if (temp1 == 45) mynumber.push(temp3 - temp2);//�жϴ�ʱ�ڶ���ջ��ջ��Ԫ�أ�ִ�ж�Ӧ���� 
							if (temp1 == 42) mynumber.push(temp2 * temp3);
							if (temp1 == 43) mynumber.push(temp2 + temp3);
							if (temp1 == 47) mynumber.push(temp3 / temp2);
							j--;
						}
					}
				}
				else if (a[j] == 42 || a[j] == 47)//�ַ���*�Ż���/��ʱ������������ͬ��ֻ�����ȼ����иı� 
				{
					if (myoperator.size() == 0)
						myoperator.push(a[j]);
					else
					{
						if (myoperator.top() == 40|| myoperator.top() == 43|| myoperator.top() == 45)
							myoperator.push(a[j]);
						else
						{
							double temp1 = myoperator.top();
							myoperator.pop();
							double temp2 = mynumber.top();
							mynumber.pop();
							double temp3 = mynumber.top();
							mynumber.pop();
							if (temp1 == 42) mynumber.push(temp2 * temp3);
							if (temp1 == 47) mynumber.push(temp3 / temp2);
							j--;
						}
					}
				}
				else if (a[j] == 41)//�����������ţ���Ӧ��ѭ���Ĵӵڶ���ջ��ȡ��Ԫ�أ����Ͳ�����ִ����ز�����ֱ��������Ϊֹ�� 
				{
					while (myoperator.top() != 40&&myoperator.size()>=0)
					{
						double temp1 = myoperator.top();
						myoperator.pop();
						double temp2 = mynumber.top();
						mynumber.pop();
						double temp3 = mynumber.top();
						mynumber.pop();
						if (temp1 == 45) mynumber.push(temp3 - temp2);
						if (temp1 == 42) mynumber.push(temp2 * temp3);
						if (temp1 == 43) mynumber.push(temp2 + temp3);
						if (temp1 == 47) mynumber.push(temp3 / temp2);
					}
					myoperator.pop();
				}
			}
		}
		//for (int g = 0; g < 3; g++)
		//{
		//	cout << mynumber.top() << " ";
		//	mynumber.pop();
		//}
		//int u = myoperator.size();
	/*	cout << w << " " << u;*/
		while (myoperator.size() > 0)//����ʱջ2��Ϊ�գ������ȼ�Ϊ�Ҹ���ף�ֻ��Ҫ���μ��㼴�ɣ�ֱ��ջ2Ϊ�� 
		{
			double temp1 = myoperator.top();
			myoperator.pop();
			double temp2 = mynumber.top();
			mynumber.pop();
			double temp3 = mynumber.top();
			mynumber.pop();
			if (temp1 == 45) mynumber.push(temp3 - temp2);
			if (temp1 == 42) mynumber.push(temp2 * temp3);
			if (temp1 == 43) mynumber.push(temp2 + temp3);
			if (temp1 == 47) mynumber.push(temp3 / temp2);
		}
//		for (int g = 0; mynumber.size() != 0; g++)
//		{
//			cout << mynumber.top() << " ";
//			mynumber.pop();
//		}
		double result=mynumber.top();//ѭ��������ջ2Ϊ�գ�ջ1��ջ��Ԫ��Ϊ���Ľ�� 
//		double c = mynumber.size();
		//cout << c << " ";
		cout <<fixed<<setprecision(2)<<result << endl;
		//mynumber.free();
		//myoperator.free();
	}
	return 0;
}


