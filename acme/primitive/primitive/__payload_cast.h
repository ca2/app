﻿// From payload.h by camilo on 2022-10-06 21:20 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/filesystem/filesystem/path.h"
//#include "acme/primitive/collection/numeric_array.h"
//#include "acme/primitive/collection/payload_array.h"
//#include "acme/primitive/collection/string_array.h"
//#include "acme/primitive/primitive/property_set.h"


class CLASS_DECL_ACME payload_cast
{
public:


   const payload & m_payload;


   payload_cast(const ::payload & payload) :
      m_payload(payload)
   {

   }


   operator enum_check () const { return m_payload.echeck(); }

   operator bool() const { return m_payload.get_bool(); }
   operator i8 ()const { return m_payload.i8(); }
   operator u8 ()const { return m_payload.u8(); }
   operator i16 () const { return m_payload.i16(); }
   operator u16 ()const { return m_payload.u16(); }
   operator i32 () const { return m_payload.i32(); }
   operator u32 ()const { return m_payload.u32(); }
   operator i64 () const { return m_payload.i64(); }
   operator u64 ()const { return m_payload.u64(); }

   operator f32 () const { return m_payload.f32(); }
   operator f64 ()const { return m_payload.f64(); }

   operator duration ()const { return m_payload.duration(); }
   operator earth::time()const { return m_payload.earth_time(); }


   operator string ()const { return m_payload.string(); }
   //operator property ()const { return m_payload.property(); }


   operator ::int_array ()const { return m_payload.ia(); }
   operator ::i64_array ()const { return m_payload.i64a(); }
   operator ::string_array ()const { return m_payload.stra(); }
   operator ::payload_array() const { return m_payload.payloada(); }
   operator ::property_set() const { return m_payload.propset(); }
   operator ::file::path() const { return m_payload.file_path(); }


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