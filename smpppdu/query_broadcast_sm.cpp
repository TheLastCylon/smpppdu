// File  : query_broadcast_sm.cpp
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

#include "query_broadcast_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_query_broadcast_sm::PDU_query_broadcast_sm() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::QueryBroadcastSm),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_query_broadcast_sm::PDU_query_broadcast_sm(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_query_broadcast_sm::PDU_query_broadcast_sm(const PDU_query_broadcast_sm &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    message_id_ (o.message_id_ ),
    source_addr_(o.source_addr_) {}


  //--------------------------------------------------------------------------------
  PDU_query_broadcast_sm::~PDU_query_broadcast_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_query_broadcast_sm::getBodyLength()
  {
    return (
            message_id_ .length() +
            source_addr_.length()
           );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_query_broadcast_sm::encodeStandardParameters()
  {
    std::stringstream ss;
    ss << (std::string)message_id_
       << (std::string)source_addr_;
    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_query_broadcast_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = command_length.value();
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    message_id_  = sptr; sptr = commandLengthCheck(len, message_id_ .length(), sptr);
    source_addr_ = sptr; sptr = commandLengthCheck(len, source_addr_.length(), sptr);

    return sptr;
  }
}

