#include<iostream>
using namespace std;
template<class T>
class matrixterm
{
public:
	int row;
	int col;
	T value;
};

template<class T>
class sparsematrix
{
public:
	sparsematrix(int a=10);
	~sparsematrix() { delete[]terms; }//�������������ͷŽ����Ķ�̬���� 
	void add(sparsematrix<T>& b);//�ӷ����� 
	void mulity(sparsematrix<T>& b);//�˷����� 
	void operator=(sparsematrix<T>& c);//����=�� 
	void set();//���ú��� 
	void output();//������� 
private:
	int rows;
	int cols;
	matrixterm<T> *terms;
	int termssize;
};

template<class T>
sparsematrix<T>::sparsematrix(int a)
{
	termssize = 0; 
	rows = cols = 0; 
	terms = new matrixterm<T>[a]; 
}
template<class T>
void sparsematrix<T>::set()
{
	termssize = 0;
	cin >> rows >> cols;
	delete[]terms;
	terms = new matrixterm<T>[rows*cols];
	termssize = 0;
	for (int i = 0; i < rows * cols; i++)
		terms[i].value = 0;
	int m = 0;
	//	arraylist<matrixterm<int> >::iterator it=terms.begin();
	//	arraylist<matrixterm<int> >::iterator ib=x.terms.begin();
	//	arraylist<matrixterm<T> >::iterator it=terms.begin();
	//	arraylist<matrixterm<T> >::iterator it=terms.begin();
	for (int i = 0; i < rows; i++)//����ж������Ԫ���Ƿ�Ϊ0 
	{
		for (int j = 0; j < cols; j++)
		{
			T a;
			cin >> a;
			if (a != 0)//����Ϊ0�����䴫��ϡ����󣬷���ִ�иò��� 
			{
				terms[m].row = i + 1;
				terms[m].col = j + 1;
				terms[m].value = a;
				m++;
				termssize++;
			}
		}

	}
}

template<class T>
void sparsematrix<T>::operator=(sparsematrix<T>& c)
{
	
	rows = c.rows;
	cols = c.cols;
	delete[]terms;
	terms = new matrixterm<T>[rows*cols];//��ֵʱ������ɾ��ԭ����ָ��ռ� 
	for (int i = 0; i < rows * cols; i++)
		terms[i].value = 0;
	int m=0;
	//	arraylist<matrixterm<int> >::iterator it=terms.begin();
	//	arraylist<matrixterm<int> >::iterator ib=c.terms.begin();
	for (; m < c.termssize; m++)//���ν�Ԫ�ش���ϵϡ������� 
	{
		terms[m].row = c.terms[m].row;
		terms[m].col = c.terms[m].col;
		terms[m].value = c.terms[m].value;
	}
	termssize = c.termssize;//�ı�ϡ������С 
}

template<class T>
void sparsematrix<T>::add(sparsematrix<T>& b)
{
	sparsematrix<T> c;
	if (rows != b.rows || cols != b.cols)//�ӷ�ʱ��Ҫ�ж� 
	{
		*this = b;
		cout << -1 << endl;
	}
	else
	{
		delete[]c.terms;
		c.terms = new matrixterm<T>[10000];
		for (int i = 0; i < rows * cols; i++)
			c.terms[i].value = 0;
		c.termssize = 0;
		c.rows = rows;
		c.cols = cols;
		//c.terms = new matrixterm<T>[c.rows * c.cols];
		int m = 0, i=0, j=0;
		for (; i < termssize && j < b.termssize;)//�Ƚ�һ������һ��ϡ�����Ԫ��ȫ������ 
		{
			int tindex = terms[i].row * cols + terms[i].col;
			int bindex = b.terms[j].row * cols + b.terms[j].col;
			if (tindex < bindex)//�Ƚ���������ǰ��С�ں��ߣ����Ԫ��λ�ÿ�ǰ������ 
			{
				c.terms[m].row = terms[i].row;
				c.terms[m].col = terms[i].col;
				c.terms[m].value = terms[i].value;
				i++;
				m++;
			}
			else
			{
				if (tindex == bindex&&terms[i].row==b.terms[j].row)//����Ԫ��λ����ͬ������Ӻ��ж��Ƿ�Ϊ0����������� 
				{
					if (terms[i].value + b.terms[j].value != 0)
					{
						/*matrixterm<T> mterm;*/
						c.terms[m].row = terms[i].row;
						c.terms[m].col = b.terms[j].col;
						c.terms[m].value = terms[i].value + b.terms[j].value;
						/*c.terms.push_back(mterm);*/
						m++;
					}
					i++;
					j++;
				}
				else
				{
					c.terms[m].row = b.terms[j].row;
					c.terms[m].col = b.terms[j].col;
					c.terms[m].value = b.terms[j].value;
					j++;
					m++;
				}
			}
		}
		for (; i < termssize; i++)//���ν�ʣ��Ԫ�ز��� 
		{
			c.terms[m].row = terms[i].row;
			c.terms[m].col = terms[i].col;
			c.terms[m].value = terms[i].value;
			m++;
		}
		for (; j < b.termssize; j++)
		{
			//matrixterm<T> mterm;
			//mterm.row = b.terms.element[j].row;
			//mterm.col = b.terms.element[j].col;
			//mterm.value = b.terms.element[j].value;
			/*c.terms.push_back(b.terms.get(j));*/
			c.terms[m].row = b.terms[j].row;
			c.terms[m].col = b.terms[j].col;
			c.terms[m].value = b.terms[j].value;
			m++;
		}
		c.termssize = m;
		*this = c;
	}
}

template<class T>
void sparsematrix<T>::mulity(sparsematrix<T>& b)
{
	sparsematrix<T> c;
	//c.terms.clear();
	if (cols != b.rows)	
	{
		*this = b;
		cout << -1 << endl;
	}
	else
	{
		delete[]c.terms;
		c.terms = new matrixterm<T>[10000];
		for (int i = 0; i < rows * b.cols; i++)
			c.terms[i].value = 0;
		c.termssize = 0;
		c.rows = rows;
		c.cols = b.cols;
		int m=0;
		for (int k = 0; k < termssize; k++)//����������Ԫ�أ���ǰ���������ں�������������� 
		{
			for (int w = 0; w < b.termssize; w++)
			{
				if (terms[k].col == b.terms[w].row)
				{
					/*matrixterm<T> mterm;*/
					c.terms[m].row = terms[k].row;
					c.terms[m].col = b.terms[w].col;
					c.terms[m].value = terms[k].value *b.terms[w].value;
					/*.terms.push_back(mterm);*/
					//c.terms[m].row = terms[k].row;
					//c.terms[m].col= b.terms[k].col;
					//c.terms[m].value = terms[k].value * b.terms[w].value;
					for (int i = 0; i < m; i++)//�жϸ�Ԫ��λ����֮ǰ�Ƿ��Ѿ����ֹ������ǣ������ 
					{
						if (c.terms[m].row == c.terms[i].row && c.terms[m].col == c.terms[i].col)
						{
							c.terms[i].value += c.terms[m].value;
							m--;
						}
					}
					m++;
				}
			}
		}
		c.termssize = m;
		*this = c;
        matrixterm<T> *mterm=new matrixterm<T>[rows*cols];
	    for (int i = 0; i < rows*cols; i++)
		    mterm[i].value = 0;
	    m = 0;
	    for(int i=1;i<=rows;i++)
		    for (int j = 1; j <= cols; j++)
		    {
			    mterm[m].row = i;
			    mterm[m].col = j;
			    mterm[m].value = 0;
			    m++;
		    }
	//cout << m << "mdezhi";
	    for (int i = 0; i < rows*cols; i++)//����������Ԫ��λ�ã�ʹ����ϰ����������� 
	    {
		    for (int j = 0; j < termssize; j++)
		    {
			    if (mterm[i].row == terms[j].row && mterm[i].col == terms[j].col)
			    {
				    mterm[i].value = terms[j].value; break;
			    }
		    }
	    }
	    delete []terms;
	    terms =mterm;
	}

}

template<class T>
void sparsematrix<T>::output()
{
	cout << rows << " " << cols << endl;
	matrixterm<T> *mterm=new matrixterm<T>[rows*cols];
	for (int i = 0; i < rows*cols; i++)
		mterm[i].value = 0;
	int m = 0;
	for(int i=1;i<=rows;i++)
		for (int j = 1; j <= cols; j++)
		{
			mterm[m].row = i;
			mterm[m].col = j;
			mterm[m].value = 0;
			m++;
		}
	//cout << m << "mdezhi";
	for (int i = 0; i < rows*cols; i++)//���������������ÿ��Ԫ�أ�����������λ�ã������Ԫ�أ��������ֵΪ0 
	{
		for (int j = 0; j < termssize; j++)
		{
			if (mterm[i].row == terms[j].row && mterm[i].col == terms[j].col)
			{
				mterm[i].value = terms[j].value; break;
			}

		}
	}
	m = 0;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= cols; j++)
		{
			cout << mterm[m].value << " ";
			m++;
		}
		cout << endl;
	}
	delete[]mterm;
}

int main()
{
	int w, num;
	sparsematrix<int> a;
	//	a.set();
	//	a.transpose(s);
	//	s.output();
	cin >> w;
	for (int i = 0; i < w; i++)
	{
		cin >> num;
		if (num == 1)//�ж�ִ���Ĳ����� 
		{
			a.set();
		}
		if (num == 2)
		{
			sparsematrix<int> y;
			y.set();
			a.mulity(y);
		}
		if (num == 3)
		{
			sparsematrix<int> s;
			s.set();
			a.add(s);
		}
		if (num == 4)
		{
			a.output();
		}
	}
	return 0;

}











