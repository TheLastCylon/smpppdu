// File  : replace_sm.hpp
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

#ifndef __SMPP_PDU_REPLACE_SM_HPP__
#define __SMPP_PDU_REPLACE_SM_HPP__

#include "smpp_pdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_replace_sm : public SMPP_PDU
  {
    public:
      PDU_replace_sm();
      PDU_replace_sm(const char           *b);
      PDU_replace_sm(const PDU_replace_sm &o);

      ~PDU_replace_sm();

      const static int   MinLength = 25;
      MessageId          message_id;
      NormalSmeAddress   source_addr;
      Time               schedule_delivery_time;
      Time               validity_period;
      RegisteredDelivery registered_delivery;
      SmDefaultMsgId     sm_default_msg_id;
      ShortMessage       short_message;

      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
} 

#endif

