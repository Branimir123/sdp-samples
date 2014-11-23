#include <assert.h>
#include <exception>
#include "LinkedStack.h"


///
/// ����������� �� ������������ �� �������� �����
///
LinkedStack::Box::Box(double Data, Box* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}


///
/// ����������� �� ������������
///
LinkedStack::LinkedStack()
{
	Init();
}


///
/// ����������� �� ��������
///
/// \exception std::bad_alloc
///		��� ���������� �� �������� �������
///
LinkedStack::LinkedStack(LinkedStack const & Other)
{
	Init();
	CopyFrom(Other); // CopyFrom �������� ���� ���� ��,
					 // ��� ���������� � ���������
}


///
/// ����������
///
LinkedStack::~LinkedStack()
{
	Destroy();
}


///
/// �������� �� �����������
///
/// ���������� � ���������� ����, �� ����� �����������
/// ������� ����� �� ����� � ���� ���� ������ �������.
///
/// ��� ���������� �� �������� �������,
/// ��������� �������� � ������ �� ���� ������.
///
/// \exception std::bad_alloc
///		��� ���������� �� �������� �������
///
LinkedStack& LinkedStack::operator=(LinkedStack const & Other)
{
	if (this != &Other)
	{
		Destroy();
		CopyFrom(Other);
	}

	return *this;
}


///
/// ������ ������� ��������� �� ����-������� �� �����.
///
/// ����������� �����������, �� ������ � ������ � ��
/// �������� �������� �� � �������� �����.
///
void LinkedStack::Init()
{
	pTop = 0;
	Used = 0;
}


///
/// �������� ����� � ����������� ������� �� ���� �����
///
void LinkedStack::Destroy()
{
	Box* p;

	while (pTop)
	{
		p = pTop;
		pTop = pTop->pNext;
		delete p;
	}

	Init();
}


///
/// ������ ������������ �� ���� ����
///
/// ��������� ����������, �� �������,
/// � ����� �������� � ������.
///
/// \param [in] element
///		���� �����, ����� ����� ������ �� �� �������
/// 
/// \exception std::bad_alloc
///		��� ���������� �� ����� � ���� ���������
///
void LinkedStack::CopyFrom(LinkedStack const& Other)
{
	if (Other.IsEmpty())
		return;

	Box *ours, *theirs;

	// ��������� ����� �� �������� �� �������� � LinkedStack
	// ��� ���������� �� � �������, ��������� �������� ���� ���� ��
	try
	{
		pTop = new Box(Other.pTop->Data);

		ours = pTop;
		theirs = Other.pTop->pNext;

		while (theirs)
		{
			ours->pNext = new Box(theirs->Data);
			ours = ours->pNext;
			theirs = theirs->pNext;
		}

		Used = Other.Used;
	}
	catch (std::bad_alloc&)
	{
		Destroy();	// ���� �� �� ������, ������:
					// 1. pTop ���� ��� ����� �� ����������� ������
					// 2. �������� �������, ���� �� ���������� ����� ��� ��������
					//    ��� pNext == NULL
		throw;
	}
}


///
/// ������ ��� ������� �� ����� �� �����
///
/// \param [in] element
///		�������, ����� ������ �� �� ������
///
/// \return
///		true ��� ��������� ����� � false � �������� ������.
///
bool LinkedStack::Push(double element)
{
	Box* pNewBox;

	try {
		pNewBox = new Box(element, pTop);
	}
	catch(...) {
		return false;
	}

	pTop = pNewBox;
	Used++;
	return true;
}


///
/// �������� � ����� ��������, ����� �� ������ �� ����� �� �����
///
/// \param [out] element
///		��������� ����� ���������� �� �������� � ���� ���������.
///		��� ������ � ������, ��� �� �� �������.
///
/// \return
///		true ��� ��������� ����� � false � �������� ������.
///
bool LinkedStack::Pop(double& element)
{
	if (Used == 0)
		return false;

	element = pTop->Data;

	Box* pOld = pTop;
	pTop = pTop->pNext;
	delete pOld;
	
	Used--;

	return true;
}


///
/// ����� ��������, ����� �� ������ �� ����� �� �����
///
/// ��� ������ � ������, ��������� ����������� assertion fault
///
/// \return
///		���������� �� ��������
///
double LinkedStack::Peek() const
{
	assert(Used != 0);

	return pTop->Data;
}


///
/// �������� ������ �������� �� �����
///
/// ������ ���������� �����������, ���� �������
/// ����������� � ������� ����� �� �����.
///
void LinkedStack::RemoveAll()
{
	Destroy();
}


///
/// ����� ������������ ���������� �� ����� � ���� ��������
///
size_t LinkedStack::GetAllocatedSize() const
{
	return Used * sizeof(Box);
}


///
/// ����� ���� �� ����������� � ����� ��������
///
size_t LinkedStack::GetSize() const
{
	return Used;
}


///
/// ��������� ���� ������ � ������
///
bool LinkedStack::IsEmpty() const
{
	return Used == 0;
}