#include <iostream>
#include "Habit.h"
#include "Date.h"
#include <chrono>
#include <ctime>
void Habit::check_streak() {
	time_t now;
	now = time(NULL);
	struct tm time_now {};
	localtime_s(&time_now,&now);
	time_now.tm_hour = 0;
	time_now.tm_min = 0;
	time_now.tm_sec = 0;
	time_now.tm_isdst = -1;
	now = mktime(&time_now);

	struct tm last_date {};
	last_date.tm_year = last_done.year - 1900;
	last_date.tm_mon = last_done.month - 1;
	last_date.tm_mday = last_done.day;
	last_date.tm_hour = 0;
	last_date.tm_min = 0;
	last_date.tm_sec = 0;
	last_date.tm_isdst = -1;
	time_t ld = mktime(&last_date);
	int difference = difftime(now,ld)/86400;

	if (difference > 1) {
		current_streak = 0;
	}
}