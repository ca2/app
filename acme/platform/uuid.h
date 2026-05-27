// Created by camilo on 2025-01-08 02:51 <3ThomasBorregaardSorensen!!
#pragma once


namespace platform
{
   

   struct uuid_t 
   {
      ulong  data1;
      ::u16 data2;
      ::u16 data3;
      ::u8  data4[8];
   };
   
   // 128-bit
   // 16 bytes
   class CLASS_DECL_ACME uuid
   {
   public:
      
      union
      {
         uuid_t         m_uuid;
         ::u8  m_u8a[16];

      };


      uuid();
      uuid(const uuid_t & uuid_t);
      uuid(const uuid & uuid);

      ::string as_string() const;




   };





} // namespace platform



