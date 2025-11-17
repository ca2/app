// Created by camilo on 2025-10-24 02:02 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/file_system_cache_item.h"


namespace dynamic_source
{

   class cache_item :
      virtual public ::file_system_cache_item
   {
   public:

      ::pointer < script > m_pscript;


      using ::file_system_cache_item::file_system_cache_item;
      using ::file_system_cache_item::operator =;

   };


} // namespace dynamic_source



