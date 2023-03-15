#include "framework.h"
#include "file.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
//#include "acme/primitive/primitive/payload.h"
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

      m_estatus = error_not_initialized;

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


   void file::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
   {

//      auto pfile = __create <::file::file>();
//
//      if (::is_null(pfile))
//      {
//
//         ::transfer(pfile);
//
//      }
//
///*      auto estatus =*/
//
//      pfile->open(path, eopen);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      /* return */ ::transfer(pfile);

   }


   void file::translate(filesize offset, ::enum_seek eseek)
   {

      __UNREFERENCED_PARAMETER(offset);

      __UNREFERENCED_PARAMETER(eseek);

      //return 0;

   }


   int file::getc()
   {

      byte byte = 0;

      auto iRead = read({ &byte, 1 });

      if (iRead <= 0)
      {

         return -1;

      }

      return byte;

   }


   int file::ungetc(int iChar)
   {

      throw ::interface_only();

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

      throw interface_only();

      return 0;

      //return ((file *) this)->translate(0, ::e_seek_current);

   }


   void file::set_position(filesize position)
   {

      ((file *) this)->translate(position, ::e_seek_set);

   }


    void file::increment_position(filesize offset)
   {

      translate(offset, ::e_seek_current);

   }


    void file::decrement_position(filesize offset)
   {

      return translate(-offset, ::e_seek_current);

   }


    void file::seek_from_end(filesize offset)
   {

      return translate(offset, ::e_seek_from_end);

   }


   void file::abort()
   {

   }


   void file::flush()
   {
      
   }


   void file::close()
   {


   }


   ::file::file & file::getline(char* sz, strsize n)
   {

      char c;

      while (n > 0)
      {

         c = (char) get_u8();

         if (is_end_of_file())
         {

            break;

         }
         else if (c == '\n')
         {

            c = (char) get_u8();

            if (c != '\r' && !is_end_of_file())
            {

               --position();

            }

            break;

         }
         else if (c == '\r')
         {

            c = get_u8();

            if (c != '\n' && !is_end_of_file())
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


   memsize file::read(const ::block & block)
   {

      return 0;

   }


   bool file::full_read(const ::block & block)
   {

      memsize uRead;

      memsize uiPos = 0;

      auto nCount = block.size();

      while(nCount > 0)
      {

         uRead = read(block(uiPos, nCount));

         if(uRead <= 0)
         {

            return false;

         }

         nCount   -= uRead;

         uiPos    += uRead;

      }

      return true;

   }


   void file::write_from_hex(const ::block & block)
   {

      memory memory;

      memory.from_hex(block);

      write(memory);

   }


   void file::write(const ::block & block)
   {

   }


   //void file::write(const ::block & block)
   //{

   //   write(block.data(), block.size());

   //}


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


   filesize file::size() const
   {

      return 0;

   }


//   void file::assert_ok() const
//   {
//
//   }
//
//
//   void file::dump(dump_context & dumpcontext) const
//   {
//
//   }


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


   bool file::read(char * pchar)
   {

      return read((byte *)pchar);
      
   }


   bool file::read(byte * pbyte)
   {

      if (!read({ pbyte, 1 }))
      {

         set_end_of_file();

         return false;

      }

      return true;
      
   }


   bool file::peek(char * pchar)
   {

      return peek((::byte *)pchar);

   }


   bool file::peek(byte * pbyte)
   {
   
      if (!read({ pbyte, 1 }))
      {

         set_end_of_file();

         return false;

      }

      --position();

      return true;

   }


   int file::peek_byte()
   {

      ::byte b = 0;

      if (peek(&b) != 1)
      {

         return -1;

      }

      return b;

   }


   int file::get_u8()
   {

      byte byte = 0;

      if (read(&byte) != 1)
      {

         return -1;

      }

      return byte;

   }

   
   int file::get_u16()
   {

      u16 u = 0;

      if (read({ &u, 2 }) != 2)
      {

         return -1;

      }

      return u;

   }


   bool file::get_u64(::u64 & u)
   {

      if (read({ &u, 8 }) != 8)
      {

         return false;

      }

      return true;

   }


   void file::put_byte_back(::byte byte)
   {

      throw ::exception(::error_unsupported_function, "Please use buffered_file for buffered operations.");

   }


   bool file::read_string(string & str)
   {

      memory mem;

      str.empty();

      if (!read_string(mem))
      {

         return false;

      }

      str = mem.as_utf8();

      return true;

   }


   bool file::read_string(memory_base & memory)
   {

      auto position = get_position();

      byte b;

      byte b1 = 0;

      while (true)
      {

         if (b1)
         {

            b = b1;

            b1 = 0;

         }
         else
         {

            b = get_u8();

         }

         if (is_end_of_file())
         {

            if (get_position() > position)
            {

               return true;

            }
            else
            {

               return false;

            }

         }

         if (b == '\r')
         {

            b1 = get_u8();

            if (b1 != '\n' && !is_end_of_file())
            {

               b = '\r';

            }

            return true;

         }
         else if (b == '\n')
         {

            return true;

         }

         memory.append(&b, 1);

      }

   }


   bool file::read_block(block & block)
   {

      auto readBytes = read(block);

      return readBytes == block.size();

   }


   void file::as(memory_base & memory)
   {

      auto left = get_left();

      if(left > 100000000000000)
      {

         int i = 1;

         int j = 2;

         int l = i+j;

      }

      memory.set_size((memsize)left);

      auto readBytes = read(memory);

      if(readBytes != left)
      {
         
         throw ::file::exception(error_io, {e_error_code_type_unknown, 0}, m_path, m_eopen, "readBytes != left");
         
      }

   }


   ::memory file::as_memory()
   {
      
      ::memory memory;
      
      as(memory);
      
      return ::transfer(memory);
      
   }


   void file::as(string & str)
   {

      ::memory memory;

      as(memory);

      str = memory.get_string();

   }


   ::string file::as_string()
   {
      
      ::string string;
      
      as(string);
      
      return ::transfer(string);
      
   }


   void file::print(const ::string & str)
   {

      write(str);

   }


   void file::println(const ::string & str)
   {

      print(str);

      write({ LINE_SEPARATOR, STATIC_ASCII_STRING_LENGTH(LINE_SEPARATOR) });

   }


   void file::printf(const char *format, ...)
   {

      string strFormat;

      va_list list;

      va_start(list, format);

      strFormat.format(format, list);

      va_end(list);

      write(strFormat);

   }


   void file::set_file_path(const ::file::path & path)
   {

      __UNREFERENCED_PARAMETER(path);

   }


//   void file::write(const ::string & str)
//   {
//
//      write(str,  str.length());
//
//   }


   bool file::is_end_of_file() const 
   {
      
      return m_estate & ::file::e_state_end_of_file; 
   
   }
   
   
   void file::set_end_of_file() 
   {
      
      m_estate |= ::file::e_state_end_of_file; 
   
   }


   bool file::is_in_memory_file() const
   {

      return false;

   }


   ::byte * file::full_data_begin()
   {

      return nullptr;

   }


   ::byte * file::full_data_end()
   {

      return nullptr;

   }

   
   const ::byte * file::full_data_begin() const
   {

      return nullptr;

   }


   const ::byte * file::full_data_end() const
   {

      return nullptr;

   }


   ::byte * file::data_begin()
   {

      return nullptr;

   }


   ::byte * file::data_end()
   {

      return nullptr;

   }


   const ::byte * file::data_begin() const
   {

      return nullptr;

   }


   const ::byte * file::data_end() const
   {

      return nullptr;

   }

   //const void* file::get_internal_data() const
   //{

   //   return ((file*)this)->get_internal_data();

   //}


   //memsize file::get_internal_data_size() const
   //{

   //   return 0;

   //}


   bool file::full_data_set_size(memsize c)
   {

      return false;

   }


   bool file::full_data_increase_size(memsize c)
   {

      return false;

   }


   void file::seek_to_begin()
   {

      return set_position(0);

   }


   void file::seek_to_end()
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

      //u8 * buffer = memory.data();

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


   //void file::to(::file::file * pfileOut, memsize uiBufMax)
   //{

   //   pfileOut->set_size(0);

   //   read_file(pfileOut, uiBufMax);


   //}


   //void file::read_file(::file::file * pfileOut, memsize uiBufMax)
   //{

   //   if(internal_data().is_set())
   //   {

   //      if(pfileOut->increase_internal_data_size(internal_data().size()) && pfileOut->internal_data().is_set())
   //      {

   //         if (pfileOut->internal_data() == internal_data())
   //         {

   //            return;

   //         }

   //         __memmov(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + internal_data().size(), ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), pfileOut->internal_data().size() - internal_data().size());

   //         ::memcpy_dup(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), internal_data().data(), internal_data().size());

   //         pfileOut->position() += internal_data().size();

   //      }
   //      else
   //      {

   //         pfileOut->write(internal_data());

   //      }

   //      return;

   //   }

   //   uiBufMax = maximum(8 * 1024, uiBufMax);
   //   memsize uiBufMin = uiBufMax / 8;
   //   memsize uiBufSize = uiBufMax;
   //   memsize uiBufInc = uiBufSize;
   //   memsize uRead;
   //   ///memsize uiSize = pfileOut->get_internal_data_size();

   //   while(pfileOut->increase_internal_data_size(uiBufInc) && pfileOut->internal_data().data() != nullptr)
   //   {
   //      __memmov(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + uiBufInc, ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), uiBufInc);
   //      uRead = read(pfileOut->internal_data()(pfileOut->get_position(), uiBufSize));
   //      pfileOut->position() += uRead;
   //      uiBufSize -= uRead;
   //      if(uiBufSize < uiBufMin)
   //      {
   //         uiBufSize   = uiBufMax;
   //         uiBufInc    = uiBufSize;
   //      }
   //   }

   //   if(uiBufSize > 0)
   //   {

   //      __memmov(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + uiBufSize, uiBufSize);

   //      pfileOut->increase_internal_data_size(-(memsize)uiBufSize);

   //   }

   //   memory buf;

   //   buf.set_size(uiBufMax);

   //   try
   //   {
   //      
   //      while(true)
   //      {
   //         
   //         uRead = read(buf);

   //         pfileOut->write(buf(0, uRead));

   //         if(uRead <= 0)
   //         {

   //            return;

   //         }

   //      }

   //   }
   //   catch(...)
   //   {

   //   }

   //}


   static const memsize kBlockSize = ((u32)1 << 31);


   //memsize read(::file::file * pfileIn, const ::block & block)
   //{

   //   auto p = block.data();

   //   auto sizeLeft = block.size();

   //   memsize totalRead = 0;

   //   while (sizeLeft > 0)
   //   {

   //      memsize sizeToRead = minimum(sizeLeft, kBlockSize);

   //      ::e_status estatus = ::success;

   //      auto amountRead = pfileIn->read({ p, sizeToRead });

   //      if (amountRead <= 0)
   //      {

   //         return totalRead;

   //      }

   //      totalRead += amountRead;

   //      p += amountRead;

   //      sizeLeft -= amountRead;

   //   }

   //}


   memsize file::defer_write(const ::block & block)
   {

      throw ::interface_only();

      return 0;

   }


   /*void file::from_begin(::file::file * pfileIn, memsize uiBufSize)
   {

      set_size(0);

      write_file_from_begin(pfileIn, uiBufSize);

   }*/


   void file::write_from_beginning(::file::file * pfileIn, memsize uiBufSize)
   {

      pfileIn->seek_to_begin();

      write(pfileIn, uiBufSize);

   }


   /*void file::from(::file::file * pfileIn, memsize uiBufSize)
   {

      write_file(pfileIn, uiBufSize);

   }*/


   void file::write(::file::file* pfileIn, memsize uiBufSize)
   {

      if(pfileIn->full_data_is_set())
      {

         write(pfileIn->data());

         return;

      }

      memsize uRead;
      //memsize uiSize = 0;
      uiBufSize = maximum(32 * 1024, uiBufSize);

      memory buf;

      buf.set_size(uiBufSize);

      if(buf.data() == nullptr)
         throw ::exception(error_no_memory);

      try
      {
         while(true)
         {
            uRead = pfileIn->read(buf);
            if(uRead <= 0)
            {
               break;
            }
            write(buf(0,  uRead));
            //uiSize += uRead;
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
   void file::from_hex(const ::scoped_string & scopedstr)
   {
      memory memory;
      memory.from_hex(psz);
      write(memory.data(), memory.size());
   }*/

   //void file::flush()
   //{
   //}

   /*
   void file::write (char ch)
   {
      __UNREFERENCED_PARAMETER(ch);
      throw ::interface_only();
   }

   void file::write (uchar uch)
   {
      __UNREFERENCED_PARAMETER(uch);
      throw ::interface_only();
   }

   void file::write (i16 sh)
   {
      __UNREFERENCED_PARAMETER(sh);
      throw ::interface_only();
   }

   void file::write (u16 u)
   {
      __UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (unichar wch)
   {
      __UNREFERENCED_PARAMETER(wch);
      throw ::interface_only();
   }

   void file::write (bool b)
   {
      __UNREFERENCED_PARAMETER(b);
      throw ::interface_only();
   }

   void file::write (i32 i)
   {
      __UNREFERENCED_PARAMETER(i);
      throw ::interface_only();
   }

   void file::write (u32 u)
   {
      __UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (i64 i)
   {
      __UNREFERENCED_PARAMETER(i);
      throw ::interface_only();
   }

   void file::write (u64 u)
   {
      __UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (float f)
   {
      __UNREFERENCED_PARAMETER(f);
      throw ::interface_only();
   }

   void file::write (double d)
   {
      __UNREFERENCED_PARAMETER(d);
      throw ::interface_only();
   }

   void file::write (const ::rectangle_i32 & rectangle)
   {
      __UNREFERENCED_PARAMETER(pcrect);

      throw ::interface_only();
   }

   void file::write (const size_i32 & & size)
   {
      __UNREFERENCED_PARAMETER(size);
      throw ::interface_only();
   }

   void file::write (::type info)
   {
      __UNREFERENCED_PARAMETER(info);
      throw ::interface_only();
   }

   void file::write (matter & matter)
   {
      __UNREFERENCED_PARAMETER(matter);
      throw ::interface_only();
   }

   void file::write (const ::scoped_string & scopedstr)
   {
      __UNREFERENCED_PARAMETER(psz);
      throw ::interface_only();
   }

   void file::write (const atom & atom)
   {
      __UNREFERENCED_PARAMETER(atom);
      throw ::interface_only();
   }

   void file::write (const ::payload & payload)
   {
      __UNREFERENCED_PARAMETER(payload);
      throw ::interface_only();
   }

   void file::write (const ::string & str)
   {
      __UNREFERENCED_PARAMETER(str);
      throw ::interface_only();
   }
   */


    void write(file * pwriter, const ::block & block)
    {

        //::e_status estatus = ::success;

        try
        {

            pwriter->write(block);

        }
        catch(...)
        {

            //estatus = error_failed;

        }

        //if(!estatus)
        //{

        //    return estatus;

        //}

        //return estatus;

    }


    filesize file::get_left() const
    {

        return size() - get_position();

    }


   string file::as_string() const
   {

      string str;

      auto pfile = (file *)this;

      auto position = pfile->get_position();

      pfile->as(str);

      pfile->set_position(position);

      return str;

   }


   void file::as_memory(memory_base & memory) const
   {

      auto pfile = (file*)this;

      auto position = pfile->get_position();

      pfile->as(memory);

      pfile->set_position(position);

   }


   ::file::file& file::put(char ch) 
   {
      
      write({ &ch, 1 });
      
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

         payload.file_path_reference().flags() |= ::file::e_flag_bypass_cache;

      }

   }


   void file::put_lines(const string_array& stra)
   {

      for (auto& strLine : stra)
      {

         println(strLine);

      }

   }


   class ::time file::modification_time()
   {

      throw ::interface_only();

      return {};

   }
   
   
   void file::set_modification_time(const class ::time& time)
   {

      throw ::interface_only();

   }


} // namespace file



