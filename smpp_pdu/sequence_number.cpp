// File  : sequence_number.cpp
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

#include "sequence_number.hpp"
#include "lexical_cast.hpp"
#include "command_status.hpp"

namespace smpp_pdu
{
  SequenceNumber::Invalid::Invalid(const uint32_t seq) : Error(CommandStatus::ESME_RX_R_APPN)
  {
    Error::seq(seq);
  }
}

