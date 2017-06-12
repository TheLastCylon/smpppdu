// File  : cancel_broadcast_sm.hpp
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

#ifndef __SMPP_PDU_CANCEL_BROADCAST_SM_HPP__
#define __SMPP_PDU_CANCEL_BROADCAST_SM_HPP__

#include "smpppdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_cancel_broadcast_sm : public SMPP_PDU
  {
    public:
      PDU_cancel_broadcast_sm();
      PDU_cancel_broadcast_sm(const char                    *b);
      PDU_cancel_broadcast_sm(const PDU_cancel_broadcast_sm &o);

      ~PDU_cancel_broadcast_sm();

      const static int MinLength = 21;
      ServiceType      service_type_;
      MessageId        message_id_;
      NormalSmeAddress source_addr_;

      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
}

#endif

