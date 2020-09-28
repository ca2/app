#include "framework.h"


memory_file::memory_file() :
   memory_container(__new(class memory()))
{

   m_position = 0;

}


memory_file::memory_file(efileopen eopen) :
   memory_container(__new(class memory()))
{

   m_eopen = eopen;
   m_position = 0;

}



memory_file::memory_file(memsize size) :
   memory_container(size)
{

   m_position = 0;

}


memory_file::memory_file(const memory_file & m) :
   ::elemental((const elemental &)m),
   file((const file &)m),
   memory_container((const memory_container &)m)
{

   m_position = m.m_position;

}

memory_file::memory_file(memory_file && m) :
   ::elemental(::move(m)),
   file(::move(m)),
   memory_container(::move(m))
{

   m_position = m.m_position;

}





memory_file::memory_file(void * pMemory, memsize dwSize) :
   memory_container(pMemory, dwSize)
{

   m_position = 0;

}


//memory_file::memory_file(const memory_file & memoryfile) :
//   memory_container(((memory_file &)memoryfile).get_memory())
//{
//
//   m_position = 0;
//
//}

memory_file::memory_file(var & var, UINT nFlags) :
   memory_container(var)
{

   m_eopen = nFlags;
   m_position = 0;

}




memory_file::memory_file(memory_base & memory, efileopen eopen) :
   memory_container(memory)
{

   m_eopen = eopen;
   m_position = 0;

}


memory_file::memory_file(memory_base* pmemory, efileopen eopen) :
   memory_container(pmemory)
{

   m_eopen = eopen;
   m_position = 0;

}



//memory_file::memory_file(memory_base * pmemory, efileopen eopen) :
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


memsize memory_file::read(void *pdata, memsize nCount)

{

   return read_inline(pdata, nCount);


}


void memory_file::write(const void * pdata, memsize nCount)

{

   write_inline(pdata, nCount);


}


void memory_file::write_from_hex(const void * pdata, memsize nCount)

{

   char ch = 0;

   strsize iLen = nCount;

   if ((iLen % 2) != 0)
   {

      iLen++;

   }

   memsize iEndPosition = m_position + iLen / 2;

   if (iEndPosition > this->get_size())
   {

      set_size(iEndPosition);

   }

   if (iEndPosition <= 0)
   {

      m_position = 0;

      return;

   }

   byte * pb = get_data();


   ASSERT(__is_valid_address(&(pb)[m_position], (uptr)nCount, TRUE));


   char * pch = (char *)&(pb)[m_position];


   const char * psz = (const char *)pdata;


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


//void memory_file::Truncate(filesize size)
//{
//
//   allocate((memsize)size);
//
//   if (m_position > (memsize)size)
//      m_position = (memsize)size;
//
//
//}



void memory_file::clear()
{

   m_position = 0;

   set_size(0);

}


void memory_file::set_size(filesize size)
{

   ::memory_container::set_size((memsize) size);

   if (m_position > get_size())
   {

      m_position = 0;

   }

}


filesize memory_file::get_size() const
{

   return ::memory_container::get_size();

}


filesize memory_file::get_position() const
{

   if (!is_valid())
   {

      __throw(io_exception("memory_file::get_position"));

   }

   return (filesize)m_position;

}


filesize memory_file::seek(filesize lOff, ::file::e_seek nFrom)
{

   ASSERT(is_valid());

   ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
   //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

   memsize dwNew = (memsize)m_position;

   switch (nFrom)
   {
   case ::file::seek_begin:
      if(lOff < 0)
      {

         dwNew = 0;

      }
      else
      {
         dwNew = (memsize)lOff;

      }
      break;
   case ::file::seek_end:
      if(lOff < -(memsize)get_size())
      {

         dwNew = 0;

      }
      else
      {
         dwNew = (memsize)(get_size() + lOff);
      }
      break;
   case ::file::seek_current:
      if(lOff < -(memsize)m_position)
      {

         dwNew = 0;

      }
      else
      {

         dwNew = (memsize)(m_position + lOff);

      }
      break;
   default:
      return m_position;
   }

   m_position = dwNew;

   //if(dwNew > this->get_size())
   //allocate((memsize) dwNew);

   return (filesize)dwNew;
}


//void memory_file::create(memsize iSize)
//{
//
//   allocate(iSize);
//
//}


void memory_file::load_string(string &str)
{

   char * psz = str.get_string_buffer((i32)(this->get_size() + 1));

   ::memcpy_dup(psz, get_data(), (size_t) this->get_size());

   psz[this->get_size()] = 0;

   str.release_string_buffer();

}


memsize memory_file::remove_begin(void *pdata, memsize uiCount)
{

   //ASSERT(is_valid());

   auto pmemory = get_memory();

   if (uiCount > pmemory->m_memory.m_cbStorage)
   {

      uiCount = pmemory->m_memory.m_cbStorage;

   }

   if (pdata != nullptr)
   {

      ::memcpy(pdata, get_data(), (size_t)uiCount);

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


void memory_file::assert_valid() const
{

   file::assert_valid();

}


void memory_file::dump(dump_context & dumpcontext) const
{

   file::dump(dumpcontext);

}


//void memory_file::full_load(var varFile)
//{
//
//   ASSERT(is_valid());
//
//   auto pfile = Context.file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);
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
//   memsize uiRead;
//
//   while ((uiRead = pfile->read(storage.get_data(), storage.get_size())) > 0)
//   {
//
//      write(storage.get_data(), uiRead);
//
//   }
//
//}


void * memory_file::get_internal_data()
{

   return get_data();

}


memsize memory_file::get_internal_data_size() const
{

   return (memsize) get_size();

}


bool memory_file::set_internal_data_size(memsize c)
{

   set_size(c);

   return c == get_internal_data_size();

}


void memory_file::to(::file::file* pfileOut, memsize uiSize)
{

   if (get_internal_data() == nullptr || get_internal_data_size() <= 0)
   {

      return;

   }

   if (pfileOut->get_internal_data() == get_internal_data())
   {

      return;

   }

   if (uiSize > get_internal_data_size())
   {

      uiSize = get_internal_data_size();

   }

   if (pfileOut->increase_internal_data_size(uiSize) && pfileOut->get_internal_data() != nullptr)
   {

      __memmov(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position() + uiSize, ((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), pfileOut->get_internal_data_size() - uiSize);

      ::memcpy_dup(((u8 *)pfileOut->get_internal_data()) + pfileOut->get_position(), get_internal_data(), uiSize);

      pfileOut->seek(get_internal_data_size(), ::file::seek_current);

   }
   else
   {

      pfileOut->write(get_internal_data(), uiSize);

   }

}


bool memory_file::get_status(::file::file_status & status) const
{

   status.m_size = get_size();

   status.m_mtime = 0;

   status.m_ctime = 0;

   status.m_atime = 0;

   return true;

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

   //::elemental::copy_this(file);

   //::file::file::copy_this(file);

   memory_container::copy_this(file);

   return *this;

}
