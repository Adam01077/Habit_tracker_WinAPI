#include "Logic.h"
#include <ctime>

namespace Logic {
    std::wstring Profile_name{};
    View Current_view = View::Welcome;
    std::vector<std::wstring> Files_names{};
    std::vector<Habit> Habits{};

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

}
