// File  : bind_receiver_resp.hpp
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

#ifndef __SMPP_PDU_BIND_RECEIVER_RESP_HPP__
#define __SMPP_PDU_BIND_RECEIVER_RESP_HPP__

#include "bind_type_resp.hpp"

namespace smpp_pdu
{
  class PDU_bind_reciever_resp : public PDU_bind_type_resp
  {
    public:
      PDU_bind_reciever_resp()                                : PDU_bind_type_resp(CommandId::BindReceiverResp) {};
      PDU_bind_reciever_resp(const char                   *b) : PDU_bind_type_resp(b)                           {};
      PDU_bind_reciever_resp(const PDU_bind_reciever_resp &o) : PDU_bind_type_resp(o)                           {};

      ~PDU_bind_reciever_resp() {};
  };
}

#endif

