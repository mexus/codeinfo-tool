#pragma once
#include <fstream>

class TempFile {
public:
    TempFile();
    TempFile(const TempFile&) = delete;
    ~TempFile();

    template<class T>
    std::ostream& operator << (T&& t) {
        return file_stream_ << std::forward<T>(t);
    }

    const std::string& GetFileName() const;

private:
    const std::string file_name_;
    std::fstream file_stream_;

    static std::string GenerateFileName();
};

