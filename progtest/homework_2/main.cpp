#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

struct node
{
	long long value;
	node* next;
};

class stack
{
private:
	long size;
	node* root;
public:
	stack()
	{
		size = 0;
		root = NULL;
	}

	~stack()
	{
		node* cur = root;
		while(cur != NULL)
		{
			node* old = cur;
			cur = cur->next;
			delete old;
		}
	}

	void push(long long value)
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

	long long pop()
	{
		long long value = root->value;
		
		node* elem = root;
		root = elem->next;
		delete elem;
		size--;
		
		return value;
	}

	void addToTop(long long val)
	{
		if(root)
			root->value += val;
	}

};

class keyvalue
{
public:
	std::string key;
	long value;

	keyvalue(const std::string& pkey, long pvalue) : key(pkey), value(pvalue)
	{}
};

class mymap
{
private:
	long size;
	long count;
	keyvalue** data;

	unsigned long hash(const std::string& value, long repeat, long psize)
	{
		unsigned long hash = 0;
		long length = value.length();
	    for(long x = 0; x < length; x++)
	    {
	    	hash += value[x];
	    	hash += (hash << 10);
	    	hash ^= (hash >> 6);
	    }

	    hash += (hash << 3);
	    hash ^= (hash >> 11);
	    hash += (hash << 15);
		return (hash + repeat) % psize;
	}

public:
	long max;

	mymap(long psize) : max(0)
	{
		size = psize;
		count = 0;
		data = new keyvalue*[size];
		for (long x = 0; x < size; x++)
		{
			data[x] = NULL;
		}
	}

	~mymap()
	{
		for (long x = 0; x < size; x++)
		{
			if (data[x] != NULL)
				delete data[x];
		}
		delete[] data;
	}

	void rehash()
	{
		// cout << "rehashing" << endl;
		long newSize = size * 2;
		keyvalue** buf = new keyvalue*[newSize];
		for(long x = 0; x < newSize; x++)
		{
			buf[x] = NULL;
		}

		for(long x = 0; x < size; x++)
		{
			if(data[x])
			{
				// cout << x << endl;
				long tryCount = 0;
				count++;
				while (true)
				{
					long pos = hash(data[x]->key, tryCount, newSize);
					// cout << pos << endl;
					if (buf[pos] == NULL)
					{
						buf[pos] = data[x];
						break;
					}
					tryCount++;
				}
			}
		}

		delete[] data;
		data = buf;
		size = newSize;
	}

	void add(const std::string& key, long value)
	{
		if(count > 3 * size / 4)
		{
			rehash();
		}

		if(value > max)
		{
			max = value;
		}

		long tryCount = 0;
		count++;
		while (true)
		{
			long pos = hash(key, tryCount, size);
			// cout << pos << endl;
			if (data[pos] == NULL)
			{
				data[pos] = new keyvalue(key, value);
				return;
			}
			else if (data[pos]->key == key)
			{
				data[pos]->value += value;
				if(data[pos]->value > max)
				{
					max = data[pos]->value;
				}
				// cout << "key: " << key << ", value: " << endl;
				count--;
				return;
			}

			tryCount++;
		}
	}

	std::string getmax()
	{
		if(count)
		{
			std::string found;
			long index = 0;
			for(index = 0; index < size; index++)
			{
				if(data[index] && data[index]->value == max)
				{
					found = data[index]->key;
					break;
				}
			}

			for(; index < size; index++)
			{
				if(data[index] && data[index]->value == max)
				{
					if(found > data[index]->key)
					{
						found = data[index]->key;
					}
				}
			}
			return found;
		}
		return std::string();
	}

};

bool checkPossibility(mymap& names)
{

	long count = 0;
	scanf("%ld\n", &count);

	stack halves;
	stack sizes;

	long depth = 0;
	long cur = 0;
	std::string name;

	bool isok = (count % 2 == 0);
	long x = 0;

	if(isok)
	{
		for(; x < count; x++)
		{
			std::cin >> cur;
			std::cin.get();
			std::getline(std::cin, name);
			if(cur < 0)
			{
				names.add(name, -cur);
				sizes.push(0);
				halves.push(cur);
				depth++;
			}
			else if(cur > 0)
			{
				names.add(name, cur);
				if(halves.length() < 1 || sizes.length() < 1)
				{
					isok = false;
					break;
				}

				long val = halves.pop();
				long size = sizes.pop();
				if(sizes.length())
					sizes.addToTop(cur);
				
				if(val + size > 0)
				{
					isok = false;
					break;
				}

				if(cur + val != 0)
				{	
					isok = false;
					break;
				}

				depth--;

				if(depth == 0 && x != count -1)
				{
					isok = false;
					break;
				}
			 }
		}
	}
	else
	{
		x--;
	}

	if(depth != 0)
	{
		isok = false;
	}

	for(x++; x < count; x++)
	{
		std::cin >> cur;
		std::cin.get();
		std::getline(std::cin, name);
		names.add(name, cur < 0 ? -cur : cur);
	}

	return isok;
}

int main(int argc, char* argv[])
{
	mymap names(128);
	if(checkPossibility(names))
	{
		printf("Ano\n");
	}
	else
	{
		printf("Ne\n");
	}

	printf("%s\n", names.getmax().c_str());
	return 0;
}