// From payload.h by camilo on 2022-10-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/filesystem/filesystem/path.h"
////#include "acme/prototype/collection/numeric_array.h"
//#include "acme/prototype/collection/payload_array.h"
////#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/prototype/property_set.h"


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
   operator i8 ()const { return m_payload.as_i8(); }
   operator u8 ()const { return m_payload.as_u8(); }
   operator i16 () const { return m_payload.as_i16(); }
   operator u16 ()const { return m_payload.as_u16(); }
   operator i32 () const { return m_payload.as_i32(); }
   operator u32 ()const { return m_payload.as_u32(); }
   operator i64 () const { return m_payload.as_i64(); }
   operator u64 ()const { return m_payload.as_u64(); }

   operator f32 () const { return m_payload.as_f32(); }
   operator f64 ()const { return m_payload.as_f64(); }

   operator class ::time ()const { return m_payload.as_time(); }
   operator earth::time()const { return m_payload.as_earth_time(); }


   operator string ()const { return m_payload.as_string(); }
   //operator property ()const { return m_payload.property(); }


   operator ::i32_array ()const { return m_payload.as_i32_array(); }
   operator ::i64_array ()const { return m_payload.as_i64_array(); }
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
//inline payload_cast::operator property_set () const
//{
//
//   return m_payload.propset();
//
//}
