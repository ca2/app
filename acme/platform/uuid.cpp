// Created by camilo on 2025-01-08 02:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "uuid.h"


namespace platform
{


   uuid::uuid()
   {

      ::zero(m_ucha);

   }
   
   
   uuid::uuid(const uuid_t & uuid)
   {

      memcpy(this, &uuid, sizeof(uuid));

   }
   
   
   uuid::uuid(const uuid & uuid)
   {
      memcpy(this, &uuid, sizeof(uuid));

   }



   ::string uuid::as_string() const
   {

      ::string str;

      const unsigned char * p = m_ucha;

      str.formatf(
               "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
               *((int*)p),
               *((short*)(p + 4)), 
               *((short*)(p + 6)),
               p[8], p[9], 
               p[10], p[11], p[12], p[13], p[14], p[15]);

      return ::transfer(str);

   }


} // namespace platform



