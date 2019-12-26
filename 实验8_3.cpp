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
	bool* help;//数据成员还包括bool型的动态数组 
};
template<class K>
hashtable<K>::hashtable(int a)
{
	dsize = 0;
	divisor = a;
	table = new K[divisor];
	help = new bool[divisor];
	for (int i = 0; i < divisor; i++)//初始化散列表时将bool型的数组全部赋为false 
		help[i] = false;
}
template<class K>
int hashtable<K>::find(K& opt)//查询函数 
{
	int i = opt % divisor;
	int j = i;
	do
	{
		if (help[j] == false)//如果一直查询到空值处，则说明不存在所在元素 
			return -1;
		else
			if (table[j] == opt)//如果找到对应元素，输出元素下标 
				return j;
			else j = (j + 1) % divisor;//如果不为空，也不是所要元素，则遍历下一位 
	} while (j != i);
	return -1;//如果一直遍历到回到该位置，则说明不存在该元素
}
template<class K>
void hashtable<K>::insert(K& opt)//插入指定元素 
{
	int ba = find(opt);
	if (ba !=-1)
		cout << "Existed" << endl;//如果已存在该元素，则直接输出 
	else
	{
		if (help[opt % divisor] == false)//如果起始桶即为空，则可以直接插入 
		{
			table[opt % divisor] = opt;
			help[opt % divisor] = true;//插入时将该位置设置为true 
			dsize++;
			cout << opt % divisor << endl;
		}
		else//如果起始桶不为空，则需要向后遍历，直到遇到空桶为止 
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
void hashtable<K>::erase(K& opt)//线性开型寻址解决溢出问题 
{
	int ba = find(opt);
	if (ba == -1)//删除时如果不存在该元素，则直接输出 
		cout << "Not Found" << endl;
	else
	{
		help[ba] = false;
		int j = (ba + 1) % divisor;
		while (help[j] == true && j != ba)//当未遇到空格或者没有回到目前元素时，遍历下一个 
			j = (j + 1) % divisor;//j为首次遇到的空桶位置 
		int i = ba;//i为删除元素以后的空桶 
		int count = 0;//count用来记录删除之后需要移动元素的次数 
		int temp = (i + 1) % divisor;//temp为遍历的桶 
		while (temp != j)//当未遍历到空桶时 
		{
			int f = table[temp]%divisor;//f为当前桶中元素的起始桶 
			if (i<temp&&f<=temp && f>i||(i>temp&&(f<=temp|| f>i)))//不能移动元素的两种情况 
			{
				temp=(temp+1)%divisor;
			}
			else//除了这两种情况，均可以移动桶中元素 
			{
				table[i] = table[temp % divisor];
				help[i] = true;
				help[temp % divisor] = false;//移动之后的true和false值需要交换 
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
	cin >> div >> n;//依次输入除数和操作数 
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

