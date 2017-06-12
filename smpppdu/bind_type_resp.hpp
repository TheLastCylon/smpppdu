// File  : bind_type_resp.hpp
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

#ifndef __SMPP_PDU_BIND_TYPE_RESP_HPP__
#define __SMPP_PDU_BIND_TYPE_RESP_HPP__

#include "smpppdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_bind_type_resp : public SMPP_PDU
  {
    public:
      PDU_bind_type_resp();
      PDU_bind_type_resp(uint32_t                  c);
      PDU_bind_type_resp(const char               *b);
      PDU_bind_type_resp(const PDU_bind_type_resp &o);

      ~PDU_bind_type_resp();

      SystemId system_id_;

      const static int MinLength = 17;

      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
}

#endif

