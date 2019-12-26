#include<iostream>
#include<queue>
static int treesize;
using namespace std;
template<class T>
struct binarytreenode
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

class linkedbinarytree
{
public:
	linkedbinarytree(int t=10)
	{
		root=new binarytreenode<int>(t);
		treesize = 1;
	}
	~linkedbinarytree();
	void maketree(int a[],int b[],int fa,int la,int fb,int lb)
	{maketree(root,a,b,fa,la,fb,lb);}
//	void calculate(int n);
	bool empty() { return treesize == 0; }
	int size() { return treesize; }
	void preorder() { preorder(root); }
	void preorders() { preorders(root); }
	void inorder() { inorder(root); }
	void postorder() { postorder(root); }
	void levelorder() { levelorder(root); }
	int height() { return height(root); }
	void erase() { erase(root); }
//	void orderoutput(int n);
private:
	binarytreenode<int>* root;
	static int treesize;
	static void maketree(binarytreenode<int>* t,int a[],int b[],int fa,int la,int fb,int lb);
	static void preorder(binarytreenode<int>* t);
	static void preorders(binarytreenode<int>* t);
	static void inorder(binarytreenode<int>* t);
	static void postorder(binarytreenode<int>* t);
	static void levelorder(binarytreenode<int>* t);
	static int height(binarytreenode<int>* t);
	static void erase(binarytreenode<int>* t);
};
//template<class T>
void linkedbinarytree::maketree(binarytreenode<int>* t,int a[],int b[],int fa,int la,int fb,int lb)
{//����a�д洢ǰ�����е�ֵ��b�洢�������е�ֵ 
	//�������δ���ǰ�������ֵ������ڵ��ֵ���������� 
	if(t!=NULL)
	{
		int i;
		for(i=fb;i<=lb;i++)//�ҵ�����b�ж�Ӧ����a��ֵ 
		    if(b[i]==a[fa])
		       break;
		if(i==fb)//�жϸýڵ��Ƿ��������� 
		    t->leftchild=NULL;
		else
		    t->leftchild=new binarytreenode<int>(a[fa+1]);
		if(i==lb)//�жϸýڵ��Ƿ��������� 
		    t->rightchild=NULL;
		else
		    t->rightchild=new binarytreenode<int>(a[fa+1+i-fb]);
		maketree(t->leftchild,a,b,fa+1,fa+i-fb,fb,i-1);//�ݹ齨�������� 
		maketree(t->rightchild,a,b,fa+1+i-fb,la,i+1,lb);//�ݹ齨�������� 
	}
	else return;
}       
//template<class T>
void linkedbinarytree::preorder(binarytreenode<int>* t)
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
void linkedbinarytree::levelorder(binarytreenode<int>* t)
{
	queue<binarytreenode<int>*> q;
	while (t != NULL)
	{
		cout << t->element << " ";
		//��t�ĺ��Ӳ������ 
		if (t->leftchild != NULL)
			q.push(t->leftchild);
		if (t->rightchild != NULL)
			q.push(t->rightchild);
		//��ȡ��һ��Ҫ���ʵ�Ԫ��
		if (!q.empty())
		{
			t = q.front();
			q.pop();
		}
		else break;
	}
}
//template<class T>
int linkedbinarytree::height(binarytreenode<int>* t)
{
	if (t == NULL)
		return 0;
	else
	{
		// �����������ĸ߶Ⱥ��������ĸ߶� 
		int lHeight = height(t->leftchild);
		int rHeight = height(t->rightchild);
		// ���ض��߽ϴ��߼�1 
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
//template<class T>
linkedbinarytree::~linkedbinarytree()
{
	erase(root);
}

int linkedbinarytree::treesize;
int main()
{
	int n;
	cin>>n;
	int *a=new int[n];
	int *b=new int[n];
	for(int i=0;i<n;i++)
	    cin>>a[i];
	for(int i=0;i<n;i++)
	    cin>>b[i];
	linkedbinarytree m(a[0]);
	m.maketree(a,b,0,n-1,0,n-1);
    m.postorder();
	return 0;
}
