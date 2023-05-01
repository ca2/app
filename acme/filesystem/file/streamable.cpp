// Created by camilo on 2021-09-09 22:54 Thomas Month!! <3ThomasBS__!!
#include "framework.h"
#include "streamable.h"
#include "file.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/exception/interface_only.h"


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


   memsize readable::read(void * p, ::memsize s)
   {

      throw error_interface_only;

   }


   ::file::file * readable::get_file()
   {

      return nullptr;

   }


   void writable::write(const void * p, ::memsize s)
   {

      throw ::interface_only();

   }


   ::memsize writable::defer_write(const void * p, ::memsize s)
   {

      throw ::interface_only();
      
      return 0;

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


   filesize streamable::right_size() const
   {

      throw error_interface_only;

   }


   void streamable::right_memory(::memory_base & memory, ::memsize iReadAtMostByteCount)
   {

      auto uSize = this->right_size();

      if (iReadAtMostByteCount < 0)
      {

         iReadAtMostByteCount = (strsize)uSize;

      }
      else
      {

         iReadAtMostByteCount = minimum(iReadAtMostByteCount, (strsize)uSize);

      }

      memory.set_size(iReadAtMostByteCount);

      auto p = memory.data();

      ::size_t iPos = 0;

      while (iReadAtMostByteCount - iPos > 0)
      {

         auto dwRead = this->read({ p + iPos, (size_t)iReadAtMostByteCount - iPos });

         if (dwRead <= 0)
         {

            break;

         }

         iPos += dwRead;

      }

   }


   ::memory streamable::right_memory(::memsize iReadAtMostByteCount)
   {

      ::memory memory;

      right_memory(memory, iReadAtMostByteCount);

      return ::transfer(memory);

   }


   void streamable::right_string(string & str, ::memsize iReadAtMostByteCount)
   {

      ::memory memory;

      right_memory(memory, iReadAtMostByteCount);

      str = memory.get_string();

   }


   ::string streamable::right_string(::memsize iReadAtMostByteCount)
   {

      ::string str;

      right_string(str, iReadAtMostByteCount);

      return ::transfer(str);

   }


   ::string streamable::full_string(::memsize iReadAtMostByteCount)
   {

      seek_to_begin();

      return ::transfer(right_string(iReadAtMostByteCount));

   }

   //string file::as_string() const
   //{

   //   string str;

   //   auto pfile = (file *)this;

   //   auto position = pfile->get_position();

   //   pfile->as(str);

   //   pfile->set_position(position);

   //   return str;

   //}


   void streamable::full_memory(memory_base & memory, ::memsize iReadAtMostByteCount)
   {

      /*auto pfile = (file *)this;

      auto position = pfile->get_position();

      pfile->as(memory);

      pfile->set_position(position);*/

      seek_to_begin();

      right_memory(memory, iReadAtMostByteCount);


   }

   
   ::memory streamable::full_memory(::memsize iReadAtMostByteCount)
   {

      ::memory memory;

      full_memory(memory, iReadAtMostByteCount);

      return ::transfer(memory);

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

         //uiSize += uRead;

      }

   }
   catch (...)
   {

   }

}



