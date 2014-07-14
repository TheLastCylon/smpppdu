// File  : tlv_list.cpp
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

#include "tlv_list.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  void TLVList::add(const TLV *tlv)
  {
    add(*tlv);
  }

  //--------------------------------------------------------------------------------
  void TLVList::add(const TLV &tlv)
  {
    tlvlist.push_back(new TLV(tlv));
  }

  //--------------------------------------------------------------------------------
  void TLVList::add(const uint16_t &tag, const std::string &value)
  {
    add(tag, value.size(), value);
  }

  //--------------------------------------------------------------------------------
  void TLVList::add(const uint16_t &tag, const uint16_t &length, const std::string &value)
  {
    tlvlist.push_back(new TLV(tag, length, value));
  }

  //--------------------------------------------------------------------------------
  void TLVList::add(const uint16_t &tag, const uint16_t &length, const uint8_t *value)
  {
    tlvlist.push_back(new TLV(tag, length, value));
  }

  //--------------------------------------------------------------------------------
  const TLV *TLVList::get(const uint16_t &tag)
  {
    TLV *retval = NULL;

    for(unsigned i = 0; i < tlvlist.size(); ++i) {
      if(tag == tlvlist[i]->getTag()) {
        retval = tlvlist[i];
        break;
      }
    }

    return retval;
  }

  //--------------------------------------------------------------------------------
  void TLVList::decode(const size_t pduLen, const size_t startpos, const uint8_t *p)
  {
    size_t   sp  = startpos;
    uint8_t *ptr = const_cast<uint8_t*>(p);

//    std::cout << "TLV Start pos: " << sp << std::endl;
    while(sp < pduLen && ((pduLen - sp) > 5))
    {
      tlvlist.push_back(new TLV(ptr));
      size_t lastTLVsize = tlvlist[tlvlist.size()-1]->encodedLength(); //std::cout << "lastTLVsize: "        << lastTLVsize << std::endl;
      sp  += lastTLVsize;                                              //std::cout << "Next Tlv start pos: " << sp          << std::endl;
      ptr += lastTLVsize;
    }
  }
}

