#pragma once
#include <string>

class Habit {
public:
	enum class Type { good, bad };
	enum class Difficulty { hard, meduim, easy, common };
	enum class Frequency { daily, weekly, monthly };
private:
	std::wstring name;	
	Type type;
	Difficulty difficulty; // how hard is it to stop/start 
	Frequency frequency; // how often do you have to do habit
	time_t last_done;
	int current_streak;

public:
	Habit() : name(L"-"), type(Type::good), difficulty(Difficulty::common), frequency(Frequency::daily), last_done(0), current_streak(0) {}
	Habit(std::wstring Name,Type type,Difficulty diffculty, Frequency frequency) : // ustawic last_done jako obecny dzien 
		name(Name), type(type), difficulty(diffculty), frequency(frequency), last_done(0), current_streak(0) {}

	~Habit() {}

	void check_streak();

	void print_last_done() const;

	void set_name(std::wstring habit_name);

	void set_type(Type habit_type);

	void set_difficulty(Difficulty difficulty);

	void set_frequency(Frequency frequency);

	void set_last_done(time_t time);

	void set_custom_streak(int streak);

	void increase_streak();

	const std::wstring get_name() const;
	
	const Type get_type() const;

	const Difficulty get_difficulty() const;

	const Frequency get_frequency() const;

	const time_t get_last_done() const;

	const int get_current_streak() const;

	std::wstring to_save() const;

	Habit from_file(const std::wstring& data);
};