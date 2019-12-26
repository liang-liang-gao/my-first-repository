#include <iostream>
using namespace std;
template<class K>
class hashtable
{
	public:
		hashtable(int a=10);
		~hashtable(){delete []table;}
		int find(K& opt);
//	    void search(K& opt);
	    void insert(K& opt);
	    void erase(K& opt);
	private:
		K *table;
		int dsize;
		int divisor; 
};
template<class K>
hashtable<K>::hashtable(int a)
{
	dsize=0;
	divisor=a;
	table=new K[divisor];
	for(int i=0;i<divisor;i++)
	table[i]=0;
}
template<class K>
int hashtable<K>::find(K& opt)
{
	int i=opt%divisor;
	int j=i;
	do
	{
		if(table[j]==0)
		    return -1;
		else 
		   if(table[j]==opt)
		       return j;
		    else j=(j+1)%divisor;
	}while(j!=i);
	return -1;
}
template<class K>
void hashtable<K>::insert(K& opt)
{
	int ba = find(opt);
	if (ba == 1)
		cout << "Existed" << endl;
	else
	{
		if(table[opt%divisor]==0)
		{
			table[opt%divisor]=opt;
			dsize++;
			cout<<opt%divisor<<endl;
		}
		else
		{
			int i=opt%divisor;
			int j=(i+1)%divisor;
			while(j!=i)
			{
				if(table[j]==0)
				{
					dsize++;
				    table[j]=opt;
				    cout<<j<<endl;
				    break;
				}
				else
				    j=(j+1)%divisor;	
			}
		}	
	}
}
template<class K>
void hashtable<K>::erase(K& opt)
{
	int ba = find(opt);
	if (ba == -1)
		cout << "Not Found" << endl;
	else
	{
		table[ba]=0;
		int j=(ba+1)%divisor;
		while(table[j]!=0)
		    j=(j+1)%divisor;
		int i=ba%divisor;
		int count=0;
		int temp=1;
		while((i+temp)%divisor!=j)
		{
			if(table[(i+temp)%divisor]%divisor!=(i+temp)%divisor)
			{
		       table[i]=table[(i+temp)%divisor];
		       table[(i+temp)%divisor]=0;
		       count++;
		       i=(i+1)%divisor;
		    }
			else
			{
				temp++;
//			   table[i]=0;
//			   cout<<count<<endl;
//			   break;
		    }
			
		}
		dsize--;
		cout<<count<<endl;
	}
}
int main()
{
	int n,div;
	int num,opt;
	cin >> div >> n;
	hashtable<int> a(div);
	for (int i = 0; i < n; i++)
	{
		cin >> num >> opt;
		if (num == 0)
		    a.insert(opt);
		if (num == 1)
		    cout<<a.find(opt)<<endl;
		if (num == 2)
		    a.erase(opt);
	}
	return 0;
}
