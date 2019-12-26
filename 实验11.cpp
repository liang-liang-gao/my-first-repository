#include"stdio.h"
#include<iostream>
using namespace std;
template<class T>
struct binaryTreeNode
{
	T element;
	int leftsize;//��������������������ڵ�����Ҫ���Ӽ�¼��������С������leftsize
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
	void postdelete(binaryTreeNode<int>* t);//�������ɾ������
	bool search(int k);//�ж�Ԫ���Ƿ���ڵĺ���
	void find(int k);//���Һ���           ��
	void get(int k);//�����β��Һ���      ��
	void insert(int k);//���뺯��         ��
	void erase(int k);//ɾ������          ��
	void indexedErase(int k);//������ɾ������     ��
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
{//�������ɾ��������
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
				return true;//�����ֵ����
	}
	return false;//�����ֵ������
}
void  indexedBinarySearchTree::insert(int k)
{
	bool temp = search(k);
	if (temp == true)//��Ԫ���Ѿ����ڣ������ֱ�����0
		cout << 0 << endl;
	else
	{
		binaryTreeNode<int>* p = root, * pp = NULL;//ppʼ��ָ��p�ĸ��ڵ㣬�������ָ�������ӵĽڵ�
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
		else                //�����ʱ����û�нڵ㣬����Ҫ�����µĸ��ڵ�
			root = newnode;
		treesize++;
		cout << sum << endl;
	}

}
void indexedBinarySearchTree::find(int k)
{
	bool temp = search(k);
	if (temp == false)//���ж�Ԫ���Ƿ���ڣ��������ڣ���ֱ�����0
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
	if (k > treesize || treesize == 0)//��Ҫ���ҵ�Ԫ�����������������Ĵ�С�����߶�������Ԫ�أ���ֱ�����0
		cout << 0 << endl;
	else
	{
		int m = k - 1;//���ڽڵ��leftsize�Ǵ�0��ʼ�ģ����ȡmΪ�����Ƚϱ�����ֵ
		binaryTreeNode<int>* p = root;
		int sum = 0;
		while (p != NULL)
		{
			sum ^=  p->element;
			if (m < p->leftsize)
				p = p->leftChild;
			else
				if (m > p->leftsize)//������ҵ�Ԫ�����������У�����Ҫ����m�Ĵ�С
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
		binaryTreeNode<int>* p = root, * pp = NULL;//pp����ָ��ɾ���ڵ�ĸ��ڵ㣬�����޸�ָ��
		int sum = 0;
		while (p != NULL&&p->element!=k)
		{
			sum ^= p->element;
			pp = p;
			if (k < p->element)
			{
				p->leftsize--;//��Ҫɾ���Ľڵ�λ�ڵ�ǰ�ڵ��������ʱ����ǰ�ڵ��leftsize��Ҫ��һ
				p = p->leftChild;
			}
			else
				p = p->rightChild;
		}

		if (p != NULL)
		{
			sum ^= p->element;//���Ҫ�ʹ�ɾ����Ԫ�ؽ������
			//��������������������ǽڵ��ɾ��

			if (p->leftChild != NULL && p->rightChild != NULL)//���Ҫɾ���Ľڵ��������������ڵ����
			{
				binaryTreeNode<int>* s = p->rightChild, * ps = p;//s��Ϊ���ҳ���ɾ��������������ֵ��С�Ľڵ㣬ps��s�ڵ�ĸ��ڵ�
				while (s->leftChild != NULL)
				{
					ps = s;
					s->leftsize--;//!!!!!!!!!!!!��Ѱ������ڵ�ʱ��ҲҪ��·���ϵĽڵ��leftsize��һ
					s = s->leftChild;
				}
				binaryTreeNode<int>* q = new binaryTreeNode<int>(s->element, p->leftChild, p->rightChild, p->leftsize);//��������ڵ��ֵ�����µĽڵ�

				if (pp == NULL)
					root = q;
				else
				{
					if (p == pp->leftChild)
						pp->leftChild = q;
					else
						pp->rightChild = q;
				}
				if (ps == p) pp = q;//��ʱ�Ѿ�û�нڵ�ָ��p�ڵ㣬�����Ҫ���������������
				else pp = ps;
				delete p;//�ͷ�pԭ��ָ��Ľڵ�ռ�
				p = s;
			}
			binaryTreeNode<int>* c;
			if (p->leftChild != NULL)
				c = p->leftChild;//��¼p�����һ���ڵ�
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
			delete p;//�ͷ�Ҫɾ���Ľڵ�ռ�
			cout << sum << endl;
		}
	}

}

void indexedBinarySearchTree::indexedErase(int k)//˼·ͬ�������ƣ����ҳ���k���Ԫ�أ�Ȼ��Ըýڵ����ɾ������
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









