#include <iostream>
#include <vector>
#include "Habit.h"
#include "Logic.h"
#include <Windows.h>
#include "Fonts.h"
#include "Files.h"

using namespace Files;
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
	optFreq,
	bCreateHabit, // tworzenie nawyku po wpisaniu informacji
};
void UpdateUI(HWND hWnd) {
	switch (Logic::Current_view) {
	case View::Welcome:
		ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_SHOW);
		break;
	
	case View::Load_profile:
		ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_HIDE);
		for (int i = 0; i < Logic::Files_names.size(); i++) {
			ShowWindow(GetDlgItem(hWnd, Logic::Profile_ID + i), SW_SHOW);
		}
		break;
	case View::Main_menu:
		ShowWindow(GetDlgItem(hWnd, bNewHabit), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optGood), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optBad), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optHard), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optMedium), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optEasy), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optCommon), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, bCreateHabit), SW_HIDE);

		break;
	case View::Add_habit:
		ShowWindow(GetDlgItem(hWnd, insInfo), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bNewHabit), SW_HIDE);
		ShowWindow(GetDlgItem(hWnd, optGood), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optBad), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optHard), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optMedium), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optEasy), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, optCommon), SW_SHOW);
		ShowWindow(GetDlgItem(hWnd, bCreateHabit), SW_SHOW);
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
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create new profile"), WS_CHILD | BS_PUSHBUTTON,380, 200, 150, 25, hWnd, (HMENU)bNewProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Load profile"), WS_CHILD | BS_PUSHBUTTON, 380, 200, 150, 25, hWnd, (HMENU)bLoadProfile, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("EDIT"), TEXT(""), WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 380, 230, 150, 25, hWnd, (HMENU)insInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("SAVE"), WS_CHILD | BS_PUSHBUTTON, 380, 300, 70, 25, hWnd, (HMENU)bSave, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("CANCEL"), WS_CHILD | BS_PUSHBUTTON, 480, 300, 70, 25, hWnd, (HMENU)bCancel, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Add new habit"), WS_CHILD | BS_PUSHBUTTON, 480, 300, 150, 25, hWnd, (HMENU)bNewHabit, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("..."), WS_CHILD | BS_PUSHBUTTON, 480, 300, 70, 25, hWnd, (HMENU)bMoreInfo, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Good"), WS_GROUP |WS_CHILD | BS_RADIOBUTTON, 380, 300, 70, 25, hWnd, (HMENU)optGood, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Bad"), WS_CHILD | BS_RADIOBUTTON , 410, 300, 70, 25, hWnd, (HMENU)optBad, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Hard"), WS_GROUP | WS_CHILD | BS_RADIOBUTTON, 340, 300, 70, 25, hWnd, (HMENU)optHard, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Medium"), WS_CHILD | BS_RADIOBUTTON, 370, 300, 70, 25, hWnd, (HMENU)optMedium, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Easy"), WS_CHILD | BS_RADIOBUTTON, 400, 300, 70, 25, hWnd, (HMENU)optEasy, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Common"), WS_CHILD | BS_RADIOBUTTON, 430, 300, 70, 25, hWnd, (HMENU)optCommon, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Create habit"), WS_CHILD | BS_PUSHBUTTON, 380, 400, 70, 25, hWnd, (HMENU)bCreateHabit, GetModuleHandle(NULL), NULL);
		for (int i = 0; i < Logic::Files_names.size();i++) {
			CreateWindowEx(0, TEXT("BUTTON"), Logic::Files_names[i].c_str(), WS_CHILD | BS_PUSHBUTTON, 380, 200, 150, 25, hWnd, (HMENU)(Logic::Profile_ID+i), GetModuleHandle(NULL), NULL);
		}
		UpdateUI(hWnd);
		return 0;
	}
	case WM_COMMAND:
	{
		int button_ID = LOWORD(wParam);
		switch(button_ID){
			if (HIWORD(wParam) == BN_CLICKED) {
		case bNewProfile:
			ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, insInfo), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, bSave), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, bCancel), SW_SHOW);
			break;
		case bLoadProfile:
			Logic::Current_view = View::Load_profile;
			UpdateUI(hWnd);
			break;
		case bSave:
		{
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			Logic::Profile_name.resize(length + 1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &Logic::Profile_name[0], length + 1);
			Logic::Profile_name.resize(length);
			MessageBox(hWnd, TEXT("Dodano nowy profil"), TEXT("Potwierdzenie"), MB_OK);
			ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, insInfo), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, bCancel), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, bSave), SW_HIDE);
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			UpdateUI(hWnd);
		}
			break;
		case bNewHabit:
			Logic::Current_view = View::Add_habit;
			UpdateUI(hWnd);
			break;
		case bCancel:
			ShowWindow(GetDlgItem(hWnd, insInfo), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, bSave), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, bCancel), SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_SHOW);
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			break;
		case bCreateHabit:
		{
			Habit new_habit{};
			int length = GetWindowTextLength(GetDlgItem(hWnd, insInfo));
			std::wstring name;
			name.resize(length +1);
			GetWindowText(GetDlgItem(hWnd, insInfo), &name[0], length + 1);
			name.resize(length);
			new_habit.set_name(name);
			Logic::Current_view = View::Main_menu;
			SetWindowText(GetDlgItem(hWnd, insInfo), TEXT(""));
			// dziala do tego meomentu


			Logic::Habits.push_back(new_habit);
			UpdateUI(hWnd);
		}
		break;
		default:
			if (button_ID >= Logic::Profile_ID && button_ID < Logic::Profile_ID + Logic::Files_names.size()) {
				int index = button_ID - Logic::Profile_ID;
				auto profile_name = Logic::Files_names[index];
				if (load_save(profile_name)) {
					MessageBox(hWnd, TEXT("Za³adowano profil"), TEXT("Potwierdzenie"), MB_OK);
					for (int i = 0; i < Logic::Files_names.size(); i++) {
						ShowWindow(GetDlgItem(hWnd, Logic::Profile_ID + i), SW_HIDE);
					}
					Logic::Current_view = View::Main_menu;
					UpdateUI(hWnd);
				}
				else {
					MessageBox(hWnd, TEXT("Could not open save file. Please check your files"), TEXT("Error"), MB_OK);
				}
			}
			break;
			}
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
		// Ruszaj¹ce siê przyciski
		RECT ButtonRect;
		InvalidateRect(hWnd, NULL, TRUE);
		GetClientRect(hWnd, &ButtonRect);
		int b_height = 25;
		int b_width = 150;
		int b_gap = 10;
		int x = (ButtonRect.right - b_width) / 2;
		int y = (ButtonRect.bottom - ButtonRect.top) / 2;

		HWND hButton = GetDlgItem(hWnd, bNewProfile);
		SetWindowPos(hButton, NULL, x, y, b_width, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, bLoadProfile);
		SetWindowPos(hButton, NULL, x, y+b_height+b_gap, b_width, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, insInfo); 
		SetWindowPos(hButton, NULL, x, y + b_height + b_gap, b_width, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, bSave);
		SetWindowPos(hButton, NULL, x, y+2*b_height+ 2*b_gap, 70, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, bCancel);
		SetWindowPos(hButton, NULL, b_gap+ x+70, y + 2 * b_height +2* b_gap, 70, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, optGood);
		SetWindowPos(hButton, NULL, x, y + 2 * b_height + 2 * b_gap, 70, b_height, SWP_NOZORDER);
	
		hButton = GetDlgItem(hWnd, optBad);
		SetWindowPos(hButton, NULL, b_gap + x + 70, y + 2 * b_height + 2 * b_gap, 70, b_height, SWP_NOZORDER);

		// do poprawy
		int y_temp = y;
		y_temp += b_height + b_gap;
		hButton = GetDlgItem(hWnd, optHard);
		SetWindowPos(hButton, NULL, x-140, y_temp + 2 * b_height + 2 * b_gap, 70, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, optMedium);
		SetWindowPos(hButton, NULL, b_gap + x -70, y_temp + 2 * b_height + 2 * b_gap, 80, b_height, SWP_NOZORDER);
		
		hButton = GetDlgItem(hWnd, optEasy);
		SetWindowPos(hButton, NULL, 2*b_gap + x+10, y_temp + 2 * b_height + 2 * b_gap, 70, b_height, SWP_NOZORDER);

		hButton = GetDlgItem(hWnd, optCommon);
		SetWindowPos(hButton, NULL,3* b_gap + x + 70+10, y_temp + 2 * b_height + 2 * b_gap, 90, b_height, SWP_NOZORDER);

		
		hButton = GetDlgItem(hWnd, bCreateHabit);
		SetWindowPos(hButton, NULL, x, y_temp + 3 * b_height + 3 * b_gap, 85, b_height, SWP_NOZORDER);
		y_temp = y;
		for (int i = 0; i < Logic::Files_names.size(); i++) {
			hButton = GetDlgItem(hWnd, Logic::Profile_ID + i);
			y_temp += b_height + b_gap;
			SetWindowPos(hButton, NULL, x, y_temp, b_width, b_height, SWP_NOZORDER);
		}
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