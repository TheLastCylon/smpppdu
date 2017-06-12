// File  : query_sm_resp.cpp
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

#include "query_sm_resp.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_query_sm_resp::PDU_query_sm_resp() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::QuerySmResp),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}


  //--------------------------------------------------------------------------------
  PDU_query_sm_resp::PDU_query_sm_resp(const PDU_query_sm_resp &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    message_id_   (o.message_id_   ),
    final_date_   (o.final_date_   ),
    message_state_(o.message_state_),
    error_code_   (o.error_code_   ) {}

  //--------------------------------------------------------------------------------
  PDU_query_sm_resp::PDU_query_sm_resp(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_query_sm_resp::~PDU_query_sm_resp() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_query_sm_resp::getBodyLength()
  {
    return
      (
       message_id_   .length() +
       final_date_   .length() +
       message_state_.length() +
       error_code_   .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_query_sm_resp::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)message_id_
       << (std::string)final_date_
       << (uint8_t)    message_state_
       << (uint8_t)    error_code_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_query_sm_resp::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    message_id_    = sptr; sptr = commandLengthCheck(len, message_id_   .length(), sptr);
    final_date_    = sptr; sptr = commandLengthCheck(len, final_date_   .length(), sptr);
    message_state_ = sptr; sptr = commandLengthCheck(len, message_state_.length(), sptr);
    error_code_    = sptr; sptr = commandLengthCheck(len, error_code_   .length(), sptr);

    return sptr;
  }
}

