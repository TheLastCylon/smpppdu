// File  : standard_parameters.cpp
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

#include "standard_parameters.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  /// @brief Prints a hex dump of a buffer.
  /// @note The debug are rows of 16 octets with their hexadecimal value on
  /// the left and if printable their character representation on the right
  /// or a dot (.) if not printable.
  /// @param buff The buffer to print.
  /// @param len Number of octets in buff.
  /// @param file The C file stream to write to (default standard output).
  void chex_dump(const uint8_t* buff, uint32_t len, FILE* file)
  {
    if(len == 0)
      return;

    uint32_t i;
    for(i = 0; i < len; ++i) {
      if(i != 0 && i % 16 == 0) {
        fprintf(file, "   ");
        for(uint32_t j = i - 16; j < i; ++j)
          if(buff[j] > 31 && buff[j] < 128)
            fprintf(file, "%c", static_cast<char>(buff[j]));
          else
            fprintf(file, ".");
        fprintf(file, "\n");
      }

      fprintf(file, "%02x ", buff[i]);
    }

    uint32_t m = i % 16 ? 16 - i % 16 : 0; // octets needed to make up 16
    m && fprintf(file, "%*c", m * 3, ' ');
    fprintf(file, "   ");
    for(uint32_t j = i % 16 ? i - i % 16 : i - 16 ; j < i; ++j)
      if(buff[j] > 31 && buff[j] < 128)
        fprintf(file, "%c", static_cast<char>(buff[j]));
      else
        fprintf(file, ".");

    fprintf(file, "\n");
    fflush(file);
  }

  //--------------------------------------------------------------------------------
  /// @brief Prints a hex dump of a buffer.
  /// @note The debug are rows of 16 octets with their hexadecimal value on
  /// the left and if printable their character representation on the right
  /// or a dot (.) if not printable.
  /// @param buff The buffer to print.
  /// @param len Number of octets in buff.
  /// @param file The C++ file stream to write to (default standard output).
  void hex_dump(const uint8_t* buff, uint32_t len, std::ostream& os)
  {
    if(len == 0)
      return;

    uint32_t i;
    for(i = 0; i < len; ++i) {
      if(i != 0 && i % 16 == 0) {
        os << "   ";
        for(uint32_t j = i - 16; j < i; ++j)
          if(buff[j] > 31 && buff[j] < 128)
            os << static_cast<char>(buff[j]);
          else
            os << ".";
        os << "\n";
      }

      os << std::setw(2) << std::setfill('0')
        << std::hex << (int)buff[i] << std::dec << ' ';
    }

    uint32_t m = i % 16 ? 16 - i % 16 : 0;// octets needed to make up 16
    m && os << std::setw(m*3) << std::setfill(' ') << ' ';

    os << "   ";
    for(uint32_t j = i % 16 ? i - i % 16 : i - 16 ; j < i; ++j)
      if(buff[j] > 31 && buff[j] < 128)
        os << static_cast<char>(buff[j]);
      else
        os << ".";

    os << "\n";
    std::flush(os);
  }
}

