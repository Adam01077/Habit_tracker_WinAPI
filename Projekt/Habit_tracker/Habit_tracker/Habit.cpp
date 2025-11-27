#include <iostream>
#include "Habit.h"
#include "Date.h"
#include <chrono>
#include <ctime>
#include <string>

const time_t today_() {
	time_t now;
	now = time(nullptr);
	struct tm time_now {};
	localtime_s(&time_now, &now);
	time_now.tm_hour = 0;
	time_now.tm_min = 0;
	time_now.tm_sec = 0;
	time_now.tm_isdst = -1;
	now = mktime(&time_now);
	return now;
}

void Habit::check_streak() {
	auto time_now = today_();	
	int difference = difftime(time_now, last_done) / 86400;
	switch (frequency) {
	case Frequency::daily:
		if (difference > 1) {
			current_streak = 0;
		}
		break;
	case Frequency::weekly:
		if (difference > 7) {
			current_streak = 0;
		}
		break;
	case Frequency::monthly: 
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

void Habit::print_last_done() const {
	struct tm last_done_tm {};
	localtime_s(&last_done_tm, &last_done);
	int day, month, year;
	day = last_done_tm.tm_mday;
	month = last_done_tm.tm_mon + 1;
	year = last_done_tm.tm_year + 1900;
	std::cout << day << "." << month << "." << year << std::endl;
}

void Habit::set_last_done(time_t time) {
	last_done = time;
}

void Habit::set_name(std::string habit_name) {
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

const std::string Habit::get_name() const {
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

std::string Habit::to_save() const {
	std::string info;
	std::string type_string;
	std::string diff_string;
	std::string freq_string;
	switch (type) {
	case Type::good:
		type_string = "G";
		break;
	case Type::bad:
		type_string = "B";
		break;
	}
	switch (difficulty) {
	case Difficulty::common:
		diff_string = "C";
		break;
	case Difficulty::easy:
		diff_string = "E";
			break;
	case Difficulty::meduim:
		diff_string = "M";
		break;
	case Difficulty::hard:
		diff_string = "H";
		break;
	}
	switch (frequency) {
	case Frequency::daily:
		freq_string = "D";
		break;
	case Frequency::weekly:
		freq_string = "W";
		break;
	case Frequency::monthly:
		freq_string = "M";
	}
	info = get_name() +";" + type_string + ";" + diff_string + ";" + freq_string+ ";" + std::to_string(last_done) + ";" + std::to_string(current_streak);
	return info;
}