// From payload.h by camilo on 2022-10-06 21:18 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME payload_reference
{
public:


   payload & m_payload;


   payload_reference(payload & payload) :
      m_payload(payload)
   {

   }

   operator e_check & () { return m_payload.echeck_reference(); }

   operator bool & () { return m_payload.bool_reference(); }
   operator i8 & () { return m_payload.i8_reference(); }
   operator unsigned char & () { return m_payload.u8_reference(); }
   operator i16 & () { return m_payload.i16_reference(); }
   operator u16 & () { return m_payload.u16_reference(); }
   operator i32 & () { return m_payload.i32_reference(); }
   operator u32 & () { return m_payload.u32_reference(); }
   operator i64 & () { return m_payload.i64_reference(); }
   operator u64 & () { return m_payload.u64_reference(); }


#ifdef __APPLE__

   operator long & () { return m_payload.long_reference(); }
   operator unsigned long & () { return m_payload.unsigned_long_reference(); }

#endif


   operator f32 & () { return m_payload.f32_reference(); }
   operator f64 & () { return m_payload.f64_reference(); }


   //operator second & () { return m_payload.secs(); }
   //operator class ::time & () { return m_payload.millis(); }
   //operator microsecond & () { return m_payload.micros(); }
   //operator nanosecond & () { return m_payload.nanos(); }

   operator class ::time & () { return m_payload.time_reference(); }
   operator earth::time & () { return m_payload.earth_time_reference(); }


   operator string & () { return m_payload.string_reference(); }
   //operator property & () { return m_payload.property_reference(); }


   operator i32_array & () { return m_payload.i32_array_reference(); }
   operator i64_array & () { return m_payload.i64_array_reference(); }
   operator string_array & () { return m_payload.string_array_reference(); }
   operator payload_array & () { return m_payload.payload_array_reference(); }
   operator property_set & () { return m_payload.property_set_reference(); }
   operator ::file::path & () { return m_payload.file_path_reference(); }


};



