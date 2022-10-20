// Created by camilo on 2021-09-09 22:54 Thomas Month!! <3ThomasBS__!!
#include "framework.h"


namespace file
{


   enum_status streamable::_open(const char *pszFilePath, const ::file::enum_open &eopen)
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


   void writeable::write(const void *pdata, memsize nCount)
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


CLASS_DECL_ACME void __transfer_to_writable(::file::writable *pwritable, ::file::file *pfileIn, memsize uiBufSize);
{


   if (pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
   {

      pwriter->write((u8*)pfileIn->get_internal_data() + pfileIn->get_position(), (memsize)(pfileIn->get_internal_data_size() - pfileIn->get_position()));

      return;

   }


   memsize uRead;

   memsize uiSize = 0;

   uiBufSize = maximum(32 * 1024, uiBufSize);

   memory buf;

   buf.set_size(uiBufSize);

   if (buf.get_data() == nullptr)
   {

      throw ::exception(error_no_memory);

   }

   try
   {

      while (true)
      {

         uRead = pfileIn->read(buf.get_data(), buf.get_size());

         if (uRead <= 0)
         {

            break;

         }

         writer.write(buf.get_data(), uRead);

         uiSize += uRead;

      }

   }
   catch (...)
   {

   }

}



