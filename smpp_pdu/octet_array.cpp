// File  : octet_array.cpp 
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

#include "octet_array.hpp"

namespace smpp_pdu
{
  unsigned octet_array::raw_assign(const uint8_t* p) 
  {
    unsigned i = 0;
    while(p[i] != '\0') { ++i; }
    return raw_assign(p, i);
  }

  unsigned octet_array::raw_assign(const uint8_t* p, unsigned len) 
  {
    _len = len;
    _v   = new uint8_t[_len];
    memcpy(_v, p, _len);
    return _len;
  }

  bool octet_array::operator==(const octet_array &rhs)
  {
    bool retval = false;
    if(_len == rhs._len && _v == rhs._v ) {
      retval = true;
    }
    return retval;
  }

  bool octet_array::operator!=(const octet_array &rhs)
  {
    return !operator==(rhs);
  }

  octet_array& octet_array::operator=(const uint8_t* p)
  {
    if(p) {
      if(_v != p) {
        if(_v) { delete [] _v; }
        raw_assign(p);
      }
    }
    return *this;
  }

  octet_array& octet_array::operator=(const octet_array& rhs)
  {
    if(operator!=(rhs)) {
      if(_v && _v != rhs._v) { delete [] _v; }
      raw_assign(rhs._v, rhs._len);
    }
    return *this;
  }

  octet_array& octet_array::operator=(const std::string &p)
  {
    if(_v) { delete [] _v; }
    raw_assign(reinterpret_cast<const uint8_t*>(p.c_str()), p.size());
    return *this;
  }
}

