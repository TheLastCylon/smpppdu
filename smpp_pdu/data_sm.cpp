// File  : data_sm.cpp
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

#include "data_sm.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_data_sm::PDU_data_sm() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId(CommandId::DataSm), 
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_data_sm::PDU_data_sm(const PDU_data_sm &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    service_type_       (o.service_type_       ),
    source_addr_        (o.source_addr_        ),
    destination_addr_   (o.destination_addr_   ),
    esm_class_          (o.esm_class_          ),
    registered_delivery_(o.registered_delivery_),
    data_coding_        (o.data_coding_        )
  {}

  //--------------------------------------------------------------------------------
  PDU_data_sm::PDU_data_sm(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_data_sm::~PDU_data_sm() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_data_sm::getBodyLength()
  {
    return
      (
       service_type_       .length() +
       source_addr_        .length() +
       destination_addr_   .length() +
       esm_class_          .length() +
       registered_delivery_.length() +
       data_coding_        .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_data_sm::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)service_type_
       << (std::string)source_addr_
       << (std::string)destination_addr_
       << (uint8_t)    esm_class_
       << (uint8_t)    registered_delivery_
       << (uint8_t)    data_coding_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_data_sm::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    service_type_        = sptr; sptr = commandLengthCheck(len, service_type_       .length(), sptr);
    source_addr_         = sptr; sptr = commandLengthCheck(len, source_addr_        .length(), sptr);
    destination_addr_    = sptr; sptr = commandLengthCheck(len, destination_addr_   .length(), sptr);
    esm_class_           = sptr; sptr = commandLengthCheck(len, esm_class_          .length(), sptr);
    registered_delivery_ = sptr; sptr = commandLengthCheck(len, registered_delivery_.length(), sptr);
    data_coding_         = sptr; sptr = commandLengthCheck(len, data_coding_        .length(), sptr);

    return sptr;
  }
}

