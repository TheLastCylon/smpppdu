// File  : replace_sm.cpp
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

#include "replace_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_replace_sm::PDU_replace_sm() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::ReplaceSm),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_replace_sm::PDU_replace_sm(const PDU_replace_sm &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    message_id            (o.message_id            ),
    source_addr           (o.source_addr           ),
    schedule_delivery_time(o.schedule_delivery_time),
    validity_period       (o.validity_period       ),
    registered_delivery   (o.registered_delivery   ),
    sm_default_msg_id     (o.sm_default_msg_id     ),
    short_message         (o.short_message         ) {}

  //--------------------------------------------------------------------------------
  PDU_replace_sm::PDU_replace_sm(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_replace_sm::~PDU_replace_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_replace_sm::getBodyLength()
  {
    return
      (
       message_id            .length() +
       source_addr           .length() +
       schedule_delivery_time.length() +
       validity_period       .length() +
       registered_delivery   .length() +
       sm_default_msg_id     .length() +
       short_message         .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_replace_sm::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)message_id
       << (std::string)source_addr
       << (std::string)schedule_delivery_time
       << (std::string)validity_period
       << (uint8_t)    registered_delivery
       << (uint8_t)    sm_default_msg_id
       << (std::string)short_message;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_replace_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    message_id             = sptr; sptr = commandLengthCheck(len, message_id            .length(), sptr);
    source_addr            = sptr; sptr = commandLengthCheck(len, source_addr           .length(), sptr);
    schedule_delivery_time = sptr; sptr = commandLengthCheck(len, schedule_delivery_time.length(), sptr);
    validity_period        = sptr; sptr = commandLengthCheck(len, validity_period       .length(), sptr);
    registered_delivery    = sptr; sptr = commandLengthCheck(len, registered_delivery   .length(), sptr);
    sm_default_msg_id      = sptr; sptr = commandLengthCheck(len, sm_default_msg_id     .length(), sptr);
    short_message          = sptr; sptr = commandLengthCheck(len, short_message         .length(), sptr);

    return sptr;
  }
}

