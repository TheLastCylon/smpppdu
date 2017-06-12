// File  : command_id.hpp
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

#ifndef __SMPP_PDU_COMMAND_ID_HPP__
#define __SMPP_PDU_COMMAND_ID_HPP__

#include <cstring>
#include <string>
#include "endian_util.hpp"

namespace smpp_pdu
{
  class CommandId
  {
    public:
      // standard command ids
      enum {
        BindReceiver          = 0x00000001, BindTransmitter       = 0x00000002, QuerySm               = 0x00000003,
        SubmitSm              = 0x00000004, DeliverSm             = 0x00000005, Unbind                = 0x00000006,
        ReplaceSm             = 0x00000007, CancelSm              = 0x00000008, BindTransceiver       = 0x00000009,
        Outbind               = 0x0000000B, EnquireLink           = 0x00000015, SubmitMulti           = 0x00000021,
        AlertNotification     = 0x00000102, DataSm                = 0x00000103, BroadcastSm           = 0x00000111,
        QueryBroadcastSm      = 0x00000112, CancelBroadcastSm     = 0x00000113, GenericNack           = 0x80000000,
        BindReceiverResp      = 0x80000001, BindTransmitterResp   = 0x80000002, QuerySmResp           = 0x80000003,
        SubmitSmResp          = 0x80000004, DeliverSmResp         = 0x80000005, UnbindResp            = 0x80000006,
        ReplaceSmResp         = 0x80000007, CancelSmResp          = 0x80000008, BindTransceiverResp   = 0x80000009,
        EnquireLinkResp       = 0x80000015, SubmitMultiResp       = 0x80000021, DataSmResp            = 0x80000103,
        BroadcastSmResp       = 0x80000111, QueryBroadcastSmResp  = 0x80000112, CancelBroadcastSmResp = 0x80000113 
      };

      CommandId(const uint32_t    &p) : val_(p)         {};
      CommandId(const char        *p) : val_(decode(p)) {};
      CommandId(const std::string &p) : val_(decode(p.c_str())) {};

      CommandId& operator =(const uint32_t& p) { val_ = p; return *this; } // Assign a 32 bit integer.

      operator uint32_t() const { return val_; }                           // Conversion operator

      uint32_t value() { return val_; }

      static uint32_t decode(const char* b) { uint32_t x; memcpy(&x, &b[4], sizeof x); return smpp_pdu::ntoh32(x); }

    private:
      uint32_t val_;
      CommandId();
  };
}

#endif

