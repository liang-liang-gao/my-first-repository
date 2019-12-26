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
		class iterator//定义一个迭代器 
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
		chain(int a=10);//构造函数 
		~chain();//析构函数 
		void search(const T& theelement)const;//搜索函数 
		void erase(const T& theelement);//删除指定元素的函数 
	    void insert_head(const T& theelement);//自表首插入元素的函数 
        void output(ostream& out);//输出链表 
        iterator begin(){ return iterator(firstnode); }
        iterator end() { return iterator(NULL); }
        void reverseout();//逆向输出函数 
        void mergeout(chain<T>&a);//合并链表并输出函数 
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


template<class T>
void chain<T>::erase(const T& theelement)
{
	chainnode<T>*deletenode;
	if(firstnode->element==theelement)//删除表首元素时 
	{ 
	    deletenode=firstnode;
	    firstnode=firstnode->next;
    }
    else
    {
    	chainnode<T> *currentnode=firstnode->next;//用来记录要删除的数据 
    	chainnode<T> *previous=firstnode;//用来记录需要删除的数据的前一个数据 
    	while(currentnode->element!=theelement)
    	{
    		currentnode=currentnode->next;
    	    previous=previous->next;
        }
    	deletenode=currentnode;
    	previous->next=deletenode->next;//将删除数据的前后数据连接起来 
	}
	listsize--;
	delete deletenode;
}

template<class T>
void chain<T>::search(const T& theelement)const
{
	int i;
	chainnode<T> *currentnode=firstnode;
	for(i=0;i<listsize;i++)
    {
    	if(currentnode->element==theelement) 
	    {   cout<<i<<endl;  break;   }//若找到该元素，则跳出函数，并输出第一次索引 
    	else currentnode=currentnode->next;
	}
	if(i==listsize) cout<<-1<<endl;//若未找到，则输出-1 
}

template<class T>
void chain<T>::output(ostream& out)
{
	for(chainnode<T>*currentnode=firstnode;currentnode!=NULL;currentnode=currentnode->next)
	    out<<currentnode->element<<" ";
	cout<<endl;
}

template<class T>
void chain<T>::reverseout()
{ 
    T p[listsize];//用来存储逆向后的链表数据 
    int i=listsize-1;//将数据从数组的最后面向前存储，实现逆向存储 
    for(chainnode<T>*currentnode=firstnode;currentnode!=NULL;currentnode=currentnode->next,i--)
        p[i]=currentnode->element;
    for(i=0;i<listsize;i++)
        cout<<p[i]<<" ";
    cout<<endl;
} 

template<class T>
void chain<T>::mergeout(chain<T>&a)
{
	chain<T> list1;//用来记录合并后的链表 
	chain<T>::iterator x=begin();//通过迭代器来遍历链表 
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
	while(x==end()&&y!=a.end())//第一个链表全部遍历，只需要遍历第二个链表 
	{
		list1.insert_head(*y);
		y++;
	}
	while(x!=end()&&y==end())
	{
		list1.insert_head(*x);
		x++;
	}
	list1.output(cout);//输出合并后的链表 
}
int main()
{
	chain<int> list;
	chain<int> list2;
	chain<int> list3;
    int n,num,pname;
	cin>>n;
    int listsize1,listsize2;
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
		    list.search(pname);//调用搜索数据函数
		}
		if(num==4)
		{
			list.output(cout);//调用输出函数 
		}
		if(num==5)
		{
			list.reverseout();//调用逆向输出函数 
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
		    list2.mergeout(list3);//调用合并函数 
		}
	}
	return 0;
}

