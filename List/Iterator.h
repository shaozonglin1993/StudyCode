#pragma once

//
// ���������ͱ�
//
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template <class Category, class T, class Distance = ptrdiff_t,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category   IteratorCategory;      // ����������
	typedef T          ValueType;            // ��������ָ��������
	typedef Distance   DifferenceType;        // ����������֮��ľ���
	typedef Pointer    Pointer;               // ��������ָ�������͵�ָ��
	typedef Reference Reference;             // ��������ָ�������͵�����
};


//
// Traits ����һ̨��������ȡ������եȡ���������������ԣ���Ӧ���ͱ�
//
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

//
// ƫ�ػ�ԭ��ָ������
//
template <class T>
struct IteratorTraits< T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                           ValueType;
	typedef ptrdiff_t                   DifferenceType;
	typedef T *                         Pointer;
	typedef T &                         Reference;
};

//
// ƫ�ػ�constԭ��ָ������
//
template <class T>
struct IteratorTraits< const T *>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                           ValueType;
	typedef ptrdiff_t                   DifferenceType;
	typedef const T*                   Pointer;
	typedef const T&                   Reference;
};

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, ForwardIteratorTag)
{
	size_t distance = 0;
	while (first != last)
	{
		++distance;
		++first;
	}

	return distance;
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, BidirectionalIteratorTag)
{
	size_t distance = 0;
	while (first != last)
	{
		++distance;
		++first;
	}

	return distance;
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag)
{
	return last - first;
}

template <class InputIterator>
inline size_t Distance(InputIterator first, InputIterator last)
{
	return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}

template <class InputIterator>
inline void _Advance(InputIterator& i, int n, RandomAccessIteratorTag) {
	i += n;
}

template <class InputIterator>
inline void _Advance(InputIterator& i, size_t n, ForwardIteratorTag) {
	for (size_t i = 0; i < n; ++i)
	{
		++i;
	}
}

template <class InputIterator>
inline void _Advance(InputIterator& i, int n, BidirectionalIteratorTag) {
	if (n > 0)
	{
	}
	else
	{
	}
}



template <class InputIterator>
inline void Advance(InputIterator& i, size_t n) {
	_Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}


template <class Iterator>
class ReverseIterator
{
protected:
	Iterator _current;
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory
		IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType
		ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType
		DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer
		Pointer;
	typedef typename IteratorTraits<Iterator>::Reference
		Reference;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;

public:
	ReverseIterator() {}
	explicit ReverseIterator(IteratorType x) : _current(x) {}

	// ?
	Reference operator*() const {
		Iterator tmp = _current;
		return *--tmp;
	}

	Pointer operator->() const { return &(operator*()); }

	Self& operator++() {
		--_current;
		return *this;
	}
	Self operator++(int) {
		Self tmp = *this;
		--_current;
		return tmp;
	}
	Self& operator--() {
		++_current;
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		++_current;
		return tmp;
	}

	bool operator != (Self& s)
	{
		return _current != s._current;
	}

	bool operator == (Self& s)
	{
		return _current == s._current;
	}

};