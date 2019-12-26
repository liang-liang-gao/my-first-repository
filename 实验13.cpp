#include <iostream>
#include <queue>
using namespace std;
//建立并查集
struct unionFindNode
{
	int parent;
	bool root;
	unionFindNode()
	{
		parent = 1; root = true;
	}
};
class unionFind
{
public:
	unionFind(int numberOfElements)
	{
		node = new unionFindNode[numberOfElements + 1];
	}

	int unite(int rootA, int rootB)
	{
		if (node[rootA].parent < node[rootB].parent)
		{
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
			return 0;
		}
		else
		{
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
			return 1;
		}
	}

	int find(int theElement)
	{
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;


		int currentNode = theElement;
		while (currentNode != theRoot)
		{
			int parentNode = node[currentNode].parent;
			node[currentNode].parent = theRoot;
			currentNode = parentNode;
		}
		return theRoot;
	}

protected:
	unionFindNode* node;
};
//建立权值边类
struct weightedEdge
{
	weightedEdge(int a = 0, int b = 0, int c = 0) :v1(a), v2(b), weight(c) {}
	int v1;//边连接的第一个点
	int v2;//边连接的第二个点
	int weight;//权值
	//operator int() { return weight; }
};
//建立小根堆类
class minheap
{
public:
	minheap(int n = 20);//小根堆的构造函数
	~minheap() { delete[]heap; }
	void makeheap(weightedEdge a[]);//小根堆的初始化
	void push(weightedEdge& theheap);//小根堆的插入
	void pop();//小根堆的删除
	weightedEdge top() { return heap[1]; }//小根堆返回最小点
private:
	weightedEdge* heap;
	int arraylength;
	int heapsize;
};
//template<class T>
minheap::minheap(int n)
{
	arraylength = n + 1;
	heap = new weightedEdge[n + 1];
	heapsize = n;
	//	cout<<n<<"ndezhi"<<endl;
}
//template<class T>
void minheap::makeheap(weightedEdge a[])
{
	delete[]heap;
	heap = a;
	for (int i = heapsize / 2; i >= 1; i--)
	{
		weightedEdge temp = heap[i];
		//		cout<<i<<" "<<heap[i].weight<<"asddsd"<<endl;
		int child = 2 * i;

		while (child <= heapsize)
		{
			if (child + 1 <= heapsize)
			{
				if (heap[child + 1].weight < heap[child].weight)
					child++;
			}
			if (heap[child].weight > temp.weight)
				break;
			heap[child / 2] = heap[child];
			child = child * 2;
		}
		heap[child / 2] = temp;
	}
}
void minheap::push(weightedEdge& theheap)
{
	if (heapsize >= arraylength - 1)
	{
		weightedEdge* newheap = new weightedEdge[2 * arraylength];
		for (int i = 1; i <= heapsize; i++)
			newheap[i] = heap[i];
		delete[]heap;
		heap = newheap;
		arraylength = 2 * arraylength;
	}
	heap[++heapsize] = theheap;
	int temp = heapsize;//temp是待插入的位置 
	while (temp > 1 && heap[temp / 2].weight > theheap.weight)
	{
		heap[temp] = heap[temp / 2];
		temp = temp / 2;
	}
	heap[temp] = theheap;
	//cout << heap[1] << endl;
}
void minheap::pop()
{
	//heap[1].~();
	weightedEdge temp = heap[heapsize--];
	int child = 2;
	while (child <= heapsize)
	{
		if (heap[child + 1].weight < heap[child].weight && child + 1 <= heapsize)
			child++;
		if (temp.weight < heap[child].weight)
			break;
		heap[child / 2] = heap[child];
		child = child * 2;
	}
	heap[child / 2] = temp;
}
int main()
{

	int n, m, q, k = 0;
	int u, v, w;
	cin >> n >> m >> q;
	weightedEdge* edge = new weightedEdge[m + 1];//建立边数组 
	weightedEdge current;
	minheap heap(m);
	for (int i = 1; i <= m; i++)
	{

		cin >> u >> v >> w;
		edge[i] = weightedEdge(u, v, w);
	}

	heap.makeheap(edge);//用边数组初始化小根堆 
	unionFind uf(n);//建立并查集
	int* sum = new int[n + 1];//sum用来记录最小生成树的权值之和。初始时每个点为一棵生成树 
	for (int i = 0; i <= n; i++)
		sum[i] = 0;
	while (k < m)
	{
		weightedEdge x = heap.top();//取出最小权值的边 
		heap.pop();
		int a = uf.find(x.v1);
		int b = uf.find(x.v2);
		if (a != b)//判断会不会形成环 
		{
			int temp = uf.unite(a, b);//并查集合并 
			if (temp == 1)
				sum[a] += sum[b] + x.weight;
			else
				sum[b] += sum[a] + x.weight;
		}
		k++;
	}
	int s;
	for (int i = 0; i < q; i++)
	{
		cin >> s;
		v = uf.find(s);//找到对应的头节点并输出 
		cout << sum[v] << endl;
	}
	return 0;
}
