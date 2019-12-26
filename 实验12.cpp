#include<iostream>
#include<queue>
using namespace std;
template<class T>
struct chainnode//单链表节点的定义 
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
class chain//建立链表类 
{
public:
	friend class linkedGraph;
	chain(int a = 10);
	~chain();
	void erase(const T& theelement);
	void sortedinsert(const T& theelement);//定义一个有序插入链表的函数，为后面实现字典序做准备 
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
	if (firstnode == NULL||theelement<firstnode->element)//需要改变firstnode指向的两种情况 
		firstnode = new chainnode<T>(theelement, firstnode);
	else
	{
		chainnode<T>* pre = firstnode;
		chainnode<T>* current = firstnode->next;//建立两个指针，方面后面插入时找到对应节点 
		while (current != NULL&&theelement >= current->element)//while循环找到待插入的位置 
		{
			pre = current;
			current = current->next;
		}
		pre->next = new chainnode<T>(theelement, current);//插入新建立的节点 
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


class linkedGraph//建立无向无权邻接链表 
{
public:
	linkedGraph(int a = 0);
	~linkedGraph() { delete[]aList; delete[]c; }
	void insertEdge(int i, int j);
	void eraseEdge(int i, int j);
	int labelComponents();//构建标记，求得连通分量的个数 
	int bfs(int v, int label);//广度优先遍搜索
	int bfs(int v, int label, int* b);
	//int dfs(int v, int label);//深度优先搜索 
	int dfs(int v, int label, int* b);
	//void rDfs(int v, int& length);//深度优先递归实现 
	void rDfs(int v, int& length, int* b);
	int findPath(int s, int t,int* pre);
	bool rfindPath(int s, int t, int& length,int *pre);
	void output(int s, int t);
private:
	int n;//图中点的个数 
	int e;//图中边的个数 
	int* c;//用来标记某点是否已到达 
	int lab;//用来作为到达的标记 
	chain<int>* aList;//链表数组，用来记录和每个点相连的点 
};
linkedGraph::linkedGraph(int a)
{
	n = a;
	e = 0;
	lab = 1;
	c = new int[n + 1];
	aList = new chain<int>[n + 1];
}

void linkedGraph::insertEdge(int i, int j)//由于是无向链表，插入一条边时必须同时操作两个点的邻接链表 
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

int linkedGraph::bfs(int v, int label)//v是bfs遍历的起点，label是标记值。函数返回的是bfs序列的长度 
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

int linkedGraph::bfs(int v,  int label, int* b)//bfs的重载函数，需要额外记录字典序最小的bfs序列 
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
//	int lgt = 1;//深度搜索长度初始值为1
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
int linkedGraph::dfs(int v, int label, int* b)//v是起始点，label是标记值，指针b用来记录dfs序列 
{
	int lgt = 1;//深度搜索长度初始值为1
	lab = label;
	rDfs(v, lgt, b);//数组b用来记录字典序列 
	return lgt;
}
void linkedGraph::rDfs(int v, int& length, int* b)//dfs递归遍历节点 
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
int linkedGraph::labelComponents()//函数返回连通子图的个数 
{
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	lab = 0;
	for (int i = 1; i <= n; i++)
	{
		if (c[i] == 0)
		{
			lab++;
			bfs(i, lab);//调用bfs序列查找 
		}
	}
	return lab;
}
int linkedGraph::findPath(int s, int t,int *pre)//s和t分别是起点和终点，pre是记录序列的指针，函数返回 
{
	int length = 0;
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	if (s == t || rfindPath(s, t, length, pre))//如果两者是同一点或者存在最短路径，则 
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
				if (u->element == t)//如果找到最短路径，直接返回真 
					return true;
			}
		}
	}
	return false;
}
void linkedGraph::output(int s, int t)
{
	int x = labelComponents();
	//第一行输出的值    √ 
	cout << x << endl;

	//sort(c,c+n);
	//for(int i=)
	int out=0;//out用来标记第几个连通子图
	//int* a = new int[x + 1];
	//for (int i = 1; i <= n; i++)
	//	a[i] = 0;
	bool* min = new bool[x + 1];//min用来记录每个元素所在的连通子图的最小元素是否被输出
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
	////第二行输出的值	√ 
	//for (int i = 1; i <= x; i++)
	//	cout << min[i] <<" ";
	//cout << endl;

	int* m = new int[n + 1];
	for (int i = 1; i <= n; i++)
		m[i] = 0;
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	int temp = dfs(s, 1,m);
	//第三行输出的值    √ 
	cout << temp << endl;

	//
	//for (int i = 1; i <= n; i++)
	//	c[i] = 0;
	//dfs(s, 1, m);
	////第四行输出的值    √ 
	for (int i = 1; i <= temp; i++)
		cout << m[i] << " ";
	cout << endl;

	for (int i = 1; i <= n; i++)
		c[i] = 0;
	for (int i = 1; i <= temp; i++)
		m[i] = 0;
	int temp2 = bfs(t, 1,m);
	//第五行输出的值    √
	cout << temp2 << endl;

	//for (int i = 1; i <= n; i++)
	//	c[i] = 0;

	//bfs(t, 1, m);
	////第六行输出的值    √ 
	for (int i = 1; i <= temp2; i++)
		cout << m[i] << " ";
	cout << endl;

	int* path = new int[n + 1];
	path[s] = -1;
	temp = findPath(s, t,path);
	//第七行输出的值    √
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





