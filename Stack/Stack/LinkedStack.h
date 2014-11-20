#pragma once

///
///	��������� �� ���� ��� �������� �����������
///
/// ������ �������� ���������, ������ ���� �� �����������
/// � ���� ��������.
///
class LinkedStack {
	class Box {
	public:
		double Data;
		Box* pNext;
		Box(double, Box* = 0);
	};

public:
	LinkedStack();
	~LinkedStack();
	LinkedStack(LinkedStack const & Other);
	LinkedStack& operator=(LinkedStack const & Other);

public:
	bool Push(double element);
	bool Pop(double& element);
	double Peek() const;
	void RemoveAll();

	size_t GetAllocatedSize() const;
	size_t GetSize() const;
	bool IsEmpty() const;

private:
	void Init();
	void Destroy();
	void CopyFrom(LinkedStack const & Other);

private:
	Box* pTop;
	size_t Used;
};