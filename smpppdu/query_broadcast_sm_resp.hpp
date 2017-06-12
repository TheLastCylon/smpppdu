// File  : query_broadcast_sm_resp.hpp
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

#ifndef __SMPP_PDU_QUERY_BROADCAST_SM_RESP_HPP__
#define __SMPP_PDU_QUERY_BROADCAST_SM_RESP_HPP__

#include "smpppdu.hpp"
#include "standard_parameters.hpp"

//TODO : standard TLVs for this PDU Type

namespace smpp_pdu
{
  class PDU_querybroadcast_sm_resp : public SMPP_PDU
  {
    public:
      PDU_querybroadcast_sm_resp();
      PDU_querybroadcast_sm_resp(const char                       *b);
      PDU_querybroadcast_sm_resp(const PDU_querybroadcast_sm_resp &o);

      ~PDU_querybroadcast_sm_resp();

      const static int MinLength = 18;                  // not including mandatory TLVs
      MessageId        message_id_;
      bool             defaultBroadcastAreaIdentifier_; // true if the BroadcastAreaIdentifier is set from the default constructor, in which case it should be replaced.

      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
}

      //MessageState     message_state_;
      /*
      void broadcast_area_identifier(const BroadcastAreaIdentifier& p)
      {
        if(defaultBroadcastAreaIdentifier_) {
          removeTLV(TLV::broadcast_area_identifier);
          defaultBroadcastAreaIdentifier_ = false;
        }
        this->insertBeforeTLV(new TLV(p), TLV::broadcast_area_success);
      }

      void broadcast_area_success(const BroadcastAreaSuccess& p)
      {
        removeTLV(TLV::broadcast_area_success);
        this->insertAfterTLV(new TLV(p), TLV::broadcast_area_identifier);
      }

      const TLVList       broadcast_area_identifier() const { return findTLVList(TLV::broadcast_area_identifier); }

      const BroadcastAreaSuccess& broadcast_area_success() const
      {
        const TLV* t = findTLV(TLV::broadcast_area_success);
        if(!t) throw smpp_pdu::MissingTlv(TLV::broadcast_area_success);
        return *static_cast<const BroadcastAreaSuccess*>(t);
      }
      */

#endif

