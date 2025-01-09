// Created by camilo on 2025-01-08 02:51 <3ThomasBorregaardSorensen!!
#pragma once


namespace platform
{
   

   struct uuid_t 
   {
      unsigned long  data1;
      unsigned short data2;
      unsigned short data3;
      unsigned char  data4[8];
   };
   
   // 128-bit
   // 16 bytes
   class CLASS_DECL_ACME uuid
   {
   public:
      
      union
      {
         uuid_t         m_uuid;
         unsigned char  m_ucha[16];

      };


      uuid();
      uuid(const uuid_t & uuid_t);
      uuid(const uuid & uuid);

      ::string as_string() const;




   };





} // namespace platform



