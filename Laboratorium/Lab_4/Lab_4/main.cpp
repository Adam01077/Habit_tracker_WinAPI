#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include<algorithm>
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
	std::vector<Order> orders; //latwy odstep do danych, operacja dodawania ma stala zlozonosc 
	orders.reserve(100); // zapobiega wielokrotnemu realokowaniu pamieci
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
		orders.push_back(std::move(order));

	}
	/*
	for (const auto &order : orders) {
		std::cout << order.ID << " " << order.SKU << " " << order.quantity << std::endl;
	}
	*/
	// Zadanie 2
	// Bedziemy agregowac, a unordered_map ma stala zlozonosc dsotepu
	std::unordered_map<std::string, long long> u_map;
	u_map.reserve(orders.size() * 2 + 1); // rezerwujemy trochê wiêcej ni¿ liczba wpisów by zmniejszyæ kolizje
	u_map.max_load_factor(0.7f); // mniejszy load factor daje nam mniej kolizji kosztem pamieci 
	for (const auto& order : orders) {
		u_map[order.ID] += order.quantity;
	}

	//for (const auto& pair : u_map) {
	//	std::cout << pair.first << " " << pair.second << std::endl; // wypisane 0 jest poniewaz wektor jest wiekszy niz ilosc danych 
	//}
	// Zadanie 3
	// unordered_set bo chcemy tylko unikalnych klientów, nie liczy siê ich kolejnosc
	std::unordered_set<std::string> unique_orders;
	for (const auto& order : orders) {
		unique_orders.insert(order.ID);
	}
	/*
	for (const auto& order : unique_orders) {
		std::cout << order << std::endl;
	}
	*/
	// Zadanie 4

	std::queue<Order, std::deque<Order>> order_queue;
	order_queue.push(orders[0]);
	order_queue.push(orders[6]);
	order_queue.push(orders[35]);
	order_queue.push(orders[9]);
	order_queue.pop();
	Order o = order_queue.front();
	std::cout << o.ID << std::endl;


	// Zadanie 5
	std::cout << "----- RAPORT -----" << std::endl;
	std::cout << "Laczna liczba zamowien: " << orders.size() << std::endl;
	std::cout << "Liczba unikalnych klientow: " << unique_orders.size() << std::endl;
	std::vector<std::pair<std::string, int>> sku_list;
	sku_list.reserve(u_map.size());
	for (auto& p : u_map) sku_list.emplace_back(p.first, p.second);
	std::sort(sku_list.begin(), sku_list.end(),
		[](const auto& a, const auto& b) { return a.second > b.second; });

	std::cout << "TOP-3 SKU:" << std::endl;
	size_t to_show = std::min<size_t>(3, sku_list.size());
	for (size_t i = 0; i < to_show; ++i) {
		std::cout << i + 1 << ". " << sku_list[i].first << " -> " << sku_list[i].second << std::endl;
	}
	if (to_show == 0) {
		std::cout << "(brak danych SKU)" << std::endl;
	}
	return 0;
}