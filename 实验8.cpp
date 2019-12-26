#include <iostream>
using namespace std;
template<class K>
struct chainnode//定义一个结构体节点，用来存放当前元素值和下一个节点的地址 
{
	K element;
	chainnode<K>* next;

	chainnode() {}//节点的三种构造函数 
	chainnode(const K& theelement) { element = theelement; }
	chainnode(const K& theelement, chainnode<K>* thenext) { element = theelement; next = thenext; }
};
template<class K>
class sortedchain//定义一个链表类，实现的操作有返回链表大小，查询，尾部插入，删除指定元素函数 
{
public:
	sortedchain(int a = 10)
	{
		firstnode = NULL;
		listsize = 0;
	}
	~sortedchain()//析构函数中依次删除每个节点，释放节点空间 
	{
		while (firstnode != NULL)
		{
			chainnode<K>* nextnode = firstnode->next;
			delete firstnode;
			firstnode = nextnode;
		}
	}
	int size() { return listsize; }
	K* find(K& thekey)// 
	{
		chainnode<K>* currentnode = firstnode;
		while (currentnode != NULL && currentnode->element != thekey)
			currentnode = currentnode->next;
		if (currentnode != NULL && currentnode->element == thekey)
			return &currentnode->element;
		return NULL;
	}
	void push_back(K& theelement)//尾部插入函数中，首先判断链表是否为空，为空时需要考虑头节点的指向 
	{
		if (listsize == 0)
		{
			firstnode = new chainnode<K>(theelement, firstnode);
		}
		else
		{
			chainnode<K>* currentnode = firstnode;
			for (int i = 0; i < listsize - 1; i++)
				currentnode = currentnode->next;
			currentnode->next = new chainnode<K>(theelement, currentnode->next);
		}
		listsize++;
	}
	void erase(K& theelement)//删除指定元素节点时，首先找到该节点，然后释放空间 
	{
		chainnode<K>* deletenode;
		if (firstnode->element == theelement)
		{
			deletenode = firstnode;
			firstnode = firstnode->next;
		}
		else
		{
			chainnode<K>* currentnode = firstnode->next;
			chainnode<K>* previous = firstnode;
			while (currentnode->element != theelement)
			{
				currentnode = currentnode->next;
				previous = previous->next;
			}
			deletenode = currentnode;
			previous->next = deletenode->next;
		}
		listsize--;
		delete deletenode;
	}
private:
	chainnode<K>* firstnode;
	int listsize;
};
template<class K>
class hashchains//建立散列类 
{
public:
	hashchains(int a = 10);
	~hashchains() { delete[]table; }
	bool find(K& opt);
	void search(K& opt);
	void insert(K& opt);
	void erase(K& opt);
private:
	int dsize;//散列大小 
	int divisor;//除数 
	sortedchain<K>* table;//链表数组 
};
template<class K>
hashchains<K>::hashchains(int a)//构造函数中需要根据除数初始化动态链表 
{
	dsize = 0;
	divisor = a;
	table = new sortedchain<K>[divisor];
}
template<class K>
bool hashchains<K>::find(K& opt)//查询函数，判断元素是否存在 
{
	K* t = table[opt % divisor].find(opt);
	if (t == NULL)
		return false;
	else 
		return true;
}
template<class K>
void hashchains<K>::search(K& opt)//寻找指定元素，若找到，则返回元素所在链表的大小 
{
	bool ba = find(opt);
	if (ba == true)
		cout << table[opt % divisor].size() << endl;
	else cout << "Not Found" << endl;
}
template<class K>
void hashchains<K>::insert(K& opt)//尾部插入函数 
{
	bool ba = find(opt);
	if (ba == true)
		cout << "Existed" << endl;
	else
	{
		table[opt % divisor].push_back(opt);
		dsize++;
	}
}
template<class K>
void hashchains<K>::erase(K& opt)//删除指定位置函数 
{
	bool ba = find(opt);
	if (ba == false)
		cout << "Delete Failed" << endl;
	else
	{
		table[opt % divisor].erase(opt);
		dsize--;
		cout << table[opt % divisor].size() << endl;
	}
}
int main()
{
	int n,div;
	int num,opt;
	cin >> div >> n;//输入除数和操作数个数 
	hashchains<int> a(div);
	for (int i = 0; i < n; i++)
	{
		cin >> num >> opt;
		if (num == 0)
		    a.insert(opt);
		if (num == 1)
		    a.search(opt);
		if (num == 2)
		    a.erase(opt);
	}
	return 0;
}

