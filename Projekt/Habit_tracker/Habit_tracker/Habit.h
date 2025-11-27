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
	time_t last_done;
	int current_streak;

public:
	Habit(std::string Name,Type type,Difficulty diffculty, Frequency frequency) : // ustawic last_done jako obecny dzien 
		name(Name), type(type), difficulty(diffculty), frequency(frequency), last_done(0), current_streak(0) {}

	~Habit() {}

	void check_streak();

	void print_last_done() const;

	void set_name(std::string habit_name);

	void set_type(Type habit_type);

	void set_difficulty(Difficulty difficulty);

	void set_frequency(Frequency frequency);

	void set_last_done(time_t time);

	void set_custom_streak(int streak);

	void increase_streak();

	const std::string get_name() const;
	
	const Type get_type() const;

	const Difficulty get_difficulty() const;

	const Frequency get_frequency() const;

	const time_t get_last_done() const;

	const int get_current_streak() const;

	std::string to_save() const;
};

const time_t today_();