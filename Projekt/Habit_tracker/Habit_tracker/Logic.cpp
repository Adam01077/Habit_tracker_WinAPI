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
}
