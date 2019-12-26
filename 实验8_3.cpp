#include <iostream>
using namespace std;
template<class K>
class hashtable
{
public:
	hashtable(int a = 10);
	~hashtable() { delete[]table; delete[]help; }
	int find(K& opt);
	//	    void search(K& opt);
	void insert(K& opt);
	void erase(K& opt);
private:
	K* table;
	int dsize;
	int divisor;
	bool* help;//���ݳ�Ա������bool�͵Ķ�̬���� 
};
template<class K>
hashtable<K>::hashtable(int a)
{
	dsize = 0;
	divisor = a;
	table = new K[divisor];
	help = new bool[divisor];
	for (int i = 0; i < divisor; i++)//��ʼ��ɢ�б�ʱ��bool�͵�����ȫ����Ϊfalse 
		help[i] = false;
}
template<class K>
int hashtable<K>::find(K& opt)//��ѯ���� 
{
	int i = opt % divisor;
	int j = i;
	do
	{
		if (help[j] == false)//���һֱ��ѯ����ֵ������˵������������Ԫ�� 
			return -1;
		else
			if (table[j] == opt)//����ҵ���ӦԪ�أ����Ԫ���±� 
				return j;
			else j = (j + 1) % divisor;//�����Ϊ�գ�Ҳ������ҪԪ�أ��������һλ 
	} while (j != i);
	return -1;//���һֱ�������ص���λ�ã���˵�������ڸ�Ԫ��
}
template<class K>
void hashtable<K>::insert(K& opt)//����ָ��Ԫ�� 
{
	int ba = find(opt);
	if (ba !=-1)
		cout << "Existed" << endl;//����Ѵ��ڸ�Ԫ�أ���ֱ����� 
	else
	{
		if (help[opt % divisor] == false)//�����ʼͰ��Ϊ�գ������ֱ�Ӳ��� 
		{
			table[opt % divisor] = opt;
			help[opt % divisor] = true;//����ʱ����λ������Ϊtrue 
			dsize++;
			cout << opt % divisor << endl;
		}
		else//�����ʼͰ��Ϊ�գ�����Ҫ��������ֱ��������ͰΪֹ 
		{
			int i = opt % divisor;
			int j = (i + 1) % divisor;
			while (j != i)
			{
				if (help[j] == false)
				{
					dsize++;
					table[j] = opt;
					help[j] = true;// 
					cout << j << endl;
					break;
				}
				else
					j = (j + 1) % divisor;
			}
		}
	}
}
template<class K>
void hashtable<K>::erase(K& opt)//���Կ���Ѱַ���������� 
{
	int ba = find(opt);
	if (ba == -1)//ɾ��ʱ��������ڸ�Ԫ�أ���ֱ����� 
		cout << "Not Found" << endl;
	else
	{
		help[ba] = false;
		int j = (ba + 1) % divisor;
		while (help[j] == true && j != ba)//��δ�����ո����û�лص�ĿǰԪ��ʱ��������һ�� 
			j = (j + 1) % divisor;//jΪ�״������Ŀ�Ͱλ�� 
		int i = ba;//iΪɾ��Ԫ���Ժ�Ŀ�Ͱ 
		int count = 0;//count������¼ɾ��֮����Ҫ�ƶ�Ԫ�صĴ��� 
		int temp = (i + 1) % divisor;//tempΪ������Ͱ 
		while (temp != j)//��δ��������Ͱʱ 
		{
			int f = table[temp]%divisor;//fΪ��ǰͰ��Ԫ�ص���ʼͰ 
			if (i<temp&&f<=temp && f>i||(i>temp&&(f<=temp|| f>i)))//�����ƶ�Ԫ�ص�������� 
			{
				temp=(temp+1)%divisor;
			}
			else//����������������������ƶ�Ͱ��Ԫ�� 
			{
				table[i] = table[temp % divisor];
				help[i] = true;
				help[temp % divisor] = false;//�ƶ�֮���true��falseֵ��Ҫ���� 
				count++;
				i = temp;
				temp = (temp + 1) % divisor; 
			}
        }
		dsize--;
		cout << count << endl;
	}
}
int main()
{
	int n, div;
	int num, opt;
	cin >> div >> n;//������������Ͳ����� 
	hashtable<int> a(div);
	for (int i = 0; i < n; i++)
	{
		cin >> num >> opt;
		if (num == 0)
			a.insert(opt);
		if (num == 1)
			cout << a.find(opt) << endl;
		if (num == 2)
			a.erase(opt);
	}
	return 0;
}

