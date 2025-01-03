#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

namespace brcpp
{
    class file_reader
    {
    public:
        virtual size_t read(uint8_t* dest, size_t position, size_t bytes) = 0;
        virtual size_t size() = 0;
        virtual bool depleted() = 0;
        virtual std::shared_ptr<file_reader> clone() = 0;
        virtual ~file_reader() = default;
    };
}
