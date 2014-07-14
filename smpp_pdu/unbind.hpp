// File  : unbind.hpp
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

#ifndef __SMPP_PDU_UNBIND_HPP__
#define __SMPP_PDU_UNBIND_HPP__

#include "header_pdu.hpp"

namespace smpp_pdu
{
  class PDU_unbind : public PDU_header
  {
    public:
      PDU_unbind()                    : PDU_header(CommandId::Unbind) {};
      PDU_unbind(const char       *b) : PDU_header(b)                 {};
      PDU_unbind(const PDU_unbind &o) : PDU_header(o)                 {};

      ~PDU_unbind() {};
  };
}

#endif

