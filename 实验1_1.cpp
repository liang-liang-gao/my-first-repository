#include<iostream>
#include<math.h>
using namespace std;
int v = 0;
class subset
{
	public:
		void f(int*a,int*b,int k,int n);
		subset(int*a1,int*b1,int k1=0,int m1=0):a(a1),b(b1),k(k1),m(m1){}
	private:
		int*a;
		int*b;
		int k;
		int m;
 }; 
void subset::f(int* a, int* b, int k, int n)
{
	if (k > n - 1)
	{
		int sum=0,t=0;
        for(int i=0,t=0;i<n;i++)
            if (b[i] == 1)
			{
				sum=sum+a[i]*(t+1);
				t++;
			}//��ÿ���Ӽ��ļ�ֵ 
        v=v^sum;//���ֵ������                                                                            
	}
	else
	{
		b[k] = 0;
		f(a, b, k + 1, n);
		b[k] = 1;
		f(a, b, k + 1, n);
	}//�����еĸ����Ӽ� 

}
int main()
{
	int n;
	cin >> n;
	int *a=new int[n];
	int *b=new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	subset sub(a,b,0,n);//a�����������У�bͨ��ȡ0��1����¼�Ӽ����Ƿ������Ԫ�� 
	sub.f(a,b,0,n);
	cout<<v<<endl;
	delete[]b;
	delete[]a;
	return 0;
}



