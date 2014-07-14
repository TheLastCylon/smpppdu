// File  : tlv.cpp
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

#include "tlv.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  std::string TLV::encode()
  {
    std::stringstream ss;

    ss << int16str(smpp_pdu::hton16(tag))
       << int16str(smpp_pdu::hton16(length))
       << std::string(reinterpret_cast<char*>(value), length);

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  void TLV::decode(const uint8_t *p)
  {
    uint8_t *tptr = const_cast<uint8_t*>(p);

    if(value != NULL) {
      delete [] value;
    }

    tag    = ntoh16(tptr); tptr += sizeof(uint16_t);
    length = ntoh16(tptr); tptr += sizeof(uint16_t);
    value  = new uint8_t[length];

//    std::cout << "tag :["     << tag
//              << "] length:[" << length
//              << "] value :[";
//    for(unsigned i = 0; i <= length; ++i)
//      std::cout << value[i];

//    std::cout << std::endl;

    std::copy(tptr, tptr+length, value);
  }
};
