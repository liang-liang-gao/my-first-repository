#include<iostream>
using namespace std;
template<class T>
class minheap
{
	public:
		minheap(int n=20);
//		~minheap(){delete []heap;}
		void makeheap(T a[]);
		void push(T &theheap);
		void pop();
		T top(){return heap[1];}
		void sortedout(int n,T a[]);
	private:
		T *heap;
		int arraylength;
		int heapsize;
};
template<class T>
minheap<T>::minheap(int n)
{
	arraylength=n+1;
	heap=new T[n+1];
	heapsize=n;
}
template<class T>
void minheap<T>::makeheap(T a[])
{
	delete []heap;
	heap=a;
	for(int i=heapsize/2;i>=1;i--)
	{
		T temp=heap[i];
		int child=2*i;
        
		while(child<=heapsize)
		{
			if(child+1<=heapsize)
		    {
			    if(heap[child+1]<heap[child])
			        child++;
		    }
		    if(heap[child]>temp)
		        break;
		    heap[child/2]=heap[child];
		    child=child*2;
		}
		heap[child/2]=temp;
	}
}
template<class T>
void minheap<T>::push(T &theheap)
{
	if(heapsize>=arraylength-1)
	{
		T *newheap=new T[2*arraylength];
		for(int i=1;i<=heapsize;i++)
		    newheap[i]=heap[i];
		delete []heap;
		heap=newheap;
		arraylength=2*arraylength;
	}
	heap[++heapsize]=theheap;
	int temp=heapsize;//temp是待插入的位置 
	while(temp>1&&heap[temp/2]>theheap)
	{
		heap[temp]=heap[temp/2];
		temp=temp/2;
	}
	heap[temp]=theheap;
	cout<<heap[1]<<endl;
}
template<class T>
void minheap<T>::pop()
{
	heap[1].~T();
	T temp=heap[heapsize--];
	int child=2;
	while(child<=heapsize)
	{
		if(heap[child+1]<heap[child]&&child+1<=heapsize)
		    child++;
		if(temp<heap[child])
		    break;
		heap[child/2]=heap[child];
		child=child*2;
	}
	heap[child/2]=temp;
}
template<class T>
void minheap<T>::sortedout(int n,T a[])
{
	minheap<T> temp(n);
	temp.makeheap(a);
	for(int i=1;i<=n;i++)
	{
		cout<<temp.heap[1]<<" ";
		temp.pop();
	}
//	temp.deactivateArray();
	cout<<endl;
}
int main()
{
	int n,num,op,element,sortedsize;
	cin>>n;
	minheap<int> a(n);
	int *temp=new int[n+1];
	int *c=new int[n+1];
	for(int i=1;i<=n;i++)
	    cin>>temp[i];
	cout<<a.top()<<endl;
	a.makeheap(temp);
	cin>>op;
	for(int i=0;i<op-1;i++)
	{
		cin>>num;
		if(num==1)
		{
			cin>>element;
			a.push(element);
		}
		if(num==2)
		{
			a.pop();
			cout<<a.top()<<endl;
		}
	}
	cin>>num>>sortedsize;
	for(int i=1;i<=n;i++)
	    cin>>c[i];
	a.sortedout(sortedsize,c);
	return 0;
}














