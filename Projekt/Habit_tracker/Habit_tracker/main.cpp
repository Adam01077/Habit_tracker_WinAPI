#include <iostream>
#include <vector>
#include "Habit.h"
#include "Logic.h"
#include <Windows.h>
#include "Fonts.h"
#include "Files.h"
#include "Layouts.h"
using namespace Files;

void UpdateUI(HWND hWnd) {
	switch (Logic::Current_view) {
	case View::Welcome:
	{
		ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bNewHabit), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bChangeProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bSave), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bCancel), SW_HIDE);
		break;
	}
	case View::New_profile:
	{
		ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bSave), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bCancel), SW_SHOW);
		break;
	}
	case View::Load_profile:
	{
		ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_HIDE);
		for (int i = 0; i < Logic::Files_names.size(); i++) {
			ShowWindow(GetDlgItem(hWnd, Logic::Profile_ID + i), SW_SHOW);
		}
		//ShowWindow(GetDlgItem(hWnd, bCancel), SW_SHOW); zle miejsce pokazania 
		break;
	}
	case View::Main_menu:
	{
		ShowWindow(GetDlgItem(hWnd, bNewHabit), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bChangeProfile), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optGood), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optBad), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optHard), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optMedium), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optEasy), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optCommon), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optDaily), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optWeekly), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optMonthly), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bCreateHabit), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bCancel2), SW_HIDE);

		for (int i = 0; i < Logic::Habits.size(); i++) {
			SetWindowText(GetDlgItem(hWnd, Logic::Habit_info_ID + i), Logic::Habits[i].to_print().c_str());
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_info_ID + i), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_more_info_ID + i), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_done_box_ID + i), SW_SHOW);
		}
		break;
	}
	case View::Add_habit:
	{
		for (int i = 0; i < Logic::Habits.size(); i++) {
			SetWindowText(GetDlgItem(hWnd, Logic::Habit_info_ID + i), Logic::Habits[i].to_print().c_str());
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_info_ID + i), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_more_info_ID + i), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, Logic::Habit_done_box_ID + i), SW_HIDE);
		}
		ShowWindow(GetDlgItem(hWnd, bCancel2), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bNewHabit), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bChangeProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optGood), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optBad), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optHard), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optMedium), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optEasy), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optCommon), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optDaily), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optWeekly), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optMonthly), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bCreateHabit), SW_SHOW);
		break;
	}
	}

	switch (Logic::new_habit.get_type()) {
	case Habit::Type::good:
		SendMessage(GetDlgItem(hWnd, optGood), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optBad), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Type::bad:
		SendMessage(GetDlgItem(hWnd, optBad), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optGood), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	}
	switch (Logic::new_habit.get_difficulty()) {
	case Habit::Difficulty::common:
		SendMessage(GetDlgItem(hWnd, optCommon), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optEasy), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optMedium), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optHard), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Difficulty::easy:
		SendMessage(GetDlgItem(hWnd, optEasy), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optCommon), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optMedium), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optHard), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Difficulty::meduim:
		SendMessage(GetDlgItem(hWnd, optMedium), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optEasy), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optCommon), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optHard), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Difficulty::hard:
		SendMessage(GetDlgItem(hWnd, optHard), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optEasy), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optMedium), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optCommon), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	}
	switch (Logic::new_habit.get_frequency()) {
	case Habit::Frequency::daily:
		SendMessage(GetDlgItem(hWnd, optDaily), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optWeekly), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optMonthly), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Frequency::weekly:
		SendMessage(GetDlgItem(hWnd, optWeekly), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optDaily), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optMonthly), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	case Habit::Frequency::monthly:
		SendMessage(GetDlgItem(hWnd, optMonthly), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optWeekly), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(hWnd, optDaily), BM_SETCHECK, BST_UNCHECKED, 0);
		break;
	}
};

					// uchwyt okna  kod MSG		parametry wiadomosci 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // wParam ma du¿o informacji górna czêœæ to kod powiadomienia dolna to ID kontorlki 
	// lParam to uchwyt do kontrolki 
	// lParam to uchwyt do kontrolki 
	switch (uMsg) {
	case WM_CREATE:
	{
		int x_mid = 380;
		int y_mid = 200;
		int button_gap = 20;
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create new profile"), WS_CHILD | BS_PUSHBUTTON,0,0,0,0, hWnd, (HMENU)bNewProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Load profile"), WS_CHILD | BS_PUSHBUTTON, 0,0,0,0, hWnd, (HMENU)bLoadProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Change Profile"), WS_CHILD | BS_PUSHBUTTON, 0,0,0,0, hWnd, (HMENU)bChangeProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, (HMENU)insInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("SAVE"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bSave, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("CANCEL"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCancel, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("CANCEL"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCancel2, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Add new habit"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bNewHabit, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("..."), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bMoreInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Good"), WS_GROUP |WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optGood, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Bad"), WS_CHILD | BS_RADIOBUTTON , 0, 0, 0, 0, hWnd, (HMENU)optBad, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Hard"), WS_GROUP | WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optHard, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Medium"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optMedium, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Easy"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optEasy, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Common"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optCommon, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Daily"), WS_GROUP| WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd, (HMENU)optDaily, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Weekly"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd,(HMENU)optWeekly, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Monthly"), WS_CHILD | BS_RADIOBUTTON, 0, 0, 0, 0, hWnd,(HMENU)optMonthly, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create habit"), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)bCreateHabit, GetModuleHandle(NULL), NULL);
		for (int i = 0; i < Logic::Files_names.size();i++) {
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[i].c_str(), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)(Logic::Profile_ID+i), GetModuleHandle(NULL), NULL);
		}
		UpdateUI(hWnd);
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
			UpdateUI(hWnd);
		}
		break;
		case bLoadProfile:
		{
			Logic::Current_view = View::Load_profile;
			UpdateUI(hWnd);
		}
		break;
		case bChangeProfile:
		{
			Logic::DestroyHabitControls(hWnd);
			Logic::Habits.clear();
			Logic::Current_view = View::Welcome;
			UpdateUI(hWnd);
		}
		break;
		case bSave:
		{
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			Logic::Profile_name.resize(length + 1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &Logic::Profile_name[0], length + 1);
			Logic::Profile_name.resize(length);
			Logic::Files_names.push_back(Logic::Profile_name);
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[Logic::Files_names.size()-1].c_str(), WS_CHILD | BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, (HMENU)(Logic::Profile_ID + Logic::Files_names.size() - 1), GetModuleHandle(NULL), NULL);
			// nie pokazuje tego okienka i nie ustawiam go 
			MessageBox(hWnd, TEXT("Dodano nowy profil"), TEXT("Potwierdzenie"), MB_OK);
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			UpdateUI(hWnd);
		}
		break;
		case bNewHabit:
		{
			Logic::Current_view = View::Add_habit;
			UpdateUI(hWnd);
		}
		break;
		case bCancel: 
		{
			Logic::Current_view = View::Welcome;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			UpdateUI(hWnd);
		}
		break;
		case optGood:
		{
			Logic::new_habit.set_type(Habit::Type::good);
			UpdateUI(hWnd);
		}
		break;
		case optBad:
		{
			Logic::new_habit.set_type(Habit::Type::bad);
			UpdateUI(hWnd);
		}
		break;
		case optCommon:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::common);
			UpdateUI(hWnd);
		}
		break;
		case optEasy:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::easy);
			UpdateUI(hWnd);
		}
		break;
		case optMedium:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::meduim);
			UpdateUI(hWnd);
		}
		break;
		case optHard:
		{
			Logic::new_habit.set_difficulty(Habit::Difficulty::hard);
			UpdateUI(hWnd);
		}
		break;
		case optDaily:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::daily);
			UpdateUI(hWnd);
		}
		break;
		case optWeekly:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::weekly);
			UpdateUI(hWnd);
		}
		break;
		case optMonthly:
		{
			Logic::new_habit.set_frequency(Habit::Frequency::monthly);
			UpdateUI(hWnd);
		}
		break;
		case bCreateHabit:
		{
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			std::wstring name;
			name.resize(length + 1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &name[0], length + 1);
			name.resize(length);
			Logic::new_habit.set_name(name);
			Logic::Habits.push_back(Logic::new_habit);
			Logic::new_habit.clear_habit();
			Logic::RebuildHabitUI(hWnd);
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			Logic::Current_view = View::Main_menu;
			UpdateUI(hWnd);
		}
		break;
		case bCancel2:
		{
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			UpdateUI(hWnd);
		}
		default:
		{	// wybor profilu do wczytania
			if (button_ID >= Logic::Profile_ID && button_ID < Logic::Profile_ID + Logic::Files_names.size()) {
				int index = button_ID - Logic::Profile_ID;
				auto profile_name = Logic::Files_names[index];
				Logic::Habits.clear();
				if (load_save(profile_name)) {
					Logic::RebuildHabitUI(hWnd);
					MessageBox(hWnd, TEXT("Za³adowano profil"), TEXT("Potwierdzenie"), MB_OK);
					for (int i = 0; i < Logic::Files_names.size(); i++) {
						ShowWindow(GetDlgItem(hWnd, Logic::Profile_ID + i), SW_HIDE);
					}
					Logic::Current_view = View::Main_menu;
					SendMessage(hWnd, WM_SIZE, 0, 0);
					UpdateUI(hWnd);
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
					L"Nazwa: " + h.get_name() + L"\n" +
					L"Typ: " + h.type_to_string() + L"\n" +
					L"Trudnoœæ: " + h.diff_to_string() + L"\n" +
					L"Czêstotliwoœæ: " + h.freq_to_string();

				MessageBox(hWnd, info.c_str(), L"Szczegó³y nawyku", MB_OK);
			}
			// Odznaczenie wykonania nawyku
			if (button_ID >= Logic::Habit_done_box_ID && button_ID < Logic::Habit_done_box_ID + Logic::Habits.size()) {
				int index = button_ID - Logic::Habit_done_box_ID;
				// sprawdzic kiedy ostatnio bylo robione
				Logic::Habits[index].increase_streak();

				Logic::RebuildHabitUI(hWnd);
				SendMessage(hWnd, WM_SIZE, 0, 0);
				UpdateUI(hWnd);
			}
		}
		break;
		}
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		RECT ButtonRect,TextRect;
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
		UpdateUI(hWnd);
		return 0;
	} 
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
					// uchyt do plikacji	(nic)	  wskaznik na CMD	// sposób wyswietlania okna 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
	
	Logic::Files_names = get_files_names();
	if (first_run()) {
		Logic::Current_view = View::Welcome;
		// blokowanie loadProfile
	}
	else {
		Logic::Files_names = get_files_names();
	}
	
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = TEXT("MainWindow");
	wc.lpszMenuName = NULL;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc)) {
		return -1;
	}
	auto hWnd = CreateWindowEx(0, wc.lpszClassName, TEXT("Habit Tracker"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL) {
		return -1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}