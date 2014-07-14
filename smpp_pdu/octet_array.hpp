// File  : octet_array.hpp
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

#ifndef _OCTET_ARRAY_HPP_
#define _OCTET_ARRAY_HPP_

#include <string>
#include <cstring>
#include <stdint.h>

namespace smpp_pdu
{
  class octet_array
  {
    public:
      octet_array()                                   : _v(NULL), _len(0) {}
      octet_array(const octet_array &p)               : _v(NULL), _len(0) { operator=(p); }
      octet_array(const uint8_t     *p)               : _v(NULL), _len(0) { raw_assign(p); }
      octet_array(const uint8_t     *p, unsigned len) : _v(NULL), _len(0) { raw_assign(p, len); }

//      octet_array(const std::string *p)
//      {
//        _len = p->size();
//        raw_assign(reinterpret_cast<const uint8_t*>(p->c_str()), _len);
//      }

      ~octet_array()
      {
        if(_v) {
          delete [] _v;
        }
      }

      unsigned     raw_assign(const uint8_t* p);
      unsigned     raw_assign(const uint8_t* p, unsigned len);

      bool operator==(const octet_array &rhs);
      bool operator!=(const octet_array &rhs);

      octet_array& operator= (const uint8_t     *p);
      octet_array& operator= (const octet_array &rhs);
      octet_array& operator= (const std::string &p);

      // the difference between casting operator std::string() and function data() is intentional.
      operator std::string()
      {
        std::string retval(reinterpret_cast<const char*>(_v), _len);
        retval += '\0';
        return retval;
      }

      std::string data()
      {
        return std::string(reinterpret_cast<const char*>(_v), _len);
      }

      unsigned size() { return _len; }

    private:
      uint8_t  *_v;
      unsigned  _len;
  };
}

#endif // _OCTET_ARRAY_HPP_

