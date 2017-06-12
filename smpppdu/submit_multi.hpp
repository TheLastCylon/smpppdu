// File  : submit_multi.hpp
// Author: Dirk J. Botha <bothadj@gmail.com>
//
// This file is part of smpppdu library.
//
// The smpppdu library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The smpppdu library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the smpppdu library. If not, see <http://www.gnu.org/licenses/>.

#ifndef __SMPP_PDU_SUBMIT_MULTI_HPP__
#define __SMPP_PDU_SUBMIT_MULTI_HPP__

#include "smpppdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_submit_multi : public SMPP_PDU
  {
    public:
      PDU_submit_multi();
      PDU_submit_multi(const char             *b);
      PDU_submit_multi(const PDU_submit_multi &o);

      ~PDU_submit_multi();

      const static int              MinLength = 31;
      ServiceType                   service_type;
      NormalSmeAddress              source_addr;
      MultiSmDestinationAddressList destination_addr;
      EsmClass                      esm_class;
      ProtocolId                    protocol_id;
      PriorityFlag                  priority_flag;
      Time                          schedule_delivery_time;
      Time                          validity_period;
      RegisteredDelivery            registered_delivery;
      ReplaceIfPresentFlag          replace_if_present_flag;
      DataCoding                    data_coding;
      SmDefaultMsgId                sm_default_msg_id;
      ShortMessage                  short_message;


      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
}

#endif

