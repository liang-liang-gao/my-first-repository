#include<iostream>
#include<queue>
static int treesize;
using namespace std;
template<class T>
struct binarytreenode//�������������Ľṹ�� 
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

class linkedbinarytree//������������ 
{
public:
	linkedbinarytree()
	{
		//root=new binarytreenode<int>(1);
		root = NULL;
		treesize = 0;
	}
	//~linkedbinarytree();
	void calculate(int n);//���������������������Ӧ��� 
	bool empty() { return treesize == 0; }
	int size() { return treesize; }
	void preorder() { preorder(root); }//����ִ�������ǰ����� 
	void preorders() { preorders(root); }//��������ڵ������ǰ����� 
	void inorder() { inorder(root); }//������� 
	void postorder() { postorder(root); }//������� 
	void levelorder() { levelorder(root); }//��α��� 
	int height() { return height(root); }//����������߶� 
	void erase() { erase(root); }//ɾ����������� 
private:
	binarytreenode<int>* root;//�������ĸ� 
	static int treesize;//��¼�������Ľڵ���� 
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
	binarytreenode<int>** temp = new binarytreenode<int>*[n];//����һ���洢�������������� 
	
	for (int i = 1; i <= n; i++)
		temp[i]=new binarytreenode<int>(i);//�Ƚ������ڵ�洢�������� 
	root = temp[1];
	for (int i = 1; i <= n; i++)
	{
//		queue<binarytreenode<int>*> q;
//		binarytreenode<int>* p = root;
		int left, right;
		cin >> left >> right;
		if (left != -1)//������������������ڵ�֮�����ϵ 
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
	levelorder();//ִ�в�α�����������ڵ�
	cout << endl;
	for (int i = 1; i <= n; i++)//���μ��������ŵ������ڵ���� 
	{
		linkedbinarytree temp2;
		temp2.root = new binarytreenode<int>(i, temp[i]->leftchild, temp[i]->rightchild);
		temp2.treesize = 0;
		temp2.preorders();//ǰ���������ڵ���� 

		cout << temp2.size() << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++)//���μ��������ŵ������߶� 
	{
		linkedbinarytree temp2;
		temp2.root = new binarytreenode<int>(i, temp[i]->leftchild, temp[i]->rightchild);
		cout<<temp2.height()<<" ";
	}
}
//template<class T>
void linkedbinarytree::preorder(binarytreenode<int>* t)//�ݹ��ǰ������������ 
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
void linkedbinarytree::levelorder(binarytreenode<int>* t)//�ǵݹ�Ĳ�α���������� 
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
int linkedbinarytree::height(binarytreenode<int>* t)//�ݹ�ļ��������߶Ⱥ��� 
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
int linkedbinarytree::treesize;
int main()
{
	int n;
	cin >> n;//����ڵ���� 
	linkedbinarytree a;
	a.calculate(n);//��������������� 
	cout << endl;
	return 0;
}
