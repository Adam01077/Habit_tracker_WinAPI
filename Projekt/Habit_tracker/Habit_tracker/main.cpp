#include <iostream>
#include <vector>
#include "Habit.h"
#include "Date.h"
#include "Logic.h"
#include <Windows.h>
#include "Fonts.h"

enum BOX_ID {
	ID_CHECKBOX1 = 101,
};

					// uchwyt okna  kod MSG		parametry wiadomosci 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // wParam ma du¿o informacji górna czêœæ to kod powiadomienia dolna to ID kontorlki 
	// lParam to uchwyt do kontrolki 
	// lParam to uchwyt do kontrolki 
	switch (uMsg) {
	case WM_CREATE:
		//CreateWindowEx(0, TEXT("BUTTON"), TEXT("CHECKBOX"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 10, 150, 30, hWnd, (HMENU)ID_CHECKBOX1, GetModuleHandle(NULL), NULL);
		return 0;
	case WM_COMMAND:
		/*if (LOWORD(wParam) == ID_CHECKBOX1 && HIWORD(wParam) == BN_CLICKED) {
			MessageBox(hWnd, TEXT("Potwierdzono"), TEXT("Potwierdzenie"), MB_OK);
		}*/
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		Font1;

		HDC hdc = BeginPaint(hWnd, &paint);
		SetBkMode(hdc, TRANSPARENT);
		HFONT staraCzcionka = (HFONT)SelectObject(hdc, Font1);
		SetTextColor(hdc, RGB(255, 0, 0));
		TextOut(hdc, 400, 20, TEXT("Habit Tracker"), lstrlen(TEXT("Habit Tracker")));
		EndPaint(hWnd, &paint);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
					// uchyt do plikacji	(nic)	  wskaznik na CMD	// sposób wyswietlania okna 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {
	
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



// to stary main 
void temp()
{
	std::vector<Habit> habits;
	Habit new_habit("Programowanie w c++", Habit::Type::good, Habit::Difficulty::easy, Habit::Frequency::daily);
	new_habit.set_last_done(today_());
	if (not Logic::make_save(new_habit)) {
		return;
		//std::cout << "Something went wrong" << std::endl;
	}
}