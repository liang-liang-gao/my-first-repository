#include<iostream>
#include<queue>
using namespace std;
template<class T>
struct chainnode//������ڵ�Ķ��� 
{
	T element;
	chainnode<T>* next;

	chainnode() {}
	chainnode(const T& theelement) { element = theelement; }
	chainnode(const T& theelement, chainnode<T>* thenext)
	{
		element = theelement; next = thenext;
	}
};
template<class T>
class chain//���������� 
{
public:
	friend class linkedGraph;
	chain(int a = 10);
	~chain();
	void erase(const T& theelement);
	void sortedinsert(const T& theelement);//����һ�������������ĺ�����Ϊ����ʵ���ֵ�����׼�� 
	int size() { return listsize; }
private:
	chainnode<T>* firstnode;
	int listsize;
};

template<class T>
chain<T>::chain(int a)
{
	firstnode = NULL;
	listsize = 0;
}

template<class T>
chain<T>::~chain()
{
	while (firstnode != NULL)
	{
		chainnode<T>* nextnode = firstnode->next;
		delete firstnode;
		firstnode = nextnode;
	}
}

template<class T>
void chain<T>::sortedinsert(const T& theelement)
{
	if (firstnode == NULL||theelement<firstnode->element)//��Ҫ�ı�firstnodeָ���������� 
		firstnode = new chainnode<T>(theelement, firstnode);
	else
	{
		chainnode<T>* pre = firstnode;
		chainnode<T>* current = firstnode->next;//��������ָ�룬����������ʱ�ҵ���Ӧ�ڵ� 
		while (current != NULL&&theelement >= current->element)//whileѭ���ҵ��������λ�� 
		{
			pre = current;
			current = current->next;
		}
		pre->next = new chainnode<T>(theelement, current);//�����½����Ľڵ� 
	}
	listsize++;
}

template<class T>
void chain<T>::erase(const T& theelement)
{
	chainnode<T>* deletenode;
	if (firstnode->element == theelement)
	{
		deletenode = firstnode;
		firstnode = firstnode->next;
	}
	else
	{
		chainnode<T>* currentnode = firstnode->next;
		chainnode<T>* previous = firstnode;
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


class linkedGraph//����������Ȩ�ڽ����� 
{
public:
	linkedGraph(int a = 0);
	~linkedGraph() { delete[]aList; delete[]c; }
	void insertEdge(int i, int j);
	void eraseEdge(int i, int j);
	int labelComponents();//������ǣ������ͨ�����ĸ��� 
	int bfs(int v, int label);//������ȱ�����
	int bfs(int v, int label, int* b);
	//int dfs(int v, int label);//����������� 
	int dfs(int v, int label, int* b);
	//void rDfs(int v, int& length);//������ȵݹ�ʵ�� 
	void rDfs(int v, int& length, int* b);
	int findPath(int s, int t,int* pre);
	bool rfindPath(int s, int t, int& length,int *pre);
	void output(int s, int t);
private:
	int n;//ͼ�е�ĸ��� 
	int e;//ͼ�бߵĸ��� 
	int* c;//�������ĳ���Ƿ��ѵ��� 
	int lab;//������Ϊ����ı�� 
	chain<int>* aList;//�������飬������¼��ÿ���������ĵ� 
};
linkedGraph::linkedGraph(int a)
{
	n = a;
	e = 0;
	lab = 1;
	c = new int[n + 1];
	aList = new chain<int>[n + 1];
}

void linkedGraph::insertEdge(int i, int j)//������������������һ����ʱ����ͬʱ������������ڽ����� 
{
	aList[i].sortedinsert(j);
	aList[j].sortedinsert(i);
	e++;
}

void linkedGraph::eraseEdge(int i, int j)
{
	if (i >= 1 && j >= 1 && i <= n && j <= n)
	{
		aList[i].erase(j);
		aList[j].erase(i);
		e--;
	}
}

int linkedGraph::bfs(int v, int label)//v��bfs��������㣬label�Ǳ��ֵ���������ص���bfs���еĳ��� 
{
	int lgt = 1;
	queue<int> q;
	c[v] = label;
	q.push(v);
	//	min=v;
	while (!q.empty())
	{
		int w = q.front();
		q.pop();
		for (chainnode<int>* u = aList[w].firstnode; u != NULL; u = u->next)
		{
			if (c[u->element] == 0)
			{
				q.push(u->element);
				lgt++;
				//				if(u->element<w)
				//				    min=u->element;
				c[u->element] = label;
			}
		}
	}
	return lgt;
}

int linkedGraph::bfs(int v,  int label, int* b)//bfs�����غ�������Ҫ�����¼�ֵ�����С��bfs���� 
{
	int lgt = 1;
	queue<int> q;
	c[v] = label;
	b[lgt] = v;
	q.push(v);
	//	min=v;
	//while (!q.empty())
	//{
	//	int w = q.front();
	//	q.pop();
	//	int m = 0;
	//	int size = aList[w].size();
	//	int* temp = new int[size];
	//	for (chainnode<int>* u = aList[w].firstnode; u != NULL; u = u->next)
	//	{
	//		temp[m] = u->element;
	//		m++;
	//	}
	//	sort(temp, temp + size);
	//	for (int i = 0; i < size; i++)
	//	{
	//		if (c[temp[i]] == 0)
	//		{
	//			q.push(temp[i]);
	//			lgt++;
	//			b[lgt] = temp[i];
	//			//				if(u->element<w)
	//			//				    min=u->element;
	//			c[temp[i]] = label;
	//		}
	//	}
	//}
	//return lgt;
	while (!q.empty())
	{
		int w = q.front();
		q.pop();
		for (chainnode<int>* u = aList[w].firstnode; u != NULL; u = u->next)
		{
			if (c[u->element] == 0)
			{
				q.push(u->element);
				lgt++;
				b[lgt] = u->element;
				//				if(u->element<w)
				//				    min=u->element;
				c[u->element] = label;
			}
		}
	}
	return lgt;
}
//int linkedGraph::dfs(int v, int label)
//{
//	int lgt = 1;//����������ȳ�ʼֵΪ1
//	lab = label;
//	rDfs(v, lgt);
//	return lgt;
//}
//void linkedGraph::rDfs(int v, int& length)
//{
//	c[v] = lab;
//	for (chainnode<int>* u = aList[v].firstnode; u != NULL; u = u->next)
//		if (c[u->element] == 0)
//		{
//			length++;
//			rDfs(u->element, length);
//		}
//}
int linkedGraph::dfs(int v, int label, int* b)//v����ʼ�㣬label�Ǳ��ֵ��ָ��b������¼dfs���� 
{
	int lgt = 1;//����������ȳ�ʼֵΪ1
	lab = label;
	rDfs(v, lgt, b);//����b������¼�ֵ����� 
	return lgt;
}
void linkedGraph::rDfs(int v, int& length, int* b)//dfs�ݹ�����ڵ� 
{
	b[length] = v;
	c[v] = lab;
	//int m = 0;
	//int size = aList[v].size();
	//int* temp = new int[size];
	for (chainnode<int>* u = aList[v].firstnode; u != NULL; u = u->next)
	{
		if (c[u->element] == 0)
		{
			length++;
			rDfs(u->element, length, b);
		}
		//temp[m] = u->element;
		//m++;
		//length++;
		//rDfs(u->element, length, b);  
	}
	//sort(temp, temp + size);
	//	for(int i=1;i<=size;i++)
	//	    cout<<"sad"<<temp[i]<<endl;
	//for (int i = 0; i < size; i++)
	//	if (c[temp[i]] == 0)
	//	{
	//		length++;
	//		rDfs(temp[i], length, b);

	//	}
	//delete[]temp;
}
int linkedGraph::labelComponents()//����������ͨ��ͼ�ĸ��� 
{
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	lab = 0;
	for (int i = 1; i <= n; i++)
	{
		if (c[i] == 0)
		{
			lab++;
			bfs(i, lab);//����bfs���в��� 
		}
	}
	return lab;
}
int linkedGraph::findPath(int s, int t,int *pre)//s��t�ֱ��������յ㣬pre�Ǽ�¼���е�ָ�룬�������� 
{
	int length = 0;
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	if (s == t || rfindPath(s, t, length, pre))//���������ͬһ����ߴ������·������ 
	{
		int v=pre[t];
		while (v != -1)
		{
			v = pre[v];
			length++;
		}
	}
	else
		length = -1;
	return length;
}
bool linkedGraph::rfindPath(int s, int t, int& length,int *pre) 
{
	queue<int> q;
	c[s] = 1;
	q.push(s);
	while (!q.empty())
	{
		int w = q.front();
		q.pop();
		for (chainnode<int>* u = aList[w].firstnode; u != NULL; u = u->next)
		{
			if (c[u->element] == 0)
			{
				/*length++;*/
				pre[u->element] = w;
				q.push(u->element);


				//				if(u->element<w)
				//				    min=u->element;
				c[u->element] = 1;
				if (u->element == t)//����ҵ����·����ֱ�ӷ����� 
					return true;
			}
		}
	}
	return false;
}
void linkedGraph::output(int s, int t)
{
	int x = labelComponents();
	//��һ�������ֵ    �� 
	cout << x << endl;

	//sort(c,c+n);
	//for(int i=)
	int out=0;//out������ǵڼ�����ͨ��ͼ
	//int* a = new int[x + 1];
	//for (int i = 1; i <= n; i++)
	//	a[i] = 0;
	bool* min = new bool[x + 1];//min������¼ÿ��Ԫ�����ڵ���ͨ��ͼ����СԪ���Ƿ����
	for (int i = 1; i <= x; i++)
		min[i] = false;
	for (int i = 1; i <= n; i++)
	{
		if (min[c[i]] == false)
		{
			cout << i << " ";
			min[c[i]] = true;
			out++;
	
			if (out == x)
				break;
		}

	}
	cout << endl;
	////�ڶ��������ֵ	�� 
	//for (int i = 1; i <= x; i++)
	//	cout << min[i] <<" ";
	//cout << endl;

	int* m = new int[n + 1];
	for (int i = 1; i <= n; i++)
		m[i] = 0;
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	int temp = dfs(s, 1,m);
	//�����������ֵ    �� 
	cout << temp << endl;

	//
	//for (int i = 1; i <= n; i++)
	//	c[i] = 0;
	//dfs(s, 1, m);
	////�����������ֵ    �� 
	for (int i = 1; i <= temp; i++)
		cout << m[i] << " ";
	cout << endl;

	for (int i = 1; i <= n; i++)
		c[i] = 0;
	for (int i = 1; i <= temp; i++)
		m[i] = 0;
	int temp2 = bfs(t, 1,m);
	//�����������ֵ    ��
	cout << temp2 << endl;

	//for (int i = 1; i <= n; i++)
	//	c[i] = 0;

	//bfs(t, 1, m);
	////�����������ֵ    �� 
	for (int i = 1; i <= temp2; i++)
		cout << m[i] << " ";
	cout << endl;

	int* path = new int[n + 1];
	path[s] = -1;
	temp = findPath(s, t,path);
	//�����������ֵ    ��
	cout << temp << endl;

	//delete []min;
	delete []path;
	//delete[]a;
	delete[]m;

}
int main()
{
	int n, m, s, t;
	int num, u, v;
	cin >> n >> m >> s >> t;
	linkedGraph a(n);
	for (int i = 0; i < m; i++)
	{
		cin >> num >> u >> v;
		if (num == 0)
			a.insertEdge(u, v);
		else
			a.eraseEdge(u, v);
	}
	a.output(s, t);
	return 0;
}





