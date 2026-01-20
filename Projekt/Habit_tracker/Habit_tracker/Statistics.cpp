#include "Statistics.h"
#include "Logic.h"
#include <algorithm>
#include <numeric>

namespace Statistics {

    HabitStats calculate_global_stats() {
        HabitStats stats;
        stats.total_habits = static_cast<int>(Logic::Habits.size());

        if (stats.total_habits == 0) return stats;

        for (const auto& habit : Logic::Habits) {
            if (habit.is_done_in_period()) {
                stats.completed_today++;
            }

            if (habit.get_current_streak() > stats.best_current_streak) {
                stats.best_current_streak = habit.get_current_streak();
                stats.best_streak_habit_name = habit.get_name();
            }
        }

        stats.completion_rate = (static_cast<double>(stats.completed_today) /
            stats.total_habits) * 100.0;

        return stats;
    }

    std::vector<TopHabit> get_top_habits(int count) {
        std::vector<TopHabit> top;

        for (const auto& habit : Logic::Habits) {
            top.push_back({
                habit.get_name(),
                habit.get_current_streak(),
                habit.get_best_streak()
                });
        }

        std::sort(top.begin(), top.end(),
            [](const TopHabit& a, const TopHabit& b) {
                return a.current_streak > b.current_streak;
            });


        if (top.size() > static_cast<size_t>(count)) {
            top.resize(count);
        }

        return top;
    }

    std::wstring generate_stats_text() {
        auto stats = calculate_global_stats();
        auto top = get_top_habits(3);

        std::wstring text;
        text += L"--HABIT STATISTICS--\n\n";

        text += L"Total habits: " + std::to_wstring(stats.total_habits) + L"\n";
        text += L"Completed today:  " + std::to_wstring(stats.completed_today) +
            L"/" + std::to_wstring(stats.total_habits) +
            L" (" + std::to_wstring(static_cast<int>(stats.completion_rate)) + L"%)\n";
        text += L"Best current streak: " + std::to_wstring(stats.best_current_streak);

        if (!stats.best_streak_habit_name.empty()) {
            text += L" (" + stats.best_streak_habit_name + L")";
        }
        text += L"\n\n";

        if (!top.empty()) {
            text += L"--TOP STREAKS--\n\n";

            int rank = 1;
            for (const auto& habit : top) {
                text += std::to_wstring(rank++) + L". " + habit.name +
                    L" - " + std::to_wstring(habit.current_streak) + L" days";
                if (habit.current_streak == habit.best_streak && habit.best_streak > 0) {
                    text += L"BEST! ";
                }
                text += L"\n";
            }
        }
        return text;
    }
}