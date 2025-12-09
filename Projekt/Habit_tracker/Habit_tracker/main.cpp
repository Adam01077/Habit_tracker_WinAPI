#include <iostream>
#include <vector>
#include "Habit.h"
#include "Date.h"
#include "Logic.h"

int main() {
	std::vector<Habit> habits;
	Habit new_habit("Programowanie w c++",Habit::Type::good,Habit::Difficulty::easy,Habit::Frequency::daily);
	new_habit.set_last_done(today_());
	if (not Logic::make_save(new_habit)) {
		std::cout << "Something went wrong" << std::endl;
	}
	return 0;
}