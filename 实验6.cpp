#include <iostream>
#include<iomanip>
#include<cstring>
using namespace std;
template<class T>
class arraystack//创建一个栈，实现需要的几个方法 
{
public:
	arraystack(int a = 10);
	~arraystack() { delete[]stack; }
	bool empty() { return stacktop == -1; }// 通过判断栈顶的标号是否为-1判断栈是否为空 
	int size() { return stacktop + 1; }//输出栈的大小 
	T& top();//得到此时的栈顶元素 
	void pop();//删除此时的栈顶元素 
	void push(const T& theelement);//在栈顶插入一个元素 


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
	if (stacktop == arraylength - 1)//判断若此时开辟的数组空间已满，则扩大空间 
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
	cin.getline(b, 1);//用来吞掉输入n后面的回车键 
	for (int i = 0; i < n; i++)
	{
		arraystack<double> mynumber;//建立第一个栈，用来存储操作数 
		arraystack<double> myoperator;//建立第二个栈，用来存储运算符和括号 
		char a[2000];
		cin.getline(a, 2000,'\n');//输入表达式 
		for (int j = 0; j<strlen(a); j++)
		{
			if (a[j] >= 48 && a[j] <= 57)//判断如果该位置字符是数字，则无条件插入第一个栈 
				mynumber.push(a[j]-48);
			else
			{
				if (a[j] == 40) myoperator.push(a[j]);//若字符是（，则无条件插入第二个栈 
				else if (a[j] == 43||a[j]==45)//若是+号或者-号，则需要进一步判断此时是否为空栈 
				{
					if (myoperator.size() == 0)
						myoperator.push(a[j]);
					else
					{
						/*if(myoperator.top()==45|| myoperator.top() == 42|| myoperator.top() == 47)*/
						if (myoperator.top() ==40 )//若不为空，则进一步判断栈顶元素是什么操作符，比较优先级 
							myoperator.push(a[j]);
						else
						{
							double temp1 = myoperator.top();
							myoperator.pop();
							double temp2 = mynumber.top();//取出第一个栈的两个操作数 
							mynumber.pop();
							double temp3 = mynumber.top();
							mynumber.pop();
							if (temp1 == 45) mynumber.push(temp3 - temp2);//判断此时第二个栈的栈顶元素，执行对应操作 
							if (temp1 == 42) mynumber.push(temp2 * temp3);
							if (temp1 == 43) mynumber.push(temp2 + temp3);
							if (temp1 == 47) mynumber.push(temp3 / temp2);
							j--;
						}
					}
				}
				else if (a[j] == 42 || a[j] == 47)//字符是*号或者/号时，方法和上面同理，只是优先级稍有改变 
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
				else if (a[j] == 41)//若遇到右括号，则应该循环的从第二个栈中取出元素，并和操作数执行相关操作，直到遇到（为止。 
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
		while (myoperator.size() > 0)//若此时栈2不为空，则优先级为右高左底，只需要依次计算即可，直到栈2为空 
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
		double result=mynumber.top();//循环结束后，栈2为空，栈1的栈顶元素为最后的结果 
//		double c = mynumber.size();
		//cout << c << " ";
		cout <<fixed<<setprecision(2)<<result << endl;
		//mynumber.free();
		//myoperator.free();
	}
	return 0;
}


