#include<iostream>
#include<math.h>
int h = 0;
using namespace std;
class subset
{
	public:
		void f(int*a,int k,int m);
		subset(int*a1,int k1,int m1):a(a1),k(k1),m(m1){}
	private:
		int*a;
		int k;
		int m;
 }; 
void subset::f(int* a, int k, int m)
{
	if (k==m)
	{
	    int sum=0;
	    for(int i=0;i<=m;i++)
	        sum+=(i+1)^a[i];//求全排列的价值 
        h=h|sum;//求价值的位运算或 
	}
	else
	{
	    for(int i=k;i<=m;i++)
		{
			swap(a[k],a[i]);
		    f(a, k + 1, m);//通过交换元素来求全排列，
            swap(a[k],a[i]);//求完一个全排列后交换回原来元素的位置 
		}
	}
}
int main()
{
	int n;
	cin >> n;
	int *a=new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	subset sub(a,0,n-1);//a是所给的序列 
    sub.f(a,0,n-1);
	cout << h << endl;
	delete[]a;

    return 0;
}


