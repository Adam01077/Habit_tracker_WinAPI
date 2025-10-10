#include<iostream>
#include"Queue.h"
#include"Wyjatek.h"
int main() {
	try {
		
		//auto kolejka = Queue<int>(0);
		auto kolejka = Queue<int>(5);
		kolejka.enqueue(3);
		kolejka.enqueue(2);
		kolejka.enqueue(5);
		kolejka.enqueue(6);
		kolejka.enqueue(0);
		kolejka.dequeue();
		kolejka.enqueue(13);

		kolejka.print();
		std::cout<< kolejka.agregate();
		}
	catch (const std::exception &e){
		std::cout << "Warning - " << e.what() << std::endl;
	}
	return 0;
}

