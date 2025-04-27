// From payload.h by camilo on 2022-10-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/filesystem/filesystem/path.h"
////#include "acme/prototype/collection/numeric_array.h"
//#include "acme/prototype/collection/payload_array.h"
////#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/prototype/::property_set.h"


class CLASS_DECL_ACME payload_cast
{
public:


   const payload & m_payload;


   payload_cast(const ::payload & payload) :
      m_payload(payload)
   {

   }


   //operator enum_check () const { return m_payload.echeck(); }

   operator bool() const { return m_payload.get_bool(); }
   operator char ()const { return m_payload.as_char(); }
   operator unsigned char ()const { return m_payload.as_unsigned_char(); }
   operator short () const { return m_payload.as_short(); }
   operator unsigned short ()const { return m_payload.as_unsigned_short(); }
   operator int () const { return m_payload.as_int(); }
   operator unsigned int ()const { return m_payload.as_unsigned_int(); }
   operator long long () const { return m_payload.as_long_long(); }
   operator unsigned long long ()const { return m_payload.as_unsigned_long_long(); }

   operator float () const { return m_payload.as_float(); }
   operator double ()const { return m_payload.as_double(); }

   operator class ::time ()const { return m_payload.as_time(); }
   operator earth::time()const { return m_payload.as_earth_time(); }


   operator string ()const { return m_payload.as_string(); }
   //operator property ()const { return m_payload.property(); }


   operator ::int_array ()const { return m_payload.as_int_array(); }
   operator ::long_long_array ()const { return m_payload.as_long_long_array(); }
   operator ::string_array ()const { return m_payload.as_string_array(); }
   operator ::payload_array() const { return m_payload.as_payload_array(); }
   operator ::property_set() const { return m_payload.as_property_set(); }
   operator ::file::path() const { return m_payload.as_file_path(); }


};


//inline payload_cast::operator payload_array () const
//{
//
//   return m_payload.payloada();
//
//}
//
//
//inline payload_cast::operator ::property_set () const
//{
//
//   return m_payload.propset();
//
//}
