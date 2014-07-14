// File  : submit_multi_resp.cpp
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

#include "submit_multi_resp.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_submit_multi_resp::PDU_submit_multi_resp() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::SubmitMultiResp),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_submit_multi_resp::PDU_submit_multi_resp(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_submit_multi_resp:: PDU_submit_multi_resp(const PDU_submit_multi_resp &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    message_id_        (o.message_id_        ),
    no_unsuccess_      (o.no_unsuccess_      ),
    unsuccess_sme_list_(o.unsuccess_sme_list_)
  {
  }

  //--------------------------------------------------------------------------------
  PDU_submit_multi_resp::~PDU_submit_multi_resp() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_submit_multi_resp::getBodyLength()
  {
    return (
            message_id_        .length() +
            no_unsuccess_      .length() +
            unsuccess_sme_list_.length()
           );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_submit_multi_resp::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)message_id_
       << (uint8_t)    no_unsuccess_
       << (std::string)unsuccess_sme_list_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_submit_multi_resp::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    message_id_         = sptr; sptr = commandLengthCheck(len, message_id_        .length(), sptr);
    no_unsuccess_       = sptr; sptr = commandLengthCheck(len, no_unsuccess_      .length(), sptr);

    unsuccess_sme_list_.raw_assign((uint8_t)no_unsuccess_, sptr);
    sptr = commandLengthCheck(len, unsuccess_sme_list_.length(), sptr);

    return sptr;
  }
}

