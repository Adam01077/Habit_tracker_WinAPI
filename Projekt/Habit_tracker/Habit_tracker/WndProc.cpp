#include "WndProc.h"
#include "Logic.h"
#include "Files.h"
#include "Fonts.h"
#include "Layouts.h"

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
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			if (length == 0) {
				MessageBox(hWnd, TEXT("Podaj nazwê profilu! "), TEXT("B³¹d"), MB_OK | MB_ICONWARNING);
				break;
			}
			Logic::Profile_name.resize(length + 1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &Logic::Profile_name[0], length + 1);
			Logic::Profile_name.resize(length);
			Logic::Files_names.push_back(Logic::Profile_name);
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[Logic::Files_names.size() - 1].c_str(), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)(Logic::Profile_ID + Logic::Files_names.size() - 1), GetModuleHandle(NULL), NULL);
			SendMessage(hWnd, WM_SIZE, 0, 0);
			Files::save_progress(Logic::Profile_name);
			MessageBox(hWnd, TEXT("Dodano nowy profil"), TEXT("Potwierdzenie"), MB_OK);
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
		case optGood:
		{
			Logic::new_habit.set_type(Habit::Type::good);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optBad:
		{
			Logic::new_habit.set_type(Habit::Type::bad);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optCommon:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::common);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optEasy:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::easy);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optMedium:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::meduim);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optHard:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::hard);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optDaily:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::daily);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optWeekly:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::weekly);
			Logic::UpdateUI(hWnd);
		}
		break;
		case optMonthly:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::monthly);
			Logic::UpdateUI(hWnd);
		}
		break;
		case bCreateHabit:
		{
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			if (length == 0) {
				MessageBox(hWnd, TEXT("Podaj nazwê profilu! "), TEXT("B³¹d"), MB_OK | MB_ICONWARNING);
				break;
			}
			std::wstring name;
			name.resize(length + 1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &name[0], length + 1);
			name.resize(length);
			Logic::new_habit.set_name(name);
			Logic::Habits.push_back(Logic::new_habit);
			Files::save_progress(Logic::Profile_name);
			Logic::new_habit.clear_habit();
			Logic::RebuildHabitUI(hWnd);
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::Current_view = View::Main_menu;
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
		default:
		{	// wybor profilu do wczytania
			if (button_ID >= Logic::Profile_ID && button_ID < Logic::Profile_ID + Logic::Files_names.size()) {
				int index = button_ID - Logic::Profile_ID;
				auto profile_name = Logic::Files_names[index];
				Logic::Profile_name = profile_name;
				Logic::Habits.clear();
				if (Files::load_save(profile_name)) {
					Logic::RebuildHabitUI(hWnd);
					MessageBox(hWnd, TEXT("Za³adowano profil"), TEXT("Potwierdzenie"), MB_OK);
					for (int i = 0; i < Logic::Files_names.size(); i++) {
						ShowWindow(GetDlgItem(hWnd, Logic::Profile_ID + i), SW_HIDE);
					}
					Logic::Current_view = View::Main_menu;
					SendMessage(hWnd, WM_SIZE, 0, 0);
					Logic::UpdateUI(hWnd);
				}
				else {
					MessageBox(hWnd, TEXT("Could not open save file. Please check your files"), TEXT("Error"), MB_OK);
				}
			}
			// wybor podania informacji dla danego nawyku
			if (button_ID >= Logic::Habit_more_info_ID && button_ID < Logic::Habit_more_info_ID + Logic::Habits.size()) {
				int index = button_ID - Logic::Habit_more_info_ID;
				const Habit& h = Logic::Habits[index];

				std::wstring info =
					L"Name: " + h.get_name() + L"\n" +
					L"Type: " + h.type_to_string() + L"\n" +
					L"Difficulty: " + h.diff_to_string() + L"\n" +
					L"Frequency: " + h.freq_to_string() + L"\n" +
					L"Last Done: " + h.print_last_done();

				MessageBox(hWnd, info.c_str(), L"Habit Info", MB_OK);
			}
			// Odznaczenie wykonania nawyku
			if (button_ID >= Logic::Habit_done_box_ID && button_ID < Logic::Habit_done_box_ID + Logic::Habits.size()) {
				int index = button_ID - Logic::Habit_done_box_ID;
				Logic::Habits[index].set_last_done(Logic::today_());
				Logic::Habits[index].increase_streak();
				Files::save_progress(Logic::Profile_name);
				Logic::RebuildHabitUI(hWnd);
				SendMessage(hWnd, WM_SIZE, 0, 0);
				Logic::UpdateUI(hWnd);
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
		RECT ButtonRect, TextRect;
		GetClientRect(hWnd, &TextRect); // przerysowywanie gdy zmiana wielkoœci
		GetClientRect(hWnd, &ButtonRect);
		TextRect.left += 45;
		TextRect.top += 45;
		HDC hdc = BeginPaint(hWnd, &paint);
		SetBkMode(hdc, TRANSPARENT); // tlo przezroczyste
		HFONT staraCzcionka = (HFONT)SelectObject(hdc, Font1); // zmiana czcionki
		SetTextColor(hdc, RGB(255, 0, 0)); // kolor czcionki
		DrawText(hdc, TEXT("Habit Tracker"), -1, &TextRect, DT_CENTER | DT_SINGLELINE);
		(HFONT)SelectObject(hdc, Font2); // zmiana czcionki 
		TextRect.left += 45;
		TextRect.top += 45;
		DrawText(hdc, TEXT("xyz"), -1, &TextRect, DT_CENTER | DT_SINGLELINE);

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