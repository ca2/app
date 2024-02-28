// Created by camilo on 2022-10-15 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "client.h"


namespace database
{


   class CLASS_DECL_APEX stream :
      virtual public ::particle
   {
   public:


      client * m_pclient;


      template < typename TYPE >
      inline void set(const ::scoped_string & scopedstr, const TYPE & t)
      {

         auto pmemoryfile = create_memory_file();

         binary_stream stream(pmemoryfile);

         stream.set_storing_flag();

         stream << t;

         m_pclient->data_set_memory(scopedstr, pmemoryfile->memory());

      }


      template < typename TYPE >
      inline bool get(const ::scoped_string & scopedstr, TYPE & t)
      {

         auto pmemoryfile = create_memory_file();

         if (!m_pclient->data_get_memory(scopedstr, pmemoryfile->memory()))
         {

            return false;

         }

         pmemoryfile->seek_to_begin();

         binary_stream stream(pmemoryfile);

         stream.set_loading_flag();

         stream >> t;

         if (stream.nok())
         {

            return false;

         }

         return true;

      }




   };


} // namespace database



