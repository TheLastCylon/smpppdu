// File  : error.cpp
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

#include "error.hpp"
#include "lexical_cast.hpp"
#include "command_status.hpp"
#include "tlv.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  Error::Error(const std::string& msg) :
    std::runtime_error("SMPP command_status="                                                       +
        lexical_cast<std::string>(HexVal<CommandStatus>(CommandStatus::ESME_RUNKNOWNERR)) +
        " ("                                                                         +
        CommandStatus::description(CommandStatus::ESME_RUNKNOWNERR)                  +
        "); "                                                                        +
        msg),
    cmd_stat_(CommandStatus::ESME_RUNKNOWNERR),
    seq_(0) {}

  //--------------------------------------------------------------------------------
  Error::Error(const CommandStatus stat) :
    std::runtime_error("SMPP command_status="                             +
        lexical_cast<std::string>(HexVal<CommandStatus>(stat))  +
        " ("                                               +
        CommandStatus::description(stat)                   +
        ")"),
    cmd_stat_(stat),
    seq_(0) {}

  //--------------------------------------------------------------------------------
  Error::Error(const CommandStatus stat, const std::string& msg) :
    std::runtime_error("SMPP command_status="                            +
        lexical_cast<std::string>(HexVal<CommandStatus>(stat)) +
        " ("                                              +
        CommandStatus::description(stat)                  +
        "); "                                             +
        msg),
    cmd_stat_(stat),
    seq_(0) {}

  //--------------------------------------------------------------------------------
  uint32_t    Error::status    ()                 const { return cmd_stat_; }
  std::string Error::descr     ()                 const { return CommandStatus::description(cmd_stat_); }
  std::string Error::descr_long()                 const { return CommandStatus::long_description(cmd_stat_); }
  uint32_t    Error::seq       ()                 const { return seq_; }
  void        Error::seq       (const uint32_t seq)     { seq_ = seq; }

  //--------------------------------------------------------------------------------
  InvalidStringFieldLength::InvalidStringFieldLength(const std::string& msg) : Error(msg) {}

  //--------------------------------------------------------------------------------
  InvalidCommandLength::InvalidCommandLength(const std::size_t cmd_len) :
    Error(CommandStatus::ESME_RINVCMDLEN, "command_length=" + lexical_cast<std::string>(cmd_len)) {}

  //--------------------------------------------------------------------------------
  InvalidCommandLength::InvalidCommandLength(const std::size_t cmd_len, const std::size_t pdu_len) :
    Error(CommandStatus::ESME_RINVCMDLEN, "command_length=" + lexical_cast<std::string>(cmd_len) + "; actual length=" + lexical_cast<std::string>(pdu_len)) {}

  //--------------------------------------------------------------------------------
  InvalidCommandLength::InvalidCommandLength(const std::size_t cmd_len, const std::size_t pdu_len, std::string field):
    Error(CommandStatus::ESME_RINVCMDLEN, "command_length=" + lexical_cast<std::string>(cmd_len) + "; actual length=" + lexical_cast<std::string>(pdu_len) + " field" + field) {}

  //--------------------------------------------------------------------------------
  MissingTlv::MissingTlv(const uint16_t tag) :
    Error(CommandStatus::ESME_RMISSINGTLV, "tag=" + lexical_cast<std::string>(HexVal<uint16_t>(tag))), tag_(tag) {}

  uint16_t MissingTlv::tag() const { return tag_; }

  //--------------------------------------------------------------------------------
  InvalidTlvLength::InvalidTlvLength(const uint16_t tag, const std::size_t len) :
    Error(CommandStatus::ESME_RINVTLVLEN, "len=" + lexical_cast<std::string>(len) + "; tag=" + lexical_cast<std::string>(HexVal<uint16_t>(tag))) {}

  //--------------------------------------------------------------------------------
  InvalidTlvLength::InvalidTlvLength(const TLV& tlv) :
    Error(CommandStatus::ESME_RINVTLVLEN, "len=" + lexical_cast<std::string>(tlv.getLength()) + "; tag=" + lexical_cast<std::string>(HexVal<uint16_t>(tlv.getTag()))) {}

  //--------------------------------------------------------------------------------
  InvalidTlvValue::InvalidTlvValue(const uint16_t tag, const std::string& msg) :
    Error(CommandStatus::ESME_RINVTLVVAL, "tag=" + lexical_cast<std::string>(HexVal<uint16_t>(tag)) + (!msg.empty() ? "; msg=" : "") + msg), tag_(tag) {}

  uint16_t InvalidTlvValue::tag() const { return tag_; }

  //--------------------------------------------------------------------------------
  InvalidMessageLength::InvalidMessageLength(const std::size_t len) :
    Error(CommandStatus::ESME_RINVMSGLEN, "len=" + lexical_cast<std::string>(len)) {}

  //--------------------------------------------------------------------------------
  InvalidMessageId::InvalidMessageId(const std::string& id) :
    Error(CommandStatus::ESME_RINVMSGID, "id=\"" + id + "\"") {} 

  //--------------------------------------------------------------------------------
  InvalidEsmClass::InvalidEsmClass(const uint8_t v) :
    Error(CommandStatus::ESME_RINVESMCLASS, "esm_class=" + lexical_cast<std::string>(static_cast<ushort>(v))) {}

  //--------------------------------------------------------------------------------
  InvalidSourceAddr::InvalidSourceAddr(const std::string& number) :
    Error(CommandStatus::ESME_RINVSRCADR, "address=" + number) {}

  //--------------------------------------------------------------------------------
  InvalidDestAddr::InvalidDestAddr(const std::string& number) :
    Error(CommandStatus::ESME_RINVDSTADR, "address=" + number) {}

  //--------------------------------------------------------------------------------
  InvalidTon::InvalidTon(const uint8_t v) :
    Error("Invalid TON; value=" + lexical_cast<std::string>(v)), ton(v) {}

  //--------------------------------------------------------------------------------
  InvalidNpi::InvalidNpi(const uint8_t v) :
    Error("Invalid NPI; value=" + lexical_cast<std::string>(v)), npi(v) {}

  //--------------------------------------------------------------------------------
  InvalidSourceTon::InvalidSourceTon(const uint8_t ton) :
    Error(CommandStatus::ESME_RINVSRCTON, "TON=" + lexical_cast<std::string>(ton)) {}

  //--------------------------------------------------------------------------------
  InvalidDestTon::InvalidDestTon(const uint8_t ton) :
    Error(CommandStatus::ESME_RINVDSTTON, "TON=" + lexical_cast<std::string>(ton)) {}

  //--------------------------------------------------------------------------------
  InvalidSourceNpi::InvalidSourceNpi(const uint8_t npi) :
    Error(CommandStatus::ESME_RINVSRCNPI, "NPI=" + lexical_cast<std::string>(npi)) {}

  //--------------------------------------------------------------------------------
  InvalidDestNpi::InvalidDestNpi(const uint8_t npi) :
    Error(CommandStatus::ESME_RINVDSTNPI, "NPI=" + lexical_cast<std::string>(npi)) {}

  //--------------------------------------------------------------------------------
  InvalidDestFlag::InvalidDestFlag(const uint8_t df) :
    Error(CommandStatus::ESME_RINVDESTFLAG, "dest_flag=" + lexical_cast<std::string>(df)) {}

  //--------------------------------------------------------------------------------
  InvalidInterfaceVersion::InvalidInterfaceVersion(const uint8_t v) :
    Error("Invalid Interface Version; value=" + lexical_cast<std::string>(v)) {}

  //--------------------------------------------------------------------------------
  InvalidPriorityFlag::InvalidPriorityFlag(const uint8_t v) :
    Error(CommandStatus::ESME_RINVPRTFLG, "priority_flag=" + lexical_cast<std::string>(v)) {}

  //--------------------------------------------------------------------------------
  InvalidReplaceIfPresentFlag::InvalidReplaceIfPresentFlag(const uint8_t v) :
    Error(CommandStatus::ESME_RINVREPFLAG, "replace_if_present=" + lexical_cast<std::string>(v)) {}

  //--------------------------------------------------------------------------------
  InvalidDataCoding::InvalidDataCoding(const uint8_t v) :
    Error(CommandStatus::ESME_RINVDCS, "data_coding=" + lexical_cast<std::string>(v)) {}

  //--------------------------------------------------------------------------------
  //InvalidDestFlag::InvalidDestFlag(const uint8_t v) :
  //  Error(CommandStatus::ESME_RINVDESTFLAG, "dest_flag=" + lexical_cast<std::string>(v)) {}

  //--------------------------------------------------------------------------------
  InvalidMessageState::InvalidMessageState(const uint8_t v) :
    Error("Invalid Message State; value=" + lexical_cast<std::string>(v)) {}

};

