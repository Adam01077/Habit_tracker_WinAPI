#include <iostream>
#include <fstream>
#include "FileArray.h"
#include <string>

int main() {
	const std::string testFile = "data.bin";

	try {
		std::cout << " Test FileArray<int>\n\n";

		FileArray<int> fa("data.bin");
		std::cout << "Utworzono:  " << fa.filename() << "\n";

		fa.push_back(10);
		fa.push_back(20);
		fa.push_back(30);
		fa.append(40);
		fa.append(50);
		std::cout << "Dopisano: 10, 20, 30, 40, 50\n";

		std::cout << "\nsize() = " << fa.size() << "\n";

		std::cout << "\nOdczyt:\n";
		std::cout << "  at(0)       = " << fa.at(0) << "\n";
		std::cout << "  at(2)       = " << fa.at(2) << "\n";
		std::cout << "  operator[1] = " << fa[1] << "\n";
		std::cout << "  operator[4] = " << fa[4] << "\n";

		std::cout << "\nWszystkie:  ";
		for (size_t i = 0; i < fa.size(); ++i) {
			std::cout << fa[i] << " ";
		}
		std::cout << "\n";

		std::cout << "\nTest move\n";
		FileArray<int> fa2 = std::move(fa);
		std::cout << "Po move:  fa2.size() = " << fa2.size() << "\n";

		std::cout << "\nTest wyj¹tku\n";
		try {
			std::cout << "Proba:  fa2.at(100)...\n";
			fa2.at(100);  
		}
		catch (const std::out_of_range& e) {
			std::cout << "Zlapano blad\n  " << e.what() << "\n";
		}

		std::cout << "\nKoniec\n";

	}
	catch (const std::exception& e) {
		std::cerr << "Blad krytyczny: " << e.what() << "\n";
		return 1;
	}

	std::remove(testFile.c_str());
	return 0;
}