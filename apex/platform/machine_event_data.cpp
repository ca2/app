#include "framework.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include <stdio.h>


//blob::blob()
//{
//   m_sizet     = 0;
//   m_pchData   = nullptr;
//}
//
//
//blob::~blob()
//{
//
//   if(m_pchData != nullptr)
//   {
//
//      memory_free_debug(m_pchData, 0);
//
//      m_pchData = nullptr;
//
//   }
//
//}
//
//
//void blob::read(FILE * file)
//{
//
//   if(m_pchData != nullptr)
//   {
//
//      memory_free_debug(m_pchData, 0);
//
//   }
//
//   auto iRead = fread(&m_sizet, 1, (int) sizeof(m_sizet), file);
//
//   if(m_sizet == 0)
//   {
//
//      m_pchData = nullptr;
//
//   }
//   else
//   {
//
//      m_pchData = (char *) ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(m_sizet);
//
//      size_t sRead = 0;
//
//      while(true)
//      {
//
//         iRead  = (int) fread(&m_pchData[sRead], 1, 1024, file);
//
//         if(iRead == 0)
//            break;
//
//         sRead += iRead;
//
//      }
//
//   }
//
//}
//
//void blob::write(FILE * file)
//{
//
//   size_t iWritten = fwrite(&m_sizet, 1, sizeof(m_sizet), file);
//
//   if(iWritten == sizeof(m_sizet) && m_sizet > 0)
//   {
//
//      iWritten = ::fwrite(m_pchData, 1, (size_t) m_sizet, file);
//
//      if(iWritten == m_sizet)
//      {
//
//      }
//
//   }
//
//}
//
//
//blob & blob::operator = (const ::scoped_string & scopedstr)
//{
//
//   m_sizet = scopedstr.size() + 1;
//
//   m_pchData = (char *) ansi_duplicate(scopedstr);
//
//   return *this;
//
//}


machine_event_data::fixed::fixed()
{
   m_bRequestCloseApplication    = false;
   m_bSpaUpgrade                 = false;
}


void machine_event_data::read(::file::readable * preadable)
{

   size_t iRead = preadable->read(&m_fixed, sizeof(m_fixed));

   if (iRead != sizeof(m_fixed))
   {

      throw "fread failure";

   }

   ::i32 s = (::i32) m_memoryCommand.size();

   preadable->read(s);

   m_memoryCommand.set_size(s);

   preadable->read({m_memoryCommand.data(), s });

}


void machine_event_data::write(::file::writable * pwritable)
{

   size_t iWritten = pwritable->defer_write(&m_fixed, sizeof(m_fixed));

   if(iWritten != sizeof(m_fixed))
   {

      throw "file write failure";

   }

   ::i32 s = (::i32) m_memoryCommand.size();

   pwritable->write(s);

   auto sWritten = pwritable->defer_write({ m_memoryCommand.data(), s });

   if (sWritten != s)
   {

      throw "file write failure";

   }

}



