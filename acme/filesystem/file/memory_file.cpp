﻿#include "framework.h"
#include "memory_file.h"
#include "acme/primitive/primitive/memory.h"
////#include "acme/exception/exception.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"


memory_file::memory_file() :
   memory_container(__new(class memory()))
{

   m_position = 0;
   m_estatus = ::success;
   set_ok_flag();

}


memory_file::memory_file(::file::e_open eopen) :
   memory_container(__new(class memory()))
{

   m_eopen = eopen;
   m_position = 0;
   m_pbyte = nullptr;
   m_estatus = ::success;
   set_ok_flag();

}


memory_file::memory_file(memsize size) :
   memory_container(size)
{

   m_position = 0;
   m_pbyte = nullptr;
   m_estatus = ::success;
   set_ok_flag();

}


memory_file::memory_file(const memory_file & m) :
   ::matter((const matter &)m),
   file((const file &)m),
   memory_container((const memory_container &)m)
{

   m_position = m.m_position;
   m_estatus = m.m_estatus;
   if(m.is_ok()) set_ok_flag();

}

memory_file::memory_file(memory_file && m) :
   ::matter(::transfer(m)),
   file(::transfer(m)),
   memory_container(::transfer(m))
{

   m_position = m.m_position;
   m_estatus = m.m_estatus;
   if(m.is_ok()) set_ok_flag();

}


memory_file::memory_file(const void * pmemory, memsize dwSize) :
   memory_container(pmemory, dwSize)
{

   m_position = 0;
   m_estatus = ::success;

}


memory_file::memory_file(const ::block & block) :
   memory_file(block.data(), block.size())
{


}



memory_file::memory_file(memory_base & memory, ::file::e_open eopen) :
   memory_container(memory)
{

   m_eopen = eopen;
   m_position = 0;
   m_estatus = ::success;

}


memory_file::memory_file(memory_base* pmemory, ::file::e_open eopen) :
   memory_container(pmemory)
{

   m_eopen = eopen;
   m_position = 0;
   m_estatus = ::success;

}



//memory_file::memory_file(memory_base * pmemory, ::file::e_open eopen) :
//   memory_container(pmemory)
//{
//
//   m_eopen = eopen;
//   m_position = 0;
//
//}


memory_file::~memory_file()
{

}


memsize memory_file::read(void * p, ::memsize s)
{

   return read_inline(p, s);

}


void memory_file::write(const void * p, ::memsize s)
{

   write_inline(p, s);

}


void memory_file::put_byte_back(::byte byte)
{

   if(m_position <= 0 || m_position >= size())
   {

      throw ::exception(error_wrong_state);

   }

   m_position--;

   m_pmemory.m_p->data()[m_position] = byte;

}



void memory_file::write_from_hex(const ::block & block)
{

   char ch = 0;

   strsize iLen = block.size();

   if ((iLen % 2) != 0)
   {

      iLen++;

   }

   memsize iEndPosition = m_position + iLen / 2;

   if (iEndPosition > this->size())
   {

      set_size(iEndPosition);

   }

   if (iEndPosition <= 0)
   {

      m_position = 0;

      return;

   }

   byte * pb = full_data_begin();

   auto nCount = block.size();

   ASSERT(is_memory_segment_ok(&(pb)[m_position], (uptr)nCount));

   char * pch = (char *)&(pb)[m_position];

   const char * psz = (const char *)block.data();

   bool bEven = true;

   while (nCount > 0)
   {

      if (bEven)
      {

         if (*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
         else
            ch |= ((*psz - '0') & 0x0f) << 4;

         if (*psz == '\0')
            break;

      }
      else
      {

         if (*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f);
         else
            ch |= ((*psz - '0') & 0x0f);

         *pch = ch;

         pch++;

      }

      psz++;

      nCount--;

      bEven = !bEven;

   }

   if (bEven)
   {
      *(pch - 1) = ch;
   }

   m_position = (memsize)iEndPosition;
}


//void memory_file::Truncate(filesize size_i32)
//{
//
//   allocate((memsize)size_i32);
//
//   if (m_position > (memsize)size_i32)
//      m_position = (memsize)size_i32;
//
//
//}


int memory_file::get_u8()
{

   return _get_u8();

}


int memory_file::get_u16()
{

   return _get_u16();

}


bool memory_file::get_u64(::u64 & u64)
{

   return _get_u64(u64);

}


bool memory_file::is_end_of_file() const
{

   return _is_end_of_file();

}


bool memory_file::read_string(memory_base & memory)
{

   auto position = get_position();

   auto start = m_position;

   const int iLookAhead = 1024;

   while (true)
   {

      auto iLeft = _get_left();

      int iCount = (int) minimum(iLookAhead, _get_left());

      if (iCount <= (iLookAhead -1))
      {
         
         if (iCount <= 0)
         {

            memory.assign(m_pbyte + start, m_position - start);

            break;

         }
         else
         {

            int i = 0;

            for (; i < iCount; i++, m_position++)
            {

               auto b = m_pbyte[m_position];

               if (b == '\r')
               {

                  memory.assign(m_pbyte + start, m_position - start);

                  m_position++;

                  b = m_pbyte[m_position];

                  if (b == '\n')
                  {

                     m_position++;

                  }

                  return true;

               }
               else if (b == '\n')
               {

                  memory.assign(m_pbyte + start, m_position - start);

                  m_position++;

                  return true;

               }

            }

            memory.assign(m_pbyte + start, m_position - start);

            return true;

         }

      }

      // there are 258 bytes left;

      auto b = (m_pbyte + m_position)[(iLookAhead -2)]; // stop searching at byte 257

      (m_pbyte + m_position)[(iLookAhead - 2)] = '\0';

      const byte * p = (const byte *) strpbrk((const char*)(m_pbyte + m_position), "\r\n");

      (m_pbyte + m_position)[(iLookAhead - 2)] = b;

      if ((p == nullptr && (b == '\r' || b == '\n')) || p)
      {

         if (p)
         {

            m_position = p - m_pbyte;

            b = *p;

         }
         else
         {

            m_position += (iLookAhead - 2);

         }

         if (b == '\r')
         {

            memory.assign(m_pbyte + start, m_position - start);

            m_position++;

            b = m_pbyte[m_position];

            if (b == '\n')
            {

               m_position++;

            }

            return true;

         }
         else if (b == '\n')
         {

            memory.assign(m_pbyte + start, m_position - start);

            m_position++;

            return true;

         }

      }

      m_position += (iLookAhead - 2);

   }

   return ::file::file::read_string(memory);

}



void memory_file::clear()
{

   m_position = 0;

   set_size(0);

}


void memory_file::set_size(filesize size_i32)
{

   ::memory_container::set_size((memsize) size_i32);

   if (m_position > size())
   {

      m_position = 0;

   }

}


filesize memory_file::size() const
{

   return ::memory_container::size();

}


filesize memory_file::get_position() const
{

   if (!is_valid())
   {

      throw ::exception(error_io, "memory_file::get_position");

   }

   return (filesize)m_position;

}


void memory_file::raw_set_position(memsize memsize)
{

   m_position = memsize;

}


void memory_file::translate(filesize offset, ::enum_seek eseek)
{

   ASSERT(is_valid());

   ASSERT(eseek == ::e_seek_set || eseek == ::e_seek_from_end || eseek == ::e_seek_current);
   //ASSERT(::e_seek_set == FILE_BEGIN && ::e_seek_end == FILE_END && ::e_seek_current == FILE_CURRENT);

   m_memsize = m_pmemory->size();

   m_pbyte = (::byte *)m_pmemory->begin();

   memsize dwNew = (memsize)m_position;

   switch (eseek)
   {
   case ::e_seek_set:
      if(offset < 0)
      {

         dwNew = 0;

      }
      else
      {
         dwNew = (memsize)offset;

      }
      break;
   case ::e_seek_from_end:
      if(offset < -(memsize)size())
      {

         dwNew = 0;

      }
      else
      {
         dwNew = (memsize)(size() + offset);
      }
      break;
   case ::e_seek_current:
      if(offset < -(memsize)m_position)
      {

         dwNew = 0;

      }
      else
      {

         dwNew = (memsize)(m_position + offset);

      }
      break;
   default:
      return;
      //return m_position;
   }

   m_position = dwNew;

   //if(dwNew > this->size())
   //allocate((memsize) dwNew);

   //return (filesize)dwNew;
}


//void memory_file::create(memsize iSize)
//{
//
//   allocate(iSize);
//
//}


void memory_file::load_string(string &str)
{

   char * psz = str.get_string_buffer((i32)(this->size() + 1));

   ::memcpy_dup(psz, data_begin(), (size_t) data_size());

   psz[this->size()] = 0;

   str.release_string_buffer();

}


memsize memory_file::erase_begin(memsize uiCount)
{

   return erase_begin(nullptr, uiCount);

}


memsize memory_file::erase_begin(void *pdata, memsize uiCount)
{

   //ASSERT(is_valid());

   auto pmemory = get_memory();

   if (uiCount > pmemory->size())
   {

      uiCount = pmemory->size();

   }

   if (pdata != nullptr)
   {

      ::memcpy(pdata, full_data_begin(), (size_t)uiCount);

   }

   if (m_position <= uiCount)
   {

      m_position = 0;

   }
   else
   {

      m_position -= uiCount;

   }

   pmemory->delete_begin(uiCount);

   return uiCount;

}


bool memory_file::is_valid() const
{

   return memory_container::is_valid();

}


::file::path memory_file::get_file_path() const
{

   return file::get_file_path();

}


void memory_file::flush()
{

}


string memory_file::as_string() const
{
   
   return memory_container::as_string();
   
}


//void memory_file::assert_ok() const
//{
//
//   //file::assert_ok();
//
//}
//
//
//void memory_file::dump(dump_context & dumpcontext) const
//{
//
//   //file::dump(dumpcontext);
//
//}


//void memory_file::full_load(::payload payloadFile)
//{
//
//   ASSERT(is_valid());
//
//   auto pfile = file()->get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);
//
//   if (!pfile)
//   {
//
//      return;
//
//   }
//
//   class memory storage;
//
//   storage.set_size(1_mb);
//
//   memsize uRead;
//
//   while ((uRead = pfile->read(storage.data(), storage.size())) > 0)
//   {
//
//      write(storage.data(), uRead);
//
//   }
//
//}


::byte * memory_file::full_data_begin()
{

   return m_pmemory ? m_pmemory->begin() : nullptr;

}


::byte * memory_file::full_data_end()
{

   return m_pmemory ? m_pmemory->end() : nullptr;

}


const ::byte * memory_file::full_data_begin() const
{

   return m_pmemory ? m_pmemory->begin() : nullptr;

}


const ::byte * memory_file::full_data_end() const
{

   return m_pmemory ? m_pmemory->end() : nullptr;

}



::byte * memory_file::data_begin()
{

   auto pbegin = full_data_begin();

   return ::is_set(pbegin) ? pbegin + m_position : nullptr;

}


::byte * memory_file::data_end()
{

   auto pend = full_data_end();

   return ::is_set(pend) ? pend : nullptr;

}


const ::byte * memory_file::data_begin() const
{

   auto pbegin = full_data_begin();

   return ::is_set(pbegin) ? pbegin + m_position : nullptr;

}



const ::byte * memory_file::data_end() const
{

   auto pend = full_data_end();

   return ::is_set(pend) ? pend : nullptr;

}

//memsize memory_file::get_internal_data_size() const
//{
//
//   return (memsize) size();
//
//}


bool memory_file::full_data_set_size(memsize c)
{

   set_size(c);

   return true;

}


void memory_file::write(::file::readable* preadable, memsize uiBufSize)
{

   ::pointer <::file::file> pfile = preadable;

   if (pfile && pfile->full_data_is_set())
   {

      auto size = pfile->size();

      full_data_set_size((memsize)size);
      
      auto read = pfile->read(this->data()(0, size));

      if (read != size)
      {

         throw io_exception();

      }

      return;

   }

   ::file::file::write(preadable, uiBufSize);

}


//void memory_file::to(::file::file* pfileOut, memsize uiSize)
//{
//
//   if (pfileOut->increase_internal_data_size(uiSize) && pfileOut->get_internal_data() != nullptr)
//   {
//
//      __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + uiSize, ((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), pfileOut->get_internal_data_size() - uiSize);
//
//      ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), get_internal_data(), uiSize);
//
//      pfileOut->position() += get_internal_data_size();
//
//   }
//   else
//   {
//
//      pfileOut->write(get_internal_data(), uiSize);
//
//   }
//
//}


::file::file_status memory_file::get_status() const
{

   ::file::file_status filestatus;

   filestatus.m_filesize = size();

   filestatus.m_timeModification.set_null();

   filestatus.m_timeCreation.set_null();

   filestatus.m_timeAccess.set_null();

   return filestatus;

}


void memory_file::copy_this(const memory_file & file)
{

   m_position = file.m_position;

}


memory_file & memory_file::operator = (const memory_file & file)
{

   if (&file == this)
   {

      return *this;

   }

   //::matter::copy_this(file);

   //::file::file::copy_this(file);

   memory_container::copy_this(file);

   return *this;

}


CLASS_DECL_ACME memory_file_pointer create_memory_file()
{
   
   return __new(::memory_file); 

}


CLASS_DECL_ACME memory_file_pointer create_memory_file(::memory_base & memory)
{
   
   return __new(::memory_file(memory)); 

}


CLASS_DECL_ACME memory_file_pointer create_memory_file(const ::block & block)
{
   
   return __new(::memory_file(block)); 

}


CLASS_DECL_ACME memory_file_pointer create_memory_file_as_copy(const memory & memory) 
{
   
   return __new(::memory_file(__new(::memory(memory)))); 

}


CLASS_DECL_ACME memory_file_pointer create_memory_file_by_reading(::file::file * pfile)
{

   auto pmemoryfile = create_memory_file();

   auto left = pfile->get_left();

   if (left > UINTPTR_MAX)
   {

      throw ::exception(error_no_memory);

   }

   pmemoryfile->full_data_set_size(left);

   auto amountRead = pfile->read(pmemoryfile->full_data());

   if (amountRead != pmemoryfile->full_data_size())
   {

      throw ::file::exception(error_failed, { e_error_code_type_unknown, -1 }, pfile->m_path, pfile->m_eopen, "Read bytes less than recorded left bytes");

   }

   //pmemoryfile->m_pbyte = pmemoryfile->data();

   //pmemoryfile->m_memsize = (memsize) pmemoryfile->size();

   return pmemoryfile;

}



