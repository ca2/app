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


   void streamable::translate(filesize offset, ::enum_seek eseek)
   {

      throw error_interface_only;

   }


   memsize readable::read(const ::block & block)
   {

      throw error_interface_only;

   }


   ::file::file * readable::get_file()
   {

      return nullptr;

   }


   void writable::write(const ::block & block)
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

   if (pfileIn->full_data().is_set())
   {

      pwritable->write(pfileIn->data());

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

         uRead = pfileIn->read(buf);

         if (uRead <= 0)
         {

            break;

         }

         pwritable->write(buf(0, uRead));

         uiSize += uRead;

      }

   }
   catch (...)
   {

   }

}



