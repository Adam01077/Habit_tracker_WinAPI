#pragma once
#include <string>

class Habit {
public:
	enum class Type { good, bad, unknown };
	enum class Difficulty { hard, medium, easy, common,unknown };
	enum class Frequency { daily, weekly, monthly, unknown };
private:
	std::wstring name;	
	Type type;
	Difficulty difficulty; 
	Frequency frequency; 
	time_t last_done;
	int current_streak;
	int best_streak = 0;

public:
	Habit() : name(L"-"), type(Type::unknown), difficulty(Difficulty::unknown), frequency(Frequency::unknown), last_done(0), current_streak(0) {}
	Habit(std::wstring Name,Type type,Difficulty diffculty, Frequency frequency) :
		name(Name), type(type), difficulty(diffculty), frequency(frequency), last_done(0), current_streak(0) {}

	~Habit() {}

	void check_streak();

	std::wstring print_last_done() const;

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

	void clear_habit();

	std::wstring to_print() const;

	std::wstring type_to_string() const;

	std::wstring freq_to_string() const;

	std::wstring diff_to_string() const;

	bool is_done_in_period() const;

	int get_best_streak() const;

	void update_best_streak();
};