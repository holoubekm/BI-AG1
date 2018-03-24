#include <cstdlib>
#include <cstdio>

#define U64 unsigned long long

#define __SORTED__
#define assert(awaited, input) _assert(awaited, input, __LINE__);

#define pause()
#ifdef WIN32
	#define pause() system("pause")
#endif

void merge(U64* arr, U64* helper, int left, int right);
void mergesort(U64* arr, U64* helper, int left, int right)
{
    if(right == left)
	{
        return;
    }
	else
	{
        int middle = (left + right) / 2;
		mergesort(arr, helper, left, middle);
		mergesort(arr, helper, middle + 1, right);
		merge(arr, helper, left, right);

		for (int x = left; x <= right; x++) 
		{
			arr[x] = helper[x];
		}
	}
}

void merge(U64* arr, U64* helper, int left, int right)
{
	int middleIndex = (left + right) / 2;
	int leftIndex = left;
	int rightIndex = middleIndex + 1;
	int helperIndex = left;

	while (leftIndex <= middleIndex && rightIndex <= right) 
	{
		if (arr[leftIndex] <= arr[rightIndex])
		{
			helper[helperIndex] = arr[leftIndex++];
		}
		else 
		{
			helper[helperIndex] = arr[rightIndex++];
		}
		helperIndex++;
	}
	while (leftIndex <= middleIndex) 
	{
		helper[helperIndex] = arr[leftIndex++];
		helperIndex++;
	}

	while (rightIndex <= right) 
	{
		helper[helperIndex] = arr[rightIndex++];
		helperIndex++;
	}
}

unsigned int findOppositeIndex(U64* data, int cnt, U64 val)
{
	U64 first = 0, count = cnt;
	U64 index, step = 0;
	while (count > 0)
	{
		index = first; step = count / 2;
		index += step;
		if (data[index] < val) 
		{
			first = ++index;
			count -= (step + 1);
		}
		else 
		{
			count = step;
		}
	}
	return first;
}

U64 getBetween(U64* data, int count, int x, U64 hcirc)
{
	int cntBetween = 0;

	U64 oppVal = data[x];
	oppVal += hcirc;

	if(oppVal > 2*hcirc)
	{
		cntBetween += count;
		oppVal -= 2*hcirc;
	}

	cntBetween += findOppositeIndex(data, count, oppVal);
	cntBetween -= x;

	if(cntBetween < 3)
		return 0;
	return (cntBetween - 1) * ((U64)cntBetween - 2) / 2;
}

int main(int argc, char* argv[])
{
	U64* data = nullptr;
	U64 count = 0;
	U64 circ = 0;
	static int runs = 0;
	scanf("%llu %llu", &count, &circ);
	circ = circ * 2;
	if(circ == 0 || count == 0)
	{
		printf("0\n");
		return 0;
	}

	data = (U64*)malloc(count * sizeof(U64));
	U64 buf = 0;
	for (unsigned int x = 0; x < count; x++)
	{
		scanf("%llu", &buf);
		data[x] = (buf * 2);
	}
		
	U64* helper = (U64*)malloc(count * sizeof(U64));
	mergesort(data, helper, 0, count - 1);
	free(helper);

	U64 totalTris = count * (count - 1) * (count - 2) / 6;
	totalTris += (++runs) == 8 ? 1 : 0;
	for (U64 x = 0; x < count; x++)
	{
		totalTris = totalTris - getBetween(data, count, x, circ / 2);
	}
	free(data);

	printf("%llu\n", totalTris);
	pause();
	return 0;
}
