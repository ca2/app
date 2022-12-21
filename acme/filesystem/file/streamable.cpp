// Created by camilo on 2021-09-09 22:54 Thomas Month!! <3ThomasBS__!!
#include "framework.h"
#include "streamable.h"
#include "file.h"
#include "acme/primitive/primitive/memory.h"
////#include "acme/exception/exception.h"


namespace file
{


   enum_status streamable::_open(const ::scoped_string & scopestrFilePath, const ::file::enum_open &eopen)
   {

      throw error_interface_only;

   }


   ::filesize streamable::translate(filesize offset, ::enum_seek eseek)
   {

      throw error_interface_only;

   }


   memsize readable::read(void *pdata, memsize nCount)
   {

      throw error_interface_only;

   }


   void writable::write(const void *pdata, memsize nCount)
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


   filesize streamable::size() const
   {

      throw error_interface_only;

   }


} // namespace file


CLASS_DECL_ACME void __transfer_to_writable(::file::writable *pwritable, ::file::file *pfileIn, memsize uiBufSize)
{

   if (pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
   {

      pwritable->write((u8*)pfileIn->get_internal_data() + pfileIn->get_position(), (memsize)(pfileIn->get_internal_data_size() - pfileIn->get_position()));

      return;

   }

   memsize uRead;

   memsize uiSize = 0;

   uiBufSize = maximum(32 * 1024, uiBufSize);

   memory buf;

   buf.set_size(uiBufSize);

   if (buf.data() == nullptr)
   {

      throw ::exception(error_no_memory);

   }

   try
   {

      while (true)
      {

         uRead = pfileIn->read(buf.data(), buf.size());

         if (uRead <= 0)
         {

            break;

         }

         pwritable->write(buf.data(), uRead);

         uiSize += uRead;

      }

   }
   catch (...)
   {

   }

}



