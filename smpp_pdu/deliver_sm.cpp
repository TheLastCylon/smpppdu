// File  : deliver_sm.cpp
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

#include <iostream>
#include "deliver_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_deliver_sm::PDU_deliver_sm() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::DeliverSm),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_deliver_sm::PDU_deliver_sm(const PDU_deliver_sm& o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    service_type            (o.service_type           ),
    source_addr             (o.source_addr            ),
    destination_addr        (o.destination_addr       ),
    esm_class               (o.esm_class              ),
    protocol_id             (o.protocol_id            ),
    priority_flag           (o.priority_flag          ),
    schedule_delivery_time  (o.schedule_delivery_time ),
    validity_period         (o.validity_period        ),
    registered_delivery     (o.registered_delivery    ),
    replace_if_present_flag (o.replace_if_present_flag),
    data_coding             (o.data_coding            ),
    sm_default_msg_id       (o.sm_default_msg_id      ),
    short_message           (o.short_message          ) {}

  //--------------------------------------------------------------------------------
  PDU_deliver_sm::PDU_deliver_sm(const char* b) : SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_deliver_sm::~PDU_deliver_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_deliver_sm::getBodyLength()
  {
    return
      (
       service_type           .length() +
       source_addr            .length() +
       destination_addr       .length() +
       esm_class              .length() +
       protocol_id            .length() +
       priority_flag          .length() +
       schedule_delivery_time .length() +
       validity_period        .length() +
       registered_delivery    .length() +
       replace_if_present_flag.length() +
       data_coding            .length() +
       sm_default_msg_id      .length() +
       short_message          .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_deliver_sm::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string) service_type
       << (std::string) source_addr
       << (std::string) destination_addr
       << (uint8_t)     esm_class
       << (uint8_t)     protocol_id
       << (uint8_t)     priority_flag
       << (std::string) schedule_delivery_time
       << (std::string) validity_period
       << (uint8_t)     registered_delivery
       << (uint8_t)     replace_if_present_flag
       << (uint8_t)     data_coding
       << (uint8_t)     sm_default_msg_id
       << (std::string) short_message;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_deliver_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    service_type            = sptr; sptr = commandLengthCheck(len, service_type           .length(), sptr);
    source_addr             = sptr; sptr = commandLengthCheck(len, source_addr            .length(), sptr);
    destination_addr        = sptr; sptr = commandLengthCheck(len, destination_addr       .length(), sptr);
    esm_class               = sptr; sptr = commandLengthCheck(len, esm_class              .length(), sptr);
    protocol_id             = sptr; sptr = commandLengthCheck(len, protocol_id            .length(), sptr);
    priority_flag           = sptr; sptr = commandLengthCheck(len, priority_flag          .length(), sptr);
    schedule_delivery_time  = sptr; sptr = commandLengthCheck(len, schedule_delivery_time .length(), sptr);
    validity_period         = sptr; sptr = commandLengthCheck(len, validity_period        .length(), sptr);
    registered_delivery     = sptr; sptr = commandLengthCheck(len, registered_delivery    .length(), sptr);
    replace_if_present_flag = sptr; sptr = commandLengthCheck(len, replace_if_present_flag.length(), sptr);
    data_coding             = sptr; sptr = commandLengthCheck(len, data_coding            .length(), sptr);
    sm_default_msg_id       = sptr; sptr = commandLengthCheck(len, sm_default_msg_id      .length(), sptr);
    short_message           = sptr; sptr = commandLengthCheck(len, short_message          .length(), sptr);

    return sptr;
  }
}

