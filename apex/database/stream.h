// Created by camilo on 2022-10-15 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/memory_file.h"


namespace database
{


   class CLASS_DECL_APEX stream :
      virtual public ::particle
   {
   public:


      client * m_pclient;


      template < typename TYPE >
      inline void set(const key & key, const TYPE & t)
      {

         memory_file memoryfile;

         auto stream = __binary_stream(&memoryfile);

         stream.set_storing();

         stream << t;

         m_pclient->data_set_memory(key, memoryfile.memory());

      }


      template < typename TYPE >
      inline bool get(const key & key, TYPE & t)
      {

         memory_file memoryfile;

         if (!m_pclient->data_get_memory(key, memoryfile.memory()))
         {

            return false;

         }

         memoryfile.seek_to_begin();

         auto stream = __binary_stream(&memoryfile);

         stream.set_loading();

         stream >> t;

         if (stream.nok())
         {

            return false;

         }

         return true;

      }




   };


} // namespace database



