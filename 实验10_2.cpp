#include<iostream>
#include<string> 
#include<algorithm>
using namespace std;

//�������ڵ�ṹ�� 
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
	{//�������ɾ��������
		if (t != NULL)
		{
			postdelete(t->leftchild);
			postdelete(t->rightchild);
			delete t;
		}
	}
	//ɾ��������
	void posterasebinaryTree()
	{
		posterasebinaryTree(root);
		treesize = 0;
	}
	//��������
	void maketree(const T& element, linkedbinarytree<T>& left, linkedbinarytree<T>& right)
	{//��left��right��element�ϲ���һ������
	//left��right��this�����ǲ�ͬ����
		root = new binarytreenode<T>(element, left.root, right.root);
		treesize = left.treesize + right.treesize + 1;
		//��ֹ����left��right
		left.root = NULL;
		right.root = NULL;
	}
	//���ظ�ֵ�����
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
	//����ɾ���������ڵ㺯�� 
	void pop()
	{
		if (heapsize == 0)
			return;
		huffmannode lastelement = heap[heapsize--];
		int currentnode = 1, child = 2;
		while (child <= heapsize)
		{
			//���������еĽ�С��
			if (child<heapsize&&heap[child].weight>heap[child + 1].weight)
				child++;
			//�Ⱥ���С����ȷ���˳���
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
	char* letter;		//letter��������ַ�
	int* weight;			//��¼�ַ�Ƶ��
	int* lengthOfchar;			//����ͳ��ÿ���ַ��ڻ��������е�·������ 
	int arraylength;		//�������� 
	int	differ;			//ͳ�Ʋ�ͬ���ַ����� 
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
	int length = str.length();		//��string�������� 

	arraylength = length + 1;
	letter = new char[arraylength];
	weight = new int[arraylength];
	//�ַ�Ƶ�������ʼ��
	for (int i = 0; i < arraylength; i++)
		weight[i] = 0; 		//��ʼ��Ϊ0 
	differ = 0;
	//���ַ�������ַ�Ƶ�����鸳ֵ ������1��ʼ���� 
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
{//��Ȩweight[1:n]���ɻ���������n>=1
	//����һ�鵥�ڵ���
	huffmannode* hnode = new huffmannode[differ + 1];
	linkedbinarytree<int> emptytree;
	for (int i = 1; i <= differ; i++)
	{
		hnode[i].weight = weight[i];
		hnode[i].tree = new linkedbinarytree<int>;
		hnode[i].tree->maketree(i, emptytree, emptytree);
	}
	//ʹһ�鵥�ڵ�������С����
	minheap heap(differ);
	heap.initialize(hnode);
	huffmannode w, x, y;
	linkedbinarytree<int>* z;
	for (int i = 1; i < differ; i++)
	{
		//��С����������ȡ�������ϲ���ֱ��ʣ��һ����
		x = heap.top();
		heap.pop();
		y = heap.top();
		heap.pop();
		//�ϲ���һ����
		z = new linkedbinarytree<int>;
		z->maketree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}
	
//	u = heap.top().tree;		//ʹ������ָ��ָ��������� 
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

