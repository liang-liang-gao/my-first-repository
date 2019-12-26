 #include<iostream>
using namespace std;
template<class T>
struct chainnode//������ڵ�Ķ��� 
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
		class iterator//����һ�������� 
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
		chain(int a=10);//���캯�� 
		~chain();//�������� 
		void search(const T& theelement)const;//�������� 
		void erase(const T& theelement);//ɾ��ָ��Ԫ�صĺ��� 
	    void insert_head(const T& theelement);//�Ա��ײ���Ԫ�صĺ��� 
        void output(ostream& out);//������� 
        iterator begin(){ return iterator(firstnode); }
        iterator end() { return iterator(NULL); }
        void reverseout();//����������� 
        void mergeout(chain<T>&a);//�ϲ������������ 
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
	if(firstnode->element==theelement)//ɾ������Ԫ��ʱ 
	{ 
	    deletenode=firstnode;
	    firstnode=firstnode->next;
    }
    else
    {
    	chainnode<T> *currentnode=firstnode->next;//������¼Ҫɾ�������� 
    	chainnode<T> *previous=firstnode;//������¼��Ҫɾ�������ݵ�ǰһ������ 
    	while(currentnode->element!=theelement)
    	{
    		currentnode=currentnode->next;
    	    previous=previous->next;
        }
    	deletenode=currentnode;
    	previous->next=deletenode->next;//��ɾ�����ݵ�ǰ�������������� 
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
	    {   cout<<i<<endl;  break;   }//���ҵ���Ԫ�أ��������������������һ������ 
    	else currentnode=currentnode->next;
	}
	if(i==listsize) cout<<-1<<endl;//��δ�ҵ��������-1 
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
    T p[listsize];//�����洢�������������� 
    int i=listsize-1;//�����ݴ�������������ǰ�洢��ʵ������洢 
    for(chainnode<T>*currentnode=firstnode;currentnode!=NULL;currentnode=currentnode->next,i--)
        p[i]=currentnode->element;
    for(i=0;i<listsize;i++)
        cout<<p[i]<<" ";
    cout<<endl;
} 

template<class T>
void chain<T>::mergeout(chain<T>&a)
{
	chain<T> list1;//������¼�ϲ�������� 
	chain<T>::iterator x=begin();//ͨ������������������ 
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
	while(x==end()&&y!=a.end())//��һ������ȫ��������ֻ��Ҫ�����ڶ������� 
	{
		list1.insert_head(*y);
		y++;
	}
	while(x!=end()&&y==end())
	{
		list1.insert_head(*x);
		x++;
	}
	list1.output(cout);//����ϲ�������� 
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
		if(num==1)//�ж�Ҫִ�����ֲ��� 
		{
			cin>>pname;
			list.insert_head(pname);//���ò��뺯�� 
		}
		if(num==2)
		{
			cin>>pname;
			list.erase(pname); //����ɾ������
		}
		if(num==3)
		{
		    cin>>pname;
		    list.search(pname);//�����������ݺ���
		}
		if(num==4)
		{
			list.output(cout);//����������� 
		}
		if(num==5)
		{
			list.reverseout();//��������������� 
		}
		if(num==6)
		{
			cin>>listsize1;
		    for(int i=0;i<listsize1;i++)
		    {
			    cin>>pname;
			    list2.insert_head(pname);//���ò��뺯�� 
		    }
		    cin>>listsize2;
		    for(int i=0;i<listsize2;i++)
		    {
			    cin>>pname;
			    list3.insert_head(pname);//���ò��뺯�� 
		    }
		    list2.mergeout(list3);//���úϲ����� 
		}
	}
	return 0;
}

