/**
 * @file DataStream.cc
 * @author Nicholas Burley (nick.burley@protonmail.com)
 * @brief 
 * @version 1.0
 * @date 2021-03-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "DataStream.hh"


DataStream::DataStream(const DataBuffer& buffer) {
    _buffer = buffer;
}


DataStream::DataStream() {}


DataStream::DataStream(const std::uint64_t size) {
    _buffer.reserve(size);
}


DataStream::DataStream(const char* buffer, std::uint32_t size) {
    _buffer = DataBuffer(buffer, buffer + size);
}


std::string DataStream::ToString() {
    return std::string(begin(), end());
}


std::ostream& operator<<(std::ostream& os, const DataStream& ds) {
    os << ds.ToBuffer().data();
    return os;
}


void DataStream::Goto(std::uint64_t stream_pos) {
    if (stream_pos < _buffer.size() && stream_pos >= 0) {
        _streampos = stream_pos;
    }
}


void DataStream::Goto_Start() {
    _streampos = 0ULL;
}


void DataStream::Goto_End() {
    _streampos = _buffer.size();
}


std::uint8_t DataStream::ReadByte() {
    std::uint8_t byte = _buffer.at(_streampos);
    _streampos++;
    return byte;    
}


std::uint16_t DataStream::ReadUInt16() {
    DataBuffer buf = Read(2);
    std::uint16_t i = buf[0] | (buf[1] << 8);
    _streampos += 2;
    return i;
}

std::uint32_t DataStream::ReadUInt32() 
{
    DataBuffer buf = Read(4);
    std::uint32_t i = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
    _streampos += 4;
    return i;
}


std::uint64_t DataStream::ReadUInt64() 
{
    DataBuffer buf = Read(8);
    std::uint64_t i = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) | (buf[4] << 32) | (buf[5] << 40) | (buf[6] << 48) | (buf[7] << 56);
    _streampos += 8;
    return i;
}


std::string DataStream::ReadString(std::uint64_t len) {
    auto dta = Read(len);
    return std::string(dta.begin(), dta.end());
}


void DataStream::WriteByte(std::uint8_t data) {
    _buffer.insert(_buffer.begin()+_streampos, data);
    _streampos++;
}


void DataStream::WriteUInt16(std::uint16_t data) {
    unsigned char* rawData = reinterpret_cast<unsigned char*>(&data);
    DataBuffer buf = DataBuffer(rawData, rawData+2);
    Write(buf);
}


void DataStream::WriteUInt32(std::uint32_t data) {
    unsigned char* rawData = reinterpret_cast<unsigned char*>(&data);
    DataBuffer buf = DataBuffer(rawData, rawData+4);
    Write(buf);
}


void DataStream::WriteUInt64(std::uint64_t data) {
    unsigned char* rawData = reinterpret_cast<unsigned char*>(&data);
    DataBuffer buf = DataBuffer(rawData, rawData+8);
    Write(buf);
}


void DataStream::WriteString(const std::string& str) {
    DataBuffer buf(str.begin(), str.end());
    Write(buf);
}


void DataStream::Clear() {
    _buffer.clear();
    _streampos = 0ULL;  
}


std::uint8_t DataStream::operator[](size_t idx) {
    return _buffer[idx];
}


void DataStream::Write(DataBuffer data) {
    _buffer.insert(_buffer.begin()+_streampos, data.begin(), data.end());
    _streampos += data.size();
}


void DataStream::Write(const char* data, std::uint64_t len) {
    auto intBuf = DataBuffer(data, data + len);
    Write(intBuf);
}


DataStream::DataBuffer DataStream::Read(std::uint64_t len) {
    auto ret = Read(_streampos, len);
    return ret;
}


DataStream::DataBuffer DataStream::Read(std::uint64_t pos, std::uint64_t len) {
    std::uint64_t readCount = 0;
    if (pos < 0 || pos >= _buffer.size()) {
        return DataBuffer();
    }

    readCount = len;
    if ((pos + len) > _buffer.size()) {
        // Cannot read past end of buffer, only read up to the last possible byte
        readCount = _buffer.size() - pos;
    }
    DataBuffer ret = DataBuffer(_buffer.begin()+pos, (_buffer.begin()+pos) + readCount);
    return ret;
}
