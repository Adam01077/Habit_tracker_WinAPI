#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
// Autor: Adam S³odownik 
// sekcja 1 Œroda 12:00
// github: Adam01077


int main() {
	// otwieranie pliku
	std::ifstream plik("events.txt");

	// sprawdzanie czy siê tworzy³
	if (!plik) {
		std::cout << "Nie mozna otworzyc pliku" << std::endl;
		return 1;
	}

	// wczytywanie linii do wektora
	auto start = std::istream_iterator<std::string>(plik);
	auto end = std::istream_iterator<std::string>();
	std::vector<std::string> lines(start, end);
	/*
	for (const auto &line : lines) {
		std::cout << line << std::endl;
	}
	*/

	
	
	std::vector<std::string> errors;
	// filtrowanie linii zawieraj¹cych "ERROR" i dodanie ich do wektora errors
	// back_inserter dzia³a jak push_back
	std::copy_if(lines.begin(), lines.end(), std::back_inserter(errors), [](const auto& line) {
		return line.find("ERROR") != std::string::nppos;
		});
	// npos mowi czy nie znaleziono ciagu znakow, i zwraca wartosc maksymalna dla size_t jak znaleziono to zwraca indeks pierwszego wystapienia
	// zaprzeczenie w warunku oznacza ze szukam wystepujacych
	/*
	for (const auto& line : errors) {
		std::cout << line << std::endl;
	}
	  */
	// kopiowanie 5 ostatnich bledow z wektora bledow 
	std::vector<std::string> last_5_errors;
	std::copy_n(errors.rbegin(), 5, std::back_inserter(last_5_errors));

	for (const auto& line : last_5_errors) {
		std::cout << line << std::endl;
	}
	return 0;
}