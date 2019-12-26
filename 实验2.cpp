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
		void myinsertsort();//声明四种排序算法 
		void output();
	private:
		T *data;
		int size;
	
 }; 
 template <class T>
 void mysortable<T>::mymingcisort() //通过名次排序
 {
 	int *w=new int[size];
 	for(int i=0;i<size;i++)
 	    w[i]=0;//w用来记录名次 
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
		 } //通过判断元素是否按照名次从低到高的顺序排列来原地重排数组 
 	delete []w;
 }
 
  template <class T>
 void mysortable<T>::myselectsort()//用及时终止的选择算法求排列 
 {
 	bool sorted=true;//假定原始数组有序 
 	for(int i=0;i<size;i++)
 	{
 	    int max=0; 		 
	    for(int j=1;j<size-i;j++)
 	        if(data[j]>=data[max]) max=j;
 	        else sorted=false;//无序 
 	    swap(data[max],data[size-i-1]);
 	    if(sorted==true) break;//若循环后发现数组本就有序，则可直接跳出循环 
    }
 }
 
  template <class T>
 void mysortable<T>::mypoposort()//用及时终止的冒泡算法求排列 
 {
 	bool sorted=true;//假定原始数组有序
 	for(int i=0;i<size;i++)
 	{
		for(int j=0;j<size-i-1;j++)
 	        if(data[j+1]<data[j]) 
			{
			    swap(data[j+1],data[j]);
 	            sorted=false;//无序 
 	        }
 	    if(sorted==true) break;//若循环后发现数组本就有序，则可直接跳出循环 
    }
 }
 
  template <class T>
 void mysortable<T>::myinsertsort()//用插入算法求排序 
 {
 	for(int i=1;i<size;i++)
    {
    	T x=data[i];//x为待插入的值 
    	int j;
        for(j=i-1;j>=0;j--)
            if(x<data[j])  data[j+1]=data[j];
			else  break;//如果待插入的值排在最后面，则不执行j--，直接跳出循环 
		data[j+1]=x;
	}
 }

   template <class T>
 void mysortable<T>::output()//定义输出函数 
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
 	mysortable<int> m(a,n);//根据类模板建立对象 
	m.mymingcisort();
	m.output();
	delete []a; 
 	return 0;
 }

