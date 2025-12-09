#pragma once
#include "Habit.h"
#include <fstream>
#include <string>
namespace Logic {

	bool make_save(Habit habit) {
		std::ofstream save("save.txt"); // to bedzie fstream
		if (not save) {
			std::cerr << "Save problem" << std::endl;
			return false;
		}
		save << habit.to_save();
		save.close();
		std::cout << "Progress saved" << std::endl;
		return true;
	}

	// bool load_save();
}

namespace narrator {
	void first_time_welcome() {
		std::cout << "Hello player!" << std::endl;
		std::cout << "Welcome to the Habit Tracker!" << std::endl;
	}
}