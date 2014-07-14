// File  : query_sm.hpp
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

#ifndef __SMPP_PDU_QUERY_SM_HPP__
#define __SMPP_PDU_QUERY_SM_HPP__

#include "smpp_pdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_query_sm : public SMPP_PDU
  {
    public:
      PDU_query_sm();
      PDU_query_sm(const char         *b);
      PDU_query_sm(const PDU_query_sm &o);

      ~PDU_query_sm();

      const static int MinLength = 20;
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

