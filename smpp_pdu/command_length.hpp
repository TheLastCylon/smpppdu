// File  : command_length.hpp
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

#ifndef __SMPP_PDU_COMMAND_LENGTH_HPP__
#define __SMPP_PDU_COMMAND_LENGTH_HPP__

#include <algorithm>
#include <cstring>
#include <string>
#include "endian_util.hpp"

namespace smpp_pdu
{
  class CommandLength
  {
    public:
      CommandLength() {};
      CommandLength(const uint32_t    &p) : val_(p) {};
      CommandLength(const char        *p) : val_(decode(p)) {};
      CommandLength(const std::string &p) : val_(decode(p.c_str())) {};

      CommandLength& operator += (int             i) { val_ += i; return *this; }
      CommandLength& operator  = (const uint32_t &p) { val_  = p; return *this; } // Assign a 32 bit integer.

      operator uint32_t () const { return val_; }

      uint32_t value() { return val_; }

      static uint32_t decode(const char* b) { uint32_t x; memcpy(&x, &b[0], sizeof x); return smpp_pdu::ntoh32(x); }

    private:
      uint32_t val_;
  };
}

#endif

