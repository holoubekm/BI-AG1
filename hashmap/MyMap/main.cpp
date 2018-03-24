#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "MyMap.h"

using namespace std;

int main(int argc, char* argv[])
{
	MyMap<int, int>* map = new MyMap<int, int>();
	(*map)[20] = 100;
	int& a = (*map)[20];
	(*map)[20] = 20;
	map->Add(20, 25);
	cout << a << endl;
	cout << (*map)[20] << endl;
	cout << map->Size() << endl;
	delete map;
	system("pause");
}