#pragma once 
#include <string>
template <typename T>
class FileArray {
private:
    std::unique_ptr<std::fstream> file_;    // Dodano _ dla rozró¿nienia
    std::string filename_;                   // Dodano _
    size_t size_;                            // Ujednolicono nazwê

    void update_size() {
        if (!file_ || !file_->is_open()) {
            throw std::runtime_error("Plik nie jest otwarty");
        }
        file_->seekg(0, std::ios::end);
        if (file_->fail()) {
            throw std::runtime_error("Blad seekg");
        }
        std::streampos file_size = file_->tellg();
        if (file_size == std::streampos(-1)) {
            throw std::runtime_error("Blad tellg");
        }
        size_ = static_cast<size_t>(file_size) / sizeof(T);
    }

public:
    explicit FileArray(const std::string& filename)
        : file_(std::make_unique<std::fstream>()),  // Inicjalizacja unique_ptr
        filename_(filename),
        size_(0)
    {
        file_->open(filename, std::ios::in | std::ios::out | std::ios::binary);

        if (!file_->is_open()) {
            file_->clear();
            file_->open(filename, std::ios::in | std::ios::out |
                std::ios::binary | std::ios::trunc);
        }

        if (!file_->is_open()) {
            throw std::runtime_error("Nie mozna otworzyc pliku: " + filename);
        }
        update_size();
    }

    // Destruktor - domyœlny wystarczy (RAII przez unique_ptr)
    ~FileArray() = default;

    // Zakaz kopiowania
    FileArray(const FileArray&) = delete;
    FileArray& operator=(const FileArray&) = delete;

    // Move constructor
    FileArray(FileArray&& other) noexcept
        : file_(std::move(other.file_)),
        filename_(std::move(other.filename_)),
        size_(other.size_)
    {
        other.size_ = 0;
    }

    // Move assignment - poprawiony && i &other
    FileArray& operator=(FileArray&& other) noexcept {
        if (this != &other) {                    // & brakowa³o
            file_ = std::move(other.file_);
            filename_ = std::move(other.filename_);
            size_ = other.size_;                 // size_ to pole, nie metoda
            other.size_ = 0;
        }
        return *this;
    }

    // BRAKUJ¥CA METODA append()
    void append(const T& value) {
        if (!file_ || !file_->is_open()) {
            throw std::runtime_error("Plik nie jest otwarty");
        }
        file_->seekp(0, std::ios::end);
        file_->write(reinterpret_cast<const char*>(&value), sizeof(T));

        if (file_->fail()) {
            throw std::runtime_error("Blad zapisu do pliku:  " + filename_);
        }
        file_->flush();
        ++size_;
    }

    void push_back(const T& value) { append(value); }

    T at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range(
                "Indeks " + std::to_string(index) +
                " poza zakresem [0, " + std::to_string(size_) + ")"
            );
        }

        file_->seekg(static_cast<std::streamoff>(index * sizeof(T)), std::ios::beg);
        T value;
        file_->read(reinterpret_cast<char*>(&value), sizeof(T));

        if (file_->fail()) {
            throw std::runtime_error("Blad odczytu z pliku:  " + filename_);
        }
        return value;
    }

    T operator[](size_t index) const {
        return at(index);
    }

    // Gettery - nazwy ró¿ne od pól
    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    const std::string& filename() const noexcept { return filename_; }
};