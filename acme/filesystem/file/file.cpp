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

      m_dwErrorBlockTimeout = 0;
      m_eopen = 0;

   }


   /// half-initialization (of file element)
   /// seeded (the file element has been...)
   /// (the file element) requires another call to effectively finish creating itself,
   ///
   /// Much probably another ::element with some assigned ::acme::application should be supplied
   /// to realize the file element.
   file::file(const ::file::path & path) :
      m_path(path)
   {

      m_dwErrorBlockTimeout = 0;
      m_eopen = 0;

   }



   file::~file()
   {

   }


   void file::set_storing()
   {

      m_eopen -= ::file::mode_read;

      m_eopen |= ::file::mode_write;

   }


   void file::set_loading()
   {

      m_eopen -= ::file::mode_write;

      m_eopen |= ::file::mode_read;

   }


   //file_pointer file::Duplicate() const
   //{

   //   return nullptr;

   //}


   ::status::result file::open(const ::file::path & path, const efileopen & eopen)
   {

      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(eopen);

      return ::error_failed;

   }


   filesize file::seek(filesize lOff, ::file::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }


   bool file::is_seekable()
   {

      return true;

   }


   filesize file::seek_from_begin(filesize lPos)
   {

      return seek(lPos, ::file::seek_begin);

   }


   filesize file::seek_to_begin(filesize lPos)
   {

      return seek_from_begin(lPos);

   }


   filesize file::seek_begin(filesize lPos)
   {

      return seek_to_begin(lPos);

   }


   bool file::has_write_mode()
   {

      return m_eopen & ::file::mode_write;

   }

   filesize file::get_position() const
   {
      return ((file *) this)->seek(0, ::file::seek_current);
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
         return uch;

      return EOF;

   }


   int file::peek()
   {
      unsigned char uch;

      if (read(&uch, 1) == 1)
      {
         seek(-1, ::file::seek_current);
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
               seek(-1, ::file::seek_current);
            break;
         }
         else if (c == '\r')
         {
            c = get();
            if (c != '\n' && c != EOF)
               seek(-1, ::file::seek_current);
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

      memsize uiRead;
      memsize uiPos = 0;
      u8 * buf = (u8 *) pdata;


      while(nCount > 0)
      {

         uiRead = read(&buf[uiPos], nCount);

         if(uiRead <= 0)
         {

            return false;

         }

         nCount   -= uiRead;
         uiPos    += uiRead;

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

      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);

   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {

      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);

   }


   void file::set_size(filesize dwNewLen)
   {

      UNREFERENCED_PARAMETER(dwNewLen);

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

      UNREFERENCED_PARAMETER(rStatus);

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

      seek(-1, ::file::seek_current);

      return true;

   }


   bool file::peek(uchar * puch)
   {
   
      if(read(puch, 1) != 1)
      {

         return false;

      }

      seek(-1, ::file::seek_current);

      return true;

   }


   int file::sgetc()
   {

      char ch;

      if (!peek(&ch))
      {

         return EOF;

      }

      return ch;

   }


   int file::sbumpc()
   {

      char ch;

      if (read(&ch, 1) <= 0)
      {

         return EOF;

      }

      return ch;

   }


   bool file::read_string(string & str)
   {

      int i = sbumpc();

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

         i = sbumpc();

      };

      m.to_string(str);

      int iNew = sbumpc();

      if(iNew == EOF)
      {

         return true;

      }

      if (iNew == i || ((char)iNew != '\n' && (char)iNew != '\r'))
      {

         seek(-1, seek_current);

      }

      return true;

   }


   bool file::read_string(memory_base & mem)
   {

      m_efilestate -= filestate_read_line_truncated;

      int i = sbumpc();

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

         i = sbumpc();

         iPos++;

      };

      mem.set_char_at_grow(iPos, '\0');

      int iNew = sbumpc();

      if ((iNew == i || ((char)iNew != '\n' && (char)iNew != '\r')) && iNew != EOF)
      {

         seek(-1, seek_current);

      }

      return true;

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

      memory.to_string(str);

      return true;

   }


   void file::print(const string & str)
   {

      write(str, str.get_length());

   }


   void file::println(const string & str)
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

      UNREFERENCED_PARAMETER(path);

   }


   void file::write(const string & str)
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


   filesize file::seek_to_end()
   {

      return seek(0, seek_end);

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
            pfileOut->seek(get_internal_data_size(), seek_current);

         }
         else
         {

            pfileOut->write(get_internal_data(), get_internal_data_size());

         }

         return;

      }

      uiBufMax = max(8 * 1024, uiBufMax);
      memsize uiBufMin = uiBufMax / 8;
      memsize uiBufSize = uiBufMax;
      memsize uiBufInc = uiBufSize;
      memsize uiRead;
      memsize uiSize = pfileOut->get_internal_data_size();

      while(pfileOut->increase_internal_data_size(uiBufInc) && pfileOut->get_internal_data() != nullptr)
      {
         __memmov(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position() + uiBufInc, ((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), uiBufInc);
         uiRead = read(((u8 *) pfileOut->get_internal_data()) + pfileOut->get_position(), uiBufSize);
         pfileOut->seek(uiRead, seek_current);
         uiBufSize -= uiRead;
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
         __throw(::exception::exception("no memory"));
      try
      {
         while(true)
         {
            uiRead = read(buf, buf.get_size());
            pfileOut->write(buf, uiRead);
            if(uiRead <= 0)
            {
               return;
            }
            uiSize += uiRead;
         }
      }
      catch(...)
      {

      }

   }


   //filesize file::get_position() const
   //{
   //   ::exception::throw_interface_only();
   //   return 0;
   //}


   //bool file::get_length(filesize & size) const
   //{

   //   return false;

   //}

   //
   //::filesize file::get_left() const
   //{

   //   return get_length() - get_position();

   //}


   static const memsize kBlockSize = ((u32)1 << 31);


   HRESULT read(::file::file * pfileIn, void * data, memsize * sizeRead)
   {

      memsize size = *sizeRead;

      *sizeRead = 0;

      while (size != 0)
      {

         memsize curSize = min(size, kBlockSize);

         memsize processedSizeLoc;

         HRESULT res = S_OK;

         try
         {

            processedSizeLoc = pfileIn->read(data, curSize);

         }
         catch(...)
         {

            res = E_FAIL;

         }

         *sizeRead += processedSizeLoc;

         data = (void *)((u8 *)data + processedSizeLoc);

         size -= processedSizeLoc;

         RINOK(res);

         if (processedSizeLoc == 0)
         {

            return S_OK;

         }

      }

      return S_OK;

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


      memsize uiRead;
      memsize uiSize = 0;
      uiBufSize = max(32 * 1024, uiBufSize);

      memory buf;

      buf.set_size(uiBufSize);

      if(buf.get_data() == nullptr)
         __throw(memory_exception());

      try
      {
         while(true)
         {
            uiRead = pfileIn->read(buf.get_data(), buf.get_size());
            if(uiRead <= 0)
            {
               break;
            }
            write(buf.get_data(), uiRead);
            uiSize += uiRead;
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
      UNREFERENCED_PARAMETER(ch);
      ::exception::throw_interface_only();
   }

   void file::write (uchar uch)
   {
      UNREFERENCED_PARAMETER(uch);
      ::exception::throw_interface_only();
   }

   void file::write (i16 sh)
   {
      UNREFERENCED_PARAMETER(sh);
      ::exception::throw_interface_only();
   }

   void file::write (u16 ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only();
   }

   void file::write (unichar wch)
   {
      UNREFERENCED_PARAMETER(wch);
      ::exception::throw_interface_only();
   }

   void file::write (bool b)
   {
      UNREFERENCED_PARAMETER(b);
      ::exception::throw_interface_only();
   }

   void file::write (i32 i)
   {
      UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only();
   }

   void file::write (u32 ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only();
   }

   void file::write (i64 i)
   {
      UNREFERENCED_PARAMETER(i);
      ::exception::throw_interface_only();
   }

   void file::write (u64 ui)
   {
      UNREFERENCED_PARAMETER(ui);
      ::exception::throw_interface_only();
   }

   void file::write (float f)
   {
      UNREFERENCED_PARAMETER(f);
      ::exception::throw_interface_only();
   }

   void file::write (double d)
   {
      UNREFERENCED_PARAMETER(d);
      ::exception::throw_interface_only();
   }

   void file::write (const ::rect & rect)
   {
      UNREFERENCED_PARAMETER(pcrect);

      ::exception::throw_interface_only();
   }

   void file::write (const size & & size)
   {
      UNREFERENCED_PARAMETER(size);
      ::exception::throw_interface_only();
   }

   void file::write (::type info)
   {
      UNREFERENCED_PARAMETER(info);
      ::exception::throw_interface_only();
   }

   void file::write (element & element)
   {
      UNREFERENCED_PARAMETER(element);
      ::exception::throw_interface_only();
   }

   void file::write (const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      ::exception::throw_interface_only();
   }

   void file::write (const id & id)
   {
      UNREFERENCED_PARAMETER(id);
      ::exception::throw_interface_only();
   }

   void file::write (const var & var)
   {
      UNREFERENCED_PARAMETER(var);
      ::exception::throw_interface_only();
   }

   void file::write (const string & str)
   {
      UNREFERENCED_PARAMETER(str);
      ::exception::throw_interface_only();
   }
   */


   HRESULT write(file * pwriter, const void * data, memsize size)
   {
      HRESULT res = S_OK;
      try
      {
         pwriter->write(data, size);
      }
      catch(...)
      {
         res = E_FAIL;
      }
      RINOK(res);
      return res;
   }



   filesize file::get_left() const
   {

      return get_size() - get_position();

   }


   void file::to_string(const class string_exchange & str) const
   {

      auto pfile = (file *)this;

      pfile->full_read_string(*str.m_pstr);

   }


   ::file::file& file::put(char ch) 
   {
      
      write(&ch, 1); 
      
      return *this; 
   
   }

   CLASS_DECL_ACME void set_no_cache(var& var)
   {

      if (var.get_type() == type_propset)
      {

         var["nocache"] = true;

      }
      else
      {

         var.operator path &() |= ::file::flag_bypass_cache;

      }

   }


} // namespace file



