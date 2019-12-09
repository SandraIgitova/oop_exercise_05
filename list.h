#ifndef D_CONTAINERS_list_H_
#define D_CONTAINERS_list_H_ 1

#include <iterator>
#include <memory>

// контейнер из примера с гитхаба с модификациями для использования в качестве списка
// используются shared_ptr, weak_ptr, реализован доступ к элементу по оператору []

namespace containers {

	template<class T>
	struct list {
	private:
		struct list_node;

	public:
		list() = default;

		struct forward_iterator {
			using value_type = T;
			using reference = T & ;
			using pointer = T * ;
			using difference_type = ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			forward_iterator(list_node* ptr);

			T& operator*();
			forward_iterator& operator++();
			forward_iterator operator++(int);
			forward_iterator operator[](uint num);

			bool operator== (const forward_iterator& o) const;
			bool operator!= (const forward_iterator& o) const;

		private:
			list_node* ptr_;
			friend list;
		};
		forward_iterator begin();
		forward_iterator end();
		forward_iterator get_iterator(uint num);

		void insert(uint index, const T& value);
		void erase(const forward_iterator& it);

		std::shared_ptr<typename list<T>::list_node> operator[](uint num);

	private:
		struct list_node {
			T value;
			std::weak_ptr<list_node> prev ;
			std::shared_ptr<list_node> next;
			forward_iterator first_element();
			forward_iterator nextit();
		};
		std::shared_ptr<list_node> root_ = nullptr;
	};

	template<class T>
	std::shared_ptr<typename list<T>::list_node> list<T>::operator[](uint num) { // доступ к элементу списка через []
		return *(this.get_iterator(num));
	};

	template<class T>
	typename list<T>::forward_iterator list<T>::get_iterator(uint num) {
		if (root_ == nullptr && num != 0) {
			throw std::logic_error("в пустом списке сначала заполняется 0й элемент");
		}
		forward_iterator ptr = begin();

		for (uint i = 0; i < num; i++, ptr++) {
			if (ptr == NULL) {
				throw std::logic_error("попытка вставки/удаления недопустимой позиции");
			}
		}
		return ptr;
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::begin() {
		return root_->first_element();
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::end() {
		return nullptr;
	}

	template<class T>
	void list<T>::insert(uint index, const T& value) {
		if (index<0) {
			throw std::logic_error("попытка доступа к несуществующему элементу");
		}
		list<T>::forward_iterator it = get_iterator(index);

		if (root_ != nullptr) {
			if (it == NULL) { // вставка в позицию end()+1
				index--;
				it = get_iterator(index);
				std::shared_ptr<list_node> ptr = std::shared_ptr<list_node>(new list_node{ value });
				ptr->prev = it.ptr_->prev;
				ptr->next = nullptr;
				it.ptr_->next = ptr;
				return;
			}
			if (it.ptr_->prev.lock() == nullptr) {// вставка в позицию begin() непустого списка
				std::shared_ptr<list_node> ptr = std::shared_ptr<list_node>(new list_node{ value });
				ptr->prev = root_->prev;
				ptr->next = root_;
				ptr->next->prev = ptr;
				root_ = ptr;
				return;
			}
			else {
				std::shared_ptr<list_node> ptr = std::shared_ptr<list_node>(new list_node{ value });
				ptr->prev = it.ptr_->prev;
				ptr->next = it.ptr_->prev.lock()->next;
				it.ptr_->prev = ptr;
				ptr->prev.lock()->next = ptr;
				return;
			}
		}
		// вставка в позицию 0 пустого списка
		root_ = std::shared_ptr<list_node>(new list_node{ value });
	}

	template<class T>
	void list<T>::erase(const typename list<T>::forward_iterator& it) {
		if (it.ptr_ == nullptr) {
			throw std::logic_error("попытка доступа к несуществующему элементу");
		}
		if (it.ptr_->prev.lock() == nullptr) {
			if (it.ptr_->next) {
				it.ptr_->next->prev.lock() = nullptr;
				root_ = it.ptr_->next;
			}
			else {
				root_->next = nullptr;
				root_->prev.lock() = nullptr;
				root_ = nullptr;
			}
		}
		else if (it.ptr_->next == nullptr) {
			it.ptr_->prev.lock()->next = nullptr;
		}
		else {
			it.ptr_->prev.lock()->next = it.ptr_->next;
			it.ptr_->next->prev = it.ptr_->prev;
		}
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::list_node::first_element() {
		return this;
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::list_node::nextit() {
		if (next) {
			return next.get();
		}
		return NULL;
	}

	template<class T>
	list<T>::forward_iterator::forward_iterator(list_node* ptr) : ptr_{ ptr } {}

	template<class T>
	T& list<T>::forward_iterator::operator*() {
		return ptr_->value;
	}

	template<class T>
	typename list<T>::forward_iterator& list<T>::forward_iterator::operator++() {
		*this = ptr_->nextit();
		return *this;
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::forward_iterator::operator++(int) {
		forward_iterator old = *this;
		++*this;
		return old;
	}

	template<class T>
	bool list<T>::forward_iterator::operator== (const forward_iterator& o) const {
		return ptr_ == o.ptr_;
	}

	template<class T>
	bool list<T>::forward_iterator::operator!= (const forward_iterator& o) const {
		return ptr_ != o.ptr_;
	}

	template<class T>
	typename list<T>::forward_iterator list<T>::forward_iterator::operator[](uint num) {
		forward_iterator ptr = begin();
		for (uint i = 0; i < num; i++, num++);
		return ptr;
	}
}
#endif // D_CONTAINERS_list_H_
