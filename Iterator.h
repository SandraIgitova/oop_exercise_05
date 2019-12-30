#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <iostream>
#include "TListItem.h"

template <class N, class T>
class forward_iterator
{
public:
	using value_type = T;
	using reference = T & ;
	using pointer = T * ;
	using difference_type = ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	forward_iterator(std::shared_ptr<N> n) {
        cur = n;
    }

	std::shared_ptr<N> operator* () {
        return cur;
    }
	
    std::shared_ptr<T> operator-> () {
        return cur->GetFigure();
    }

    void operator++() {
		if (((!cur)&&(!(cur->GetNext())))) {
			throw std::logic_error("попытка доступа к несуществующему элементу");
		}
        cur = cur->GetNext();
    }

	forward_iterator operator++ (int) {
		forward_iterator cur(*this);
        ++(*this);
        return cur;
    }

    void operator--() {
		if (((!cur) && (!(cur->GetPrev())))) {
			throw std::logic_error("попытка доступа к несуществующему элементу");
		}
        cur = cur->GetPrev();
    }

	forward_iterator operator-- (int) {
		forward_iterator cur(*this);
        --(*this);
        return cur;
    }

    bool operator== (const forward_iterator &i) {
        return (cur == i.cur);
    }

    bool operator!= (const forward_iterator &i) {
        return (cur != i.cur);
    }

private:
    std::shared_ptr<N> cur;
};

#endif