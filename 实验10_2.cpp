#include<iostream>
#include<string> 
#include<algorithm>
using namespace std;

//二叉树节点结构体 
template<class T>
struct binarytreenode
{
	T element;
	binarytreenode<T>*leftchild,*rightchild;
	binarytreenode(){leftchild = rightchild = NULL;}
	binarytreenode(const T& theelement)
	{
		element = theelement;
		leftchild = rightchild = NULL;
	}
	binarytreenode(const T& theelement, binarytreenode *left, binarytreenode *right)
	{
		element = theelement;
		leftchild = left;
		rightchild = right;
	}
};
template<class T>
class linkedbinarytree
{
//	friend class huffmantree;

public:
	linkedbinarytree()
	{
		root = NULL;
		treesize = 0;
	}
	~linkedbinarytree(){postdelete(root);}
	void postdelete(binarytreenode<T>* t)
	{//后序遍历删除二叉树
		if (t != NULL)
		{
			postdelete(t->leftchild);
			postdelete(t->rightchild);
			delete t;
		}
	}
	//删除二叉树
	void posterasebinaryTree()
	{
		posterasebinaryTree(root);
		treesize = 0;
	}
	//创建新树
	void maketree(const T& element, linkedbinarytree<T>& left, linkedbinarytree<T>& right)
	{//将left，right和element合并成一棵新树
	//left，right和this必须是不同的树
		root = new binarytreenode<T>(element, left.root, right.root);
		treesize = left.treesize + right.treesize + 1;
		//阻止访问left和right
		left.root = NULL;
		right.root = NULL;
	}
	//重载赋值运算符
	linkedbinarytree<T>& operator=(linkedbinarytree<T>& t)
	{
		root = t.root;
		treesize = t.treesize;
		t.root = NULL;
		t.treesize = 0;
	}
private:
	binarytreenode<T>* root;
	int treesize;
};


class huffmannode
{
	friend class minheap;
	friend class huffmantree;
public:
	~huffmannode()
	{
		tree = NULL;
	}
	void operator=(const huffmannode& x)
	{
		weight = x.weight;
		tree = x.tree;
	}
private:
	int weight;
	linkedbinarytree<int> *tree;
};

class minheap
{
public:
	minheap(int n)
	{
		heapsize = n;
		arraylength = n + 1;
		heap = new huffmannode[arraylength];
	}
	~minheap()
	{
		if (heapsize != 0)
			delete[]heap;
	}
	void initialize(huffmannode* huffmantree)
	{
		if (heap != NULL)
		    delete[]heap;
//		arraylength = n + 1;
//		heapsize = n;
		heap = huffmantree;
		for (int root = heapsize / 2; root >= 1; root--)
		{
			huffmannode rootelement = heap[root];
			int child = root * 2;	
			while (child <= heapsize)
			{
				if (child<heapsize && heap[child].weight>heap[child + 1].weight)
					child++;
				if (rootelement.weight <= heap[child].weight)
					break;	
				heap[child / 2] = heap[child];	
				child *= 2;
			}
			heap[child / 2] = rootelement;
		}
	}
	void changeLength1D(huffmannode*& a, int oldlength, int newlength)
	{
		huffmannode* temp = new huffmannode[newlength];			
		int number = min(oldlength, newlength);		 
		copy(a, a + number, temp + 1);					
		delete[]a;									
		a = temp;
	}
	void push(const huffmannode& theelement)
	{
		if (heapsize == arraylength - 1)
		{
			changeLength1D(heap, arraylength, 2 * arraylength);
			arraylength *= 2;
		}
		int currentnode = ++heapsize;
		while (currentnode != 1 && heap[currentnode / 2].weight > theelement.weight)
		{
			heap[currentnode] = heap[currentnode / 2];	
			currentnode /= 2;									
		}
		heap[currentnode] = theelement;
	}
	//堆中删除霍夫曼节点函数 
	void pop()
	{
		if (heapsize == 0)
			return;
		huffmannode lastelement = heap[heapsize--];
		int currentnode = 1, child = 2;
		while (child <= heapsize)
		{
			//挑出孩子中的较小者
			if (child<heapsize&&heap[child].weight>heap[child + 1].weight)
				child++;
			//比孩子小则正确，退出。
			if (lastelement.weight <= heap[child].weight)
				break;	
			heap[currentnode] = heap[child];
			currentnode = child;						
			child *= 2;
		}
		heap[currentnode] = lastelement;
	}
	huffmannode& top() { return heap[1]; }
private:
	huffmannode* heap;
	int heapsize;
	int arraylength;
};

class huffmantree
{
public:
	huffmantree();
	~huffmantree();
	void initialize();
	void makehuffumantree();
	void getcLength(binarytreenode<int>* t, int length);
	int calCodelength();
private:
	char* letter;		//letter数组接收字符
	int* weight;			//记录字符频率
	int* lengthOfchar;			//用来统计每个字符在霍夫曼树中的路径长度 
	int arraylength;		//数组容量 
	int	differ;			//统计不同的字符个数 
	linkedbinarytree<int>* u;
};
huffmantree::huffmantree()
{
	letter = NULL;
	weight = NULL;
	lengthOfchar = NULL;
	arraylength = 0;
	differ = 0;
	u=NULL;
}
huffmantree::~huffmantree()
{
	if (letter != NULL)
		delete[]letter;
	if (weight != NULL)
		delete[]weight;
	if (lengthOfchar != NULL)
		delete[]lengthOfchar;
}
void huffmantree::initialize()
{
	string str;
	cin >> str;
	int length = str.length();		//求string变量长度 

	arraylength = length + 1;
	letter = new char[arraylength];
	weight = new int[arraylength];
	//字符频率数组初始化
	for (int i = 0; i < arraylength; i++)
		weight[i] = 0; 		//初始都为0 
	differ = 0;
	//给字符数组和字符频率数组赋值 ，都从1开始存数 
	for (int i = 0; i < length; i++)
	{
		char c = str[i];
		int j = 1;
		for (; j <= differ && letter[j] != c; j++);
		if (j == differ + 1)
		{
			letter[++differ] = c;
			weight[differ]++;
		}
		else
			weight[j]++;
	}
	lengthOfchar = new int[differ + 1];	
}
void huffmantree::makehuffumantree()
{//用权weight[1:n]生成霍夫曼树，n>=1
	//创建一组单节点树
	huffmannode* hnode = new huffmannode[differ + 1];
	linkedbinarytree<int> emptytree;
	for (int i = 1; i <= differ; i++)
	{
		hnode[i].weight = weight[i];
		hnode[i].tree = new linkedbinarytree<int>;
		hnode[i].tree->maketree(i, emptytree, emptytree);
	}
	//使一组单节点树构成小根堆
	minheap heap(differ);
	heap.initialize(hnode);
	huffmannode w, x, y;
	linkedbinarytree<int>* z;
	for (int i = 1; i < differ; i++)
	{
		//从小根堆里面提取两棵树合并，直到剩下一棵树
		x = heap.top();
		heap.pop();
		y = heap.top();
		heap.pop();
		//合并成一棵树
		z = new linkedbinarytree<int>;
		z->maketree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}
	
//	u = heap.top().tree;		//使二叉树指针指向霍夫曼树 
	getcLength(u->root,-1);
}
void huffmantree::getcLength(binarytreenode<int>* t, int length) 
{
	if (t != NULL)
	{
		length++;
		if (t->leftchild == NULL && t->rightchild == NULL)
		{
			lengthOfchar[t->element] = length;	
			return;
		}
		getcLength(t->leftchild, length);
		getcLength(t->rightchild, length);
	}
}

int huffmantree::calCodelength()
{
	getcLength(u->root,-1);
	int sum = 0;
	for (int i = 1; i <= differ; i++)
	{
		sum = sum + weight[i] * lengthOfchar[i];	
	}
	return sum;
}
int main()
{
	huffmantree huffmantree;
	huffmantree.initialize();
	huffmantree.makehuffumantree();
	cout << huffmantree.calCodelength() << endl;
	return 0;
}

