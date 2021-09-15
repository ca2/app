#include "framework.h"
#include <stdio.h>
#include <stdarg.h>


thread_local int t_generate_sync_io_error;
thread_local int t_sync_io_error;


CLASS_DECL_ACME int get_sync_io_error()
{

   return t_sync_io_error;

}


CLASS_DECL_ACME void set_sync_io_error(int iError)
{

   t_sync_io_error = iError;

}


CLASS_DECL_ACME int get_generate_sync_io_error()
{

   return t_generate_sync_io_error;

}


CLASS_DECL_ACME void set_generate_sync_io_error(int iError)
{

   t_generate_sync_io_error = iError;

}


namespace file
{

   //HRESULT read_false(::file::file * pfileIn, void* data, memsize size);
   //HRESULT read_fail(::file::file* pfileIn, void* data, memsize size);


   file::file()
   {

      m_millisErrorBlockTimeout = 0;

   }


   /// half-initialization (of file matter)
   /// seeded (the file matter has been...)
   /// (the file matter) requires another call to effectively finish creating itself,
   ///
   /// Much probably another ::matter with some assigned ::acme::application should be supplied
   /// to realize the file matter.
   file::file(const ::file::path & path) :
      m_path(path)
   {

      m_millisErrorBlockTimeout = 0;

   }



   file::~file()
   {

   }


   void file::set_storing()
   {

      m_eopen -= ::file::e_open_read;

      m_eopen |= ::file::e_open_write;

   }


   void file::set_loading()
   {

      m_eopen -= ::file::e_open_write;

      m_eopen |= ::file::e_open_read;

   }


   //file_pointer file::Duplicate() const
   //{

   //   return nullptr;

   //}


   ::extended::status file::open(const ::file::path & path, const ::file::e_open & eopen)
   {

      auto pfile = __create <::file::file>();

      if (!pfile)
      {

         return ::move(pfile);

      }

      auto estatus = pfile->open(path, eopen);

      if (!estatus)
      {

         return estatus;

      }

      return ::move(pfile);

   }


   filesize file::translate(filesize offset, ::enum_seek eseek)
   {

      __UNREFERENCED_PARAMETER(offset);

      __UNREFERENCED_PARAMETER(eseek);

      return 0;

   }


   int file::getc()
   {

      byte byte = 0;

      auto iRead = read(&byte, 1);

      if (iRead <= 0)
      {

         return -1;

      }

      return byte;

   }


   int file::ungetc(int iChar)
   {

      __throw(error_interface_only);

      return -1;

   }


   bool file::is_seekable()
   {

      return true;

   }


   bool file::has_write_mode()
   {

      return m_eopen & ::file::e_open_write;

   }


   filesize file::get_position() const
   {

      return ((file *) this)->translate(0, ::e_seek_current);

   }


   filesize file::set_position(filesize position)
   {

      return ((file *) this)->translate(position, ::e_seek_set);

   }


   filesize file::increment_position(filesize offset)
   {

      return translate(offset, ::e_seek_current);

   }


   filesize file::decrement_position(filesize offset)
   {

      return translate(-offset, ::e_seek_current);

   }


   filesize file::seek_from_end(filesize offset)
   {

      return translate(offset, ::e_seek_from_end);

   }



   void file::flush()
   {
      
   }


   void file::close()
   {


   }


   int file::get()
   {

      unsigned char uch;

      if (read(&uch, 1) == 1)
      {

         return uch;

      }

      return EOF;

   }


   int file::peek()
   {

      unsigned char uch;

      if (read(&uch, 1) == 1)
      {

         --position();

         return uch;

      }

      return EOF;

   }


   ::file::file & file::getline(char* sz, strsize n)
   {

      int c;

      while (n > 0)
      {

         c = get();

         if (c == EOF)
         {

            break;

         }
         else if (c == '\n')
         {

            c = get();

            if (c != '\r' && c != EOF)
            {

               --position();

            }

            break;

         }
         else if (c == '\r')
         {

            c = get();

            if (c != '\n' && c != EOF)
            {

               --position();

            }

            break;

         }

         *sz = (char)c;

         sz++;

         n--;

      }

      return *this;

   }


   memsize file::read(void *pdata, memsize nCount)
   {

      return 0;

   }


   bool file::full_read(void * pdata, memsize nCount)
   {

      memsize uRead;

      memsize uiPos = 0;

      u8 * buf = (u8 *) pdata;

      while(nCount > 0)
      {

         uRead = read(&buf[uiPos], nCount);

         if(uRead <= 0)
         {

            return false;

         }

         nCount   -= uRead;

         uiPos    += uRead;

      }

      return true;

   }


   void file::write_from_hex(const void * pdata,memsize nCount)
   {

      memory memory;

      memory.from_hex((const char *) pdata, nCount);

      write(memory.get_data(),memory.get_size());

   }


   void file::write(const void * pdata, memsize nCount)
   {

   }


   void file::write(const memory_base & base)
   {

      write(base.get_data(), base.get_size());

   }


   void file::lock(filesize dwPos, filesize dwCount)
   {

      __UNREFERENCED_PARAMETER(dwPos);
      __UNREFERENCED_PARAMETER(dwCount);

   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {

      __UNREFERENCED_PARAMETER(dwPos);
      __UNREFERENCED_PARAMETER(dwCount);

   }


   void file::set_size(filesize dwNewLen)
   {

      __UNREFERENCED_PARAMETER(dwNewLen);

   }


   filesize file::get_size() const
   {

      return 0;

   }


   void file::assert_valid() const
   {

   }


   void file::dump(dump_context & dumpcontext) const
   {

   }


   ::file::path file::get_file_path() const
   {

      return m_path;

   }


   bool file::get_status(file_status & rStatus) const
   {

      __UNREFERENCED_PARAMETER(rStatus);

      return false;

   }


   bool file::is_opened() const
   {

      return false;

   }


   bool file::is_valid() const
   {

      return is_opened();

   }

   string file::get_location() const
   {

      return get_file_path();

   }


   bool file::read(char * pch)
   {

      if(read(pch, 1) != 1)
      {

         return false;

      }

      return true;
      
   }


   bool file::read(uchar * puch)
   {

      if(read(puch, 1) != 1)
      {

         return false;

      }

      return true;
      
   }


   bool file::peek(char * pch)
   {

      if(read(pch, 1) != 1)
      {

         return false;

      }

      --position();

      return true;

   }


   bool file::peek(uchar * puch)
   {
   
      if(read(puch, 1) != 1)
      {

         return false;

      }

      --position();

      return true;

   }


   int file::peek_character()
   {

      char ch;

      if (!peek(&ch))
      {

         return -1;

      }

      return ch;

   }


   int file::get_character()
   {

      char ch;

      if (read(&ch, 1) <= 0)
      {

         return -1;

      }

      return ch;

   }


   int file::put_character_back(int iCharacter)
   {

      __throw(error_interface_only);

      return -1;

   }


   bool file::read_string(string & str)
   {

      int i = get_character();

      if (i == EOF)
      {

         return false;

      }

      str.Empty();

      memory m;

      while (i != EOF)
      {

         if ((char)i == '\n' || (char)i == '\r')
         {

            break;

         }
         
         char ch = i;

         m.append(&ch, 1);

         i = get_character();

      };

      str = m.as_utf8();

      int iNew = get_character();

      if(iNew == EOF)
      {

         return true;

      }

      if (iNew == i || ((char)iNew != '\n' && (char)iNew != '\r'))
      {

         put_character_back(iNew);

      }

      return true;

   }


   bool file::read_string(memory_base & mem)
   {

      m_estate -= ::file::e_state_read_line_truncated;

      int i = get_character();

      if (i == EOF)
      {

         return false;

      }

      strsize iPos = 0;

      while (i != EOF)
      {

         if ((char)i == '\n' || (char)i == '\r')
         {

            break;

         }

         mem.set_char_at_grow(iPos, char(i));

         i = get_character();

         iPos++;

      };

      mem.set_char_at_grow(iPos, '\0');

      int iNew = get_character();

      if ((iNew == i || ((char)iNew != '\n' && (char)iNew != '\r')) && iNew != EOF)
      {

         --position();

      }

      return true;

   }


   bool file::read_block(const block & block)
   {

      auto readBytes = read(block.get_data(), block.get_size());

      return readBytes == block.get_size();

   }


   bool file::full_read(memory_base & memory)
   {

      auto fileLen = get_size();

      memory.set_size((memsize)fileLen);

      auto readBytes = read(memory.get_data(), memory.length());

      return readBytes == fileLen;

   }


   bool file::full_read_string(string & str)
   {

      ::memory memory;

      full_read(memory);

      str = memory.to_string();

      return true;

   }


   void file::print(const ::string & str)
   {

      write(str);

   }


   void file::println(const ::string & str)
   {

      print(str);

      write(LINE_SEPARATOR, STATIC_ASCII_STRING_LENGTH(LINE_SEPARATOR));

   }


   void file::printf(const char *format, ...)
   {

      string strFormat;

      va_list list;

      va_start(list, format);

      strFormat.Format(format, list);

      va_end(list);

      write(strFormat);

   }


   void file::set_file_path(const ::file::path & path)
   {

      __UNREFERENCED_PARAMETER(path);

   }


   void file::write(const ::string & str)
   {

      write(str,  str.get_length());

   }


   void* file::get_internal_data()
   {

      return nullptr;

   }


   const void* file::get_internal_data() const
   {

      return ((file*)this)->get_internal_data();

   }


   memsize file::get_internal_data_size() const
   {

      return 0;

   }


   bool file::set_internal_data_size(memsize c)
   {

      return false;

   }


   bool file::increase_internal_data_size(memsize c)
   {

      return set_internal_data_size(c + get_internal_data_size());

   }


   filesize file::seek_to_begin()
   {

      return set_position(0);

   }


   filesize file::seek_to_end()
   {

      return translate(0, e_seek_from_end);

   }


   filesize file::find(const void * pFind, memsize sizeFind, const filesize * psizeStop)
   {

      throw_todo();

      return -1;

      //const u32 kBufferSize = (1 << 16);

      //u8 * pu8Find = (u8 *) pFind;

      //memory memory;

      //memory.set_size(kBufferSize);

      //u8 * buffer = memory.get_data();

      //memsize positionSearch = 0;

      //memsize sizeTotalRead = 0;

      //for (;;)
      //{

      //   if (psizeStop != nullptr)
      //   {

      //      if (positionSearch > *psizeStop)
      //      {

      //         return -1;

      //      }

      //   }

      //   do
      //   {

      //      memsize sizeRequestRead = kBufferSize - sizeTotalRead;

      //      memsize sizeRead;

      //      sizeRead = read(buffer + sizeTotalRead, sizeRequestRead);

      //      sizeTotalRead += sizeRead;

      //      if (sizeRead == 0)
      //      {

      //         return -1;

      //      }

      //   }
      //   while (sizeTotalRead < sizeFind);

      //   u32 sizeSearch = (u32) (sizeTotalRead - sizeFind + 1);

      //   for (u32 pos = 0; pos < sizeSearch; pos++)
      //   {

      //      byte b = pu8Find[0];

      //      if(buffer[pos] != b && pos < sizeSearch; pos++);

      //      if (pos == sizeSearch)
      //      {

      //         break;

      //      }

      //      if (__memcmp(buffer + pos, pu8Find, (size_t) sizeFind) == 0)
      //      {

      //         positionSearch += pos;

      //         return positionSearch;

      //      }

      //   }
      //   
      //   positionSearch += sizeSearch;

      //   sizeTotalRead -= sizeSearch;

      //   __memmov(buffer, buffer + sizeSearch, sizeTotalRead);

      //}

   }


   void file::to(::file::file * pfileOut, memsize uiBufMax)
   {

      pfileOut->set_size(0);

      read_file(pfileOut, uiBufMax);


   }


   void file::read_file(::file::file * pfileOut, memsize uiBufMax)
   {

      if(get_internal_data() && get_internal_data_size() > 0)
      {

         if(pfileOut->increase_internal_data_size(get_internal_data_size()) && pfileOut->get_internal_data() != nullptr)
         {

            if(pfileOut->get_internal_data() == get_internal_data())
               return;

            __memmov(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position() + get_internal_data_size(), ((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), pfileOut->get_internal_data_size() - get_internal_data_size());
            ::memcpy_dup(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), get_internal_data(), get_internal_data_size());
            pfileOut->position() += get_internal_data_size();

         }
         else
         {

            pfileOut->write(get_internal_data(), get_internal_data_size());

         }

         return;

      }

      uiBufMax = maximum(8 * 1024, uiBufMax);
      memsize uiBufMin = uiBufMax / 8;
      memsize uiBufSize = uiBufMax;
      memsize uiBufInc = uiBufSize;
      memsize uRead;
      memsize uiSize = pfileOut->get_internal_data_size();

      while(pfileOut->increase_internal_data_size(uiBufInc) && pfileOut->get_internal_data() != nullptr)
      {
         __memmov(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position() + uiBufInc, ((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), uiBufInc);
         uRead = read(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), uiBufSize);
         pfileOut->position() += uRead;
         uiBufSize -= uRead;
         if(uiBufSize < uiBufMin)
         {
            uiBufSize   = uiBufMax;
            uiBufInc    = uiBufSize;
         }
      }

      if(uiBufSize > 0)
      {
         __memmov(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), ((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position() + uiBufSize, uiBufSize);
         pfileOut->increase_internal_data_size(-(memsize)uiBufSize);
      }

      memory buf;
      buf.set_size(uiBufMax);
      if(buf.get_data() == nullptr)
         __throw(error_no_memory, "no memory");
      try
      {
         while(true)
         {
            uRead = read(buf, buf.get_size());
            pfileOut->write(buf, uRead);
            if(uRead <= 0)
            {
               return;
            }
            uiSize += uRead;
         }
      }
      catch(...)
      {

      }

   }


   static const memsize kBlockSize = ((u32)1 << 31);


   ::e_status read(::file::file * pfileIn, void * data, memsize * sizeRead)
   {

      memsize size = *sizeRead;

      *sizeRead = 0;

      while (size != 0)
      {

         memsize curSize = minimum(size, kBlockSize);

         memsize processedSizeLoc;

         ::e_status estatus = ::success;

         try
         {

            processedSizeLoc = pfileIn->read(data, curSize);

         }
         catch(...)
         {

             estatus = error_failed;

         }

         *sizeRead += processedSizeLoc;

         data = (void *)((u8 *)data + processedSizeLoc);

         size -= processedSizeLoc;

         if(!estatus)
         {


         }

         if (processedSizeLoc == 0)
         {

            return ::success;

         }

      }

      return ::success;

   }


   void file::write(const void *pdata, memsize nCount, memsize * dwWritten)
   {

      ::exception::throw_interface_only();

   }

   void file::from_begin(::file::file * pfileIn, memsize uiBufSize)
   {

      set_size(0);

      write_file_from_begin(pfileIn, uiBufSize);

   }


   void file::write_file_from_begin(::file::file * pfileIn, memsize uiBufSize)
   {

      pfileIn->seek_to_begin();

      write_file(pfileIn, uiBufSize);

   }


   void file::from(::file::file * pfileIn, memsize uiBufSize)
   {

      set_size(0);

      write_file(pfileIn, uiBufSize);

   }


   void file::write_file(::file::file* pfileIn, memsize uiBufSize)
   {

      if(pfileIn->get_internal_data() != nullptr && pfileIn->get_internal_data_size() > pfileIn->get_position())
      {

         write((u8 *) pfileIn->get_internal_data() + pfileIn->get_position(), (memsize) (pfileIn->get_internal_data_size() - pfileIn->get_position()));

         return;

      }


      memsize uRead;
      memsize uiSize = 0;
      uiBufSize = maximum(32 * 1024, uiBufSize);

      memory buf;

      buf.set_size(uiBufSize);

      if(buf.get_data() == nullptr)
         __throw(error_no_memory);

      try
      {
         while(true)
         {
            uRead = pfileIn->read(buf.get_data(), buf.get_size());
            if(uRead <= 0)
            {
               break;
            }
            write(buf.get_data(), uRead);
            uiSize += uRead;
         }
      }
      catch(...)
      {
      }

   }

   /*
   bool file::is_writer_null()
   {
      return m_spwriter.is_null();
   }

   bool file::is_writer_set()
   {
      return m_spwriter.is_set();
   }
   */
   //void file::close()
   //{
   //   /*
   //   if(m_spwriter.is_set())
   //   {
   //      //m_spwriter->close();
   //      ::release(m_spwriter.m_p);
   //   }
   //   */
   //}

   /*
   void file::from_hex(const char * psz)
   {
      memory memory;
      memory.from_hex(psz);
      write(memory.get_data(), memory.get_size());
   }*/

   //void file::flush()
   //{
   //}

   /*
   void file::write (char ch)
   {
      __UNREFERENCED_PARAMETER(ch);
      ::exception::throw_interface_only();
   }

   void file::write (uchar uch)
   {
      __UNREFERENCED_PARAMETER(uch);
      ::exception::throw_interface_only();
   }

   void file::write (i16 sh)
   {
      __UNREFERENCED_PARAMETER(sh);
      ::exception::throw_interface_only();
   }

   void file::write (u16 u)
   {
      __UNREFERENCED_PARAMETER(u);
      ::exception::throw_interface_only();
   }

   void file::write (unichar wch)
   {
      __UNREFERENCED_PARAMETER(wch);
      ::exception::throw_interface_only();
   }

   void file::write (bool b)
   {
      __UNREFERENCED_PARAMETER(b);
      ::exception::throw_interface_only();
   }

   void file::write (i32 i)
   {
      __UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only();
   }

   void file::write (u32 u)
   {
      __UNREFERENCED_PARAMETER(u);
      ::exception::throw_interface_only();
   }

   void file::write (i64 i)
   {
      __UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only();
   }

   void file::write (u64 u)
   {
      __UNREFERENCED_PARAMETER(u);
      ::exception::throw_interface_only();
   }

   void file::write (float f)
   {
      __UNREFERENCED_PARAMETER(f);
      ::exception::throw_interface_only();
   }

   void file::write (double d)
   {
      __UNREFERENCED_PARAMETER(d);
      ::exception::throw_interface_only();
   }

   void file::write (const ::rectangle_i32 & rectangle)
   {
      __UNREFERENCED_PARAMETER(pcrect);

      ::exception::throw_interface_only();
   }

   void file::write (const size_i32 & & size)
   {
      __UNREFERENCED_PARAMETER(size);
      ::exception::throw_interface_only();
   }

   void file::write (::type info)
   {
      __UNREFERENCED_PARAMETER(info);
      ::exception::throw_interface_only();
   }

   void file::write (matter & matter)
   {
      __UNREFERENCED_PARAMETER(matter);
      ::exception::throw_interface_only();
   }

   void file::write (const char * psz)
   {
      __UNREFERENCED_PARAMETER(psz);
      ::exception::throw_interface_only();
   }

   void file::write (const id & id)
   {
      __UNREFERENCED_PARAMETER(id);
      ::exception::throw_interface_only();
   }

   void file::write (const ::payload & payload)
   {
      __UNREFERENCED_PARAMETER(payload);
      ::exception::throw_interface_only();
   }

   void file::write (const ::string & str)
   {
      __UNREFERENCED_PARAMETER(str);
      ::exception::throw_interface_only();
   }
   */


    ::e_status write(file * pwriter, const void * data, memsize size)
    {

        ::e_status estatus = ::success;

        try
        {

            pwriter->write(data, size);

        }
        catch(...)
        {

            estatus = error_failed;

        }

        if(!estatus)
        {

            return estatus;

        }

        return estatus;

    }


    filesize file::get_left() const
    {

        return get_size() - get_position();

    }


   string file::to_string() const
   {

      string str;

      auto pfile = (file *)this;

      auto position = pfile->get_position();

      pfile->full_read_string(str);

      pfile->set_position(position);

      return str;

   }


   void file::as_memory(memory_base & memory) const
   {

      auto pfile = (file*)this;

      auto position = pfile->get_position();

      pfile->full_read(memory);

      pfile->set_position(position);

   }


   ::file::file& file::put(char ch) 
   {
      
      write(&ch, 1); 
      
      return *this; 
   
   }


   CLASS_DECL_ACME void set_no_cache(::payload& payload)
   {

      if (payload.get_type() == e_type_property_set)
      {

         payload["nocache"] = true;

      }
      else
      {

         payload.as_file_path() |= ::file::e_flag_bypass_cache;

      }

   }


} // namespace file



