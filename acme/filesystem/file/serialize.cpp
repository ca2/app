#include "framework.h"


//stream::stream(stream & stream) :
////   ::element(::move(stream)),
//   //stream(::move(stream))
//   m_pfile(::move(stream.m_pfile))
//{
//
//   //m_b64bit = stream.m_b64bit;
//
//}
//
//
//stream::stream(::file::file * pfile, index iVersion) :
//   m_pfile(pfile)
//   //::element(pfile->get_object()),
//   //stream(pfile, iVersion)
//{
//   m_iVersion = iVersion;
//   //m_b64bit = false;
//
//}
//
//stream::stream(e_set_version, index iVersion)// :
//   //stream(e_create_new, get_object(), iVersion)
//{
//   m_iVersion = iVersion;
//   //m_b64bit = false;
//
//}
//
//
//stream::stream(e_create_new, ::element * pobject, index iVersion) :
//   //::element(pobject),
//   //stream(e_create, iVersion)
//{
//
//   m_iVersion = iVersion;
//   //m_b64bit = false;
//
//}
//
//
//stream::~stream()
//{
//
//   close();
//
//}
//
//
//
//
//
//
//bool stream::is_stream_null()
//{
//
//   return is_writer_null() && is_reader_null();
//
//}
//
//
//bool stream::is_stream_set()
//{
//
//   return is_writer_set() || is_reader_set();
//
//}
//
//
//void stream::close()
//{
//
//   stream::close();
//
//}
//
//
//filesize stream::get_position() const
//{
//
//   return m_pfile->get_position();
//
//}
//
//
//
//
//
//int get_arbitrary_length(u64 ui);
//
//
//
//
//// string serialization code
//// string format:
////      UNICODE strings are always prefixed by 0xff, 0xfffe
////      if < 0xff chars: len:BYTE, char chars
////      if >= 0xff characters: 0xff, len:WORD, char chars
////      if >= 0xfffe characters: 0xff, 0xffff, len:u32, TCHARs
//
//stream & stream::write(const string & string)
//{
//
//   ::i64 s = string.get_length();
//
//   write_buffer_length(s);
//
//   m_pfile->write((const char *)string, string.get_length());
//
//}
//
//
//
//
////
////
////stream & stream::write(bool b)
////{
////
////   return raw_write(b);
////
////}
////
////
////void stream::write(char ch)
////{
////
////   oblt(ch);
////
////}
////
////
////void stream::write(uchar uch)
////{
////
////   oblt(uch);
////
////}
////
////
////void stream::write(i8 i)
////{
////
////   oblt(i);
////
////}
////
////
////void stream::write(i16 i)
////{
////
////   oblt(i);
////
////}
////
////
////void stream::write(u16 ui)
////{
////
////   oblt(ui);
////
////}
////
////
////#ifdef WINDOWS
////
////
////void stream::write(unichar wch)
////{
////
////   oblt(wch);
////
////}
////
////
////#endif
////
////
////void stream::write(i32 i)
////{
////
////   oblt(i);
////
////}
////
////
////void stream::write(u32 ui)
////{
////
////   oblt(ui);
////
////}
////
////
////void stream::write(i64 i)
////{
////
////   oblt(i);
////
////}
////
////
////void stream::write(u64 ui)
////{
////
////   oblt(ui);
////
////}
////
////
////void stream::write(float f)
////{
////
////   oblt(f);
////
////}
////
////
////void stream::write(double d)
////{
////
////   oblt(d);
////
////}
////
////
////void stream::write(RECT * prect)
////{
////
////   oblt(*prect);
////
////}
////
////
////void stream::write(SIZE * psize)
////
////{
////
////   oblt(*psize);
////
////
////}
////
////
////void stream::write(POINT * ppoint)
////{
////
////   oblt(*ppoint);
////
////}
////
////
////void stream::write(const char * psz)
////{
////
////   write((const string &) psz);
////
////}
////
//
//void stream::write_from_hex(const char * psz, strsize iLen)
//{
//
//   stream::write_from_hex(psz, iLen < 0 ? strlen(psz) + iLen + 1 : iLen);
//
//}
//
//
//void stream::write_from_hex(const string & str)
//{
//
//   stream::write_from_hex(str, str.get_length());
//
//}
//
//
//UINT __read_string_length(stream & ar)
//{
//
//   u32 nNewLen;
//
//   byte bLen;
//
//   ar >> bLen;
//
//   if (ar.fail())
//   {
//
//      return 0;
//
//   }
//
//   if (bLen < 0xff)
//      return bLen;
//
//   u16 wLen;
//
//   ar >> wLen;
//
//   if (wLen == 0xfffe)
//   {
//
//      // UNICODE string prefix (length will follow)
//
//      return (UINT)-1;
//
//   }
//   else if (wLen == 0xffff)
//   {
//
//      // read u32 of length
//
//      ar >> nNewLen;
//
//      return (UINT)nNewLen;
//
//   }
//   else
//   {
//
//      return wLen;
//
//   }
//
//}
//
//
//int get_arbitrary_length(u64 ui);
//
//
//bool stream::read(char & ch)
//{
//
//   return iblt(ch);
//
//}
////
////
//bool stream::read(uchar & uch)
//{
//
//   return iblt(uch);
//
//}
//
//
//void stream::read(i8 & i)
//{
//
//   iblt(i);
//
//}
//
//
//void stream::read(i16 & i)
//{
//
//   iblt(i);
//
//}
//
//
//void stream::read(u16 & ui)
//{
//   iblt(ui);
//
//}
//
//
//#ifdef WINDOWS
//
//
//void stream::read(unichar & wch)
//{
//   blt(wch);
//
//}
//
//
//#endif
//
//
//void stream::read(bool & b)
//{
//
//   iblt(b);
//
//}
//
//
//void stream::read(i32 & i)
//{
//
//   iblt(i);
//
//}
//
//
//void stream::read(u32 & ui)
//{
//
//   iblt(ui);
//
//}
//
//
//void stream::read(i64 & i)
//{
//
//   iblt(i);
//
//}
//
//
//void stream::read(u64 & ui)
//{
//
//   iblt(ui);
//
//}
//
//
//void stream::read(float & f)
//{
//
//   iblt(f);
//
//}
//
//
//void stream::read(double & d)
//{
//
//   iblt(d);
//
//}
//
//void stream::read(RECT * prect)
//
//{
//
//   iblt(*prect);
//
//
//}
//
//void stream::read(SIZE *psize)
//{
//
//   iblt(*psize);
//
//}
//
//
//void stream::read(POINT * ppoint)
//{
//
//   iblt(*ppoint);
//
//}
//
//
//string stream::get_location() const
//{
//
//   return "<unknown stream locationd>";
//
//}
//
//
//void stream::full_load(string & str)
//{
//
//   if (!m_pfile)
//   {
//
//      return;
//
//   }
//
//   if (m_pfile->is_seekable())
//   {
//
//      m_pfile->seek_to_end();
//
//      filesize uiLength = m_pfile->get_position();
//
//      m_pfile->seek_to_begin();
//
//      ::strsize uiCount = ::numeric_info< strsize >::natural(uiLength);
//
//      filesize uiPos = 0;
//
//      LPSTR pstr = str.get_string_buffer((strsize)(uiLength + 1));
//
//      while (uiCount > 0)
//      {
//
//         memsize uiRead = m_pfile->read(&pstr[uiPos], (memsize)uiCount);
//
//         uiCount -= uiRead;
//
//         uiPos += uiRead;
//
//      }
//
//      str.release_string_buffer((strsize)uiLength);
//
//   }
//   else
//   {
//
//      ::memory_file file;
//
//      transfer_to(&file);
//
//      str = file.get_memory()->to_string();
//
//   }
//
//}
//
//
//void stream::read(string & string)
//{
//
//   strsize iLength = __read_string_length(*this);
//
//   char * psz;
//
//   psz = string.get_string_buffer(iLength);
//
//   memsize iRead = 0;
//
//   if (iLength > 0)
//   {
//
//      iRead = m_pfile->read(psz, iLength);
//
//      if (iRead != iLength)
//      {
//
//         setstate(::file::failbit);
//
//      }
//
//   }
//
//   psz[iRead] = '\0';
//
//   string.release_string_buffer();
//
//
//}
//
//
//
////namespace file
////{
////
////
////   byte_stream_memory_file::byte_stream_memory_file(::element * pobject) :
////      ::element(pobject)
////   {
////
////      m_pfile = this;
////
////   }
////
////
////   byte_stream_memory_file::~byte_stream_memory_file()
////   {
////
////
////   }
////
////
////   filesize byte_stream_memory_file::seek(filesize offset, e_seek seekOrigin)
////   {
////
////      return memory_file::seek(offset, seekOrigin);
////
////   }
////
////
////   filesize byte_stream_memory_file::get_position() const
////   {
////
////      return memory_file::get_position();
////
////   }
////
////
////   void byte_stream_memory_file::flush()
////   {
////
////      memory_file::flush();
////
////   }
////
////
////   void * byte_stream_memory_file::get_internal_data()
////   {
////
////      return memory_file::get_internal_data();
////
////   }
////
////
////   const void * byte_stream_memory_file::get_internal_data() const
////   {
////
////      return memory_file::get_internal_data();
////
////   }
////
////
////   memsize byte_stream_memory_file::get_internal_data_size() const
////   {
////
////      return memory_file::get_internal_data_size();
////
////   }
////
////   bool byte_stream_memory_file::set_internal_data_size(memsize s)
////   {
////
////      return memory_file::set_internal_data_size(s);
////
////   }
////
////   void byte_stream_memory_file::write(const void * p, memsize s)
////   {
////
////      memory_file::write(p, s);
////
////   }
////
////
////   memsize byte_stream_memory_file::read(void * p, memsize s)
////   {
////
////      return memory_file::read(p, s);
////
////   }
////
////
////   void byte_stream_memory_file::set_length(filesize dwNewLen)
////   {
////
////      stream::set_length(dwNewLen);
////
////   }
////
////
////   void byte_stream_memory_file::close()
////   {
////
////      stream::close();
////
////   }
////
////} // namespace file
////
////
////
