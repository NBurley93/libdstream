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
/**

MIT License

Copyright (c) 2021 Nicholas Burley

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

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