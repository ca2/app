// Created by camilo on 2021-09-09 22:54 Thomas Month!! <3ThomasBS__!!
#include "framework.h"


namespace file
{


   enum_status streamable::_open(const char * pszFilePath, const ::file::enum_open & eopen)
   {

      throw error_interface_only;

   }


   ::filesize streamable::translate(filesize offset, ::enum_seek eseek)
   {

      throw error_interface_only;

   }


   memsize streamable::read(void * pdata, memsize nCount)
   {

      throw error_interface_only;

   }


   void streamable::write(const void * pdata, memsize nCount)
   {

      throw error_interface_only;

   }


   void streamable::flush()
   {

      throw error_interface_only;

   }


   void streamable::close()
   {

      throw error_interface_only;

   }


   void streamable::abort()
   {

      throw error_interface_only;

   }


   void streamable::set_size(filesize dwNewLen)
   {

      throw error_interface_only;

   }


   filesize streamable::get_size() const
   {

      throw error_interface_only;

   }


} // namespace file



