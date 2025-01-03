#include "bitreader/common/direct_file_reader.hpp"
#include <stdexcept>

using namespace brcpp;

#ifdef WIN32
namespace
{
    int fseek64(FILE* file, uint64_t pos, int origin)
    {
        return _fseeki64(file, pos, origin);
    }
    
    int64_t ftell64(FILE* file)
    {
        return _ftelli64(file);
    }
    
    FILE* fopen64(const char* name, const char* mode)
    {
        return fopen(name, mode);
    }
}
#else
namespace
{
    int fseek64(FILE* file, uint64_t pos, int origin)
    {
        // Requires API 24
        //return fseeko64(file, pos, origin);
        return fseek(file, pos, origin);
    }
    
    int64_t ftell64(FILE* file)
    {
        // Requires API 24
        //return ftello64(file);
        return ftell(file);
    }
}
#endif

//----------------------------------------------------------------------
size_t direct_file_reader::read(uint8_t* dest, size_t position, size_t bytes) {
    if (fseek64(_file, position, SEEK_SET) < 0) {
        throw std::runtime_error("Could not seek to designated position");
    }

    return fread(dest, 1, bytes, _file);
}

//----------------------------------------------------------------------
size_t direct_file_reader::size() {
    fseek64(_file, 0, SEEK_END);
    auto result = ftell64(_file);
    if (result < 0) {
        throw std::runtime_error("Could not seek to the end of the file");
    }

    return static_cast<size_t>(result);
}

//----------------------------------------------------------------------
bool direct_file_reader::depleted() {
    return true;
}

//----------------------------------------------------------------------
direct_file_reader::~direct_file_reader() {
    fclose(_file);
}

//----------------------------------------------------------------------
std::shared_ptr<file_reader> direct_file_reader::open(const std::string& path) {
    return std::shared_ptr<file_reader>(new direct_file_reader(path));
}


//----------------------------------------------------------------------
direct_file_reader::direct_file_reader(const std::string& path)
    : _path(path)
{
    // Requires API 24
//    _file = fopen64(path.c_str(), "rb");
    _file = fopen(path.c_str(), "rb");
    if (!_file) {
        throw std::runtime_error("Could not open file for reading");
    }
}

//----------------------------------------------------------------------
std::shared_ptr<file_reader> direct_file_reader::clone()
{
    auto ret = new direct_file_reader(_path);
    return std::shared_ptr<file_reader>(ret);
}
