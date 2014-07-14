// File  : outbind.cpp
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

#include "outbind.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_outbind::PDU_outbind() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::Outbind),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_outbind::PDU_outbind(const PDU_outbind &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    system_id_(o.system_id_),
    password_ (o.password_ ) {}

  //--------------------------------------------------------------------------------
  PDU_outbind::PDU_outbind(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_outbind::~PDU_outbind() {} 

  //--------------------------------------------------------------------------------
  unsigned int PDU_outbind::getBodyLength()
  {
    return
      (
       system_id_.length() +
       password_ .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_outbind::encodeStandardParameters()
  {
    std::stringstream ss;
    ss << (std::string)system_id_
       << (std::string)password_;
    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_outbind::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    system_id_ = sptr; sptr = commandLengthCheck(len, system_id_.length(), sptr);
    password_  = sptr; sptr = commandLengthCheck(len, password_ .length(), sptr);

    return sptr;
  }
}

