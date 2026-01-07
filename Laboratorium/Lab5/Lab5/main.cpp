#include <iostream>
#include <fstream>
template <typename T>
class FileArray {
private:
	std::unique_ptr<std::fstream> file;
	std::string filename;
	size_t size;

	void update_size() {
		if (!file || !file->is_open()) {
			throw std::runtime_error("Plik nie mozna otworzyc");
		}
		file->seekg(0, std::ios::end);
		if (file->fail()) {
			throw std::runtime_error("Blad");
		}
		std::streampos file_size = file->tellg();
		if (file_size == std::streampos(-1)) {
			throw std::runtime_error("Blad");
		}
		size = static_cast<size_t>(file_size / sizeof(T));
	}

public:
	explicit FileArray(const std::string& filename) : file(std::make_unique<std::fstream>()), filename(filename), size(0) {
		file->open(filename, std::ios::in | std::ios::out | std::ios::binary);
		if (!file->is_open()) {
			file->clear();
			file->open(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
			if (!file->is_open()) {
				throw std::runtime_error("Nie mozna otworzyc pliku: "+ filename + ". Utworzenie rowniez sie nie powiodlo");
			}
		}
		update_size();
	}

	~FileArray() = default;
	
	// FileArray(const& FileArray) = delete;
	// FileArray& operator=(const &FileArray) = delete;
	FileArray(FileArray& other) noexcept : file(std::move(other.file)), filename(std::move(other.filename)), size(other.size) { other.size = 0; }

	FileArray& operator=(FileArray& other) noexcept{
		if (this != other) {
			file = std::move(other.file);
			filename = std::move(other.filename);
			size = other.size();
			other.size = 0;
		}
		return *this;
	}

	void append(const T &value) {
		if (!file || !file->is_open()) {
			throw std::runtime_error("Plik nie jest otwarty");
		}
		file->seekp(0, std::ios::end);
		if (file->fail()) {
			throw std::runtime_error("Blad");
		}
	}
};


int main() {
	FileArray<int> fa("data.bin");


	return 0;
}