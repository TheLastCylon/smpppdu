// File  : bind_type.cpp
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

#include "bind_type.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  PDU_bind_type::PDU_bind_type() :
    SMPP_PDU(CommandLength(MinLength),
             CommandId    (CommandId::BindReceiver),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_bind_type::PDU_bind_type(uint32_t c) :
    SMPP_PDU(CommandLength(MinLength),
             CommandId    (c),
             CommandStatus(CommandStatus::ESME_ROK),
             SequenceNumber::Min) {}

  //--------------------------------------------------------------------------------
  PDU_bind_type::PDU_bind_type(const char* b) :
    SMPP_PDU(b)
  {
    decode(b);
  }

  //--------------------------------------------------------------------------------
  PDU_bind_type::PDU_bind_type(const PDU_bind_type &o) :
    SMPP_PDU(o.command_length ,
             o.command_id     ,
             o.command_status ,
             o.sequence_number),
    system_id_        (o.system_id_),
    password_         (o.password_),
    system_type_      (o.system_type_),
    interface_version_(o.interface_version_),
    ton_              (o.ton_),
    npi_              (o.npi_),
    address_range_    (o.address_range_)
  {}

  //--------------------------------------------------------------------------------
  PDU_bind_type::~PDU_bind_type() {}

  //--------------------------------------------------------------------------------
  unsigned int  PDU_bind_type::getBodyLength()
  {
    return
      (
       system_id_        .length() +
       password_         .length() +
       system_type_      .length() +
       interface_version_.length() +
       ton_              .length() +
       npi_              .length() +
       address_range_    .length()
      );
  }

  //--------------------------------------------------------------------------------
  std::string PDU_bind_type::encodeStandardParameters()
  {
    std::stringstream ss;

    ss << (std::string)system_id_
       << (std::string)password_
       << (std::string)system_type_
       << (uint8_t)    interface_version_
       << (uint8_t)    ton_
       << (uint8_t)    npi_
       << (std::string)address_range_;

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  uint8_t *PDU_bind_type::decodeStandardParameters(const uint8_t *buff)
  {
    uint32_t len  = (uint32_t)command_length;
    uint8_t *sptr = const_cast<uint8_t*>(buff);

    system_id_          = sptr; sptr = commandLengthCheck(len, system_id_        .length(), sptr);
    password_           = sptr; sptr = commandLengthCheck(len, password_         .length(), sptr);
    system_type_        = sptr; sptr = commandLengthCheck(len, system_type_      .length(), sptr);
    interface_version_  = sptr; sptr = commandLengthCheck(len, interface_version_.length(), sptr);
    ton_                = sptr; sptr = commandLengthCheck(len, ton_              .length(), sptr);
    npi_                = sptr; sptr = commandLengthCheck(len, npi_              .length(), sptr);
    address_range_      = sptr; sptr = commandLengthCheck(len, address_range_    .length(), sptr);

    return sptr;
  }
}

