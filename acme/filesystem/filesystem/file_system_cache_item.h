// Created by camilo on 2025-10-19 17:00 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/file_system_item.h"


class CLASS_DECL_ACME file_system_cache_item :
   virtual public ::pointer < ::file_system_item >
{
public:


   ::string                      m_strName2;


   file_system_cache_item();
   file_system_cache_item(const ::scoped_string & scopedstrName, ::file_system_item * pitem) :
      ::pointer < ::file_system_item>(pitem),
      m_strName2(scopedstrName)
   {

   }
   ~file_system_cache_item();


   bool is_ok() const
   {

      return m_p->is_ok();

   }


   const ::file::path& path() const
   {

      return m_p->path();

   }


};



