// File  : lexical_cast.hpp
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

#ifndef __SMPP_PDU_LEXICAL_CAST_HPP__
#define __SMPP_PDU_LEXICAL_CAST_HPP__

#include <sstream>

namespace smpp_pdu
{
  template<typename T> struct HexVal
  {
    explicit HexVal(const T v) : val(v) {}
    const T val;
  };

  template<typename T> std::ostream& operator<<(std::ostream& s, const HexVal<T> v)
  {
    s << std::showbase << std::hex << v.val << std::dec;
    return s;
  }

  template<typename To, typename From> To lexical_cast(const From& f)
  {
    std::stringstream ss;
    ss << f;
    To t;
    ss >> t;
    return t;
  }
}

#endif

