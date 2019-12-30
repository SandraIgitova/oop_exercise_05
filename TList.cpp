#include "TList.h"
#include <iostream>
#include <cstdint>

template <class T>
TList<T>::TList()
{
    head = nullptr;
    length = 0;
}

template <class T>
void TList<T>::Insert(std::shared_ptr<T> &obj)
{
    int32_t index = 0;
    std::cout << "Введите индекс позиции: ";
    std::cin >> index;
    if (index > this->GetLength() || index < 0) {
        std::cerr << "Введенный индекс находиться за пределами возможных значений\n";
        return;
    }
    if (index == 0) {
        this->InsertFirst(obj);
    } else if (index == this->GetLength()) {
        this->InsertLast(obj);
    } else {
        this->InsertAtIndex(obj, index);
    }
    ++length;
}

template <class T>
void TList<T>::InsertAtIndex(std::shared_ptr<T> &obj, int32_t ind)
{
	forward_iterator<TListItem<T>, T> it = begin();
    for(int32_t i = 0; i < ind; ++i){
		++it;
    }
	InsertAtIterator(obj, it);
}

template <class T>
void TList<T>::InsertAtIterator(std::shared_ptr<T> &obj, forward_iterator<TListItem<T>, T> Iterator) {
	std::shared_ptr<TListItem<T>> newItem = std::make_shared<TListItem<T>>(obj);
	std::shared_ptr<TListItem<T>> tmp = *Iterator;
	tmp->GetPrev()->SetNext(newItem);
	newItem->SetPrev(tmp->GetPrev());
	newItem->SetNext(tmp);
	tmp->SetPrev(newItem);
}

template <class T>
void TList<T>::InsertLast(std::shared_ptr<T> &obj)
{
    std::shared_ptr<TListItem<T>> newItem = std::make_shared<TListItem<T>>(obj);
    std::shared_ptr<TListItem<T>> tmp = this->head;

    while (tmp->GetNext() != nullptr) {
        tmp = tmp->GetNext();
    }
    tmp->SetNext(newItem);
    newItem->SetPrev(tmp);
    newItem->SetNext(nullptr);
}

template <class T>
void TList<T>::InsertFirst(std::shared_ptr<T> &obj)
{
    std::shared_ptr<TListItem<T>> newItem = std::make_shared<TListItem<T>>(obj);
    std::shared_ptr<TListItem<T>> oldHead = this->head;
    this->head = newItem;
    if(oldHead != nullptr) {
        newItem->SetNext(oldHead);
        oldHead->SetPrev(newItem);
    }
}

template <class T>
int32_t TList<T>::GetLength()
{
    return this->length;
}

template <class T>
const bool TList<T>::IsEmpty() const
{
    return head == nullptr;
}

template <class T>
std::shared_ptr<T> TList<T>::Erase()
{
    int32_t ind = 0;
    std::cout << "Введите индекс позиции: ";
    std::cin >> ind;
    std::shared_ptr<T> res;
    if (ind > this->GetLength() - 1 || ind < 0 || this->IsEmpty()) {
        std::cout << "Измените индекс" << std::endl;
        return res;
    }

    if (ind == 0) {
        res = this->EraseFirst();
    } else if (ind == this->GetLength() - 1) {
        res = this->EraseLast();
    } else {
        res = this->EraseAtIndex(ind);
    }
    --length;
    return res;
}

template <class T>
std::shared_ptr<T> TList<T>::EraseAtIndex(int32_t ind)
{
	forward_iterator<TListItem<T>, T> it = begin();
	for (int32_t i = 0; i < ind; ++i) {
		++it;
	}
	std::shared_ptr<T> res = EraseAtIterator(it);
	return res;
}

template <class T>
std::shared_ptr<T> TList<T>::EraseAtIterator(forward_iterator<TListItem<T>, T> Iterator)
{
	std::shared_ptr<TListItem<T>> tmp = *Iterator;
	std::shared_ptr<TListItem<T>> removed = tmp;
	std::shared_ptr<T> res = removed->GetFigure();
	std::shared_ptr<TListItem<T>> nextItem = removed->GetNext();
	std::shared_ptr<TListItem<T>> prevItem = removed->GetPrev();
	prevItem->SetNext(nextItem);
	nextItem->SetPrev(prevItem);
	return res;
}

template <class T>
std::shared_ptr<T> TList<T>::EraseFirst()
{
    if (this->GetLength() == 1) {
        std::shared_ptr<T> res = this->head->GetFigure();
        this->head = nullptr;
        return res;
    }
    std::shared_ptr<TListItem<T>> tmp = this->head;
    std::shared_ptr<T> res = tmp->GetFigure();
    this->head = this->head->GetNext();
    this->head->SetPrev(nullptr);
    return res;
}

template <class T>
std::shared_ptr<T> TList<T>::EraseLast()
{
    if (this->GetLength() == 1) {
        std::shared_ptr<T> res = this->head->GetFigure();
        this->head = nullptr;
        return res;
    }
    std::shared_ptr<TListItem<T>> tmp = this->head;
    while(tmp->GetNext()->GetNext()) {
        tmp = tmp->GetNext();
    }
    std::shared_ptr<TListItem<T>> removed = tmp->GetNext();
    std::shared_ptr<T> res = removed->GetFigure();
    tmp->SetNext(removed->GetNext());
    return res;
}

template <class T>
std::ostream& operator<<(std::ostream &os, const TList<T> &list)
{
    if (list.IsEmpty()) {
        os << "Список пуст." << std::endl;
        return os;
    }

    std::shared_ptr<TListItem<T>> tmp = list.head;
    for(int32_t i = 0; tmp; ++i) {
        os << "Фигура номер " << i << " :  \n";
        tmp->GetFigure()->Print();
        os << std::endl;
        tmp = tmp->GetNext();
    }

    return os;
}

template <class T>
void TList<T>::Del()
{
    while(!this->IsEmpty()) {
        this->EraseFirst();
        --length;
    }
}

template <class T>
forward_iterator<TListItem<T>,T> TList<T>::begin()
{
    return forward_iterator<TListItem<T>,T>(head);
}

template <class T>
forward_iterator<TListItem<T>,T> TList<T>::end()
{
    return forward_iterator<TListItem<T>,T>(nullptr);
}

template <class T>
std::shared_ptr<TListItem<T>> TList<T>::operator[](uint num) { // доступ к элементу списка по номеру через оператор []
	forward_iterator<TListItem<T>, T> it = forward_iterator<TListItem<T>, T>(head);
	for (uint32_t i = 0; i < num; ++i) {
		++it;
	}
	return *it;
}

#include "triangle.h"
template class TList<Triangle>;
template std::ostream& operator<<(std::ostream &out, const TList<Triangle> &obj);