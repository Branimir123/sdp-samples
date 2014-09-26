#include <iostream>
#include <algorithm>
#include <assert.h>

///
/// ��� b < a, ��������� ������� ������� ���������
///
template <class T>
void swapif(T& a, T& b)
{
	if( b < a )
	{
		T temp(a);
		a = b;
		b = temp;
	}
}


///
/// ����� �������� (Selection Sort)
///
template <class T>
void SelectionSort(T* pArr, size_t Size)
{
	for(size_t i = 0; i < Size-1; i++)
	{
		size_t min = i;

		for(size_t j = i+1; j < Size; j++)
		{
			if(pArr[j] < pArr[min])
				min = j;
		}

		swapif(pArr[i], pArr[min]);
	}
}


///
/// ����� �� ��������� (Bubble Sort)
///
template <class T>
void BubbleSort(T* pArr, size_t Size)
{
	for(size_t i = 0; i < Size-1; i++)
	{
		for(size_t j = Size-1; j > i; j--)
		{
			swapif(pArr[j-1], pArr[j]);
		}
	}
}


///
/// ��������� ���� ������� (Shaker Sort)
///
template <class T>
void ShakerSort(T* pArr, size_t Size)
{
	size_t left = 0;
	size_t right = Size-1;

	while(left < right)
	{
		for(size_t r = right; r > left; r--)
			swapif(pArr[r-1], pArr[r]);

		left++; // ������ ���-������� ������� �� ���� ��������� ���� � �� ������ �����

		for(size_t l = left+1; l <= right; l++)
			swapif(pArr[l-1], pArr[l]);

		right--; // ������ ���-�������� ������� �� ���� ��������� ���� � ���� ������ �����
	}
}


///
/// �������, ����� ����� ����� �� ������� ���������� ���.
///
///	�� ��������� ��� ������������, �� ����� � ������ �� int
///
template <class T>
int key(T& value)
{
	return static_cast<int>(value);
}


///
/// ������ �� ������� �� ����� � ��������, ����� �� ������� �� int.
/// ���������� ��, �� ������ ������������� ������� �� int,
/// �� �������� ��������, ����� � ���������� ����� - �������� ����.
///
template <class T>
void DistributionCounting(T* pArr, size_t Size)
{
	// �������� ���-������� ���� � ������
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		int nextKey = key(pArr[i]);

		if(maxN < nextKey)
			maxN = nextKey;
	}

	// � ���� ����� �� ����� ���������, �� ����� ������� ������ �������� �� ��������
	// ��� ���� ���������� �����
	// (maxN ���� ������ �� ���� ������� ������ � ������!)
	size_t * pEndsAt = new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) // ���-������ �������� �����������
		pEndsAt[i] = 0;

	// ���� ����� ��������� �� ������� �� ����������
	for(size_t i = 0; i < Size; i++)
	{
		pEndsAt[key(pArr[i])]++;
	}

	// ���� ����� �� ��������� ���������, �� ����� ������� ����� �������� �� ��������:
	for(int i = 1; i <= maxN; i++)
	{
		pEndsAt[i] += pEndsAt[i-1];
	}

	// ���� ��������� ����������� � ��� �����:
	T* pSorted = new T[Size];

	// �����: for(size_t i = Size; myi >= 0; myi--)
	//	������ ���� �� �������!

	size_t j = Size;

	while(j--)
	{
		size_t pos = --pEndsAt[key(pArr[j])];
		pSorted[pos] = pArr[j];
	}

	// �������� ���������� ����� ������� � �����������
	for(size_t i = 0; i < Size; i++)
	{
		pArr[i] = pSorted[i];
	}

	delete [] pSorted;
	delete [] pEndsAt;
}


///
/// ������ �� ������� �� ����� � �������� � ���������� �����
///
template <> void DistributionCounting<int>(int* pArr, size_t Size)
{
	// �������� ���-�������� ����� � ������
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		if(maxN < pArr[i])
			maxN = pArr[i];
	}

	// � ���� ����� �� ����� ���� �� ��������� �� ����� �������
	// (maxN ���� ������ �� ���� ������� ������ � ������!)
	size_t * pCounts =  new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) // �������� �����������
		pCounts[i] = 0;

	// ����� ��������� �� ������� �� ����������
	for(size_t i = 0; i < Size; i++)
	{
		pCounts[pArr[i]]++;
	}

	// ��������� ���������� �� ���������� �� ����� � ������
	size_t pos = 0;

	for(int i = 0; i <= maxN; i++)
	{
		while(pCounts[i] > 0)
		{
			pArr[pos++] = i;
			pCounts[i]--;
		}
	}

	delete [] pCounts;
}



///
/// ��������� ���� �������� (Insertion Sort)
///
template <class T>
void InsertionSort(T* pArr, size_t Size)
{
	// ����������� ����������� ������� ���-������
	for(size_t i = Size-1; i > 0; i--)
	{
		swapif(pArr[i-1], pArr[i]);
	}

	// ���� ����������� �������� �� �����������
	for(size_t i = 2; i < Size; i++)
	{
		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-1] > value)
		{
			pArr[j] = pArr[j-1];
			j--;
		}

		pArr[j] = value;
	}
}


///
/// h-������� ���������� �� pArr,
/// ����� �� ������� �� ������� i, i+h, i+2h, ...
///
template <class T>
void ShellSortH(T* pArr, size_t Size, size_t k, size_t h)
{
	// h-��������� �� pArr �� ������� k, k+h, k+2h, ...
	// � �������� � h-��������� �� pArr + k �� ������� 0, h, 2h, ...
	pArr = pArr + k;
	Size = Size - k; // �����, �� �� ������� ������ ����� �������

	// �������� ���-������� ������ Ai = i*h, ����� �� Ai < Size
	size_t LastElement = (Size / h) * h - 1;

	size_t i;

	// ����������� ���-������ ������� ���-������
	for(i = LastElement; i > 0; i-=h)
	{
		assert( 0 <= i && i < Size);
		assert( 0 <= (i-h) && (i-h) < Size);
		swapif(pArr[i-h], pArr[i]);
	}

	assert(i == 0);

	// ���� h-��������� ���������� �� ������� 0, h, 2h, ...
	for(size_t i = h; i < Size; i+=h)
	{
		assert( 0 <= i && i < Size);

		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-h] > value)
		{
			assert( 0 <= j && j < Size);
			pArr[j] = pArr[j-h];
			j-=h;
		}

		assert( 0 <= j && j < Size);

		pArr[j] = value;
	}
}

///
/// ���������� �� ��� (Shell Sort)
///
template <class T>
void ShellSort(T* pArr, size_t Size)
{
	size_t h = 1;

	// determine the steps to be used for sorting
	while(h < Size / 9)
		h = h*3 + 1;

	for( ; h > 0; h = (h - 1) / 3 )
	{
		for(size_t i = 0; i < h; i++)
		{
			ShellSortH(pArr, Size, i, h);
		}
	}
}

///
/// ����� ��������� (QuickSort)
///
template <class T>
void QuickSort(T* pArr, size_t Size)
{
	if(Size <= 1)
		return;

	size_t pos = Partition(pArr, Size);

	QuickSort(pArr, pos);
	QuickSort(pArr + pos + 1, Size - pos - 1);
}

template <class T>
size_t Partition(T* pArr, size_t Size)
{
	assert(Size >= 2);

	// ������� Median-of-3 ���� �� �� �������� ��� ������� ��� ���� 3 ��������.
	// ��� ����� ���� ��� ��������, ��������� swapif � ������� 1.
	if(Size == 2)
	{
		swapif(pArr[0], pArr[1]);
		return 1;
	}

	// �������� ������� � Median-of-3
	size_t middle = Size / 2;
	swapif(pArr[0], pArr[middle]);
	swapif(pArr[0], pArr[Size-1]);
	swapif(pArr[middle], pArr[Size-1]);

	std::swap(pArr[middle], pArr[Size-2]);

	T& partitioningElement = pArr[Size-2];

	// ���� ����������� ���� �������� �� QuickSort
	size_t left = 0;
	size_t right = Size-2;

	while(true)
	{
		while(pArr[++left] < partitioningElement)
			;

		while(pArr[--right] > partitioningElement)
		{
			if(left == right)
				break;
		}

		if(left >= right)
			break;

		std::swap(pArr[left], pArr[right]);
	}

	std::swap(pArr[left], partitioningElement);

	return left;
}


///
///	����������� ��������� (Heap Sort)
///
template <class T>
void HeapSort(T* pArr, size_t Size)
{
	size_t i = Size / 2;

	while(i--)
	{
		Sift(pArr, i, Size);
	}


	i = Size;

	while(--i)
	{
		std::swap(pArr[0], pArr[i]);
		Sift(pArr, 0, i);
	}
}


///
/// ���������
///
template <class T>
void Sift(T* pArr, size_t pos, size_t Size)
{
	// ������� ��������, ����� ������ �� �� �����������
	T elem(pArr[pos]);

	size_t ni = pos; // ������ �� ����� �����
	size_t si = pos*2+1; // ������ �� ����� ���������

	while(si < Size)
	{
		// � ������� succ � �������� �� ����� ���������.
		// ��� ��� ����� ��������� � ��� � ��-�����,
		// ������ �� ��������� succ
		if(si < Size-1 && pArr[si] < pArr[si + 1])
			si++;

		// ���� succ e ��������� �� ��-������� �� ����� ����������

		// ��� ���������, ����� ������ � ��-����� �� ��-������� ���������,
		// ����������� ��������
		if(elem > pArr[si])
			break;

		pArr[ni] = pArr[si];
		ni = si;
		si = si * 2 + 1;
	}

	pArr[ni] = elem;
}


///
///	��������� ���� ������� (Merge Sort)
///
template <class T>
void MergeSort(T* pArr, size_t Size)
{
	T* pBuffer = new T[Size];

	MergeSortStep(pArr, Size, pBuffer);

	delete []  pBuffer;
}

template <class T>
void MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if(Size <= 1)
		return;

	size_t middle = Size / 2;

	MergeSortStep(pArr, middle, pBuffer);

	MergeSortStep(pArr + middle, Size - middle, pBuffer + middle);

	Merge(pArr, middle, pArr + middle, Size - middle, pBuffer);

	for(size_t i = 0; i < Size; i++)
		pArr[i] = pBuffer[i];
}

///
///	����� ������������ �� ����� ��������� ������ pA � pB
///	� ������ pResult.
///
///	������� ������� ��� ��������� ���� � ��������.
///	� pResult ������ �� ��� ���� sizeA + sizeB ��������,
///	�� �� ���� �� ������ � ���� �� ��������� �� ���������.
///
template <class T>
void Merge(T* pA, size_t sizeA, T* pB, size_t sizeB, T* pResult)
{
	size_t i = 0; 
	size_t ia = 0;
	size_t ib = 0;

	while(ia < sizeA && ib < sizeB)
		pResult[i++] = (pA[ia] < pB[ib] ? pA[ia++] : pB[ib++]);

	while(ia < sizeA)
		pResult[i++] = pA[ia++];

	while(ib < sizeB)
		pResult[i++] = pB[ib++];
}


///
///	��������� ���� ������� (������-������)
///
template <class T>
void BottomUpMergeSort(T* pArr, size_t Size)
{
	T* pBuffer = new T[Size];

	// �� �� �������� ��������� ���������, �� ���������� ���
	// ��������� � �������� �� �������� ������ ��.
	T* pRead = pArr;
	T* pWrite = pBuffer;

	// � ������ ���������� ��������� ������ �� ����������� ������� �� ������:
	// 1, 2, 4, 8, 16, ...
	for(size_t step = 1; step < Size; step *= 2)
	{
		for(size_t leftA = 0; leftA < Size; leftA += 2*step)
		{
			size_t rightA = std::min(leftA + step - 1, Size - 1);
			size_t leftB = rightA + 1;
			size_t rightB = std::min(leftB + step - 1, Size - 1);

			// ����� �����:
			//    leftA  <= Size-1 - ������� ������ � ������
			//    rightA <= Size-1 - ������� ������ � ������
			//    leftA  <= rightA - ������������ �������� �� ������ �� ������ �����
			//                       leftA � rightA � ���� 1
			//    leftB  <= Size - ������������ � ��� ������� ������ � ������ ��� ����� ��
			//                     ���� ������� ���� ��������� �������
			//    rightB <= Size-1 - ��� leftB � ������� ������ � ������ ����� leftB <= rightB
			//                       ��� leftB == Size, �� rightB == Size-1

			size_t sizeA = (rightA - leftA) + 1; // 1 ��� ������
			size_t sizeB = (rightB - leftB) + 1; // 0, ��� leftB � ����� ������

			Merge(pRead + leftA,
				  sizeA,
				  pRead + leftB,
				  sizeB,
				  pWrite + leftA);
		}

		// ��������� ������ �� ����� ������
		std::swap(pRead, pWrite);
	}

	// ��� ���������� �������� � �������� ��������� �� ��������� � pBuffer,
	// � �� � pArr, ������ �� �������� ����������.
	// �����: ������ ����������� �� ����� ��������� �� ��������� ��� �����
	// ����������� ���� ������, ��������� �� � pWrite != pArr,
	// � pWrite != pBuffer
	if(pWrite != pBuffer)
	{
		for(size_t i = 0; i < Size; i++)
			pArr[i] = pBuffer[i];
	}

	delete [] pBuffer;
}


///
/// ������� ������������ �� pArr
///
template <class SAMPLE_TYPE>
void PrintArray(const SAMPLE_TYPE* pArr, size_t Size)
{
	if(Size == 0)
	{
		std::cout << "(empty)\n";
	}
	else
	{
		std::cout << pArr[0];

		for(size_t i = 1; i < Size; i++)
		{
			std::cout << ", " << pArr[i];
		}
	}
}


///
/// ������ ����������� �� ���� ��������� �������
///
/// \param [in] pfnSort
///     �������� ��� ���������, ����� �� �� ������
///
/// \param [in] Name
///     ����� �� ���������, ����� �� �� ������
///     ���� � ������ �����, ����� �� �� ������ �� ������,
///		�� �� �� ���� ����� �� ��������� � ������� � ���� ���������
///		��� �������� �� ���������.
///
template <class SAMPLE_TYPE>
void TestSortingFunction(void pfnSort(SAMPLE_TYPE*, size_t), const char* Name)
{
	SAMPLE_TYPE DataSamples[][10] = {
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
		{9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
		{1, 0, 3, 2, 5, 4, 7, 6, 9, 8},
		{1, 9, 6, 7, 1, 3, 2, 1, 5, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 2, 1, 2, 1, 2, 1, 2, 1, 2}
	};

	const int SampleSize = 10;
	const int SamplesCount = 6;

	// ��������� ���������� �� ���������
	std::cout << "Testing " << Name;
	std::cout << "\n    Samples: " << SamplesCount;
	std::cout << "\n    Sample size: " << SampleSize;
	std::cout << "\n    Samples:";

	for(int i = 0; i < SamplesCount; i++)
	{
		std::cout << "\n        Sample " << i << ": ";
		PrintArray<SAMPLE_TYPE>(DataSamples[i], SampleSize);
	}

	// ����������� ���������
	std::cout << "\n\n    Sorting results:";
	
	for(int i = 0; i < SamplesCount; i++)
	{
		pfnSort(DataSamples[i], SampleSize);
		std::cout << "\n        Sorted " << i << ": ";
		PrintArray(DataSamples[i], SampleSize);
	}

	std::cout << "\n    [end]\n\n\n";
}


#define TEST(x, SAMPLE_TYPE) TestSortingFunction<SAMPLE_TYPE>(x, #x)

int main()
{
	TEST(SelectionSort, double);
	TEST(BubbleSort, double);
	TEST(ShakerSort, double);
	TEST(DistributionCounting, int);
	TEST(DistributionCounting, double);
	TEST(InsertionSort, double);
	TEST(ShellSort, double);
	TEST(QuickSort, double);
	TEST(HeapSort, double);
	TEST(MergeSort, double);
	TEST(BottomUpMergeSort, double);
}