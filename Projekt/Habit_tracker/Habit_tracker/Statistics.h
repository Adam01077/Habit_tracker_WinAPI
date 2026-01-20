#pragma once
#include <string>
#include <vector>
#include "Habit.h"

namespace Statistics {
    struct HabitStats {
        int total_habits = 0;
        int completed_today = 0;
        int best_current_streak = 0;
        std::wstring best_streak_habit_name;
        double completion_rate = 0.0;
    };

    struct TopHabit {
        std::wstring name;
        int current_streak;
        int best_streak;
    };

    HabitStats calculate_global_stats();
    std::vector<TopHabit> get_top_habits(int count = 3);
    std::wstring generate_stats_text();
}