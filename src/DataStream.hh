/**
 * @file DataStream.hh
 * @author Nicholas Burley (nick.burley@protonmail.com)
 * @brief 
 * @version 1.0
 * @date 2021-03-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <vector>
#include <cstdint>
#include <ostream>


/**
 * @brief A helper class that ingests a vector<uchar> to allow stream-like reading/writting
 * 
 */
class DataStream {
    //TODO: Use const char* buffers instead, as we wish to remove the extra STL overhead
    using DataBuffer = std::vector<std::uint8_t>;

public:
    DataStream();
    DataStream(const std::uint64_t size);
    DataStream(const DataBuffer& buffer);
    DataStream(const char* buffer, std::uint32_t size);

    std::uint8_t operator[](size_t idx);

    const DataBuffer ToBuffer() const { return _buffer; }
    DataBuffer ToBuffer() { return _buffer; }
    std::string ToString();

    friend std::ostream& operator<<(std::ostream& os, const DataStream& ds);

    void Goto(std::uint64_t stream_pos);
    void Goto_Start();
    void Goto_End();

    std::uint8_t ReadByte();
    std::uint16_t ReadUInt16();
    std::uint32_t ReadUInt32();
    std::uint64_t ReadUInt64();
    //TODO: Add ReadFloat and ReadDouble
    std::string ReadString(std::uint64_t len);

    void WriteByte(std::uint8_t data);
    void WriteUInt16(std::uint16_t data);
    void WriteUInt32(std::uint32_t data);
    void WriteUInt64(std::uint64_t data);
    //TODO: Add WriteFloat and WriteDouble
    void WriteString(const std::string& str);

    void Clear();
    void Write(DataBuffer data);
    void Write(const char* data, std::uint64_t len);
    DataBuffer Read(std::uint64_t len);
    DataBuffer Read(std::uint64_t pos, std::uint64_t len);
    std::uint64_t Size() { return _buffer.size(); }

    DataBuffer::iterator begin() { return _buffer.begin(); }
    DataBuffer::iterator end() { return _buffer.end(); }
    DataBuffer::const_iterator begin() const { return _buffer.begin(); }
    DataBuffer::const_iterator end() const { return _buffer.end(); }
private:

    std::uint64_t _streampos = 0ULL;
    DataBuffer _buffer;
};