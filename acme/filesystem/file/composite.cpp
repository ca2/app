#include "framework.h"
#include "composite.h"
#include "acme/filesystem/file/status.h"


namespace file
{


   reference::reference()
   {

   }


   reference::reference(file * pfile)
   {

      m_pfile = pfile;

   }


   filesize reference::get_position() const
   {

      return m_pfile->get_position();

   }


   file_status reference::get_status() const
   {

      return m_pfile->get_status();

   }


   ::file::path reference::get_file_path() const
   {

      return m_pfile->get_file_path();

   }


   void reference::set_file_path(const ::file::path & path)
   {

      return m_pfile->set_file_path(path);

   }


   void reference::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
   {

      m_pfile->open(path, eopen, pfileexception);

   }


   void reference::translate(filesize offset, ::enum_seek eseek)
   {

      return m_pfile->translate(offset, eseek);

   }


   void reference::set_size(filesize dwNewLen)
   {

      return m_pfile->set_size(dwNewLen);

   }


   filesize reference::size() const
   {

      return m_pfile->size();

   }


   void reference::lock(filesize dwPos, filesize dwCount)
   {

      return m_pfile->lock(dwPos, dwCount);

   }


   void reference::unlock(filesize dwPos, filesize dwCount)
   {

      return m_pfile->unlock(dwPos, dwCount);

   }


   void reference::abort()
   {

      return m_pfile->abort();

   }


   void reference::flush()
   {

      return m_pfile->flush();

   }


   void reference::close()
   {

      return m_pfile->close();

   }


   memsize reference::read(const ::block & block)
   {

      return m_pfile->read(block);

   }


   void reference::write(const ::block & block)
   {

      return m_pfile->write(block);

   }


   string reference::get_location() const
   {

      return m_pfile->get_location();

   }


   bool reference::is_opened() const
   {

      return m_pfile->is_opened();

   }


   reference::~reference()
   {

   }


//   void reference::assert_ok() const
//   {
//
//      return m_pfile->assert_ok();
//
//   }
//
//
//   void reference::dump(dump_context & dumpcontext) const
//   {
//
//      return m_pfile->dump(dumpcontext);
//
//   }


} // namespace file



