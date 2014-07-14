// File  : endian_util.hpp
// Author: Dirk J. Botha <bothadj@gmail.com>
//
// This file is part of smpp_pdu library.
//
// The smpp_pdu library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The smpp_pdu library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the smpp_pdu library. If not, see <http://www.gnu.org/licenses/>.

#ifndef _ENDIAN_UTIL_
#define _ENDIAN_UTIL_

#include <algorithm>
#include <stdint.h>

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  // returns true if big endian or false if little endian.
  inline bool is_big_endian()
  {
    const long x = 1;
    return *(const char*)&x ? false : true;
  }

  //--------------------------------------------------------------------------------
  // Network to host ( i.e. Big Endian to Little Endian )
  inline uint32_t ntoh32(const uint32_t &n) { if(is_big_endian()) { return n; } return (n & 0x000000ff) << 24 | (n & 0x0000ff00) << 8 | (n & 0x00ff0000) >> 8 | (n & 0xff000000) >> 24; }
  inline uint16_t ntoh16(const uint16_t &n) { if(is_big_endian()) { return n; } return (n & 0x00ff) << 8 | (n & 0xff00) >> 8; }
  inline uint16_t ntoh16(const uint8_t  *b) { uint16_t t; std::copy(b, b+2, (uint8_t*)&t); return ntoh16(t); }
  inline uint32_t ntoh32(const uint8_t  *b) { uint32_t t; std::copy(b, b+4, (uint8_t*)&t); return ntoh32(t); }

  //--------------------------------------------------------------------------------
  // Host to Network ( i.e. Little Endian to Big Endian )
  inline uint32_t hton32(const uint32_t &n) { if(is_big_endian()) { return n; } return (n & 0x000000ff) << 24 | (n & 0x0000ff00) << 8 | (n & 0x00ff0000) >> 8 | (n & 0xff000000) >> 24; }
  inline uint16_t hton16(const uint16_t &n) { if(is_big_endian()) { return n; } return (n & 0x00ff) << 8 | (n & 0xff00) >> 8; }
}

#endif// _ENDIAN_UTIL_

