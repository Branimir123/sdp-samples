#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Sorting\Sorting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortingTest
{
	///
	/// Checks whether an array is sorted
	///
	/// The function assumes that the greater than operator (>)
	/// is defined for the type T
	///
	/// \return
	///		true if the array is sorted or empty (Size==0) or pArr==NULL
	///
	template <typename T>
	bool IsSorted(T* pArr, size_t Size)
	{
		if (Size == 0 || !pArr)
			return true;

		for (size_t i = 1; i < Size; i++)
		{
			if (pArr[i-1] > pArr[i])
				return false;
		}

		return true;
	}


	///
	/// ������ ����������� �� ���� ��������� ������� �����
	/// �������� �����.
	///
	/// �� ����� �� ��������� ������� ������������� ����������
	/// ������ � �����, ���� ��������� �� ������� ����� ����� ��
	/// ��� � ���� ���� �� ��������� ���� �� ���������.
	///
	/// SAMPLE_TYPE ���� �� ���� ���������� ������ ��� � C++
	/// (�������� int, unsigned int, float, double)
	///
	/// \param [in] pfnSort
	///     �������� ��� ���������, ����� �� �� ������
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnSamples(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		// �������� �� ��������� ����� ��� ��������.
		// ��� ������� �� ��������� ��������� � ���� ������� ������ (10)
		// � ����������� ����� ���� �� ���� � ������� �� unit test-�����,
		// �� ��������, �� � BottomUpMergeSort, �� �� ��������� ����
		// ��������, ����� ����� �� ��������, � �����
		// ���������� �������� � �������� ��������� �� ��������� � pBuffer,
		// � �� � pArr.
		// ��� �������� ������, �� ����� ���� �� �� ���� ���� �������.
		// �������� ����� �� �������� ��������� � ������ � ������ �������,
		// �� BottomUpMergeSort �� ���� ���� ������� ���� �������� �� ������� �����
		// (�������� ��� �� ������� �� ������ ����� ����� � ������ ����� 4 � 8).

		SAMPLE_TYPE DataSamples[][10] = {
				{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
				{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
				{ 1, 0, 3, 2, 5, 4, 7, 6, 9, 8 },
				{ 1, 9, 6, 7, 1, 3, 2, 1, 5, 0 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 }
		};

		const int SampleSize = 10; // ��� �� �������� �������� �� 7,
		                           // �� �������� ���������� �� BottomUpMergeSort

		const int SamplesCount = 6;

		for (int i = 0; i < SamplesCount; i++)
		{
			pfnSort(DataSamples[i], SampleSize);
			Assert::IsTrue(IsSorted(DataSamples[i], SampleSize));
		}
	}

	///
	/// ������ ����������� �� ���� ��������� ������� �����
	/// NULL pointer.
	///
	/// ������ �� ����������� �� ��������� ��� �������
	/// NULL pointer � ������ �� ����� ����� �� ����, �����
	/// � ������� NULL pointer � ������ �������� �� ����.
	///
	/// SAMPLE_TYPE ���� �� ���� ���������� ������ ��� � C++
	/// (�������� int, unsigned int, float, double)
	///
	/// \param [in] pfnSort
	///     �������� ��� ���������, ����� �� �� ������
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnNull(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		pfnSort(NULL, 100);
		pfnSort(NULL, 0);
	}

	///
	/// ������ ����������� �� ���� ��������� ������� ���
	/// ������ 0 �� ��������� �����
	///
	/// ������ �� ����������� �� ��������� ��� ��������
	/// �������� 0 �� ��������� ������� �����
	///
	/// \param [in] pfnSort
	///     �������� ��� ���������, ����� �� �� ������
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnZeroSize(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		SAMPLE_TYPE Sample[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		
		pfnSort(Sample, 0);
		pfnSort(NULL, 0);
	}
	
	///
	/// ������ ����������� �� ���� ��������� �������
	///
	/// \param [in] pfnSort
	///     �������� ��� ���������, ����� �� �� ������
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunction(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		TestSortingFunctionOnSamples<SAMPLE_TYPE>(pfnSort);
		TestSortingFunctionOnNull<SAMPLE_TYPE>(pfnSort);
		TestSortingFunctionOnZeroSize<SAMPLE_TYPE>(pfnSort);
	}


	TEST_CLASS(SortingTest)
	{
	public:
		
		TEST_METHOD(SelectionSort_Test)
		{
			TestSortingFunction(SelectionSort<double>);
		}

		TEST_METHOD(BubbleSort_Test)
		{
			TestSortingFunction(BubbleSort<double>);
		}

		TEST_METHOD(ShakerSort_Test)
		{
			TestSortingFunction(ShakerSort<double>);
		}

		TEST_METHOD(DistributionCounting_Test_Double)
		{
			TestSortingFunction(DistributionCounting<double>);
		}

		TEST_METHOD(DistributionCountingInt_Test_Int)
		{
			TestSortingFunction(DistributionCounting<int>);
		}

		TEST_METHOD(InsertionSort_Test)
		{
			TestSortingFunction(InsertionSort<double>);
		}

		TEST_METHOD(ShellSort_Test)
		{
			TestSortingFunction(ShellSort<double>);
		}

		TEST_METHOD(QuickSort_Test)
		{
			TestSortingFunction(QuickSort<double>);
		}

		TEST_METHOD(HeapSort_Test)
		{
			TestSortingFunction(HeapSort<double>);
		}

		TEST_METHOD(MergeSort_Test)
		{
			TestSortingFunction(MergeSort<double>);
		}

		TEST_METHOD(BottomUpMergeSort_Test)
		{
			TestSortingFunction(BottomUpMergeSort<double>);
		}
	};
}