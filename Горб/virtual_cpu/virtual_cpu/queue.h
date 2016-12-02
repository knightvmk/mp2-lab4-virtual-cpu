#ifndef __QUEUE_H__
#define __QUEUE_H__

#define MAX_SIZE 100000 // const for max size of queue (array)
#define MIN_SIZE 20 // const for min size of queue (array) // only for default constructor
#define ALLOC_MEM 200 // const for realloc mem for add elements

template <class type>
class TQueue
{
private:
	size_t size; // size of array
	type *pMem; // mem for elem
	size_t count; // count of elements in array 
	size_t first;  // first elem in array
	void Realloc(); // realloc mem after pop

public:
	TQueue();
	TQueue(const int _size);
	TQueue(const TQueue &A);
	~TQueue();
	void Push(const type &R);
	type Pop(); 
	type Peek() const;
	bool IsEmpty() const;
	bool IsFull() const;
	size_t GetCount() const { return count; };
	type GetLast() const; // watch last elem
	type Get(int i) const; //get i-elem
	type Getd(int i); //get and del

};

template <class type>
void TQueue<type>::Realloc()
{
	size += ALLOC_MEM;
	pMem = (type*)realloc(pMem, ALLOC_MEM * sizeof(type));
}

template <class type>
TQueue<type>::TQueue()
{
	size = MIN_SIZE;
	pMem = new type[MIN_SIZE];
	count = 0;
	first = 1;
}

template <class type>
TQueue<type>::TQueue(const int _size)
{
	if (_size<1 || _size>MAX_SIZE)
		throw ("Fail. Size too small or too big");
	size = size_t(_size);
	pMem = new type[size+1];
	count =0;
	first = 1;
}

template <class type>
TQueue<type>::~TQueue()
{
	delete[] pMem;
	pMem = 0;
}

template <class type>
TQueue<type>::TQueue(const TQueue &a)
{
	size = a.size;
	pMem = new type[size+1];
	for (register int i = 0; i <= size; i++)
		pMem[i] = a.pMem[i];
	first = a.first;
	count = a.count;
}

template <class type>
void TQueue<type>::Push(const type &R)
{
	if (IsFull()) Realloc();
	pMem[++count] = R;
}

template <class type>
type TQueue<type>::Pop()
{
	if (!IsEmpty())
	{
		type res = pMem[first];
		for (register int i = 0, j = 1; i <= count; i++)
			pMem[i] = pMem[j++];
		count--;
		return res;
	}
	else throw("Fail. Queue is empty");
}

template <class type>
type TQueue<type>::Peek() const
{
	if (!IsEmpty())
	{
		return pMem[first];
	}
	else throw ("Fail. Queue is empty");
}

template <class type>
bool TQueue<type>::IsFull() const
{
	return (count == size);
}

template <class type>
bool TQueue<type>::IsEmpty() const
{
	return (count == 0);
}

template <class type>
type TQueue<type>::GetLast() const
{
	if (IsEmpty())
		throw ("Fail. Queue is empty");
		return pMem[count];
}

template <class type>
type TQueue<type>::Get(int i) const
{
	if (IsEmpty())
		throw ("Fail. Queue is empty");
	if (i <= size)
		return pMem[i];
	else throw ("Fail. Incorrect iterator");
}

template <class type>
type TQueue<type>::Getd(int i)
{
	if (IsEmpty())
		throw ("Fail. Queue is empty");
	if (i <= size)
	{
		type out = pMem[i];
		for (register int k = i, j = i + 1; i <= count; i++)
			pMem[k] = pMem[j];
		return out;
	}
	else throw ("Fail. Incorrect iterator");
}

#endif
