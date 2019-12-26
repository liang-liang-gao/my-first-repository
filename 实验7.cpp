#include <iostream>
using namespace std;
template<class T>
struct chainnode//����һ���ṹ��ڵ㣬������ŵ�ǰԪ��ֵ����һ���ڵ�ĵ�ַ 
{
	T element;
	chainnode<T>* next;

	chainnode(){}//�ڵ�����ֹ��캯�� 
	chainnode(const T& theelement) { element = theelement; }
	chainnode(const T& theelement, chainnode<T>* thenext) { element = theelement; next = thenext; }
};
template<class T>
class linkedqueue
{
public:
	linkedqueue(int a = 10);
	~linkedqueue();
	T& front() { return queuefront->element; }//���ض��еĶ���Ԫ�� 
	T& back() { return queueback->element; }//���ض��еĶ�βԪ�� 
	void pop();//ɾ������Ԫ�� 
	void push(const T& theelement);//�Ӷ�β����Ԫ�� 
	int size() { return queuesize; }//���ض��еĴ�С 
private:
	chainnode<T>* queuefront;//һ��ָ����׵�ָ�� 
	chainnode<T>* queueback;//һ��ָ���β��ָ�� 
	int queuesize;//���д�С 
};

template<class T>
linkedqueue<T>::linkedqueue(int a)
{
	queuefront = queueback = NULL;//���캯����ʼ��ʱ��ͷָ���βָ�붼Ϊ�� 
	queuesize = 0;
}

template<class T>
linkedqueue<T>::~linkedqueue()
{
	while (queuefront != NULL)
	{
		chainnode<T>* nextnode = queuefront->next;
		delete queuefront;
		queuefront = nextnode;
	}
}

template<class T>
void linkedqueue<T>::pop()//ɾ�������У���ͷ�ڵ�ɾ������ָ����һ���ڵ� 
{
	chainnode<T>* nextnode = queuefront->next;
	delete queuefront;
	queuefront = nextnode;
	queuesize--;
}

template<class T>
void linkedqueue<T>::push(const T& theelement)//β�����뺯���У��½�һ���ڵ㣬Ȼ��βָ��ָ��ýڵ� 
{
	chainnode<T>* newnode=new chainnode<T>(theelement, NULL);
	if (queuesize == 0)
		queuefront = newnode;
	else
		queueback->next = newnode;
	queueback = newnode;
	queuesize++;
}
int main()
{
	int n;
	cin >> n;
	linkedqueue<int> puke(n);
	for (int i = 1; i <= n; i++)
		puke.push(i);
	while (puke.size() >= 2)
	{
		puke.pop();
		puke.push(puke.front());
		puke.pop();
	}

	cout << puke.back() << endl;
	return 0;
}


