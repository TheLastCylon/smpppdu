// File  : smpppdu.hpp
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

#ifndef _SMPP_PDU_HPP_
#define _SMPP_PDU_HPP_

#include <iostream> 
#include <string> 
#include <stdint.h>
#include "command_length.hpp"
#include "command_id.hpp"
#include "command_status.hpp"
#include "sequence_number.hpp"
#include "endian_util.hpp"
#include "tlv.hpp"
#include "tlv_list.hpp"
#include "standard_parameters.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  class SMPP_PDU
  {
    public:
      SMPP_PDU(const std::string &p) : command_length(p), command_id(p), command_status(p), sequence_number(p) {}
      SMPP_PDU(const char        *p) : command_length(p), command_id(p), command_status(p), sequence_number(p) {} 

      SMPP_PDU(const CommandLength  &cl,
               const CommandId      &ci,
               const CommandStatus  &cs,
               const SequenceNumber &sn) :
        command_length (cl),
        command_id     (ci),
        command_status (cs),
        sequence_number(sn) {}

      SMPP_PDU(const CommandId &ci) :
        command_length ((uint32_t)0),
        command_id     (ci),
        command_status (CommandStatus::ESME_ROK),
        sequence_number((uint32_t)0)
      {
        //setCommandLength();
      }

      ~SMPP_PDU() {};

      CommandLength  command_length;
      CommandId      command_id;
      CommandStatus  command_status;
      SequenceNumber sequence_number;
      TLVList        tlvlist;

      std::string encode();

      virtual unsigned int getMinBodyLength() = 0;
      virtual unsigned int getBodyLength()    = 0;

    protected:
      virtual std::string  encodeStandardParameters()                    = 0;
      virtual uint8_t     *decodeStandardParameters(const uint8_t *buff) = 0;

      void     decode(const char    *buff) { decode(reinterpret_cast<const uint8_t *>(buff)); };
      void     decode(const uint8_t *buff);
      uint8_t *commandLengthCheck(uint32_t el, size_t fl, uint8_t* cp);

    private:
      uint32_t  decodeLen;
  };
}

#endif

