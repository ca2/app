//
// Created by camilo on 2025-08-30 02:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "block.h"
#include "acme/filesystem/file/byte2_stream.h"


namespace data
{
block::block()
{

}
block::~block()
{


}

void block::initialize_set_operation(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMime, const ::block & block)
{

   m_bWrite = true;
   m_strPath = scopedstrPath;
   m_strMime = scopedstrMime;
   m_memory = block;

}


void block::initialize_get_operation(const ::scoped_string & scopedstrPath,
                                     const ::scoped_string & scopedstrMime)
{

   m_bWrite = false;
   m_strPath = scopedstrPath;
   m_strMime = scopedstrMime;

}

   void block::byte2_exchange(byte2_stream & stream)
   {

      long long llCallback = 0;
      if(stream.m_estream == ::file::e_stream_output)
      {

         llCallback = (::iptr) (void*) (::data::block *) this;

      }
      stream.exchange(llCallback);
      stream.exchange(m_bWrite);
      stream.exchange(m_strPath);
      stream.exchange(m_strMime);
      stream.exchange(m_memory);


   }


} // namespace data