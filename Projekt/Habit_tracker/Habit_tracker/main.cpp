#include <iostream>
#include <vector>
#include "Habit.h"
#include "Date.h"
#include "Logic.h"
#include <Windows.h>


					// uchwyt okna  kod MSG		parametry wiadomosci 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = TEXT("FirstWindow");
	wc.lpszMenuName = NULL;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc)) {
		return -1;
	}
	auto hWnd = CreateWindowEx(0, wc.lpszClassName, TEXT("OKNO"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, NULL, hInstance, NULL);
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
		std::cout << "Something went wrong" << std::endl;
	}
}