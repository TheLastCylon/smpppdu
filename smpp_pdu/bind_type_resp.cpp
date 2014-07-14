// File  : bind_type_resp.cpp
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

#include "bind_receiver_resp.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_bind_type_resp::PDU_bind_type_resp() :
    SMPP_PDU(CommandLength(MinLength), CommandId(CommandId::BindReceiverResp), CommandStatus(CommandStatus::ESME_ROK), SequenceNumber::Min)
  {}

  //--------------------------------------------------------------------------------
  PDU_bind_type_resp::PDU_bind_type_resp(uint32_t c) :
    SMPP_PDU(CommandLength(MinLength),
             CommandId    (c),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min)
  {
  }

  //--------------------------------------------------------------------------------
  PDU_bind_type_resp::PDU_bind_type_resp(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_bind_type_resp::PDU_bind_type_resp(const PDU_bind_type_resp &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    system_id_(o.system_id_)
  {}

  //--------------------------------------------------------------------------------
  PDU_bind_type_resp::~PDU_bind_type_resp() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_bind_type_resp::getBodyLength()
  {
    return system_id_.length();
  }

  //--------------------------------------------------------------------------------
  std::string PDU_bind_type_resp::encodeStandardParameters()
  {
    return (std::string)system_id_;
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_bind_type_resp::decodeStandardParameters(const uint8_t* buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    system_id_ = sptr; sptr = commandLengthCheck(len, system_id_.length(), sptr);

    return sptr;
  }
}
