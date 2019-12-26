#include <iostream>
using namespace std;
template<class T>
struct chainnode//定义一个结构体节点，用来存放当前元素值和下一个节点的地址 
{
	T element;
	chainnode<T>* next;

	chainnode(){}//节点的三种构造函数 
	chainnode(const T& theelement) { element = theelement; }
	chainnode(const T& theelement, chainnode<T>* thenext) { element = theelement; next = thenext; }
};
template<class T>
class linkedqueue
{
public:
	linkedqueue(int a = 10);
	~linkedqueue();
	T& front() { return queuefront->element; }//返回队列的队首元素 
	T& back() { return queueback->element; }//返回队列的队尾元素 
	void pop();//删除队首元素 
	void push(const T& theelement);//从队尾插入元素 
	int size() { return queuesize; }//返回队列的大小 
private:
	chainnode<T>* queuefront;//一个指向队首的指针 
	chainnode<T>* queueback;//一个指向队尾的指针 
	int queuesize;//队列大小 
};

template<class T>
linkedqueue<T>::linkedqueue(int a)
{
	queuefront = queueback = NULL;//构造函数初始化时令头指针和尾指针都为空 
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
void linkedqueue<T>::pop()//删除函数中，将头节点删除，并指向下一个节点 
{
	chainnode<T>* nextnode = queuefront->next;
	delete queuefront;
	queuefront = nextnode;
	queuesize--;
}

template<class T>
void linkedqueue<T>::push(const T& theelement)//尾部插入函数中，新建一个节点，然后将尾指针指向该节点 
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


