#include "WndProc.h"
#include "Logic.h"
#include "Files.h"
#include "Fonts.h"
#include "Layouts.h"
#include "Statistics.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // wParam ma du¿o informacji górna czêœæ to kod powiadomienia dolna to ID kontorlki 
	switch (uMsg) {
	case WM_CREATE:
	{
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create new profile"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bNewProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Load profile"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bLoadProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Change Profile"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bChangeProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, (HMENU)insInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("SAVE"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bSave, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("CANCEL"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCancel, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("CANCEL"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCancel2, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Add new habit"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bNewHabit, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("..."), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bMoreInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Good"), WS_GROUP | WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optGood, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Bad"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optBad, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Hard"), WS_GROUP | WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optHard, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Medium"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optMedium, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Easy"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optEasy, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Common"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optCommon, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Daily"), WS_GROUP | WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optDaily, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Weekly"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optWeekly, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Monthly"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optMonthly, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create habit"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCreateHabit, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Stats"),WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd,(HMENU)bStats, GetModuleHandle(NULL), NULL);
		for (int i = 0; i < Logic::Files_names.size(); i++) {
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[i].c_str(), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)(Logic::Profile_ID + i), GetModuleHandle(NULL), NULL);
		}
		Logic::UpdateUI(hWnd);
		return 0;
	}
	case WM_COMMAND:
	{
		int button_ID = LOWORD(wParam);
		if (HIWORD(wParam) != BN_CLICKED) return 0;

		auto it = radioHandlers.find(button_ID);
		if (it != radioHandlers.end()) {
			it->second();
			Logic::UpdateUI(hWnd);
			return 0;
		}

		switch (button_ID) {
		case bNewProfile:
		{
			Logic::Current_view = View::New_profile;
			Logic::UpdateUI(hWnd);
		}
		break;
		case bLoadProfile:
		{
			Logic::Current_view = View::Load_profile;
			Logic::UpdateUI(hWnd);
		}
		break;
		case bChangeProfile:
		{
			if (!Logic::Profile_name.empty()) {
				Files::save_progress(Logic::Profile_name);
			}
			Logic::DestroyHabitControls(hWnd);
			Logic::Habits.clear();
			Logic::Profile_name.clear();
			Logic::Current_view = View::Welcome;
			Logic::UpdateUI(hWnd);
		}
		break;
		case bSave:
		{
			std::wstring name = Logic::GetWindowTextString(hWnd, insInfo);
			if (name.empty()) {
				MessageBox(hWnd, TEXT("Enter profile name! "), TEXT("Error"), MB_OK | MB_ICONWARNING);
				break;
			}
			if (Files::profile_exists(name)) {
				MessageBox(hWnd, TEXT("Profile already exists!"), TEXT("Error"), MB_OK | MB_ICONWARNING);
				break;
			}
			Logic::Profile_name = name;
			Logic::Files_names.push_back(Logic::Profile_name);
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[Logic::Files_names.size() - 1].c_str(), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)(Logic::Profile_ID + Logic::Files_names.size() - 1), GetModuleHandle(NULL), NULL);
			SendMessage(hWnd, WM_SIZE, 0, 0);
			Files::save_progress(Logic::Profile_name);
			MessageBox(hWnd, TEXT("A new profile has been added"), TEXT("Confirmation"), MB_OK);
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::UpdateUI(hWnd);
		}
		break;
		case bNewHabit:
		{
			Logic::Current_view = View::Add_habit;
			Logic::UpdateUI(hWnd);
		}
		break;
		case bCancel:
		{
			Logic::Current_view = View::Welcome;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::UpdateUI(hWnd);
		}
		break;
		case bCreateHabit:
		{
			std::wstring name = Logic::GetWindowTextString(hWnd, insInfo);
			if (name.empty()) {
				MessageBox(hWnd, TEXT("Enter habit name! "), TEXT("Error"), MB_OK | MB_ICONWARNING);
				break;
			}
			if (Logic::new_habit.get_type() == Habit::Type::unknown ||
				Logic::new_habit.get_difficulty() == Habit::Difficulty::unknown ||
				Logic::new_habit.get_frequency() == Habit::Frequency::unknown) {
				MessageBox(hWnd, TEXT("Select all options!"), TEXT("Error"), MB_OK | MB_ICONWARNING);
				break;
			}
			Logic::new_habit.set_name(name);
			Logic::Habits.push_back(Logic::new_habit);
			Files::save_progress(Logic::Profile_name);
			Logic::new_habit.clear_habit();
			Logic::RebuildHabitUI(hWnd);
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::Current_view = View::Main_menu;
			SendMessage(hWnd, WM_SIZE, 0, 0);
			Logic::UpdateUI(hWnd);
		}
		break;
		case bCancel2:
		{
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::UpdateUI(hWnd);
			break;
		}
		case bStats:
		{
			std::wstring stats = Statistics::generate_stats_text();
			MessageBox(hWnd, stats.c_str(), L"Habit Statistics", MB_OK);
		}
		default:
		{
			if (button_ID >= Logic::Profile_ID &&
				button_ID < Logic::Profile_ID + (int)Logic::Files_names.size()) {
				Logic::HandleProfileSelection(hWnd, button_ID);
			}
			else if (button_ID >= Logic::Habit_more_info_ID &&
				button_ID < Logic::Habit_more_info_ID + (int)Logic::Habits.size()) {
				Logic::HandleHabitMoreInfo(hWnd, button_ID);
			}
			else if (button_ID >= Logic::Habit_done_box_ID &&
				button_ID < Logic::Habit_done_box_ID + (int)Logic::Habits.size()) {
				Logic::HandleHabitDone(hWnd, button_ID);
			}
		}
		break;
		}
		return 0;
	}

	case WM_DESTROY:
	{
		if (!Logic::Profile_name.empty()) {
			Files::save_progress(Logic::Profile_name);
		}
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		RECT TextRect;
		GetClientRect(hWnd, &TextRect); // przerysowywanie gdy zmiana wielkoœci
		TextRect.left += 45;
		TextRect.top += 45;
		HDC hdc = BeginPaint(hWnd, &paint);
		SetBkMode(hdc, TRANSPARENT); // tlo przezroczyste
		HFONT staraCzcionka = (HFONT)SelectObject(hdc, Font1); // zmiana czcionki
		SetTextColor(hdc, RGB(255, 0, 0)); // kolor czcionki
		DrawText(hdc, TEXT("Habit Tracker"), -1, &TextRect, DT_CENTER | DT_SINGLELINE);
		(HFONT)SelectObject(hdc, Font2); // zmiana czcionki 
		TextRect.top += 45;
		DrawText(hdc, TEXT("Control your habits"), -1, &TextRect, DT_CENTER | DT_SINGLELINE);
		SelectObject(hdc, Font1);
		EndPaint(hWnd, &paint);
		return 0;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		Layouts::Welcome(hWnd, rect);
		Layouts::New_profile(hWnd, rect);
		Layouts::Load_profile(hWnd, rect);
		Layouts::Main_menu(hWnd, rect);
		Layouts::Add_habit(hWnd, rect);
		Logic::UpdateUI(hWnd);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}