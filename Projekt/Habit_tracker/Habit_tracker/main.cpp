#include <iostream>
#include <vector>
#include "Habit.h"
#include "Logic.h"
#include <Windows.h>
#include "Files.h"
#include "WndProc.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	Files::first_run();
	Logic::Current_view = View::Welcome;
	Logic::Files_names = Files::get_files_names();
	
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