// File  : error.hpp
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

#ifndef __SMPP_PDU_ERROR_HPP__
#define __SMPP_PDU_ERROR_HPP__

#include <stdint.h>
#include <stdexcept>
#include "error.hpp"
//#include "tlv.hpp"
//#include "command_status.hpp"
//#include "lexical_cast.hpp"

namespace smpp_pdu
{
  class CommandStatus;
  class TLV;

  // Exception with an associated SMPP command status. Users are recommended to include the associated command status in the response to the peer.
  class Error : public std::runtime_error
  {
    public:
      uint32_t    status    () const;
      uint32_t    seq       () const;
      std::string descr     () const;
      std::string descr_long() const;

      void seq(uint32_t);

    protected:
      explicit Error(const std::string& msg);

      Error(const CommandStatus stat);
      Error(const CommandStatus stat, const std::string& msg);

      virtual ~Error() throw() {};

    private:
      uint32_t cmd_stat_;
      uint32_t seq_;
  };


  //--------------------------------------------------------------------------------
  class InvalidCommandLength : public Error
  {
    public:
      explicit InvalidCommandLength(const std::size_t cmd_len = 0);
      InvalidCommandLength(const std::size_t cmd_len, const std::size_t pdu_len);
      InvalidCommandLength(const std::size_t cmd_len, const std::size_t pdu_len, std::string field);
  };

  //--------------------------------------------------------------------------------
  class MissingTlv : public Error
  {
    public:
      explicit MissingTlv(const uint16_t tag);

      uint16_t tag() const;

    private:
      uint16_t tag_;
  };

  //--------------------------------------------------------------------------------
  class InvalidTlvLength : public Error
  {
    public:
      explicit InvalidTlvLength(const smpp_pdu::TLV& tlv);
      InvalidTlvLength(const uint16_t,  const std::size_t len);
  };

  //--------------------------------------------------------------------------------
  class InvalidTlvValue : public Error
  {
    public:
      explicit InvalidTlvValue(const uint16_t tag, const std::string& msg = "");

      uint16_t tag() const;

    private:
      uint16_t tag_;
  };

  //--------------------------------------------------------------------------------
  class InvalidStringFieldLength    : public Error { public: explicit InvalidStringFieldLength(const std::string& msg); };
  class InvalidMessageLength        : public Error { public: explicit InvalidMessageLength    (const std::size_t len); };
  class InvalidMessageId            : public Error { public: explicit InvalidMessageId        (const std::string&); };
  class InvalidSourceAddr           : public Error { public: explicit InvalidSourceAddr       (const std::string&); };
  class InvalidDestAddr             : public Error { public: explicit InvalidDestAddr         (const std::string&); };

  class InvalidTon                  : public Error { public: explicit InvalidTon(const uint8_t); const uint8_t ton; };
  class InvalidNpi                  : public Error { public: explicit InvalidNpi(const uint8_t); const uint8_t npi; };

  class InvalidEsmClass             : public Error { public: explicit InvalidEsmClass            (const uint8_t); };
  class InvalidSourceTon            : public Error { public: explicit InvalidSourceTon           (const uint8_t); };
  class InvalidDestTon              : public Error { public: explicit InvalidDestTon             (const uint8_t); };
  class InvalidSourceNpi            : public Error { public: explicit InvalidSourceNpi           (const uint8_t); };
  class InvalidDestNpi              : public Error { public: explicit InvalidDestNpi             (const uint8_t); };
  class InvalidDestFlag             : public Error { public: explicit InvalidDestFlag            (const uint8_t); };
  class InvalidInterfaceVersion     : public Error { public: explicit InvalidInterfaceVersion    (const uint8_t v); };
  class InvalidPriorityFlag         : public Error { public: explicit InvalidPriorityFlag        (const uint8_t); };
  class InvalidReplaceIfPresentFlag : public Error { public: explicit InvalidReplaceIfPresentFlag(const uint8_t); };
  class InvalidDataCoding           : public Error { public: explicit InvalidDataCoding          (const uint8_t); };
//  class InvalidDestFlag             : public Error { public: explicit InvalidDestFlag            (const uint8_t); };
  class InvalidMessageState         : public Error { public: explicit InvalidMessageState        (const uint8_t); };
};

#endif

