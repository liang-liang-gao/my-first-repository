#include <iostream>
using namespace std;
template<class K>
struct chainnode//����һ���ṹ��ڵ㣬������ŵ�ǰԪ��ֵ����һ���ڵ�ĵ�ַ 
{
	K element;
	chainnode<K>* next;

	chainnode() {}//�ڵ�����ֹ��캯�� 
	chainnode(const K& theelement) { element = theelement; }
	chainnode(const K& theelement, chainnode<K>* thenext) { element = theelement; next = thenext; }
};
template<class K>
class sortedchain//����һ�������࣬ʵ�ֵĲ����з��������С����ѯ��β�����룬ɾ��ָ��Ԫ�غ��� 
{
public:
	sortedchain(int a = 10)
	{
		firstnode = NULL;
		listsize = 0;
	}
	~sortedchain()//��������������ɾ��ÿ���ڵ㣬�ͷŽڵ�ռ� 
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
	void push_back(K& theelement)//β�����뺯���У������ж������Ƿ�Ϊ�գ�Ϊ��ʱ��Ҫ����ͷ�ڵ��ָ�� 
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
	void erase(K& theelement)//ɾ��ָ��Ԫ�ؽڵ�ʱ�������ҵ��ýڵ㣬Ȼ���ͷſռ� 
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
class hashchains//����ɢ���� 
{
public:
	hashchains(int a = 10);
	~hashchains() { delete[]table; }
	bool find(K& opt);
	void search(K& opt);
	void insert(K& opt);
	void erase(K& opt);
private:
	int dsize;//ɢ�д�С 
	int divisor;//���� 
	sortedchain<K>* table;//�������� 
};
template<class K>
hashchains<K>::hashchains(int a)//���캯������Ҫ���ݳ�����ʼ����̬���� 
{
	dsize = 0;
	divisor = a;
	table = new sortedchain<K>[divisor];
}
template<class K>
bool hashchains<K>::find(K& opt)//��ѯ�������ж�Ԫ���Ƿ���� 
{
	K* t = table[opt % divisor].find(opt);
	if (t == NULL)
		return false;
	else 
		return true;
}
template<class K>
void hashchains<K>::search(K& opt)//Ѱ��ָ��Ԫ�أ����ҵ����򷵻�Ԫ����������Ĵ�С 
{
	bool ba = find(opt);
	if (ba == true)
		cout << table[opt % divisor].size() << endl;
	else cout << "Not Found" << endl;
}
template<class K>
void hashchains<K>::insert(K& opt)//β�����뺯�� 
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
void hashchains<K>::erase(K& opt)//ɾ��ָ��λ�ú��� 
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
	cin >> div >> n;//��������Ͳ��������� 
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

