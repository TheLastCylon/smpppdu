// File  : standard_parameters.hpp
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

#ifndef __SMPP_PDU_STANDARD_PARAMETERS_HPP__
#define __SMPP_PDU_STANDARD_PARAMETERS_HPP__

#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <vector>
#include <iomanip>
#include <sstream>

#include "octet.hpp"
#include "octet_array.hpp"
#include "error.hpp"
#include "command_status.hpp"
#include "lexical_cast.hpp"
#include "endian_util.hpp"

namespace smpp_pdu
{
  //--------------------------------------------------------------------------------
  inline void check_length(size_t currSize, size_t maxSize, const char* err)
  {
    if(currSize > maxSize) {
      throw smpp_pdu::InvalidStringFieldLength(err);
    }
  }

  inline std::string int32str(uint32_t i);
  inline std::string int16str(uint32_t i);

  void chex_dump(const uint8_t* buff, uint32_t len, FILE* file);
  void hex_dump (const uint8_t* buff, uint32_t len, std::ostream& os);

  //--------------------------------------------------------------------------------
  class standardParameterOctet
  {
    public:
      standardParameterOctet() {}
      virtual uint8_t check(uint8_t p) = 0;
  };

  //--------------------------------------------------------------------------------
  class standardParameterArray
  {
    private:
      size_t      maxLength;
      std::string paramName;

    public:
      size_t      getMaxLength() { return maxLength; }
      std::string getParamName() { return paramName; }

      void setMaxLength(const size_t       p) { maxLength = p; }
      void setParamName(const std::string &p) { paramName = p; }

      standardParameterArray(size_t l, std::string n) : maxLength(l), paramName(n) {}
  };

  //--------------------------------------------------------------------------------
  class spInterfaceVersion : public standardParameterOctet
  {
    public:
      enum {              // Valid interface versions
        V33       = 0x33, // Version 3.3 (decimal 51)
        V34       = 0x34, // Version 3.4 (decimal 52)
        V50       = 0x50  // Version 5.0 (decimal 80)
      };

      uint8_t check(uint8_t p)
      {
        switch(p) {
          case V33: case V34: case V50:
            return p;
          default:
            if(p < V33)
              return p;
        }
        throw InvalidInterfaceVersion(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spTon : public standardParameterOctet
  {
    public:
      enum {                  // Valid Types of numbers
        Unknown       = 0x00, // Unknown (default)
        International = 0x01, // International
        National      = 0x02, // National
        Network       = 0x03, // Network
        Subscriber    = 0x04, // Subscriber
        Alphanumeric  = 0x05, // Alphanumeric
        Abbreviated   = 0x06  // Abbreviated
      };

      uint8_t check(uint8_t p)
      {
        switch(p)
        {
          case Unknown:
          case International:
          case National:
          case Network:
          case Subscriber:
          case Alphanumeric:
          case Abbreviated:
            return p;
        }
        throw smpp_pdu::InvalidTon(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spNpi : public standardParameterOctet
  {
    public:
      // Valid numbering plan indicators
      enum { 
        Unknown  = 0x00, // Unknown
        E164     = 0x01, // E164
        Data     = 0x03, // Data
        Telex    = 0x04, // Telex
        Mobile   = 0x06, // Mobile
        National = 0x08, // National
        Private  = 0x09, // Private
        Ermes    = 0x0a, // ERMES
        Internet = 0x0e, // Internet
        Wap      = 0x12  // WAP
      };

      uint8_t check(uint8_t p)
      {
        switch(p) {
          case Unknown:
          case E164:
          case Data:
          case Telex:
          case Mobile:
          case National:
          case Private:
          case Ermes:
          case Internet:
          case Wap:
            return p;
        }
        throw smpp_pdu::InvalidNpi(p);
      }
  };

  //--------------------------------------------------------------------------------
  // TODO: Provide constances for the different possible values
  class spEsmClass : public standardParameterOctet
  {
    public:
      enum type {
        MSG_MODE_DEFAULT    = 0x00,                        // Default %message mode
        MSG_MODE_DGRAM      = 0x01,                        // Datagram mode
        MSG_MODE_FWD        = 0x02,                        // Forward (transaction) mode
        MSG_MODE_STORE_FWD  = 0x03,                        // Store and forward mode
        MSG_MODE_MASK       = 0x03,                        // Mask to separate out %message mode bits.
        MSG_TYPE_DEFAULT    = 0x00,                        // Default %message type.
        MSG_TYPE_DLR        = 0x04,                        // Delivery Receipt.
        MSG_TYPE_IDN        = 0x20,                        // Intermediate Delivery Notification.
        MSG_TYPE_MASK       = 0x3C,                        // Mask to separate out %message type bits.
        ANSI41_DLR          = 0x08,                        // Delivery acknowledgement
        ANSI41_USER_ACK     = 0x10,                        // Manual/user acknowledgement
        ANSI41_CONV_ABORT   = 0x18,                        // Conversation abort (Korean CDMA)
        ANSI41_MASK         = 0x3C,                        // Mask to separate out ANSI 41 bits.
        GSM_NONE            = 0x00,                        // No GSM flags set.
        GSM_UDHI            = 0x40,                        // User Data Header Indicator.
        GSM_REPLY_PATH      = 0x80,                        // Set reply path
        GSM_UDHI_REPLY_PATH = (GSM_UDHI | GSM_REPLY_PATH), // User Data, Header Indicator AND Set Reply Path.
        GSM_MASK            = 0xC0U,                       // Mask to separate out GSM bits.
      };

      uint8_t check(uint8_t p)
      {
        switch(p) {
          case MSG_MODE_DEFAULT   : //Also for MSG_TYPE_DEFAULT & GSM_NONE
          case MSG_MODE_DGRAM     :
          case MSG_MODE_FWD       :
          case MSG_MODE_STORE_FWD : //Also for MSG_MODE_MASK
          case MSG_TYPE_DLR       :
          case MSG_TYPE_IDN       :
          case MSG_TYPE_MASK      : //Also for ANSI41_MASK
          case ANSI41_DLR         :
          case ANSI41_USER_ACK    :
          case ANSI41_CONV_ABORT  :
          case GSM_UDHI           :
          case GSM_REPLY_PATH     :
          case GSM_UDHI_REPLY_PATH: // GSM_MASK
            return p;
        }
        throw smpp_pdu::InvalidEsmClass(p); 
      }
  };

  //--------------------------------------------------------------------------------
  class spProtocolId : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spPriorityFlag : public standardParameterOctet
  {
    public:
      enum { 
        Normal     = 0x00,
        Immediate  = 0x01,
        High       = 0x02,
        Reserved   = 0x03, // very urgent, emergency
        Background = 0x04
      };

      uint8_t check(uint8_t p)
      {
        switch(p)
        {
          case Normal:
          case Immediate:
          case High:
          case Reserved:
          case Background:
            return p;
        }
        throw smpp_pdu::InvalidPriorityFlag(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spRegisteredDelivery : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spReplaceIfPresentFlag : public standardParameterOctet
  {
    public:
      enum {
        NoReplace = 0x00,
        Replace   = 0x01
      };

      uint8_t check(uint8_t p)
      {
        switch(p)
        {
          case NoReplace:
          case Replace  :
            return p;
        }
        throw smpp_pdu::InvalidReplaceIfPresentFlag(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spDataCoding : public standardParameterOctet
  {
    public:
      enum type {
        DEFAULT             = 0x00, // MC-specific/GSM (7-bit)?
        IA5_ASCII           = 0x01, // IA5 (CCITT T.50)/ASCII (ANSI X3.4)
        OCTET_UNSPEC_2      = 0x02, // Octet-unspecified (8-bit)
        LATIN1              = 0x03, // Latin1
        OCTET_UNSPEC_4      = 0x04, // Octet-unspecified (8-bit)
        JIS                 = 0x05, // JIS (X 0208-1990)
        CYRILLIC            = 0x06, // Cyrillic (ISO-8859-5)
        LATIN_HEBREW        = 0x07, // Latin/Hebrew (ISO-8859-8)
        UCS2                = 0x08, // UCS2 (16-bit)
        PICTOGRAM           = 0x09, // Pictogram Encoding
        ISO_2022_JP         = 0x0A, // ISO-2022-JP (Music Codes)
        RESERVED_1          = 0x0B, // reserved
        RESERVED_2          = 0x0C, // reserved
        EXTENDED_KANJI_JIS  = 0x0D, // Extended Kanji JIS (X 0212-1990)
        KS_C_5601           = 0x0E  // KS C 5601
      };

      uint8_t check(uint8_t p)
      {
        switch(p)
        {
          case DEFAULT           :
          case IA5_ASCII         :
          case OCTET_UNSPEC_2    :
          case LATIN1            :
          case OCTET_UNSPEC_4    :
          case JIS               :
          case CYRILLIC          :
          case LATIN_HEBREW      :
          case UCS2              :
          case PICTOGRAM         :
          case ISO_2022_JP       :
          case EXTENDED_KANJI_JIS:
          case KS_C_5601         :
            return p;
            break;
          case RESERVED_1        :
          case RESERVED_2        :
          default                :
            throw smpp_pdu::InvalidDataCoding(p);
            break;
        }
      }
  };

  //--------------------------------------------------------------------------------
  class spSmDefaultMsgId : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spMessageState : public standardParameterOctet
  {
    public:
      enum {
        SCHEDULED     = 0,
        ENROUTE       = 1,
        DELIVERED     = 2,
        EXPIRED       = 3,
        DELETED       = 4,
        UNDELIVERABLE = 5,
        ACCEPTED      = 6,
        UNKNOWN       = 7,
        REJECTED      = 8,
        SKIPPED       = 9
      };

      uint8_t check(uint8_t p)
      {
        switch(p) {
          case SCHEDULED    :
          case ENROUTE      :
          case DELIVERED    :
          case EXPIRED      :
          case DELETED      :
          case UNDELIVERABLE:
          case ACCEPTED     :
          case UNKNOWN      :
          case REJECTED     :
          case SKIPPED      :
            return p;
        }
        throw smpp_pdu::InvalidMessageState(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spErrorCode : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spDestFlag : public standardParameterOctet
  {
    public:
      enum {
        SMEADDRESS       = 0x01,
        DISTRIBUTIONLIST = 0x02
      };

      uint8_t check(uint8_t p)
      {
        switch(p) {
          case SMEADDRESS      :
          case DISTRIBUTIONLIST:
            return p;
        }
        throw smpp_pdu::InvalidDestFlag(p);
      }
  };

  //--------------------------------------------------------------------------------
  class spNoUnsuccess : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spSmLength : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spNumberOfDests : public standardParameterOctet
  {
    public:
      uint8_t check(uint8_t p)
      {
        return p;
      }
  };

  //--------------------------------------------------------------------------------
  class spSystemId     : public standardParameterArray { public: spSystemId     () : standardParameterArray( 16, "system_id"     ) {} };
  class spPassword     : public standardParameterArray { public: spPassword     () : standardParameterArray(  9, "password"      ) {} };
  class spSystemType   : public standardParameterArray { public: spSystemType   () : standardParameterArray( 13, "system_type"   ) {} };
  class spAddressRange : public standardParameterArray { public: spAddressRange () : standardParameterArray( 41, "address_range" ) {} };
  class spServiceType  : public standardParameterArray { public: spServiceType  () : standardParameterArray(  6, "service_type"  ) {} };
  class spAddress      : public standardParameterArray { public: spAddress      () : standardParameterArray( 21, "address"       ) {} };
  class spExtendAddress: public standardParameterArray { public: spExtendAddress() : standardParameterArray( 65, "extend_address") {} };
  class spTime         : public standardParameterArray { public: spTime         () : standardParameterArray( 17, "time"          ) {} };
  class spShortMessage : public standardParameterArray { public: spShortMessage () : standardParameterArray(255, "short_message" ) {} };
  class spMessageId    : public standardParameterArray { public: spMessageId    () : standardParameterArray( 65, "message_id"    ) {} };
  class spDlName       : public standardParameterArray { public: spDlName       () : standardParameterArray( 21, "dl_name"       ) {} };

  //--------------------------------------------------------------------------------
  template <class T> class OctetArray
  {
    private:
      octet_array oa;
      T           sp;

    public:
      OctetArray(const uint8_t       *p) : oa(p)        , sp() { check_length(oa.size(), sp.getMaxLength(), sp.getParamName()); }
      OctetArray(const std::string   &p) : oa(p.c_str()), sp() { check_length(oa.size(), sp.getMaxLength(), sp.getParamName()); }
      OctetArray(const OctetArray<T> &p) : oa(p.oa)     , sp() {}
      OctetArray()                       : oa()         , sp() {}

      std::string data() { return oa.data(); }

      operator std::string() { return (std::string)oa; }

      OctetArray<T>& operator=(const std::string &p) { oa = p; check_length(oa.size(), sp.getMaxLength(), sp.getParamName().c_str()); return *this; }
      OctetArray<T>& operator=(const uint8_t     *p) { oa = p; check_length(oa.size(), sp.getMaxLength(), sp.getParamName().c_str()); return *this; }

      size_t length() { return oa.size()+1; } // length after encoding. oa.size + null terminating character.
  };

  //--------------------------------------------------------------------------------
  template <class T> class SizedOctetArray
  {
    private:
      T           sp;
      octet_array oa;
      uint8_t     len;

    public:
      SizedOctetArray(const uint8_t            *p) : sp()                       { operator=(p); check_length(oa.size(), sp.getMaxLength(), sp.getParamName()); }
      SizedOctetArray(const std::string        &p) : sp()                       { operator=(p); check_length(oa.size(), sp.getMaxLength(), sp.getParamName()); }
      SizedOctetArray(const SizedOctetArray<T> &p) : sp(), oa(p.oa), len(p.len) {}
      SizedOctetArray()                            : sp(), oa()    , len(0)     {}

      std::string data() { return oa.data(); }

      operator std::string()
      {
        std::stringstream ss;
        ss << len << oa.data();
        return ss.str();
      }

      SizedOctetArray<T>& operator=(const SizedOctetArray<T>& p)
      {
        len = p.len;
        oa  = p.oa;
        return *this;
      }

      SizedOctetArray<T>& operator=(const std::string &p)
      {
        len = p.size();
        oa.raw_assign(reinterpret_cast<const uint8_t*>(p.c_str()), len);
        check_length(oa.size(), sp.getMaxLength(), sp.getParamName().c_str());
        return *this;
      }

      SizedOctetArray<T>& operator=(const uint8_t *p)
      {
        len = p[0];
        oa.raw_assign(&p[1], len);
        check_length(oa.size(), sp.getMaxLength(), sp.getParamName().c_str());
        return *this;
      }

      size_t length() { return oa.size() + sizeof(uint8_t); } // length after encoding.
  };

  //--------------------------------------------------------------------------------
  typedef Octet<spInterfaceVersion>     InterfaceVersion;
  typedef Octet<spTon>                  Ton;
  typedef Octet<spNpi>                  Npi;
  typedef Octet<spEsmClass>             EsmClass;
  typedef Octet<spProtocolId>           ProtocolId;
  typedef Octet<spPriorityFlag>         PriorityFlag;
  typedef Octet<spRegisteredDelivery>   RegisteredDelivery;
  typedef Octet<spReplaceIfPresentFlag> ReplaceIfPresentFlag;
  typedef Octet<spDataCoding>           DataCoding;
  typedef Octet<spSmDefaultMsgId>       SmDefaultMsgId;
  typedef Octet<spMessageState>         MessageState;
  typedef Octet<spErrorCode>            ErrorCode;
  typedef Octet<spDestFlag>             DestFlag;
  typedef Octet<spNoUnsuccess>          NoUnsuccess;
  typedef Octet<spSmLength>             SmLength;
  typedef Octet<spNumberOfDests>        NumberOfDests;

  typedef OctetArray     <spSystemId>        SystemId;
  typedef OctetArray     <spPassword>        Password;
  typedef OctetArray     <spSystemType>      SystemType;
  typedef OctetArray     <spAddressRange>    AddressRange;
  typedef OctetArray     <spServiceType>     ServiceType;
  typedef OctetArray     <spAddress>         Address;
  typedef OctetArray     <spExtendAddress>   ExtendAddress;
  typedef OctetArray     <spTime>            Time;
  typedef SizedOctetArray<spShortMessage>    ShortMessage;
  typedef OctetArray     <spMessageId>       MessageId;
  typedef OctetArray     <spDlName>          DlName;

  //--------------------------------------------------------------------------------
  template<class addressType> class TriFieldAddress
  {
    public:
      TriFieldAddress()                 : ton()     , npi()     , address()      {}
      TriFieldAddress(const uint8_t *p) : ton( p[0]), npi( p[1]), address(&p[2]) {}

      TriFieldAddress(const Ton     &_ton, const Npi     &_npi, const addressType &_addr) : ton(_ton), npi(_npi), address(_addr) {} 
      TriFieldAddress(const uint8_t  _ton, const uint8_t  _npi, const std::string  _addr) : ton(_ton), npi(_npi), address(_addr) {}

      Ton         ton;
      Npi         npi;
      addressType address;

      TriFieldAddress& operator=(const uint8_t* p)
      {
        ton     =  p[0];
        npi     =  p[1];
        address = &p[2];
        return *this;
      }

      TriFieldAddress& operator=(const std::string &p)
      {
        ton     =  p[0];
        npi     =  p[1];
        address =  p.substr(2);
        return *this;
      }

      operator std::string()
      {
        std::stringstream ss;
        ss << (uint8_t)    ton
           << (uint8_t)    npi
           << (std::string)address;
        return ss.str();
      }

      size_t  length() { return (ton.length() + npi.length() + address.length()); }
  };

  typedef TriFieldAddress<Address>       NormalSmeAddress;
  typedef TriFieldAddress<ExtendAddress> ExtendSmeAddress;

  //--------------------------------------------------------------------------------
  // Destination address for submit_multi_sm pdu
  class MultiSmDestinationAddress
  {
    public:
      MultiSmDestinationAddress()                       : _dest_flag()                            , _normal_sme_address()    , _dl_name() {}
      MultiSmDestinationAddress(NormalSmeAddress &addr) : _dest_flag(spDestFlag::SMEADDRESS)      , _normal_sme_address(addr)             {}
      MultiSmDestinationAddress(DlName           &dln)  : _dest_flag(spDestFlag::DISTRIBUTIONLIST), _dl_name(dln)                         {}
      MultiSmDestinationAddress(const uint8_t    *p)    : _dest_flag(p[0])
      {
        switch((uint8_t)_dest_flag)
        {
          case spDestFlag::SMEADDRESS      : _normal_sme_address = (&p[1]); break;
          case spDestFlag::DISTRIBUTIONLIST: _dl_name            = (&p[1]); break;
        }
      }

      operator std::string()
      {
        std::stringstream ss;
        ss << (uint8_t)_dest_flag;

        switch((uint8_t)_dest_flag)
        {
          case spDestFlag::SMEADDRESS      : ss << (std::string)_normal_sme_address; break;
          case spDestFlag::DISTRIBUTIONLIST: ss << (std::string)_dl_name;            break;
        }
          
        return ss.str();
      }

      void set_normal_sme_address(NormalSmeAddress &addr)
      {
        _dest_flag          = (uint8_t)spDestFlag::SMEADDRESS;
        _normal_sme_address = addr;
      }

      void set_dl_name(DlName &dln)
      {
        _dest_flag = (uint8_t)spDestFlag::DISTRIBUTIONLIST;
        _dl_name   = dln;
      }

      size_t length()
      {
        size_t retval = _dest_flag.length();
        switch((uint8_t)_dest_flag)
        {
          case spDestFlag::SMEADDRESS      : retval += _normal_sme_address.length(); break;
          case spDestFlag::DISTRIBUTIONLIST: retval += _dl_name.length();            break;
        }
        return retval;
      }

    private:
      DestFlag         _dest_flag;
      NormalSmeAddress _normal_sme_address;
      DlName           _dl_name;
  };

  //--------------------------------------------------------------------------------
  class MultiSmDestinationAddressList
  {
    public:
      MultiSmDestinationAddressList() {};
      MultiSmDestinationAddressList(const uint8_t i, const uint8_t *p)
      {
        raw_assign(i, p);
      };

      ~MultiSmDestinationAddressList()
      {
        for(unsigned i = 0; i < addressList.size(); ++i) {
          delete addressList[i];
        }
        addressList.clear();
      }

      MultiSmDestinationAddressList& operator=(const uint8_t *p)
      {
        raw_assign(p[0], &p[1]);
        return *this;
      }

      void raw_assign(const uint8_t count, const uint8_t *ptr)
      {
        uint8_t *p = const_cast<uint8_t*>(ptr);

        for(unsigned int i = count; i > 0; --i) {
          MultiSmDestinationAddress *tptr = new MultiSmDestinationAddress(p);
          p += tptr->length()+1;
          addressList.push_back(tptr);
        }
      }

      size_t length()
      {
        size_t retval = 0;
        size_t count  = addressList.size();
        for(unsigned i = 0; i < count; ++i) {
          retval += addressList[i]->length();
        }
        return retval;
      }

      operator std::string()
      {
        std::stringstream ss;
        uint8_t           count  = addressList.size();
       
        ss << count;

        for(uint8_t i = 0; i < count; ++i) {
          ss  << (std::string)(*addressList[i]);
        }
        return ss.str();
      }

    private:
      std::vector<MultiSmDestinationAddress*> addressList;
  };

  //--------------------------------------------------------------------------------
  // A submit_multi_resp unsuccess_sme.
  class UnsuccessSme
  {
    private:
      NormalSmeAddress _normal_sme_address;
      uint32_t         _error;

    public:
      UnsuccessSme()                                           : _normal_sme_address()    , _error(0)   {}
      UnsuccessSme(const NormalSmeAddress &addr, uint32_t err) : _normal_sme_address(addr), _error(err) {}
      UnsuccessSme(const uint8_t          *p)
      {
        _normal_sme_address = p;
        memcpy(&_error, (p+_normal_sme_address.length()+1), sizeof(uint32_t));
      }

      const NormalSmeAddress &getTriFieldAddress() const { return _normal_sme_address; }
      const uint32_t         &error()              const { return _error; }

      size_t length()
      {
        return (_normal_sme_address.length()+sizeof(uint32_t));
      }

      operator std::string()
      {
        return int32str(_error);
      }
  };

  //--------------------------------------------------------------------------------
  class UnsuccessSmeList
  {
    public:
      UnsuccessSmeList() {};
      UnsuccessSmeList(const uint8_t i, const uint8_t *p)
      {
        raw_assign(i, p);
      }

      void raw_assign(const uint8_t count, const uint8_t *ptr)
      {
        uint8_t *p = const_cast<uint8_t*>(ptr);

        for(unsigned int i = count; i > 0; --i) {
          UnsuccessSme *tptr = new UnsuccessSme(p);
          p += tptr->length()+1;
          addressList.push_back(tptr);
        }
      }

      ~UnsuccessSmeList()
      {
        for(unsigned i = 0; i < addressList.size(); ++i) {
          delete addressList[i];
        }
      }

      size_t length()
      {
        size_t retval = 0;
        size_t count  = addressList.size();
        for(unsigned i = 0; i < count; ++i) {
          retval += addressList[i]->length();
        }
        return retval;
      }

      operator std::string()
      {
        std::stringstream ss;
        size_t count  = addressList.size();
        for(unsigned i = 0; i < count; ++i) {
          ss << (std::string)(*addressList[i]);
        }

        return ss.str();
      }

    private:
      std::vector<UnsuccessSme*> addressList;
  };

  //--------------------------------------------------------------------------------
//  namespace
//  {
//    inline void check_length(size_t currSize, size_t maxSize, const char* err)
//    {
//      if(currSize > maxSize) {
//        throw smpp_pdu::InvalidStringFieldLength(err);
//      }
//    }
//  }

  //--------------------------------------------------------------------------------
  inline std::string int32str(uint32_t i)
  {
    std::string retval = "";

    union {
      uint32_t a;
      uint8_t  b[sizeof(uint32_t)];
    } terr;

    terr.a = i;

    std::stringstream ss;
    for(unsigned i = 0; i < sizeof(uint32_t); ++i) {
      ss << terr.b[i];
    }

    return ss.str();
  }

  //--------------------------------------------------------------------------------
  inline uint32_t get_command_length (const uint8_t* b) { uint32_t x; std::copy(&b[ 0], &b[ 4], reinterpret_cast<uint8_t*>(&x)); return smpp_pdu::ntoh32(x); }
  inline uint32_t get_command_id     (const uint8_t* b) { uint32_t x; std::copy(&b[ 4], &b[ 8], reinterpret_cast<uint8_t*>(&x)); return smpp_pdu::ntoh32(x); }
  inline uint32_t get_command_status (const uint8_t* b) { uint32_t x; std::copy(&b[ 8], &b[12], reinterpret_cast<uint8_t*>(&x)); return smpp_pdu::ntoh32(x); }
  inline uint32_t get_sequence_number(const uint8_t* b) { uint32_t x; std::copy(&b[12], &b[16], reinterpret_cast<uint8_t*>(&x)); return smpp_pdu::ntoh32(x); }
}

#endif

