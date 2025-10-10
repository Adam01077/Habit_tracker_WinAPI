#pragma once
#include "Wyjatek.h"
#include<type_traits>

template <class T>
class Queue {
private:
	T* queue; // kolejka 
	int front; //indekst pierwszego elementu
	int rear; // indeks ostatniego elementu
	int count; // ilosc elementów w kolejce
	size_t capacity; // polejmosc kolejki

public:

	Queue(size_t capacity_) : front(0), rear(0), count(0), capacity(capacity_) { 
		if (capacity_ == 0) { 
			throw Capacity_warning(); 
		} 
		queue = new T[capacity]; 
	}

	~Queue() { delete[] queue; }


	void print() {
		std::cout << "[";
		for (int i = 0; i < count ; i++) {
			int index = (front + i) % capacity;
			std::cout << queue[index];
			if (i < count - 1) {
				std::cout << ",";
			}
		}
		std::cout<<"]" << std::endl;
	}
	// metoda mowiaca czy kolejka jest pusta
	bool isEmpty() const {
		if (count == 0) {
			return true;
		}
		return false;
	}

	// metoda mowiaca czy kolejka jest pelna
	bool isFull() const {
		if (count == capacity) {
			return true;
		}
		return false;
	}

	// metoda dodajaca element na koniec kolejki
	void enqueue(const T& element){
		if (isFull()) {
			throw Queue_full();
		}
		queue[rear]  = element;
		rear = (rear + 1) % capacity;
		count++;
	}

	// metoda usuwajaca pierwszy element kolejki
	T dequeue() {
		if (isEmpty()) {
			throw Queue_empty();
		}
		count--;
		T item = queue[front];
		front = (front + 1) % capacity;
		return item;
	}
	
	// metoda agregujaca elementy kolejki
	T agregate() {
		T result{};
		if (std::is_arithmetic_v<T>) {
			T result{};
			for (int i = 0; i < count; ++i) {
				int index = (front + i) % capacity;
				result += queue[index];
			}
			return result;
		}
		/* nie dziala
		else if (std::is_same_v<T, std::string>) {
			std::string result;
			for (int i = 0; i < count; ++i) {
				int index = (front + i) % capacity;
				result += queue[index];
				if (i < count - 1) {
					result += " ";
				}
			}
			return result; 
		}
		*/
		else { throw Wrong_type(); }
	}
};