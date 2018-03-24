#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define ull unsigned long long

struct node
{
	ull value;
	node* next;
};

class mystack
{
private:
	long size;
	node* root;
public:
	mystack()
	{
		size = 0;
		root = NULL;
	}

	~mystack()
	{
		node* cur = root;
		while (cur != NULL)
		{
			node* old = cur;
			cur = cur->next;
			delete old;
		}
	}

	void print()
	{
		node* cur = root;
		while(cur != nullptr)
		{
			cout << cur->value << endl;
			cur = cur->next;
		}
	}

	void push(ull value)
	{
		node* newone = new node();
		newone->next = root;
		newone->value = value;
		root = newone;

		size++;
	}

	long length()
	{
		return size;
	}

	ull pop()
	{
		ull value = root->value;

		node* elem = root;
		root = elem->next;
		delete elem;
		size--;

		return value;
	}
};



ull compute(ull** data, long count)
{
	mystack helper;
	mystack quests;
	helper.push(0);
	helper.push(10000000000LL);

	while (helper.length())
	{
		ull parent = helper.pop();
		ull cur = helper.pop();
		ull* children = data[cur];

		if (children[0] > 1 || children[3] != parent)
		{
			ull parIndex = 10000000000LL;
			for (ull x = 0; x < children[0]; x++)
			{
				ull child = children[x + 3];
				if (child != parent)
				{
					helper.push(child);
					helper.push(cur);
				}
				else
				{
					parIndex = x + 3;
				}
			}

			if (parIndex != 10000000000LL)
			{
				children[parIndex] = children[children[0] + 2];
				children[0]--;
			}
			//quests.push(parent);
		}
		else
		{
			children[0] = 0;
		}
			quests.push(cur);
	}

	// quests.print();

	while (quests.length())
	{
		ull cur = quests.pop();
		ull* children = data[cur];
		ull a = 1, b = 0;
		for (ull x = 0; x < children[0]; x++)
		{
			ull child = children[x + 3];
			a = (a * ((1 + data[child][1]) % 536870909LL)) % 536870909LL;
			b = (b + data[child][1] + data[child][2]) % 536870909LL;
		}
		data[cur][1] = a;
		data[cur][2] = b;
	}

	return (data[0][1] + data[0][2]) % 536870909LL;
}

int main(int argc, char* argv[])
{
	ull count = 0;
	cin >> count;

	ull** data = new ull*[count];
	for (ull x = 0; x < count; x++)
	{
		ull len = 0;
		cin >> len;
		data[x] = new ull[len + 3];
		data[x][0] = len;
		data[x][1] = 1;
		data[x][2] = 0;
		for (ull y = 0; y < len; y++)
		{
			ull value;
			cin >> value;
			data[x][y + 3] = value;
		}
	}

	ull result = compute(data, count);
	cout << result << endl;

	for (ull x = 0; x < count; x++)
	{
		delete[] data[x];
	}
	delete[] data;

	 // system("pause");
	return 0;
}

