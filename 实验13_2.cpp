#include <iostream>
#include <queue>
using namespace std;
//�������鼯
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
//����Ȩֵ����
struct weightedEdge
{
	weightedEdge(int a = 0, int b = 0, int c = 0) :v1(a), v2(b), weight(c) {}
	int v1;//�����ӵĵ�һ����
	int v2;//�����ӵĵڶ�����
	int weight;//Ȩֵ
	//operator int() { return weight; }
};
//����С������
class minheap
{
public:
	minheap(int n = 20);//С���ѵĹ��캯��
	~minheap() { delete[]heap; }
	void makeheap(weightedEdge a[]);//С���ѵĳ�ʼ��
	void push(weightedEdge& theheap);//С���ѵĲ���
	void pop();//С���ѵ�ɾ��
	weightedEdge top() { return heap[1]; }//С���ѷ�����С��
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
	int temp = heapsize;//temp�Ǵ������λ�� 
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
	weightedEdge* edge = new weightedEdge[m + 1];
	weightedEdge current;
	minheap heap(m);
	for (int i = 1; i <= m; i++)//�ڽӾ����в����
	{

		cin >> u >> v >> w;
		edge[i] = weightedEdge(u, v, w);
		//temp.insertEdge(edge[i]);//��û���ظ�������
	}

	heap.makeheap(edge);//��ʼ��С���� 
	unionFind uf(n);//�������鼯
	int* sum = new int[n + 1];//sum������¼��С��������Ȩֵ֮�͡���ʼʱÿ����Ϊһ�������� 
	for (int i = 0; i <= n; i++)
		sum[i] = 0;
	while (k < m)
	{
		weightedEdge x = heap.top();
		heap.pop();
		int a = uf.find(x.v1);
		int b = uf.find(x.v2);
		if (a != b)//�жϻ᲻���γɻ� 
		{
			int temp = uf.unite(a, b);
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
		v = uf.find(s);
		cout << sum[v] << endl;
	}
	return 0;
}
