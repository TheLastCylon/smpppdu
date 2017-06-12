// File  : tlv.hpp
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

#ifndef __SMPP_PDU_TLV_HPP__
#define __SMPP_PDU_TLV_HPP__

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdint.h>
#include "endian_util.hpp"

namespace smpp_pdu
{
  class TLV
  {
    private:
      uint16_t  tag;
      uint16_t  length;
      uint8_t  *value;

    public:
      TLV() :
        tag   (0),
        length(0) ,
        value (NULL) {} // Default constructor acts as a null TLV.

      TLV(const TLV &tlv) :
        tag   (tlv.tag),
        length(tlv.length),
        value(NULL)
      {
        value = new uint8_t[length];
        std::copy(tlv.value, tlv.value+length, value);
      }

      TLV(const uint16_t &_tag, const uint16_t &_length, const uint8_t *_value) :
        tag   (_tag),
        length(_length),
        value(NULL)
      {
        value = new uint8_t[length];
        std::copy(_value, _value+length, value);
      }

      TLV(const uint16_t &_tag, const uint16_t &_length, const std::string &p) :
        tag   (_tag),
        length(_length),
        value(NULL)
      {
        setValue(p);
      }

      TLV(const uint8_t *t) :
        tag   (0),
        length(0) ,
        value (NULL)
      {
        decode(t);
      }

      virtual ~TLV() { delete [] value; } // Deallocate the value.

      void setTag   (const uint16_t     p) { tag = p; }
      void setValue (const std::string &p)
      {
        std::string tstr(p);
        length = tstr.length();
        value  = new uint8_t[length];
        std::copy(tstr.c_str(), tstr.c_str()+length, value);
      }

      uint16_t       getTag   () const { return tag   ; }
      uint16_t       getLength() const { return length; }
      const uint8_t *getValue () const { return value ; }

      std::string    encode();

      operator std::string()
      {
        std::stringstream ss;
        ss << int16str(smpp_pdu::hton16(tag))
           << int16str(smpp_pdu::hton16(length))
           << std::string(reinterpret_cast<char*>(value), length);
        return ss.str();
      }

      TLV& operator=(const TLV& rhs)
      {
        if(this == &rhs) {
          return *this;
        } else {
          tag    = rhs.tag;
          length = rhs.length;
          value  = new uint8_t[length];
          std::copy(rhs.value, rhs.value+length, value);
        }
      }

      bool operator ==(const uint16_t& tag_) const { return (tag_ == tag); } // tag comparsion.

      operator bool()const { return tag != 0; } // Test validity of the tlv.

      //--------------------------------------------------------------------------------
      std::string int16str(uint16_t i)
      {
        std::string retval = "";

        union {
          uint16_t a;
          uint8_t  b[sizeof(uint16_t)];
        } ti;

        ti.a = i;

        for(unsigned i = 0; i < sizeof(uint16_t); ++i) {
          retval += (char)ti.b[i];
        }

        return retval;
      }

      //--------------------------------------------------------------------------------
      size_t encodedLength() { return (length>0)?(length+4):(5); }

    protected:
      // Construct using tag, length and value called from a derived class.
      // note : The value is allocated by the derived class.
      // x is extra field to differenciate this constructor from the public constructor.
      // TLV(const uint16_t &tag, const uint16_t &length, const uint8_t  *value, int x) : tag_(tag), length_(length), value_(value) {}

    private:
      void decode(const uint8_t *p);

    public:
      enum {
        dest_addr_subunit            = 0x0005, dest_network_type            = 0x0006, dest_bearer_type             = 0x0007, dest_telematics_id           = 0x0008,
        source_addr_subunit          = 0x000D, source_network_type          = 0x000E, source_bearer_type           = 0x000F, source_telematics_id         = 0x0010,
        qos_time_to_live             = 0x0017, payload_type                 = 0x0019, additional_status_info_text  = 0x001D, receipted_message_id         = 0x001E,
        ms_msg_wait_facilities       = 0x0030, privacy_indicator            = 0x0201, source_subaddress            = 0x0202, dest_subaddress              = 0x0203,
        user_message_reference       = 0x0204, user_response_code           = 0x0205, source_port                  = 0x020A, dest_port                    = 0x020B,
        sar_msg_ref_num              = 0x020C, language_indicator           = 0x020D, sar_total_segments           = 0x020E, sar_segment_seqnum           = 0x020F,
        sc_interface_version         = 0x0210, callback_num_pres_ind        = 0x0302, callback_num_atag            = 0x0303, number_of_messages           = 0x0304,
        callback_num                 = 0x0381, dpf_result                   = 0x0420, set_dpf                      = 0x0421, ms_availability_status       = 0x0422,
        network_error_code           = 0x0423, message_payload              = 0x0424, delivery_failure_reason      = 0x0425, more_messages_to_send        = 0x0426,
        message_state                = 0x0427, congestion_state             = 0x0428, ussd_service_op              = 0x0501, broadcast_channel_indicator  = 0x0600,
        broadcast_content_type       = 0x0601, broadcast_content_type_info  = 0x0602, broadcast_message_class      = 0x0603, broadcast_rep_num            = 0x0604,
        broadcast_frequency_interval = 0x0605, broadcast_area_identifier    = 0x0606, broadcast_Error_status       = 0x0607, broadcast_area_success       = 0x0608,
        broadcast_end_time           = 0x0609, broadcast_service_group      = 0x060A, billing_identification       = 0x060B, source_network_id            = 0x060D,
        dest_network_id              = 0x060E, source_node_id               = 0x060F, dest_node_id                 = 0x0610, dest_addr_np_resolution      = 0x0611,
        dest_addr_np_information     = 0x0612, dest_addr_np_country         = 0x0613, display_time                 = 0x1201, sms_signal                   = 0x1203,
        ms_validity                  = 0x1204, alert_on_message_delivery    = 0x130C, its_reply_type               = 0x1380, its_session_info             = 0x1383
      };
  };

  //typedef std::list<const TLV*>                   TLVList;
  //typedef std::list<const TLV*>::iterator         TLVListItr;
  //typedef std::list<const TLV*>::reverse_iterator TLVListRevItr;

  /*
  // Specific TLVs derived from TLV
  //--------------------------------------------------------------------------------
  class BroadcastAreaIdentifier : public TLV
  {
    private:
      uint8_t* allocate_value(const uint8_t  &format,
                              const uint8_t  *details,
                              const uint16_t &length)
      {
        uint8_t* v = new uint8_t[ length+1];
        v[0] = format;
        if(length)
          std::copy(details, details+length, v+1);
        return v;
      }

      BroadcastAreaIdentifier();

    public:
      BroadcastAreaIdentifier(const uint8_t  &format,
                              const uint8_t  *details,
                              const uint16_t &length) :
        TLV(TLV::broadcast_area_identifier,
            length+1,
            allocate_value(format, details, length),
            0) {}
  };

  //--------------------------------------------------------------------------------
  class BroadcastContentType : public TLV
  {
    private:
      uint8_t* allocate_value(const uint8_t  &typeTag,
                              const uint16_t &type)
      {
        uint8_t *v    = new uint8_t[3];
        v[0] = typeTag;
        uint16_t t    = smpp_pdu::hton16(type);
        uint8_t *tptr = reinterpret_cast<uint8_t*>(&t);
        std::memcpy(v+1, tptr, 2);
        return v;
      }
      BroadcastContentType();

    public:
      BroadcastContentType(const uint8_t  &typeTag,
                           const uint16_t &type) :
        TLV(TLV::broadcast_content_type, 3, allocate_value(typeTag, type), 0) {}
  };

  //--------------------------------------------------------------------------------
  class BroadcastFrequencyInterval : public TLV
  {
    private:
      uint8_t* allocate_value(const uint8_t& type, const uint16_t& units)
      {
        uint8_t  *v    = new uint8_t[3];
        v[0] = type;
        uint16_t  t    = smpp_pdu::hton16(units);
        uint8_t  *tptr = reinterpret_cast<uint8_t*>(&t);
        std::memcpy(v+1, tptr, 2);
        return v;
      }
      BroadcastFrequencyInterval();
    public:
      BroadcastFrequencyInterval(const uint8_t  &type,
                                 const uint16_t &units) :
        TLV(TLV::broadcast_frequency_interval, 3, allocate_value(type, units), 0) {}
  };

  //--------------------------------------------------------------------------------
  class BroadcastAreaSuccess : public TLV
  {
    public:
      uint8_t* allocate_value(const uint8_t& sRate)
      {
        uint8_t* v = new uint8_t[1];
        v[0] = sRate;
        return v;
      }
      BroadcastAreaSuccess();

    public:
      BroadcastAreaSuccess(const uint8_t& sRate) :
        TLV(TLV::broadcast_area_success, 1, allocate_value(sRate), 0) {}
  };
  */
}

#endif

