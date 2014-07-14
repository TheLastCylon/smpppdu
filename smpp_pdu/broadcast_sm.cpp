// File  : broadcast_sm.cpp
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

#include "broadcast_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_broadcast_sm::PDU_broadcast_sm() :
    SMPP_PDU(CommandLength(MinLength), CommandId(CommandId::BroadcastSm), CommandStatus(CommandStatus::ESME_ROK), SequenceNumber::Min),
    defaultBroadcastAreaIdentifier_(true)
  {
    // The command_length is automatically updated
    //insertTLV     (BroadcastAreaIdentifier(0x00, 0, 0));
    //insertTLV     (BroadcastContentType   (0x00, 0x0000));
    //insert16bitTLV(TLV::broadcast_rep_num, 0x0000);
    //insertTLV     (BroadcastFrequencyInterval(0x00, 0x0000));
  }

  //--------------------------------------------------------------------------------
  PDU_broadcast_sm::PDU_broadcast_sm(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_broadcast_sm::PDU_broadcast_sm(const PDU_broadcast_sm &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    service_type_                  (o.service_type_                  ),
    source_addr_                   (o.source_addr_                   ),
    message_id_                    (o.message_id_                    ),
    priority_flag_                 (o.priority_flag_                 ),
    schedule_delivery_time_        (o.schedule_delivery_time_        ),
    validity_period_               (o.validity_period_               ),
    replace_if_present_flag_       (o.replace_if_present_flag_       ),
    data_coding_                   (o.data_coding_                   ),
    sm_default_msg_id_             (o.sm_default_msg_id_             ),
    defaultBroadcastAreaIdentifier_(o.defaultBroadcastAreaIdentifier_)
  {
    // insert the tlvs using their mutate operations.
    //insertTLV     (broadcastAreaIdentifier);
    //insertTLV     (broadcastContentType);
    //insert16bitTLV(TLV::broadcast_rep_num, broadcastRepNum);
    //insertTLV     (broadcastFrequencyInterval); 
  }

  //--------------------------------------------------------------------------------
  PDU_broadcast_sm::~PDU_broadcast_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_broadcast_sm::getBodyLength()
  {
    return
      (
       service_type_           .length() +
       source_addr_            .length() +
       message_id_             .length() +
       priority_flag_          .length() +
       schedule_delivery_time_ .length() +
       validity_period_        .length() +
       replace_if_present_flag_.length() +
       data_coding_            .length() +
       sm_default_msg_id_      .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_broadcast_sm::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string) service_type_
       << (std::string) source_addr_
       << (std::string) message_id_
       << (uint8_t)     priority_flag_
       << (std::string) schedule_delivery_time_
       << (std::string) validity_period_
       << (uint8_t)     replace_if_present_flag_
       << (uint8_t)     data_coding_
       << (uint8_t)     sm_default_msg_id_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_broadcast_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    service_type_            = sptr; sptr = commandLengthCheck(len, service_type_           .length(), sptr);
    source_addr_             = sptr; sptr = commandLengthCheck(len, source_addr_            .length(), sptr);
    message_id_              = sptr; sptr = commandLengthCheck(len, message_id_             .length(), sptr);
    priority_flag_           = sptr; sptr = commandLengthCheck(len, priority_flag_          .length(), sptr);
    schedule_delivery_time_  = sptr; sptr = commandLengthCheck(len, schedule_delivery_time_ .length(), sptr);
    validity_period_         = sptr; sptr = commandLengthCheck(len, validity_period_        .length(), sptr);
    replace_if_present_flag_ = sptr; sptr = commandLengthCheck(len, replace_if_present_flag_.length(), sptr);
    data_coding_             = sptr; sptr = commandLengthCheck(len, data_coding_            .length(), sptr);
    sm_default_msg_id_       = sptr; sptr = commandLengthCheck(len, sm_default_msg_id_      .length(), sptr);

    // TODO : Standard TLVs for this pdu type.
    // check mandatory TLVs are present (order is not important)
    //if     (!findTLV(TLV::broadcast_area_identifier   )) { throw MissingTlv(TLV::broadcast_area_identifier   );}
    //else if(!findTLV(TLV::broadcast_content_type      )) { throw MissingTlv(TLV::broadcast_content_type      );}
    //else if(!findTLV(TLV::broadcast_rep_num           )) { throw MissingTlv(TLV::broadcast_rep_num           );}
    //else if(!findTLV(TLV::broadcast_frequency_interval)) { throw MissingTlv(TLV::broadcast_frequency_interval);}

    return sptr;
  }
}

