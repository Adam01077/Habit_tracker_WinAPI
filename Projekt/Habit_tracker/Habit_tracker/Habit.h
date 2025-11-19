#pragma once
#include "Date.h"

class Habit {
public:
	enum class Type { good, bad };
	enum class Difficulty { hard, meduim, easy, common };
	enum class Frequency { daily, weekly, monthly };
private:
	std::string name;
	Type type;
	Difficulty difficulty; // how hard is it to stop/start 
	Frequency frequency; // how often do you have to do habit
	Date last_done;
	int current_streak;

public:
	Habit(std::string Name,Type type,Difficulty diffculty, Frequency frequency) : // ustawic last_done jako obecny dzien 
		name(Name), type(type), difficulty(diffculty),frequency(frequency), current_streak(0) {}

	~Habit() {}


	void check_streak();

};