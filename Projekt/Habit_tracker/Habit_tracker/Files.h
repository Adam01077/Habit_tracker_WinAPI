#pragma once
#include <filesystem>
#include <fstream>
namespace Files {
	
	void first_run();

	bool load_save(const std::wstring& Name);

	void save_progress(const std::wstring& Name);

	std::vector<std::wstring> get_files_names();
}