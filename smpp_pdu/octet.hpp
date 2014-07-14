// File  : octet.hpp
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

#ifndef _OCTET_HPP_
#define _OCTET_HPP_ 

#include <string>
#include <stdint.h>

template<class T> class Octet
{
  private:
    uint8_t _v;
    T       sp;

  public:
    Octet()                 : sp() {}
    Octet(const uint8_t &p) : sp() { _v = sp.check(p); }
    Octet(const int     &p) : sp() { _v = sp.check(p); }

    operator uint8_t() const { return _v; }

    Octet& operator= (const uint8_t p)
    {
      _v = sp.check(p);
      return *this;
    }

    Octet& operator= (const uint8_t *p)
    {
      _v = sp.check(p[0]);
      return *this;
    }

    Octet& operator=(const Octet& rhs)
    {
      _v = rhs._v;
      return *this;
    }

    operator std::string()
    {
      std::string retval = "";

      retval += (char)_v;

      return retval;
    }

    uint8_t data    ()                   const { return _v; }
    size_t  length  ()                   const { return 1; }
    bool    bits_set(const uint8_t bits) const { return ((_v & bits) == bits); } // Checks whether a given bit pattern is set.
};

#endif
