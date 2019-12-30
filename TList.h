#ifndef TLIST_H
#define TLIST_H

#include <cstdint>
#include "triangle.h"
#include "Iterator.h"
#include "TListItem.h"

template <class T>
class TList
{
public:
    TList();
    void Insert(std::shared_ptr<T> &obj);
    const bool IsEmpty() const;
    int32_t GetLength();
    std::shared_ptr<T> Erase();
    void Del();

	std::shared_ptr<TListItem<T>> operator[](uint num);

	forward_iterator<TListItem<T>,T> begin();
	forward_iterator<TListItem<T>,T> end();

    template <class A> friend std::ostream& operator<<(std::ostream &os, const TList<A> &list);
	
private:
    int32_t length;
    std::shared_ptr<TListItem<T>> head;

    void InsertFirst(std::shared_ptr<T> &obj);
    void InsertLast(std::shared_ptr<T> &obj);
    void InsertAtIndex(std::shared_ptr<T> &obj, int32_t ind);
	void InsertAtIterator(std::shared_ptr<T> &obj, forward_iterator<TListItem<T>, T> Iterator);
    std::shared_ptr<T> EraseFirst();
    std::shared_ptr<T> EraseLast();
    std::shared_ptr<T> EraseAtIndex(int32_t ind);
	std::shared_ptr<T> EraseAtIterator(forward_iterator<TListItem<T>, T> Iterator);
};

#endif
