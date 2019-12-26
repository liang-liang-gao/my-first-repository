#include<iostream>
using namespace std;
template<class T>
struct chainnode//单链表节点的定义 
{
	T element;
	chainnode<T> *next;
	
	chainnode(){}
	chainnode(const T& theelement){element=theelement;}
	chainnode(const T& theelement,chainnode<T> *thenext)
	{element=theelement;next=thenext;}
};

template<class T>
class chain
{
	public:
		class iterator
        {
        	public:
        		iterator(chainnode<T>* thenode=NULL){ node=thenode; }
        	    T& operator*()const { return node->element; }
        	    T* operator->()const { return &node->element; }
        	    iterator& operator++() { node=node->next; return *this; }
        	    iterator operator++(int) { iterator tem=*this; node=node->next; return tem; }
        	    bool operator!=(const iterator right)const { return node!=right.node; }
        	    bool operator==(const iterator right)const { return node==right.node; }
        	protected:
        	    chainnode<T>* node;	
		};
		chain(int a=10);
		~chain();
		int search(const T& theelement)const;//搜索函数 
		void erase(const T& theelement);//删除指定元素的函数 
	    void insert_head(const T& theelement);//自表首插入元素的函数 
	    void push_back(const T& theelement);
        int output(ostream& out,T *m,int& p);//输出链表 
        iterator begin(){ return iterator(firstnode); }
        iterator end() { return iterator(NULL); }
        int merge(T *h,int& p);
        int unoinchain(chain<T>&a,T *h,int &p);
	private:
	    chainnode<T> *firstnode;
		int listsize;	
};

template<class T>
chain<T>::chain(int a)
{
	firstnode=NULL;
	listsize=0;
}

template<class T>
chain<T>::~chain()
{
	while(firstnode!=NULL)
	{
		chainnode<T>*nextnode=firstnode->next;
		delete firstnode;
		firstnode=nextnode;
	}
}

template<class T>
void chain<T>::insert_head(const T& theelement)
{
	firstnode=new chainnode<T>(theelement,firstnode);
	listsize++;
}

//template<class T>
//void chain<T>::push_back(const T& theelement)
//{
//	if(listsize==0)
//	{
//        firstnode=new chainnode<T>(theelement,firstnode);
//    }
//    else
//    {
//    	chainnode<T> *currentnode=firstnode;
//    	for(int i=0;i<listsize-1;i++)
//    	    currentnode=currentnode->next;
//    	currentnode->next=new chainnode<T>(theelement,currentnode->next);
//	}
//	listsize++;
//}
template<class T>
void chain<T>::erase(const T& theelement)
{
	chainnode<T>*deletenode;
	if(firstnode->element==theelement)
	{ 
	    deletenode=firstnode;
	    firstnode=firstnode->next;
    }
    else
    {
    	chainnode<T> *currentnode=firstnode->next;
    	chainnode<T> *previous=firstnode;
    	while(currentnode->element!=theelement)
    	{
    		currentnode=currentnode->next;
    	    previous=previous->next;
        }
    	deletenode=currentnode;
    	previous->next=deletenode->next;
	}
	listsize--;
	delete deletenode;
}

template<class T>
int chain<T>::search(const T& theelement)const
{
	int i;
	chainnode<T> *currentnode=firstnode;
	for(i=0;i<listsize;i++)
    {
    	if(currentnode->element==theelement) return i;//若找到该元素，则跳出函数，并返回第一次索引 
    	else currentnode=currentnode->next;
	}
	if(i==listsize) return -1;//若未找到，则返回-1 
}

template<class T>
int chain<T>::output(ostream& out,T *y,int& p)
{
	for(chainnode<T>*currentnode=firstnode;currentnode!=NULL;currentnode=currentnode->next,p++)
	    y[p]=currentnode->element;
	return listsize;
}

template<class T>
int chain<T>::merge(T *h,int& p)
{ 
    int i=p+listsize-1;
    for(chainnode<T>*currentnode=firstnode;currentnode!=NULL;currentnode=currentnode->next,i--)
        h[i]=currentnode->element;
    p=p+listsize;
    return listsize;
} 

template<class T>
int chain<T>::unoinchain(chain<T>&a,T *h,int &p)
{
	chain<T> list1;
	chain<T>::iterator x=begin();
	chain<T>::iterator y=a.begin();
	while(x!=end()&&y!=a.end())
	{
		if((*x)>(*y))
		{
		    list1.insert_head(*x);
		    x++;
	    }
		else
		{
		    list1.insert_head(*y);
		    y++;
	    }
	}
	while(x==end()&&y!=a.end())
	{
		list1.insert_head(*y);
		y++;
	}
	while(x!=end()&&y==end())
	{
		list1.insert_head(*x);
		x++;
	}
	return list1.output(cout,h,p);
}
int main()
{
	chain<int> list;
	chain<int> list2;
	chain<int> list3;
    int n,num,pname;//pname用来输入参数，n用来输入操作数，num用来输入执行的操作种类 
	cin>>n;
    int *a=new int[4080000];//a用来记录输出的数据 
    int *b=new int[25000];//b用来记录每次要输出的数据个数 
    int listsize1,listsize2;
	int m=0,w=0;//m是需要输出的元素总个数，w是需要执行输出的次数 
    for(int i=0;i<n;i++)
	{
		cin>>num;
		if(num==1)//判断要执行哪种操作 
		{
			cin>>pname;
			list.insert_head(pname);//调用插入函数 
		}
		if(num==2)
		{
			cin>>pname;
			list.erase(pname); //调用删除函数
		}
		if(num==3)
		{
		    cin>>pname;
		    a[m]=list.search(pname);//调用搜索数据函数
		    m++;
		    b[w]=1;
		    w++;
		}
		if(num==4)
		{
			b[w]=list.output(cout,a,m);
			w++;
		}
		if(num==5)
		{
			b[w]=list.merge(a,m);
			w++;
		}
		if(num==6)
		{
			cin>>listsize1;
		    for(int i=0;i<listsize1;i++)
		    {
			    cin>>pname;
			    list2.insert_head(pname);//调用插入函数 
		    }
		    cin>>listsize2;
		    for(int i=0;i<listsize2;i++)
		    {
			    cin>>pname;
			    list3.insert_head(pname);//调用插入函数 
		    }
		    b[w]=list2.unoinchain(list3,a,m);
		    w++;
		}
	}
	int q=0;//q用来指向每次输出的第一个位置 
	for(int i=0;i<w;i++)
	{
       for(int j=q;j<q+b[i];j++)
	        cout<<a[j]<<" ";
	   q=q+b[i];
	   cout<<endl; 
    }
	delete []a;
	delete []b;
	return 0;
}
                   

