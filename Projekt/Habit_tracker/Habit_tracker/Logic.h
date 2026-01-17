#pragma once
#include "Habit.h"
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

enum View {
	Welcome, // ekran poczatkowy
	New_profile, // dodawanie nowego profilu
	Load_profile, // wczytywanie profilu
	Main_menu, // po wczytaniu profilu 
	Add_habit, // dodawanie nawyku
};

enum MENU_ID {
	bNewProfile = 101, // Przycisk nowy profil
	bLoadProfile, // zaladowanie profilu
	insInfo, // wpisywanie informacji 
	bSave, // zapisanie wpisu noweg profilu
	bCancel, // cofniêcie wpisu nowego profilu
	bSavePrgress, // zapisanie postepów w menu
	bChangeProfile, // zmiana profilu w menu
	bNewHabit, // dodanie nawyku w menu
	bMoreInfo, // wiêcej informacji o nawyku w menu
	optGood,
	optBad,
	optHard,
	optMedium,
	optEasy,
	optCommon,
	optDaily,
	optWeekly,
	optMonthly,
	bCreateHabit, // tworzenie nawyku po wpisaniu informacji
	textStatic,
	bCancel2,
};


namespace Logic {
	inline int HabitControlsCount;
	constexpr int Profile_ID = 1000;
	constexpr int Habit_info_ID = 3000;
	constexpr int Habit_done_box_ID = 5000;
	constexpr int Habit_more_info_ID = 7000;

	extern std::wstring Profile_name;
	extern View Current_view;
	extern std::vector<std::wstring> Files_names;
	extern std::vector<Habit> Habits;
	extern Habit new_habit;

	const time_t today_();
	void CreateHabitControls(HWND hWnd, int i);
	void DestroyHabitControls(HWND hWnd);
	void RebuildHabitUI(HWND hWnd);
}