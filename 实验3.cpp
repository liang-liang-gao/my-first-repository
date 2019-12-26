#include<iostream>
#include<string>
using namespace std;
struct contacts
{ 
	string name;
	long long number;
	long long myclass;
	long long dorm;
};
template <class T>
class address
{
	public:
		address(int a=10);
		~address() { delete []element; };//�������������ͷŽ����Ķ�̬���� 
		void push_back(string pna,long long pnu,long long pmy,long long pdo);
		void erase(string pna);
		void update(string pna,long long pronum,long long newpro);
		int mysearch(string pna);
		int numout(long long pmy);
	private:
		T *element;//������¼��ϵ������ 
		int conlength;
		int listsize;//������¼��ϵ�˸��� 
}; 
template <class T>
address<T>::address(int a)
{
	conlength=a;
	element=new T[conlength];
	listsize=0;
}
template <class T>
void address<T>::push_back(string pna,long long pnu,long long pmy,long long pdo)//����β�����뺯�� 
{
	if(listsize>=conlength)//�ж��������Ѿ�������ӱ��������� 
	{
		T *t=new T[conlength*2];
		for(int i=0;i<conlength;i++)
		    t[i]=element[i];
		delete []element;
		element=t;
		conlength=2*conlength;
	}
	element[listsize].name=pna;
	element[listsize].number=pnu;
	element[listsize].myclass=pmy;
	element[listsize].dorm=pdo;
	listsize++;
}
template <class T>
void address<T>::erase(string pna)//�����������ɾ������ 
{
	int i;
	for(i=0;i<listsize&&element[i].name!=pna;i++);
	for(int j=i;j<listsize-1;j++)
	    element[j]=element[j+1];
	element[--listsize].~T();
}
template <class T>
void address<T>::update(string pna,long long pronum,long long newpro)//�����޸����ݺ��� 
{
	for(int i=0;i<listsize;i++)
	    if(element[i].name==pna)
	    {
	        if(pronum==1) element[i].number=newpro;//����������Բ�ͬ�����޸� 
	        if(pronum==2) element[i].myclass=newpro;
	        if(pronum==3) element[i].dorm=newpro;
	        break;
		}
}
template <class T>
int address<T>::mysearch(string pna)//������������ 
{
	int i;
	for(i=0;i<listsize&&element[i].name!=pna;i++);
	if(i==listsize) return 0;
	else return 1;
}
template <class T>
int address<T>::numout(long long pmy)//����������� 
{
	int sum=0;
	for(int i=0;i<listsize;i++)
	if(element[i].myclass==pmy)
	   sum=sum^element[i].dorm;
	return sum;
}
int main()
{
	address<contacts> ad;
	int n,num;
	string pname;
	long long pnumber,pmyclass,pdorm,projectnum,newproject;
	cin>>n;
	int *a=new int[n];
	int m=0;
	for(int i=0;i<n;i++)
	{
		cin>>num;
		if(num==0)//�ж�Ҫִ�����ֲ��� 
		{
			cin>>pname>>pnumber>>pmyclass>>pdorm;
			ad.push_back(pname,pnumber,pmyclass,pdorm);//���ò��뺯�� 
		}
		if(num==1)
		{
			cin>>pname;
			ad.erase(pname); //����ɾ������ 
		}
		if(num==2)
		{
			cin>>pname>>projectnum>>newproject;
			ad.update(pname,projectnum,newproject);//�����޸����ݺ���
		}
		if(num==3)
		{
		    cin>>pname;
		    a[m]=ad.mysearch(pname);//�����������ݺ���
		    m++;
		}
		if(num==4)
		{
			cin>>pmyclass;
			a[m]=ad.numout(pmyclass);//���������Ϣ����
			m++;
		}
	}
	for(int i=0;i<m;i++)
	    cout<<a[i]<<endl;
	delete []a;
	return 0;
}

