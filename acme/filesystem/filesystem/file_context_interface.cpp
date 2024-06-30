// From file_context.h by camilo on 2024-06-28 09:39 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "file_context.h"
#include "file_context_interface.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/platform/sequencer.h"


::string file_context_interface::safe_get_string(const ::payload& payloadFile, ::e_status* pestatus)
{

   memory memory;

   safe_get_memory(payloadFile, memory, pestatus);

   return memory.as_utf8();

}


void file_context_interface::safe_get_memory(const ::payload& payloadFile, memory_base& mem, ::e_status* pestatus)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_file | ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary | ::file::e_open_no_exception_on_open);

      if (!pfile)
      {

         return;

      }
      else if (pfile->m_estatus.failed())
      {

         return;

      }

   }
   catch (const ::exception& exception)
   {

      auto psequencer = nano()->user()->exception_message_console(exception);

      psequencer->do_asynchronously();

   }

   try
   {

      if (!pfile)
      {

         return;

      }

      pfile->full_memory(mem);

   }
   catch (...)
   {

   }

}


::memory file_context_interface::safe_get_memory(const ::payload& payloadFile)
{

   ::memory memory;

   safe_get_memory(payloadFile, memory);

   return ::transfer(memory);

}


::file_pointer file_context_interface::get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
{

   return file()->get_file(payloadFile, eopen, ppfileexception);

}



