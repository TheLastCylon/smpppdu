// File  : tlv_list.hpp
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

#ifndef __SMPP_PDU_TLVLIST_HPP__
#define __SMPP_PDU_TLVLIST_HPP__

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <stdint.h>
#include "endian_util.hpp"
#include "tlv.hpp"

namespace smpp_pdu
{
  class TLVList
  {
    public:
      TLVList() {}
      ~TLVList()
      {
        for(unsigned i = 0; i < tlvlist.size(); ++i) {
          delete tlvlist[i];
        }
        tlvlist.clear();
      }

      void       add   (const TLV      *tlv);
      void       add   (const TLV      &tlv);
      void       add   (const uint16_t &tag, const std::string &value);
      void       add   (const uint16_t &tag, const uint16_t &length, const std::string &value);
      void       add   (const uint16_t &tag, const uint16_t &length, const uint8_t     *value);
      const TLV *get   (const uint16_t &tag);
      void       decode(const size_t pduLen, const size_t startpos, const uint8_t *p);

      size_t size()
      {
        return tlvlist.size();
      }

      size_t length()
      {
        size_t retval = 0;
        for(unsigned i = 0; i < tlvlist.size(); ++i) {
          retval += tlvlist[i]->encodedLength();
        }
        return retval;
      }

      operator std::string()
      {
        std::stringstream ss;
        for(unsigned i = 0; i < tlvlist.size(); ++i) {
          ss << (std::string)(*tlvlist[i]);
        }
        return ss.str();
      }

    protected:
    private:
      std::vector<TLV*> tlvlist;
  };
}

#endif

