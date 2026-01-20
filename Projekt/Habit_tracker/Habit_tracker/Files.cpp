#include "Files.h"
#include <filesystem>
#include <fstream>
#include "Habit.h"
#include <sstream>
#include <string>
#include "Logic.h"
namespace Files {
	const std::filesystem::path path = "saves";

	void first_run() {
		std::filesystem::create_directories(path);
	}

	bool load_save(const std::wstring& Name) {
		std::wfstream load_file;
		std::wstring file_name = Name + L".txt";
		load_file.open(path / file_name, std::ios::in);
		if (!load_file) {
			return false;
		}
		Habit loaded_habit{};
		std::wstring line;
		while (std::getline(load_file,line)) {
			loaded_habit.from_file(line);
			loaded_habit.check_streak();
			Logic::Habits.push_back(loaded_habit);
		}
		load_file.close();
		return true;
	}

	void save_progress(const std::wstring& Name) {
		std::wfstream save_file;
		std::wstring file_name = Name + L".txt";
		save_file.open(path / file_name, std::ios::out);
		if (!save_file) {
			throw std::runtime_error("Could not open save file.");
		}
		for (const auto& habit : Logic::Habits) {
			save_file << habit.to_save() << L"\n";
		}
		save_file.close();
	}

	std::vector<std::wstring> get_files_names() {
		std::vector<std::wstring> file_names;
		for (const auto& file : std::filesystem::directory_iterator(path)) {
			if (file.path().extension() == ".txt") {
				 file_names.push_back(file.path().stem().wstring());
			}
		}
		return file_names;
	}
}