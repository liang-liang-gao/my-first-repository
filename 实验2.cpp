#include<iostream>
using namespace std;
template <class T>
class mysortable
{
	public:
		mysortable(T *a,int &n) { size=n; data=a; }
		void mymingcisort();
		void myselectsort();
		void mypoposort();
		void myinsertsort();//�������������㷨 
		void output();
	private:
		T *data;
		int size;
	
 }; 
 template <class T>
 void mysortable<T>::mymingcisort() //ͨ����������
 {
 	int *w=new int[size];
 	for(int i=0;i<size;i++)
 	    w[i]=0;//w������¼���� 
 	for(int i=1;i<size;i++)
 	    for(int j=0;j<i;j++)
 	        if(data[j]<data[i]) w[i]++;
 	        else w[j]++;
    for(int i=0;i<size;i++)
	    while(w[i]!=i)
	    {
	    	int u=w[i];
	    	swap(data[i],data[u]);
	    	swap(w[i],w[u]);
		 } //ͨ���ж�Ԫ���Ƿ������δӵ͵��ߵ�˳��������ԭ���������� 
 	delete []w;
 }
 
  template <class T>
 void mysortable<T>::myselectsort()//�ü�ʱ��ֹ��ѡ���㷨������ 
 {
 	bool sorted=true;//�ٶ�ԭʼ�������� 
 	for(int i=0;i<size;i++)
 	{
 	    int max=0; 		 
	    for(int j=1;j<size-i;j++)
 	        if(data[j]>=data[max]) max=j;
 	        else sorted=false;//���� 
 	    swap(data[max],data[size-i-1]);
 	    if(sorted==true) break;//��ѭ���������鱾���������ֱ������ѭ�� 
    }
 }
 
  template <class T>
 void mysortable<T>::mypoposort()//�ü�ʱ��ֹ��ð���㷨������ 
 {
 	bool sorted=true;//�ٶ�ԭʼ��������
 	for(int i=0;i<size;i++)
 	{
		for(int j=0;j<size-i-1;j++)
 	        if(data[j+1]<data[j]) 
			{
			    swap(data[j+1],data[j]);
 	            sorted=false;//���� 
 	        }
 	    if(sorted==true) break;//��ѭ���������鱾���������ֱ������ѭ�� 
    }
 }
 
  template <class T>
 void mysortable<T>::myinsertsort()//�ò����㷨������ 
 {
 	for(int i=1;i<size;i++)
    {
    	T x=data[i];//xΪ�������ֵ 
    	int j;
        for(j=i-1;j>=0;j--)
            if(x<data[j])  data[j+1]=data[j];
			else  break;//����������ֵ��������棬��ִ��j--��ֱ������ѭ�� 
		data[j+1]=x;
	}
 }

   template <class T>
 void mysortable<T>::output()//����������� 
 {                                                                     
 	for(int i=0;i<size;i++)
 	    cout<<data[i]<<" ";
 	cout<<endl;
 }
 int main()
 {
 	int n;
 	cin>>n;
 	int *a=new int[n];
 	for(int i=0;i<n;i++)
 	    cin>>a[i];
 	mysortable<int> m(a,n);//������ģ�彨������ 
	m.mymingcisort();
	m.output();
	delete []a; 
 	return 0;
 }

