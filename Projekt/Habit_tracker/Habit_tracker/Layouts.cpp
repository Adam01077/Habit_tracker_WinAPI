#include <iostream>
#include "Habit.h"
#include <chrono>
#include <ctime>
#include <string>
#include "Logic.h"
#include "Windows.h"

namespace Layouts{

	void Welcome(HWND hWnd, const RECT& rect) {
		int gap = 10;
		int button_width = 150;
		int button_height = 25;
		int x = (rect.right - button_width) / 2 ;
		int y = rect.bottom / 2;

		SetWindowPos(GetDlgItem(hWnd, bNewProfile), NULL, x, y, button_width, button_height, SWP_NOZORDER);

		SetWindowPos(GetDlgItem(hWnd, bLoadProfile), NULL, x, y + button_height + gap, button_width, button_height, SWP_NOZORDER);
	}

	void New_profile(HWND hWnd, const RECT& rect) {
		int gap = 10;
		int button_width = 150;
		int button_height = 25;
		int x = (rect.right - button_width) / 2;
		int y = rect.bottom / 2;

		SetWindowPos(GetDlgItem(hWnd, insInfo), NULL, x, y, 220, button_height, SWP_NOZORDER);

		SetWindowPos(GetDlgItem(hWnd, bSave), NULL, x, y + button_height + gap, 70, button_height, SWP_NOZORDER);

		SetWindowPos(GetDlgItem(hWnd, bCancel), NULL, x + gap + 70, y + button_height + gap, 70, button_height, SWP_NOZORDER);
	}

	void Load_profile(HWND hWnd, const RECT& rect) {
		int gap = 10;
		int button_width = 150;
		int button_height = 25;
		int x = (rect.right - button_width) / 2;
		int y = rect.bottom / 2;
		for (int i = 0; i < Logic::Files_names.size(); i++) {
			SetWindowPos(GetDlgItem(hWnd, Logic::Profile_ID + i), NULL, x, y, button_width, button_height, SWP_NOZORDER);
			y += button_height + gap;
		}
	}

	void Main_menu(HWND hWnd, const RECT& rect) {
		int gap = 10;
		int Info_button_width = 200;
		int button_height = 25;
		int small_button_width = 40;
		int x_Info = (rect.right- Info_button_width)/2 - 100;
		int y = (rect.bottom- button_height) / 2 - 100;
		int y_temp = y;
		int x_More_info = rect.right - 120;
		int x_Habit_done = rect.right - 60;
		int button_width = 150;
		
		x_Info += gap;
		for (int i = 0; i < Logic::Habits.size(); i++) {
			SetWindowPos(GetDlgItem(hWnd, Logic::Habit_info_ID + i), NULL, x_Info, y_temp, Info_button_width, button_height, SWP_NOZORDER);
			SetWindowPos(GetDlgItem(hWnd, Logic::Habit_more_info_ID + i), NULL, x_Info+Info_button_width, y_temp, small_button_width, button_height, SWP_NOZORDER);
			SetWindowPos(GetDlgItem(hWnd, Logic::Habit_done_box_ID + i), NULL, x_Info + Info_button_width+ small_button_width, y_temp, small_button_width, button_height, SWP_NOZORDER);

			y_temp += button_height + gap;
		}

		SetWindowPos(GetDlgItem(hWnd, bNewHabit), NULL, x_Info, y-button_height,button_width , button_height, SWP_NOZORDER);
		SetWindowPos(GetDlgItem(hWnd, bChangeProfile), NULL, x_Info, y - 2 * button_height, button_width, button_height, SWP_NOZORDER);
	}

	void Add_habit(HWND hWnd, const RECT& rect) {
		int x = rect.right / 2 - 100;
		int y = rect.bottom / 2;
		int gap = 10;
		int button_width = 80;
		int button_height = 25;
		int x_temp = gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, insInfo), NULL, x, y, 200, button_height, SWP_NOZORDER);
		y += button_height + gap;
		SetWindowPos(GetDlgItem(hWnd, optGood), NULL, x,y, button_width, button_height, SWP_NOZORDER);
		SetWindowPos(GetDlgItem(hWnd, optBad), NULL,x+x_temp, y, button_width, button_height, SWP_NOZORDER);

		y += button_height + gap;
		SetWindowPos(GetDlgItem(hWnd, optHard), NULL, x, y, button_width, button_height, SWP_NOZORDER);

		SetWindowPos(GetDlgItem(hWnd, optMedium), NULL, x+x_temp, y, button_width, button_height, SWP_NOZORDER);
		x_temp += gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, optEasy), NULL, x+x_temp, y, button_width, button_height, SWP_NOZORDER);
		x_temp += gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, optCommon), NULL, x+ x_temp , y, button_width + 10, button_height, SWP_NOZORDER);
		y += button_height + gap;
		x_temp = gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, optDaily), NULL, x, y, button_width, button_height, SWP_NOZORDER);
		SetWindowPos(GetDlgItem(hWnd, optWeekly), NULL, x+x_temp, y, button_width, button_height, SWP_NOZORDER);
		x_temp += gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, optMonthly), NULL, x+ x_temp, y, button_width, button_height, SWP_NOZORDER);
		y += button_height + gap;
		x_temp = gap + button_width;
		SetWindowPos(GetDlgItem(hWnd, bCreateHabit), NULL, x, y, 100, button_height, SWP_NOZORDER);
		SetWindowPos(GetDlgItem(hWnd, bCancel2), NULL,x+ x_temp+ 25, y, button_width, button_height, SWP_NOZORDER);
	}
}