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
	        sum+=(i+1)^a[i];//��ȫ���еļ�ֵ 
        h=h|sum;//���ֵ��λ����� 
	}
	else
	{
	    for(int i=k;i<=m;i++)
		{
			swap(a[k],a[i]);
		    f(a, k + 1, m);//ͨ������Ԫ������ȫ���У�
            swap(a[k],a[i]);//����һ��ȫ���к󽻻���ԭ��Ԫ�ص�λ�� 
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
	subset sub(a,0,n-1);//a������������ 
    sub.f(a,0,n-1);
	cout << h << endl;
	delete[]a;

    return 0;
}


