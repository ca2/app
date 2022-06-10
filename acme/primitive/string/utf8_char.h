// Created by camilo from ch.h on 2022-06-06 22:20 <3ThomasBorregaardSorensen!!
#pragma once



   class CLASS_DECL_ACME utf8_char
   {
   public:


      char     m_sz[32];
      char     m_chLen;


      utf8_char(u64 u = 0);

      i32 parse(const char * psz);


   };

