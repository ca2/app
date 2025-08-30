//
// Created by camilo on 2025-08-30 10:31 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "protocol_file.h"


protocol_file::protocol_file()
{


}


protocol_file::~protocol_file()
{


}


void protocol_file::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception)
{

   if(eopen & ::file::e_open_read)
   {

      get_memory()->assign(node()->protocol_get_data(path));

   }

   m_estatus = ::success;

   set_ok_flag();

   m_path = path;

   m_eopen = eopen;

}


void protocol_file::close()
{

   if(m_eopen & ::file::e_open_write)
   {

      node()->protocol_set_data(m_path, *get_memory());

   }

}



