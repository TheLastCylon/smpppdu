// File  : smpppdu.cpp
// Author: Dirk J. Botha <bothadj@gmail.com>
//
// This file is part of smpppdu library.
//
// The smpppdu library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The smpppdu library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the smpppdu library. If not, see <http://www.gnu.org/licenses/>.

#include "smpppdu.hpp" 

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  std::string SMPP_PDU::encode()
  {
    std::string       retval = "";
    std::stringstream ss;

    ss << int32str(smpp_pdu::hton32((uint32_t)command_id))
       << int32str(smpp_pdu::hton32((uint32_t)command_status))
       << int32str(smpp_pdu::hton32((uint32_t)sequence_number))
       << encodeStandardParameters()
       << (std::string)tlvlist;

    command_length = ((ss.str()).size()+sizeof(uint32_t));
    retval         = int32str(smpp_pdu::hton32((uint32_t)command_length)) + ss.str();

    return retval;
  }

  //--------------------------------------------------------------------------------
  void SMPP_PDU::decode(const uint8_t *buff)
  {
    size_t totalLength  = (uint32_t)command_length;
    uint8_t *ptr        = const_cast<uint8_t *>(buff);
    decodeLen           = 16;
    ptr                += decodeLen;
    ptr                 = decodeStandardParameters(ptr);
    size_t tlv_length   = totalLength - decodeLen;

//    std::cout << "totalLength: " << totalLength << std::endl;
//    std::cout << "decodeLen  : " << decodeLen   << std::endl;
//    std::cout << "tlv_length : " << tlv_length  << std::endl;

    if(tlv_length > 0) {
      if(tlv_length >= 5) { // you need at least 5 octects to have a valid TLV!
        tlvlist.decode(totalLength, decodeLen, ptr);
      } else {
        // TODO: Throw an error. This should not happen.
      }
    }
  }

  //--------------------------------------------------------------------------------
  uint8_t *SMPP_PDU::commandLengthCheck(uint32_t el, size_t fl, uint8_t* cp)
  {
    decodeLen += fl;
    if(decodeLen > el) throw InvalidCommandLength(el, fl, "");
    cp += fl;
    return cp;
  }
}

