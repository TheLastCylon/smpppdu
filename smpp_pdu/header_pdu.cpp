// File  : header_pdu.cpp
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

#include "header_pdu.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_header::PDU_header(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_header::PDU_header(uint32_t c) :
    SMPP_PDU(CommandLength(MinLength),
             CommandId    (c),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_header::PDU_header(const PDU_header &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number) {}

  //--------------------------------------------------------------------------------
  PDU_header::~PDU_header() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_header::getBodyLength()
  {
    return 0;
  }

  //--------------------------------------------------------------------------------
  std::string PDU_header::encodeStandardParameters()
  {
    return std::string("");
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_header::decodeStandardParameters(const uint8_t *buff)
  {
    uint8_t  *sptr = const_cast<uint8_t*>(buff);
    sptr = commandLengthCheck(16, 0, sptr);
    return sptr;
  }
}
