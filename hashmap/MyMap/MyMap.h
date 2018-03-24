#ifndef MY_MAP_H
#define MY_MAP_H

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename Key, typename Value> class Wrapper
{
public:
	Wrapper(const Key& key, const Value& value)
	{
		cout << "Ukladam " << key << ", " << value << endl;
		mKey = key;
		mValue = value;
	}
public:
	Key mKey;
	Value mValue;
};

template <typename Key, typename Value> class MyMap
{
public:
	static const int DEFAULT_SIZE = 7;
private:
	Wrapper<Key, Value>** mData;
	int mCount;
	int mSize;
public:
	MyMap(int size = DEFAULT_SIZE);
	~MyMap();
	Value& Add(const Key& key, const Value& value);
	Value& Get(const Key& key) const;
	int Size();

	friend ostream& operator<<(ostream& os, const MyMap& map)
	{
		for (int x = 0; x < map.mSize; x++)
		{
			if (map.mData[x] != nullptr)
			{
				os << x << ": " << map.mData[x]->mValue << endl;
			}
			else
			{
				os << x << ": nullptr" << endl;
			}
		}
		return os;
	}

	Value& operator[](const Key& key)
	{
		int tryCount = 0;
		mCount++;
		while (true)
		{
			int pos = Hash(key, tryCount);
			if (mData[pos] == nullptr)
			{
				mData[pos] = new Wrapper<Key, Value>(key, Value());
				return mData[pos]->mValue;
			}
			else if (mData[pos]->mKey == key)
			{
				mCount--;
				return mData[pos]->mValue;
			}
			tryCount++;
		}
	}
private: 
	int Hash(int key, int repeat = 0);
	int Hash(string& key, int repeat = 0);
};

template<typename Key, typename Value>MyMap<Key, Value>::MyMap(int size)
{
	mSize = size;
	mCount = 0;
	mData = new Wrapper<Key, Value>*[size];
	for (int x = 0; x < size; x++)
	{
		mData[x] = nullptr;
	}
}

template<typename Key, typename Value>int MyMap<Key, Value>::Hash(string& key, int repeat)
{
	unsigned long hash = 5381;
	for each (char cur in key)
	{
		hash = ((hash << 5) + hash) + cur;
	}

	return (hash + (repeat * hash) % 3) % mSize;
}

template<typename Key, typename Value>int MyMap<Key, Value>::Hash(int key, int repeat)
{
	
	return (key + (repeat * key) % 3) % mSize;
}

template<typename Key, typename Value>Value& MyMap<Key, Value>::Add(const Key& key, const Value& value)
{
	int tryCount = 0;
	mCount++;
	while (true)
	{
		int pos = Hash(key, tryCount);
		if (mData[pos] == nullptr)
		{
			mData[pos] = new Wrapper<Key, Value>(key, value);
			return mData[pos]->mValue;
		}
		else if (mData[pos]->mKey == key)
		{
			delete mData[pos];
			mData[pos] = new Wrapper<Key, Value>(key, value);
			cout << "key: " << key << ", value: " << value << " - overriden" << endl;
			mCount--;
			return mData[pos]->mValue;
		}
		tryCount++;
	}
}

template<typename Key, typename Value>Value& MyMap<Key, Value>::Get(const Key& key) const
{
	int tryCount = 0;
	while (true)
	{
		int pos = Hash(key, tryCount);
		if (mData[pos] == nullptr)
		{
			throw new exception("value doesn't exist!");
		}
		else if (mData[pos]->mKey == key)
		{
			return mData[pos]->mValue;
		}
		tryCount++;
	}
}

template<typename Key, typename Value>int MyMap<Key, Value>::Size()
{
	return mCount;
}

template<typename Key, typename Value>MyMap<Key, Value>::~MyMap()
{
	for (int x = 0; x < mSize; x++)
	{
		if (mData[x] != nullptr)
			delete mData[x];
	}
	delete[] mData;
}

#endif MY_MAP_H


