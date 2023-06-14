#include "framework.h"
#include "file.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/primitive/primitive/memory.h"
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

      UNREFERENCED_PARAMETER(offset);

      UNREFERENCED_PARAMETER(eseek);

      //return 0;

   }


   int file::getc()
   {

      ::u8 u8 = 0;

      auto iRead = read({ &u8, 1 });

      if (iRead <= 0)
      {

         return -1;

      }

      return u8;

   }


   int file::ungetc(int iChar)
   {

      throw ::interface_only();

      return -1;

   }


   bool file::has_write_mode()
   {

      return m_eopen & ::file::e_open_write;

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


   memsize file::read(void * p, ::memsize s)
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


   void file::write(const void * dataToWrite, ::memsize amountToWrite)
   {
      
      auto amountWritten = defer_write(dataToWrite, amountToWrite);
      
      if(amountWritten != amountToWrite)
      {
         
         throw ::file::exception(error_disk_full,
                                 {e_error_code_type_none, -1},
                                 m_path,
                                 m_eopen,
                                 "amountWritten != amountToWrite, disk full?");
         
      }

   }


   //void file::write(const ::block & block)
   //{

   //   write(block.data(), block.size());

   //}


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


   file_status file::get_status() const
   {

      return {};

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

      return read((::u8 *)pchar);
      
   }


   bool file::read(::u8 * pbyte)
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

      return peek((::u8 *)pchar);

   }


   bool file::peek(::u8 * pbyte)
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

      ::u8 b = 0;

      if (peek(&b) != 1)
      {

         return -1;

      }

      return b;

   }


   int file::get_u8()
   {

      ::u8 u8 = 0;

      if (read(&u8) != 1)
      {

         return -1;

      }

      return u8;

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


   void file::put_byte_back(::u8 u8)
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

      ::u8 b;

      ::u8 b1 = 0;

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
               
               put_byte_back(b1);

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


   //void file::as(memory_base & memory)
   //{

   //   auto left = this->left_size();

   //   if(left > 100000000000000)
   //   {

   //      int i = 1;

   //      int j = 2;

   //      int l = i+j;

   //   }

   //   memory.set_size((memsize)left);

   //   auto readBytes = read(memory);

   //   if(readBytes != left)
   //   {
   //      
   //      throw ::file::exception(error_io, {e_error_code_type_unknown, 0}, m_path, m_eopen, "readBytes != left");
   //      
   //   }

   //}



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

      UNREFERENCED_PARAMETER(path);

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


   ::u8 * file::full_data_begin()
   {

      return nullptr;

   }


   ::u8 * file::full_data_end()
   {

      return nullptr;

   }

   
   const ::u8 * file::full_data_begin() const
   {

      return nullptr;

   }


   const ::u8 * file::full_data_end() const
   {

      return nullptr;

   }


   ::u8 * file::data_begin()
   {

      return nullptr;

   }


   ::u8 * file::data_end()
   {

      return nullptr;

   }


   const ::u8 * file::data_begin() const
   {

      return nullptr;

   }


   const ::u8 * file::data_end() const
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

      //      ::u8 b = pu8Find[0];

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

      //   memory_transfer(buffer, buffer + sizeSearch, sizeTotalRead);

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

   //         memory_transfer(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + internal_data().size(), ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), pfileOut->internal_data().size() - internal_data().size());

   //         ::memory_copy(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), internal_data().data(), internal_data().size());

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
   //      memory_transfer(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + uiBufInc, ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), uiBufInc);
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

   //      memory_transfer(((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position(), ((u8 *) pfileOut->internal_data().data()) + pfileOut->get_position() + uiBufSize, uiBufSize);

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


   memsize file::defer_write(const void * dataToWrite, ::memsize amountToWrite)
   {

      throw ::interface_only();

      return 0;

   }


   /*void file::from_begin(::file::file * pfileIn, memsize uiBufSize)
   {

      set_size(0);

      write_file_from_begin(pfileIn, uiBufSize);

   }*/


   void file::write_from_beginning(::file::streamable * pstreamable, memsize uiBufSize)
   {

      pstreamable->seek_to_begin();

      write(pstreamable, uiBufSize);

   }


   ::file::file * file::get_file()
   {

      return this;

   }



   /*void file::from(::file::file * pfileIn, memsize uiBufSize)
   {

      write_file(pfileIn, uiBufSize);

   }*/


   void file::write(::file::readable * preadable, memsize uiBufSize)
   {

      {

         auto pfile = preadable->get_file();

         if (pfile && pfile->full_data_is_set())
         {

            write(pfile->data());

            return;

         }

      }

      memsize uRead;

      uiBufSize = maximum(32 * 1024, uiBufSize);

      memory buf;

      buf.set_size(uiBufSize);

      if(buf.data() == nullptr)
      {
         
         throw ::exception(error_no_memory);
         
      }

      try
      {
         
         while(true)
         {
            
            uRead = preadable->read(buf);
            
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
      UNREFERENCED_PARAMETER(ch);
      throw ::interface_only();
   }

   void file::write (uchar uch)
   {
      UNREFERENCED_PARAMETER(uch);
      throw ::interface_only();
   }

   void file::write (i16 sh)
   {
      UNREFERENCED_PARAMETER(sh);
      throw ::interface_only();
   }

   void file::write (u16 u)
   {
      UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (unichar wch)
   {
      UNREFERENCED_PARAMETER(wch);
      throw ::interface_only();
   }

   void file::write (bool b)
   {
      UNREFERENCED_PARAMETER(b);
      throw ::interface_only();
   }

   void file::write (i32 i)
   {
      UNREFERENCED_PARAMETER(i);
      throw ::interface_only();
   }

   void file::write (u32 u)
   {
      UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (i64 i)
   {
      UNREFERENCED_PARAMETER(i);
      throw ::interface_only();
   }

   void file::write (u64 u)
   {
      UNREFERENCED_PARAMETER(u);
      throw ::interface_only();
   }

   void file::write (float f)
   {
      UNREFERENCED_PARAMETER(f);
      throw ::interface_only();
   }

   void file::write (double d)
   {
      UNREFERENCED_PARAMETER(d);
      throw ::interface_only();
   }

   void file::write (const ::rectangle_i32 & rectangle)
   {
      UNREFERENCED_PARAMETER(pcrect);

      throw ::interface_only();
   }

   void file::write (const size_i32 & & size)
   {
      UNREFERENCED_PARAMETER(size);
      throw ::interface_only();
   }

   void file::write (::type info)
   {
      UNREFERENCED_PARAMETER(info);
      throw ::interface_only();
   }

   void file::write (matter & matter)
   {
      UNREFERENCED_PARAMETER(matter);
      throw ::interface_only();
   }

   void file::write (const ::scoped_string & scopedstr)
   {
      UNREFERENCED_PARAMETER(psz);
      throw ::interface_only();
   }

   void file::write (const atom & atom)
   {
      UNREFERENCED_PARAMETER(atom);
      throw ::interface_only();
   }

   void file::write (const ::payload & payload)
   {
      UNREFERENCED_PARAMETER(payload);
      throw ::interface_only();
   }

   void file::write (const ::string & str)
   {
      UNREFERENCED_PARAMETER(str);
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


    filesize file::right_size() const
    {

        return size() - get_position();

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



