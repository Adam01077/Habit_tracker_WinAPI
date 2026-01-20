#include "Logic.h"
#include <ctime>
#include "Layouts.h"

namespace Logic {
    std::wstring Profile_name{};
    View Current_view = View::Welcome;
    std::vector<std::wstring> Files_names{};
    std::vector<Habit> Habits{};
    Habit new_habit{};

     const time_t today_() {
       time_t now = time(nullptr);
        struct tm time_now {};
        localtime_s(&time_now, &now);
        time_now.tm_hour = 0;
        time_now.tm_min = 0;
        time_now.tm_sec = 0;
        time_now.tm_isdst = -1;
        return mktime(&time_now);
    }

     void CreateHabitControls(HWND hWnd, int i) {
         CreateWindowEx(0, TEXT("STATIC"), TEXT(""),WS_CHILD | SS_LEFT,
             0, 0, 0, 0,
             hWnd, (HMENU)(Logic::Habit_info_ID + i),
             GetModuleHandle(NULL), NULL);

         CreateWindowEx(0, TEXT("BUTTON"), TEXT("X"),
             WS_CHILD | BS_PUSHBUTTON,
             0, 0, 0, 0,
             hWnd, (HMENU)(Logic::Habit_done_box_ID + i),
             GetModuleHandle(NULL), NULL);

         CreateWindowEx(0, TEXT("BUTTON"), TEXT("..."),
             WS_CHILD | BS_PUSHBUTTON,
             0, 0, 0, 0,
             hWnd, (HMENU)(Logic::Habit_more_info_ID + i),
             GetModuleHandle(NULL), NULL);
     }

     void DestroyHabitControls(HWND hWnd) {
         for (int i = 0; i < Logic::HabitControlsCount; i++){
             DestroyWindow(GetDlgItem(hWnd, Logic::Habit_info_ID + i));
             DestroyWindow(GetDlgItem(hWnd, Logic::Habit_done_box_ID + i));
             DestroyWindow(GetDlgItem(hWnd, Logic::Habit_more_info_ID + i));
         }

         Logic::HabitControlsCount = 0;
     }

     void RebuildHabitUI(HWND hWnd){
         DestroyHabitControls(hWnd);

         for (int i = 0; i < Logic::Habits.size(); i++){
             CreateHabitControls(hWnd, i);
         }
         Logic::HabitControlsCount = Logic::Habits.size();
     }

	 void UpdateUI(HWND hWnd) {
		 switch (Logic::Current_view) {
		 case View::Welcome:
		 {
			 ShowWindow(GetDlgItem(hWnd, bNewProfile), SW_SHOW);
			 ShowWindow(GetDlgItem(hWnd, bLoadProfile), SW_SHOW);
			 EnableWindow(GetDlgItem(hWnd, bLoadProfile), !Logic::Files_names.empty());
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
			 ShowWindow(GetDlgItem(hWnd, bSave), SW_HIDE);
			 ShowWindow(GetDlgItem(hWnd, bCancel), SW_HIDE);
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
				 EnableWindow(GetDlgItem(hWnd, Logic::Habit_done_box_ID + i), !Logic::Habits[i].is_done_in_peroid());
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
}
