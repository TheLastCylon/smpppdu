// File  : sequence_number.hpp
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

#ifndef __SMPP_PDU_SEQUENCE_NUMBER_HPP__
#define __SMPP_PDU_SEQUENCE_NUMBER_HPP__

#include <cstring>
#include <string>
#include "error.hpp"
#include "endian_util.hpp"

namespace smpp_pdu
{
  class SequenceNumber
  {
    public:
      enum {
        Min = 0x00000001,
        Max = 0x7fffffff
      }; // Sequence number limits.

      //--------------------------------------------------------------------------------
      SequenceNumber(const uint32_t    &p, bool allow_0 = false) : val_(assign(p                , allow_0)) {}
      SequenceNumber(const char        *p, bool allow_0 = false) : val_(assign(decode(p)        , allow_0)) {}
      SequenceNumber(const std::string &p, bool allow_0 = false) : val_(assign(decode(p.c_str()), allow_0)) {}

      //--------------------------------------------------------------------------------
      static uint32_t assign(const uint32_t& seq_number, bool allow_0 = false) // Sets a sequence number.
      {
        if((seq_number <= Max && seq_number > 0) || (seq_number == 0 && allow_0 == true)) {
          return seq_number;
        } else {
          throw Invalid(seq_number);
        }
      }

      //--------------------------------------------------------------------------------
      SequenceNumber& operator ++()
      {
        if(val_ < Max) { ++val_; } else { val_ = Min; }
        return *this;
      }

      //--------------------------------------------------------------------------------
      SequenceNumber  operator ++(int)
      {
        SequenceNumber t = *this;
        if(val_ < Max) { ++val_; } else { val_ = Min; }
        return t;
      }

      //--------------------------------------------------------------------------------
      operator uint32_t() const
      {
        return val_;
      }

      //--------------------------------------------------------------------------------
      SequenceNumber& operator = (const uint32_t &p) // Assign a 32 bit integer.
      {
        val_ = p; return *this;
      }

      //--------------------------------------------------------------------------------
      uint32_t value()
      {
        return val_;
      }

      //--------------------------------------------------------------------------------
      static uint32_t decode(const char* b)
      {
        uint32_t x;
        memcpy(&x, &b[12], sizeof x);
        return smpp_pdu::ntoh32(x);
      }

      //--------------------------------------------------------------------------------
      struct Invalid : public Error
      {
        Invalid(const uint32_t);
      };
    private:
      uint32_t val_;
      SequenceNumber();
  };
}

#endif

