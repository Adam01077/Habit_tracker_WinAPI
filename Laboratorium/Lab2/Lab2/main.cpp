#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

// Autor: Adam S³odownik

struct Order {
	int id;
	std::string customer;
	double amount; // kwota netto
	bool paid; // op³acone?
	bool refunded; // zwrócone?

	void print() const {
		//std::cout << id << std::setw(6) << customer << std::setw(6) << amount << std::setw(6) << paid << std::setw(6) << refunded << std::endl;
	}
};


int main() {
	std::vector<Order> orders = {
	{101, "ACME", 199.00, true, false},
	{102, "Globex", 499.99, false, false},
	{103, "Initech", 149.50, true, true},
	{104, "Umbrella", 0.00, true, false},
	{105, "ACME", 79.99, true, false},
	{106, "Globex", 499.99, true, false}, // duplikat kwoty/klienta
	{107, "Vandelay", 899.00, true, false},
	};

	// Zadanie 1
	std::cout << "Wszystkie zamowienia: " << orders.size() << std::endl;
	
	auto paid = std::count_if(orders.begin(), orders.end(), [](const Order& order) {return order.paid; });
	std::cout << "\nOplacone zamowienia: " << paid << std::endl;

	auto not_paid = std::count_if(orders.begin(), orders.end(), [](const Order& order) {return not order.paid; });
	std::cout << "Nieoplacone zamowienia: " << not_paid << std::endl;
	
	auto refunded = std::count_if(orders.begin(), orders.end(), [](const Order& order) {return order.refunded; });
	std::cout << "Zwrocone zamowienia: " << refunded << std::endl;

	// Zadanie 2
	auto income = std::accumulate(orders.begin(), orders.end(), 0.0, [](double sum,const Order& order) {return sum+(order.paid && not order.refunded ? order.amount : 0.0); });
	std::cout << "\nPrzychod netto z zamowien: " << income<< std::endl;

	// Zadanie 3
	std::cout << "\nObecne zamowienia:";
	std::sort(orders.begin(), orders.end(), 
		[](const Order& order1, const Order& order2) 
		{
			if (order1.amount == order2.amount) 
			{ return order1.customer < order2.customer; }
			return order1.amount > order2.amount; 
		}
	);
	std::cout << "\n";
	std::cout << "ID	Customer	Amount	Paid	Refunded\n" << std::endl;
	for (const auto& order : orders) {
		order.print();
	}

	// Zadanie 4
	std::cout << "\nZamowienia pozostale: " << std::endl;
	auto it = std::remove_if(orders.begin(), orders.end(), [](const Order& order) {return order.amount <= 0 || order.refunded; });
	orders.erase(it, orders.end());
	
	std::cout << "ID	Customer	Amount	Paid	Refunded\n" << std::endl;
	for (const auto& order : orders) {
		order.print();
	}

	// Zadanie 5
	std::cout << "\n";
	std::cout << "Pozostale zamowienia (kwota brutto)"<<std::endl;
	std::cout << "ID	Customer	Amount	Paid	Refunded\n" << std::endl;
	std::vector<Order> orders_brutto(orders.size());
	std::transform(orders.begin(), orders.end(), orders_brutto.begin(), [](Order& order)->Order {order.amount *= 1.23; return order; });

	for (const auto& order : orders_brutto) {
		order.print();
	}

	return 0;
};