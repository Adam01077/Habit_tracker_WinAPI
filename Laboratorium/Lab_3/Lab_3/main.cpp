#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>

// Autor: Adam S³odownik 
// sekcja 1 Œroda 12:00
// github: Adam01077

/*
struct Linia {
	std::string wartosc;
	friend std::istream& operator>>(std::istream& is, Linia& l) {
		std::getline(is, l.wartosc);
		return is;
	}
};
*/

int main() {
	
	std::ifstream plik("events.txt");

	if (!plik) {
		std::cout << "Nie mozna otworzyc pliku" << std::endl;
		return 1;
	}


	std::vector<std::string> lines(std::istream_iterator<std::string>(plik), std::istream_iterator<std::string>());

	
	
	std::vector<std::string> errors;
	//auto it = std::copy_if(lines.begin(), lines.end(), errors.begin(), [](const ) {});

	return 0;
}