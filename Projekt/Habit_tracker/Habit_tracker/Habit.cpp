#include <iostream>
#include "Habit.h"
#include <chrono>
#include <ctime>
#include <string>
#include "Logic.h"


void Habit::check_streak() {
	if (last_done == 0) return; // nigdy nie wykonano

	auto time_now = Logic::today_();	
	int difference = difftime(time_now, last_done) / 86400;
	switch (frequency) {
	case Frequency::daily:
	{
		if (difference > 1) {
			current_streak = 0;
		}
		break;
	}
	case Frequency::weekly:
	{
		if (difference > 7) {
			current_streak = 0;
		}
		break;
	}
	case Frequency::monthly:
	{
		struct tm last_done_tm {};
		localtime_s(&last_done_tm, &last_done);
		struct tm time_now_tm {};
		localtime_s(&time_now_tm, &time_now);
		int diff = (time_now_tm.tm_year - last_done_tm.tm_year) * 12 + (time_now_tm.tm_mon - last_done_tm.tm_mon);
		if (diff > 1) {
			current_streak = 0;
		}
		break;
	}
	}
}

std::wstring Habit::print_last_done() const {
	struct tm last_done_tm {};
	localtime_s(&last_done_tm, &last_done);
	int day, month, year;
	day = last_done_tm.tm_mday;
	month = last_done_tm.tm_mon + 1;
	year = last_done_tm.tm_year + 1900;
	return std::to_wstring(day) +  L"." + std::to_wstring(month) + L"." + std::to_wstring(year);
}

void Habit::set_last_done(time_t time) {
	last_done = time;
}

void Habit::set_name(std::wstring habit_name) {
	name = habit_name;
}

void Habit::set_type(Type habit_type) {
	type = habit_type;
}

void Habit::set_difficulty(Difficulty difficulty_) {
	difficulty = difficulty_;
}

void Habit::set_frequency(Frequency frequency_) {
	frequency = frequency_;
}

void Habit::set_custom_streak(int streak) {
	current_streak = streak;
}

void Habit::increase_streak() {
	current_streak += 1;
}

const std::wstring Habit::get_name() const {
	return name;
}

const Habit::Type Habit::get_type() const {
	return type;
}

const Habit::Difficulty Habit::get_difficulty() const {
	return difficulty;
}

const Habit::Frequency Habit::get_frequency() const {
	return frequency;
}

const time_t Habit::get_last_done() const {
	return last_done;
}

const int Habit::get_current_streak() const {
	return current_streak;
}

std::wstring Habit::to_save() const {
	std::wstring info;
	std::wstring type_string;
	std::wstring diff_string;
	std::wstring freq_string;
	switch (type) {
	case Type::good:
		type_string = L"G";
		break;
	case Type::bad:
		type_string = L"B";
		break;
	}
	switch (difficulty) {
	case Difficulty::common:
		diff_string = L"C";
		break;
	case Difficulty::easy:
		diff_string = L"E";
			break;
	case Difficulty::meduim:
		diff_string = L"M";
		break;
	case Difficulty::hard:
		diff_string = L"H";
		break;
	}
	switch (frequency) {
	case Frequency::daily:
		freq_string = L"D";
		break;
	case Frequency::weekly:
		freq_string = L"W";
		break;
	case Frequency::monthly:
		freq_string = L"M";
	}
	info = get_name() +L";" + type_string + L";" + diff_string + L";" + freq_string+ L";" + std::to_wstring(last_done) + L";" + std::to_wstring(current_streak);
	return info;
}

Habit Habit::from_file(const std::wstring& data) {
	std::wstringstream ss(data);
	std::wstring name, type_str, diff_str, freq_str, last_done_str, streak_str;
	std::getline(ss, name, L';');
	set_name(name);
	std::getline(ss, type_str, L';');
	if (type_str == L"G") {
		set_type(Type::good);
	}
	else if (type_str == L"B") {
		set_type(Type::bad);
	}
	std::getline(ss, diff_str, L';');
	if (diff_str == L"C") {
		set_difficulty(Difficulty::common);
	}
	else if (diff_str == L"E") {
		set_difficulty(Difficulty::easy);
	}
	else if (diff_str == L"M") {
		set_difficulty(Difficulty::meduim);
	}
	else if (diff_str == L"H") {
		set_difficulty(Difficulty::hard);
	}
	std::getline(ss, freq_str, L';');
	if (freq_str == L"D") {
		set_frequency(Frequency::daily);
	}
	else if (freq_str == L"W") {
		set_frequency(Frequency::weekly);
	}
	else if (freq_str == L"M") {
		set_frequency(Frequency::monthly);
	}
	std::getline(ss, last_done_str, L';');
	set_last_done(static_cast<time_t>(std::stoll(last_done_str)));
	std::getline(ss, streak_str, L';');
	set_custom_streak(std::stoi(streak_str));
	return *this;
}

void Habit::clear_habit() {
	name = L"";
	type = Habit::Type::unknown;
	difficulty = Difficulty::unknown;
	frequency = Frequency::unknown;
	last_done = 0;
	current_streak = 0;
}

std::wstring Habit::to_print() const {
	return name + L" (" + std::to_wstring(current_streak) + L")";
}

std::wstring Habit::type_to_string() const {
	std::wstring result;
	switch (type) {
	case Habit::Type::good:
		result = L"Good";
		break;
	case Habit::Type::bad:
		result = L"Bad";
		break;
	}
	return result;
}

std::wstring Habit::freq_to_string() const {
	std::wstring result;
	switch (frequency) {
	case Habit::Frequency::daily:
		result = L"Daily";
		break;
	case Habit::Frequency::monthly:
		result = L"Monthly";
		break;
	case Habit::Frequency::weekly:
		result = L"Weekly";
		break;
	}
	return result;
}

std::wstring Habit::diff_to_string() const {
	std::wstring result;
	switch (difficulty) {
	case Habit::Difficulty::easy:
		result = L"Easy";
		break;
	case Habit::Difficulty::meduim:
		result = L"Medium";
		break;
	case Habit::Difficulty::common:
		result = L"Common";
		break;
	case Habit::Difficulty::hard:
		result = L"Hard";
		break;
	}
	return result;
}

bool Habit::is_done_in_peroid() const {
	if (last_done == 0) return false;  

	time_t today = Logic::today_();

	switch (frequency) {
	case Frequency::daily:
	{

		return last_done >= today;
	}

	case Frequency::weekly:
	{

		struct tm today_tm {};
		localtime_s(&today_tm, &today);
		int days_since_monday = (today_tm.tm_wday + 6) % 7;
		time_t week_start = today - (days_since_monday * 86400);

		return last_done >= week_start;
	}

	case Frequency::monthly:
	{
		struct tm last_tm {}, today_tm{};
		localtime_s(&last_tm, &last_done);
		localtime_s(&today_tm, &today);

		return (last_tm.tm_year == today_tm.tm_year &&
			last_tm.tm_mon == today_tm.tm_mon);
	}
	}
	return false;
}