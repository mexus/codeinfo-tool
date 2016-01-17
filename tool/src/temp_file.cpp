#include <temp_file.h>
#include <iostream>
#include <boost/filesystem.hpp>

TempFile::TempFile() : file_name_(GenerateFileName()), file_stream_(file_name_) {}

TempFile::~TempFile() {
    boost::system::error_code err;
    boost::filesystem::remove(file_name_, err);
    if (err.value() != 0) {
        std::cerr << "Unable to remove file `" << file_name_ << "`\n";
    }
}

const std::string& TempFile::GetFileName() const {
    return file_name_;
}

std::string TempFile::GenerateFileName() {
    return boost::filesystem::unique_path("%%%%-%%%%-%%%%-%%%%.cpp").string();
}
