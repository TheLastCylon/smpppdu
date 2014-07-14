// File  : alert_notification.cpp
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

#include "alert_notification.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_alert_notification::PDU_alert_notification() :
    SMPP_PDU(CommandLength(MinLength), CommandId(CommandId::AlertNotification), CommandStatus(CommandStatus::ESME_ROK), SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_alert_notification::PDU_alert_notification(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_alert_notification::PDU_alert_notification(const PDU_alert_notification& o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    source_addr_(o.source_addr_),
    esme_addr_  (o.esme_addr_  )
  {
  }

  //--------------------------------------------------------------------------------
  PDU_alert_notification::~PDU_alert_notification() {}

  //--------------------------------------------------------------------------------
  unsigned int PDU_alert_notification::getBodyLength()
  {
    return (source_addr_.length() + esme_addr_.length());
  }

  //--------------------------------------------------------------------------------
  std::string PDU_alert_notification::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)source_addr_
       << (std::string)esme_addr_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t* PDU_alert_notification::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t  len  = (uint32_t)command_length;
    uint8_t  *sptr = const_cast<uint8_t*>(buff);

    source_addr_   = sptr; sptr = commandLengthCheck(len, source_addr_.length(), sptr);
    esme_addr_     = sptr; sptr = commandLengthCheck(len, esme_addr_  .length(), sptr);

    return sptr;
  }
}

