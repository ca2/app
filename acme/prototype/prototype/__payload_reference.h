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
   operator char & () { return m_payload.char_reference(); }
   operator unsigned char & () { return m_payload.unsigned_char_reference(); }
   operator short & () { return m_payload.short_reference(); }
   operator unsigned short & () { return m_payload.unsigned_short_reference(); }
   operator int & () { return m_payload.int_reference(); }
   operator unsigned int & () { return m_payload.unsigned_int_reference(); }
   operator long long & () { return m_payload.long_long_reference(); }
   operator unsigned long long & () { return m_payload.unsigned_long_long_reference(); }


#ifdef __APPLE__

   operator long & () { return m_payload.long_reference(); }
   operator unsigned long & () { return m_payload.unsigned_long_reference(); }

#endif


   operator float & () { return m_payload.float_reference(); }
   operator double & () { return m_payload.double_reference(); }


   //operator second & () { return m_payload.secs(); }
   //operator class ::time & () { return m_payload.millis(); }
   //operator microsecond & () { return m_payload.micros(); }
   //operator nanosecond & () { return m_payload.nanos(); }

   operator class ::time & () { return m_payload.time_reference(); }
   operator earth::time & () { return m_payload.earth_time_reference(); }


   operator string & () { return m_payload.string_reference(); }
   //operator property & () { return m_payload.property_reference(); }


   operator int_array_base & () { return m_payload.int_array_reference(); }
   operator long_long_array_base & () { return m_payload.long_long_array_reference(); }
   operator string_array_base & () { return m_payload.string_array_reference(); }
   operator payload_array & () { return m_payload.payload_array_reference(); }
   operator ::property_set & () { return m_payload.property_set_reference(); }
   operator ::file::path & () { return m_payload.file_path_reference(); }


};



