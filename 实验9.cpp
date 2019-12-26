#include<iostream>
#include<queue>
static int treesize;
using namespace std;
template<class T>
struct binarytreenode//建立二叉树结点的结构体 
{
	T element;
	binarytreenode<T>* leftchild, * rightchild;
	binarytreenode() { leftchild = rightchild = NULL; }
	binarytreenode(T theelement) { element = theelement; leftchild = rightchild = NULL; }
	binarytreenode(T theelement, binarytreenode* left, binarytreenode* right)
	{
		element = theelement;
		leftchild = left;
		rightchild = right;
	}
};
//template<class T>

class linkedbinarytree//建立二叉树类 
{
public:
	linkedbinarytree()
	{
		//root=new binarytreenode<int>(1);
		root = NULL;
		treesize = 0;
	}
	//~linkedbinarytree();
	void calculate(int n);//用来建立二叉树和输出对应结果 
	bool empty() { return treesize == 0; }
	int size() { return treesize; }
	void preorder() { preorder(root); }//用来执行输出的前序遍历 
	void preorders() { preorders(root); }//用来计算节点个数的前序遍历 
	void inorder() { inorder(root); }//中序遍历 
	void postorder() { postorder(root); }//后序遍历 
	void levelorder() { levelorder(root); }//层次遍历 
	int height() { return height(root); }//计算二叉树高度 
	void erase() { erase(root); }//删除二叉树结点 
private:
	binarytreenode<int>* root;//二叉树的根 
	static int treesize;//记录二叉树的节点个数 
	static void preorder(binarytreenode<int>* t); 
	static void preorders(binarytreenode<int>* t);
	static void inorder(binarytreenode<int>* t);
	static void postorder(binarytreenode<int>* t);
	static void levelorder(binarytreenode<int>* t);
	static int height(binarytreenode<int>* t);
	static void erase(binarytreenode<int>* t);
};
void linkedbinarytree::calculate(int n)
{
//	root = new binarytreenode<int>(1);
	binarytreenode<int>** temp = new binarytreenode<int>*[n];//建立一个存储二叉树结点的数组 
	
	for (int i = 1; i <= n; i++)
		temp[i]=new binarytreenode<int>(i);//先将各个节点存储在数组中 
	root = temp[1];
	for (int i = 1; i <= n; i++)
	{
//		queue<binarytreenode<int>*> q;
//		binarytreenode<int>* p = root;
		int left, right;
		cin >> left >> right;
		if (left != -1)//按照输入次序建立各个节点之间的联系 
		{
			temp[i]->leftchild =temp[left];
			treesize++;
		}
		if (right != -1)
		{
			temp[i]->rightchild =temp[right];
			treesize++;
		} 
	}
	levelorder();//执行层次遍历输出各个节点
	cout << endl;
	for (int i = 1; i <= n; i++)//依次计算各个编号的子树节点个数 
	{
		linkedbinarytree temp2;
		temp2.root = new binarytreenode<int>(i, temp[i]->leftchild, temp[i]->rightchild);
		temp2.treesize = 0;
		temp2.preorders();//前序遍历计算节点个数 

		cout << temp2.size() << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++)//依次计算各个编号的子树高度 
	{
		linkedbinarytree temp2;
		temp2.root = new binarytreenode<int>(i, temp[i]->leftchild, temp[i]->rightchild);
		cout<<temp2.height()<<" ";
	}
}
//template<class T>
void linkedbinarytree::preorder(binarytreenode<int>* t)//递归的前序遍历输出函数 
{
	if (t != NULL)
	{
		cout << t->element << " ";
		preorder(t->leftchild);
		preorder(t->rightchild);
	}
}
void linkedbinarytree::preorders(binarytreenode<int>* t)
{
	if (t != NULL)
	{
		treesize++;
		preorders(t->leftchild);
		preorders(t->rightchild);
	}
}
//template<class T>
void linkedbinarytree::inorder(binarytreenode<int>* t)
{
	if (t != NULL)
	{
		inorder(t->leftchild);
		cout << t->element << " ";
		inorder(t->rightchild);
	}
}
//template<class T>
void linkedbinarytree::postorder(binarytreenode<int>* t)
{
	if (t != NULL)
	{
		postorder(t->leftchild);
		postorder(t->rightchild);
		cout << t->element << " ";
	}
}
//template<class T>
void linkedbinarytree::levelorder(binarytreenode<int>* t)//非递归的层次遍历输出函数 
{
	queue<binarytreenode<int>*> q;
	while (t != NULL)
	{
		cout << t->element << " ";
		//将t的孩子插入队列 
		if (t->leftchild != NULL)
			q.push(t->leftchild);
		if (t->rightchild != NULL)
			q.push(t->rightchild);
		//提取下一个要访问的元素
		if (!q.empty())
		{
			t = q.front();
			q.pop();
		}
		else break;
	}
}
//template<class T>
int linkedbinarytree::height(binarytreenode<int>* t)//递归的计算子树高度函数 
{
	if (t == NULL)
		return 0;
	else
	{
		// 计算左子树的高度和右子树的高度 
		int lHeight = height(t->leftchild);
		int rHeight = height(t->rightchild);
		// 返回二者较大者加1 
		if (lHeight > rHeight)
			return(lHeight + 1);
		else return(rHeight + 1);
	}
}
//template<class T>
void linkedbinarytree::erase(binarytreenode<int>* t)
{
	if (t != NULL)
	{
		binarytreenode<int>* deletenode = t;
		erase(t->leftchild);
		erase(t->rightchild);
		delete deletenode;
		treesize--;
	}
}
int linkedbinarytree::treesize;
int main()
{
	int n;
	cin >> n;//输入节点个数 
	linkedbinarytree a;
	a.calculate(n);//建立二叉树并输出 
	cout << endl;
	return 0;
}
