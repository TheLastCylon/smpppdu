// File  : bind_transmitter.hpp 
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

#ifndef __SMPP_PDU_BIND_TRANSMITTER_HPP__
#define __SMPP_PDU_BIND_TRANSMITTER_HPP__

#include "bind_type.hpp"

namespace smpp_pdu
{
  class PDU_bind_transmitter : public PDU_bind_type
  {
    public:
      PDU_bind_transmitter()                              : PDU_bind_type(CommandId::BindTransmitter) {};
      PDU_bind_transmitter(const char                 *b) : PDU_bind_type(b)                          {};
      PDU_bind_transmitter(const PDU_bind_transmitter &o) : PDU_bind_type(o)                          {};

      ~PDU_bind_transmitter() {};
  };
}

#endif

