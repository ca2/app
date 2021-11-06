#include "framework.h"


//namespace http
//{
//
//
//   stream::stream()
//   {
//
//   }
//
//
//   stream::stream(::file::file * pbuffer) :
//      ::stream(pbuffer),
//      ::text_stream(pbuffer)
//   {
//
//   }
//
//
//   stream::~stream()
//   {
//
//      close();
//
//   }
//
//
//
//   void stream::write (const ::string & str)
//   {
//
//      write((const char *) str);
//
//   }
//
//
//   stream & stream::operator << (::memory_file & memfile)
//   {
//
//      write(memfile.get_data(), (memsize) memfile.get_length());
//
//      return *this;
//
//   }
//
//
//
//
//
//
//   stream & stream::operator << (file_pointer spbuf)
//   {
//      memsize nRead;
//      memory mem;
//      if(!mem.set_size(1024 * 1024))
//      {
//         __throw(error_no_memory);
//      }
//      while((nRead = spbuf->read(mem.get_data(), mem.get_size())) > 0)
//      {
//         write(mem.get_data(), nRead);
//      }
//      return *this;
//   }
//
//
//} // namespace http
