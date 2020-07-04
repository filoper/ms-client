//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the continued Journey MMORPG client // 	Copyright (C)
//2015-2019  Daniel Allendorf, Ryan Payton						//
//																				//
//	This program is free software: you can redistribute it and/or modify
//// 	it under the terms of the GNU Affero General Public License as published by
//// 	the Free Software Foundation, either version 3 of the License, or // 	(at
//your option) any later version.											//
//																				//
//	This program is distributed in the hope that it will be useful, // 	but
//WITHOUT ANY WARRANTY; without even the implied warranty of				//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the // 	GNU Affero
//General Public License for more details.							//
//																				//
//	You should have received a copy of the GNU Affero General Public License
//// 	along with this program.  If not, see <https://www.gnu.org/licenses/>.
////
//////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "../Template/Point.h"
#include "PacketError.h"

namespace ms {
// A packet received from the server
// Contains reading functions
class InPacket {
public:
    // Construct a packet from an array of bytes
    InPacket(const int8_t *bytes, size_t length);

    // Check if there are more bytes available
    bool available() const;
    // Return the remaining length in bytes
    size_t length() const;
    // Skip a number of bytes (by increasing the offset)
    void skip(size_t count);

    // Read a byte and check if it is equal to one
    bool read_bool();
    // Read a byte
    int8_t read_byte();
    // Read a byte interpreted as a positive integer
    uint8_t read_ubyte();
    // Read a short
    int16_t read_short();
    // Read a short interpreted as a positive integer
    uint16_t read_ushort();
    // Read an int
    int32_t read_int();
    // Read an int interpreted as a positive integer
    uint32_t read_uint();
    // Read a long
    int64_t read_long();

    // Read a point
    Point<int16_t> read_point();

    // Read a string
    std::string read_string();
    // Read a fixed-length string
    std::string read_padded_string(uint16_t length);

    // Skip a byte
    void skip_bool();
    // Skip a byte
    void skip_byte();
    // Skip a short
    void skip_short();
    // Skip a int
    void skip_int();
    // Skip a long
    void skip_long();

    // Skip a point
    void skip_point();

    // Skip a string
    void skip_string();
    // Skip a fixed-length string
    void skip_padded_string(uint16_t length);

    // Inspect a byte and check if it is 1. Does not advance the buffer
    // position.
    bool inspect_bool();
    // Inspect a byte. Does not advance the buffer position.
    int8_t inspect_byte();
    // Inspect a short. Does not advance the buffer position.
    int16_t inspect_short();
    // Inspect an int. Does not advance the buffer position.
    int32_t inspect_int();
    // Inspect a long. Does not advance the buffer position.
    int64_t inspect_long();

    inline void print() {
        std::cout << "Recv: ";
        for (int i=0; i < top_; i++) {
            std::cout << (unsigned short)bytes_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    template<typename T>
    // Read a number and advance the buffer position
    T read() {
        size_t count = sizeof(T) / sizeof(int8_t);
        T all = 0;

        for (size_t i = 0; i < count; i++) {
            T val = static_cast<uint8_t>(bytes_[pos_]);
            all += val << (8 * i);

            skip(1);
        }

        return static_cast<T>(all);
    }

    // template<typename T>
    // T read() {
    //     if (top <= pos) {
    //         return 0;
    //     } if (sizeof(T) > (top - pos)) {
    //         return 0;
    //     }

    //     T val = *(T *)(bytes + pos);
    //     pos += sizeof(T);

    //     return val;
    // }

    template<typename T>
    // Read without advancing the buffer position
    T inspect() {
        size_t before = pos_;
        T value = read<T>();
        pos_ = before;

        return value;
    }

    const int8_t *bytes_;
    size_t top_;
    size_t pos_;
};

// template<>
// inline bool InPacket::read<bool>() {
//     return read<unsigned char>() != 0;
// }

// template<>
// inline std::string InPacket::read<std::string>() {
//     auto str_len = read<unsigned short>();

//     if (top <= pos) {
//         return "";
//     } if (str_len > (top - pos)) {
//         return "";
//     }

//     std::string str(reinterpret_cast<const char *>(bytes) + pos,
//                     str_len);
//     pos += str_len;

//     return str;
// }
}  // namespace ms