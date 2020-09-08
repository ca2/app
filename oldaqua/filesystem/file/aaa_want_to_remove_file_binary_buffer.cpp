#include "framework.h"


//namespace file
//{
//
//
//   binary_file::binary_file()
//   {
//   }
//
//
//   memsize binary_file::read(void *lpBuf, memsize nCount)
//   {
//      return ::file::reader::read(lpBuf, nCount);
//   }
//
//   void binary_file::write(const void * lpBuf, memsize nCount)
//   {
//      ::file::writer::write(lpBuf, nCount);
//   }
//
//
//   void binary_file::write(serialize & serialize)
//   {
//
//      seek_to_begin();
//
//      transfer_to(*serialize.m_spfile);
//
//   }
//
//
//   void binary_file::read(serialize & serialize)
//   {
//
//      transfer_from(*serialize.m_spfile);
//
//      seek_to_begin();
//
//   }
//
//
//   binary_file::~binary_file()
//   {
//   }
//
//   file_pointer  binary_file::Duplicate() const
//   {
//      return NULL;
//   }
//
//   ::status::result binary_file::open(const ::file::path & lpszFileName, UINT nOpenFlags)
//   {
//      UNREFERENCED_PARAMETER(lpszFileName);
//      UNREFERENCED_PARAMETER(nOpenFlags);
//      return __alloc(new ::file::exception());
//   }
//
//   filesize binary_file::seek(filesize lOff, ::file::e_seek nFrom)
//   {
//      UNREFERENCED_PARAMETER(lOff);
//      UNREFERENCED_PARAMETER(nFrom);
//      return 0;
//   }
//
//   filesize binary_file::get_position() const
//   {
//      return ((binary_file *) this)->seek(0, ::file::seek_current);
//   }
//
//   void binary_file::flush()
//   {
//   }
//
//   void binary_file::close()
//   {
//   }
//
//   void binary_file::Abort()
//   {
//   }
//
//   void binary_file::LockRange(filesize dwPos, filesize dwCount)
//   {
//      UNREFERENCED_PARAMETER(dwPos);
//      UNREFERENCED_PARAMETER(dwCount);
//   }
//
//   void binary_file::UnlockRange(filesize dwPos, filesize dwCount)
//   {
//      UNREFERENCED_PARAMETER(dwPos);
//      UNREFERENCED_PARAMETER(dwCount);
//   }
//
//   void binary_file::set_length(filesize dwNewLen)
//   {
//      UNREFERENCED_PARAMETER(dwNewLen);
//   }
//
//   filesize binary_file::get_length() const
//   {
//      return 0;
//   }
//
//   // file does not support direct buffering (CMemFile does)
//   u64 binary_file::GetBufferPtr(UINT nCommand, u64 nCount, void ** ppBufStart, void ** ppBufMax)
//   {
//      UNREFERENCED_PARAMETER(nCommand);
//      UNREFERENCED_PARAMETER(nCount);
//      UNREFERENCED_PARAMETER(ppBufStart);
//      UNREFERENCED_PARAMETER(ppBufMax);
//      return 0;
//   }
//
//   /*   void file::Rename(const char * lpszOldName, const char * lpszNewName)
//      {
//         UNREFERENCED_PARAMETER(lpszOldName);
//         UNREFERENCED_PARAMETER(lpszNewName);
//      }
//
//      void file::remove(const char * lpszFileName)
//      {
//         UNREFERENCED_PARAMETER(lpszFileName);
//      }*/
//
//
//   void binary_file::assert_valid() const
//   {
//      //   object::assert_valid();
//      // we permit the descriptor m_hFile to be any value for derived classes
//   }
//
//   void binary_file::dump(dump_context & dumpcontext) const
//   {
//      UNREFERENCED_PARAMETER(dumpcontext);
//      //   object::dump(dumpcontext);
//
//      //   dumpcontext << "with handle " << (UINT)m_hFile;
//      //   dumpcontext << " and name \"" << m_wstrFileName << "\"";
//      //   dumpcontext << "\n";
//   }
//
//
//
//
//   /////////////////////////////////////////////////////////////////////////////
//   // file name handlers
//
//   string binary_file::GetFileName() const
//   {
//      return "";
//   }
//
//   string binary_file::GetFileTitle() const
//   {
//      return "";
//   }
//
//   string binary_file::GetFilePath() const
//   {
//      return "";
//   }
//
//
//
//
//
//
//   // IMPLEMENT_DYNAMIC(file_exception, ::exception::exception)
//
//   /////////////////////////////////////////////////////////////////////////////
//
//
//   /////////////////////////////////////////////////////////////////////////////
//   // Help and other support
//
//   // Strings in format ".....%1 .... %2 ...." etc.
//
//
//   /////////////////////////////////////////////////////////////////////////////
//   // file Status implementation
//
//   bool binary_file::GetStatus(file_status & rStatus) const
//   {
//      UNREFERENCED_PARAMETER(rStatus);
//      return FALSE;
//   }
//
//   //bool binary_file::GetStatus(const char * lpszFileName, file_status & rStatus)
//   //{
//   //   UNREFERENCED_PARAMETER(lpszFileName);
//   //   UNREFERENCED_PARAMETER(rStatus);
//   //   return FALSE;
//   //}
//
//
//   //void binary_file::SetStatus(const char * lpszFileName, const file_status & status)
//   //{
//   //   UNREFERENCED_PARAMETER(lpszFileName);
//   //   UNREFERENCED_PARAMETER(status);
//   //}
//
//
//
//   bool binary_file::IsOpened()
//   {
//      return false;
//   }
//
//   string binary_file::get_location() const
//   {
//      return GetFileName();
//   }
//
//
//
//
//} // namespace file
//
//
//
