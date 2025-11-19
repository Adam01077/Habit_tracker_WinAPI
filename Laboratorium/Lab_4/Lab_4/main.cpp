#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
struct Order {
	std::string ID;
	std::string SKU;
	int quantity;
};

int main() {
	
	std::ifstream plik("Orders.txt");
	if (!plik) {
		std::cerr << "Nie udalo sie otworzyc danych" << std::endl;
		return 1;
	}

	// Zadanie 1
	std::string line;
	std::vector<Order> orders;
	orders.resize(100);
	int index = 0; // index pustego miejsca w wektorze
	while (std::getline(plik, line)) {

		std::stringstream ss(line);
		std::string id, sku, qtyStr;
		Order order;

		std::getline(ss, id, ',');
		std::getline(ss, sku, ',');
		std::getline(ss, qtyStr, ',');

		order.ID = id;
		order.SKU = sku;
		order.quantity = std::stoi(qtyStr);

		orders[index] = order;
		index=index+1;
	}
	/*
	for (const auto &order : orders) {
		std::cout << order.ID << " " << order.SKU << " " << order.quantity << std::endl;
	}
	*/
	// Zadanie 2
	std::unordered_map<std::string, long long> u_map;
	for (const auto& order : orders) {
		u_map[order.ID] += order.quantity;
	}

	//for (const auto& pair : u_map) {
	//	std::cout << pair.first << " " << pair.second << std::endl; // wypisane 0 jest poniewaz wektor jest wiekszy niz ilosc danych 
	//}
	// Zadanie 3
	std::unordered_set<std::string> unique_orders;
	for (const auto& order : orders) {
		unique_orders.insert(order.ID);
	}
	for (const auto& order : unique_orders) {
		std::cout << order << std::endl;
	}
	std::queue<Order, std::deque<Order>> order_queue;
	order_queue.push(orders[0]);
	order_queue.push(orders[6]);
	order_queue.push(orders[35]);
	order_queue.push(orders[9]);
	order_queue.pop();
	Order o = order_queue.front();
	std::cout << o.ID << std::endl;


	// Zadanie 4
	return 0;
}