#include"stdio.h"
#include<iostream>
using namespace std;
template<class T>
struct binaryTreeNode
{
	T element;
	int leftsize;//针对索引二叉搜索树，节点中需要增加记录左子树大小的数据leftsize
	binaryTreeNode<T>* leftChild, * rightChild;
	binaryTreeNode() { leftChild = rightChild = NULL; leftsize = 0; }
	binaryTreeNode(T theelement) { element = theelement; leftChild = rightChild = NULL; leftsize = 0;}
	binaryTreeNode(T theelement, binaryTreeNode* left, binaryTreeNode* right,int size)
	{
		element = theelement;
		leftChild = left;
		rightChild = right;
		leftsize = size;
	}
};
//template<class T>
class indexedBinarySearchTree
{
public:
	indexedBinarySearchTree();
	~indexedBinarySearchTree() { postdelete(root); }
	void postdelete(binaryTreeNode<int>* t);//后序遍历删除函数
	bool search(int k);//判断元素是否存在的函数
	void find(int k);//查找函数           √
	void get(int k);//按名次查找函数      √
	void insert(int k);//插入函数         √
	void erase(int k);//删除函数          √
	void indexedErase(int k);//按名次删除函数     √
private:
	binaryTreeNode<int>* root;
	int treesize;
};
indexedBinarySearchTree::indexedBinarySearchTree()
{
	root = NULL;
	treesize = 0;
}
void indexedBinarySearchTree::postdelete(binaryTreeNode<int>* t)
{//后序遍历删除二叉树
	if (t != NULL)
	{
		postdelete(t->leftChild);
		postdelete(t->rightChild);
		delete t;
	}
}
bool indexedBinarySearchTree::search(int k)
{
	binaryTreeNode<int>* p = root;
	while (p != NULL)
	{
		if (k < p->element)
			p = p->leftChild;
		else
			if (k > p->element)
				p = p->rightChild;
			else
				return true;//代表该值存在
	}
	return false;//代表该值不存在
}
void  indexedBinarySearchTree::insert(int k)
{
	bool temp = search(k);
	if (temp == true)//若元素已经存在，则可以直接输出0
		cout << 0 << endl;
	else
	{
		binaryTreeNode<int>* p = root, * pp = NULL;//pp始终指向p的父节点，用来最后指向新增加的节点
		int sum = 0;
		while (p != NULL)
		{
			sum ^= p->element;
			pp = p;
			if (k < p->element)
			{
				p->leftsize++;
				p = p->leftChild;
			}
			else
				p = p->rightChild;
		}
		binaryTreeNode<int>* newnode = new binaryTreeNode<int>(k);
		if (root != NULL)
			if (k < pp->element)
				pp->leftChild = newnode;
			else
				pp->rightChild = newnode;
		else                //如果此时树中没有节点，则需要创立新的根节点
			root = newnode;
		treesize++;
		cout << sum << endl;
	}

}
void indexedBinarySearchTree::find(int k)
{
	bool temp = search(k);
	if (temp == false)//先判断元素是否存在，若不存在，则直接输出0
		cout << 0 << endl;
	else
	{
		binaryTreeNode<int>* p = root;
		int sum = 0;
		while (p != NULL)
		{
			sum ^= p->element;
			if (k < p->element)
				p = p->leftChild;
			else
				if (k > p->element)
					p = p->rightChild;
				else
					break;
		}
		cout << sum << endl;
	}
}

void indexedBinarySearchTree::get(int k)
{
	if (k > treesize || treesize == 0)//若要查找的元素索引超出二叉树的大小，或者二叉树无元素，则直接输出0
		cout << 0 << endl;
	else
	{
		int m = k - 1;//由于节点的leftsize是从0开始的，因此取m为用来比较遍历的值
		binaryTreeNode<int>* p = root;
		int sum = 0;
		while (p != NULL)
		{
			sum ^=  p->element;
			if (m < p->leftsize)
				p = p->leftChild;
			else
				if (m > p->leftsize)//如果查找的元素在右子树中，则需要更改m的大小
				{
					m = m - (p->leftsize + 1);
					p = p->rightChild;
				}
				else
					break;
		}
		cout << sum << endl;
	}
}

void indexedBinarySearchTree::erase(int k)
{
	bool temp = search(k);
	if (temp == false)
		cout << 0 << endl;
	else
	{
		binaryTreeNode<int>* p = root, * pp = NULL;//pp用来指向删除节点的父节点，方便修改指向
		int sum = 0;
		while (p != NULL&&p->element!=k)
		{
			sum ^= p->element;
			pp = p;
			if (k < p->element)
			{
				p->leftsize--;//当要删除的节点位于当前节点的左子树时，当前节点的leftsize需要减一
				p = p->leftChild;
			}
			else
				p = p->rightChild;
		}

		if (p != NULL)
		{
			sum ^= p->element;//最后还要和待删除的元素进行异或
			//接下来将分三种情况考虑节点的删除

			if (p->leftChild != NULL && p->rightChild != NULL)//如果要删除的节点左右子树都存在的情况
			{
				binaryTreeNode<int>* s = p->rightChild, * ps = p;//s是为了找出待删除结点的右子树中值最小的节点，ps是s节点的父节点
				while (s->leftChild != NULL)
				{
					ps = s;
					s->leftsize--;//!!!!!!!!!!!!在寻找替代节点时，也要将路径上的节点的leftsize减一
					s = s->leftChild;
				}
				binaryTreeNode<int>* q = new binaryTreeNode<int>(s->element, p->leftChild, p->rightChild, p->leftsize);//利用替代节点的值创建新的节点

				if (pp == NULL)
					root = q;
				else
				{
					if (p == pp->leftChild)
						pp->leftChild = q;
					else
						pp->rightChild = q;
				}
				if (ps == p) pp = q;//此时已经没有节点指向p节点，因此需要单独考虑这种情况
				else pp = ps;
				delete p;//释放p原来指向的节点空间
				p = s;
			}
			binaryTreeNode<int>* c;
			if (p->leftChild != NULL)
				c = p->leftChild;//记录p下面的一个节点
			else
				c = p->rightChild;
			if (p == root)
				root = c;
			else
			{
				if (p == pp->leftChild)
					pp->leftChild = c;
				else pp->rightChild = c;
			}
			treesize--;
			delete p;//释放要删除的节点空间
			cout << sum << endl;
		}
	}

}

void indexedBinarySearchTree::indexedErase(int k)//思路同以上类似，先找出第k大的元素，然后对该节点进行删除操作
{
	if (k > treesize||root==NULL)
		cout << 0 << endl;
	else
	{
		int m = k - 1;
		binaryTreeNode<int>* p = root,*pp=NULL;
		int sum = 0;
		while (p != NULL && p->leftsize != m)
		{
			sum = sum ^ p->element;
			pp = p;
			if (m < p->leftsize)
			{
				p->leftsize--;
				p = p->leftChild;
			}
			else
				if (m > p->leftsize)
				{
					m = m - (p->leftsize + 1);
					p = p->rightChild;
				}
		}
		if (p != NULL)
		{
			sum = sum ^ p->element;
			if (p->leftChild != NULL && p->rightChild != NULL)
			{
				binaryTreeNode<int>* s = p->rightChild, * ps = p;
				while (s->leftChild != NULL)
				{
					ps = s;
					s->leftsize--;
					s = s->leftChild;
				}
				binaryTreeNode<int>* q = new binaryTreeNode<int>(s->element, p->leftChild, p->rightChild, p->leftsize);
				if (pp == NULL)
					root = q;
				else
				{
					if (p == pp->leftChild)
						pp->leftChild = q;
					else
						pp->rightChild = q;
				}
				if (ps == p) pp = q;
				else pp = ps;
				delete p;
				p = s;
			}
			binaryTreeNode<int>* c;
			if (p->leftChild != NULL)
				c = p->leftChild;
			else
				c = p->rightChild;
			if (p == root)
				root = c;
			else
			{
				if (p == pp->leftChild)
					pp->leftChild = c;
				else pp->rightChild = c;
			}
			treesize--;
			delete p;
			cout << sum << endl;
		}
	}

}
int main()
{
	int m;
	indexedBinarySearchTree temp;
	cin >> m;
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		switch (a)
		{
		case 0:temp.insert(b); break;
		case 1:temp.find(b); break;
		case 2:temp.erase(b); break;
		case 3:temp.get(b); break;
		case 4:temp.indexedErase(b); break;
		}
	}
	return 0;
}









