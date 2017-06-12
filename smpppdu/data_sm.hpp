// File  : data_sm.hpp
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

#ifndef __SMPP_PDU_DATA_SM_HPP__
#define __SMPP_PDU_DATA_SM_HPP__

#include "smpppdu.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  class PDU_data_sm : public SMPP_PDU
  {
    public:
      PDU_data_sm();
      PDU_data_sm(const char        *b);
      PDU_data_sm(const PDU_data_sm &o);

      ~PDU_data_sm();

      const static int   MinLength = 26;
      ServiceType        service_type_;
      ExtendSmeAddress   source_addr_;
      ExtendSmeAddress   destination_addr_;
      EsmClass           esm_class_;
      RegisteredDelivery registered_delivery_;
      DataCoding         data_coding_;

      unsigned int getMinBodyLength() { return MinLength; }
      unsigned int getBodyLength();

    protected:
      std::string  encodeStandardParameters();
      uint8_t     *decodeStandardParameters(const uint8_t *buff);
  };
}

#endif

