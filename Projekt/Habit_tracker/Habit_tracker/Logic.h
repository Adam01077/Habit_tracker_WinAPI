#pragma once
#include "Habit.h"
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

enum View {
	Welcome, // nie ma profilu do wczytania
	Load_profile, // wczytywanie profilu
	Main_menu, // po wczytaniu profilu 
	Add_habit, // dodawanie nawyku
};
namespace Logic {
	constexpr int Profile_ID = 1000;
	constexpr int Habit_done_ID = 5000;

	extern std::wstring Profile_name;
	extern View Current_view;
	extern std::vector<std::wstring> Files_names;
	extern std::vector<Habit> Habits;

	const time_t today_();
}