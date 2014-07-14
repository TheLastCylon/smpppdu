// File  : cancel_sm.cpp
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

#include "cancel_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_cancel_sm::PDU_cancel_sm() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::CancelSm),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_cancel_sm::PDU_cancel_sm(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_cancel_sm::PDU_cancel_sm(const PDU_cancel_sm &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    service_type_    (o.service_type_    ),
    message_id_      (o.message_id_      ),
    source_addr_     (o.source_addr_     ),
    destination_addr_(o.destination_addr_) {}

  //--------------------------------------------------------------------------------
  PDU_cancel_sm::~PDU_cancel_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_cancel_sm::getBodyLength()
  {
    return
      (
       service_type_    .length() +
       message_id_      .length() +
       source_addr_     .length() +
       destination_addr_.length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_cancel_sm::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)service_type_
       << (std::string)message_id_
       << (std::string)source_addr_
       << (std::string)destination_addr_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_cancel_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    service_type_    = sptr; sptr = commandLengthCheck(len, service_type_    .length(), sptr);
    message_id_      = sptr; sptr = commandLengthCheck(len, message_id_      .length(), sptr);
    source_addr_     = sptr; sptr = commandLengthCheck(len, source_addr_     .length(), sptr);
    destination_addr_= sptr; sptr = commandLengthCheck(len, destination_addr_.length(), sptr);

    return sptr;
  }
}

