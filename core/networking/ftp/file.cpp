#include "framework.h"
#include "file.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace ftp
{


   file::file()
   {
   }

   file::~file()
   {
      close();
   }


   bool file::Open(const string& strFileName, ::file::e_open eopen)
   {

      m_strFileName = strFileName;

      m_file = ::particle::file()->get_file(strFileName, eopen);

      return m_file.is_set();

   }


   bool file::close()
   {

      m_file->close();
      m_file.release();

      return true;

   }

   bool file::Seek(long lOffset, ::enum_seek enOrigin)
   {
      if (!m_file.is_set())
         return false;
      try
      {
         m_file->translate(lOffset, enOrigin);
         return true;
      }
      catch (...)
      {

      }

      return false;
   }


   long file::Tell()
   {

      if (m_file.is_null())
      {

         return -1L;

      }

      return (long) m_file->get_position();

   }



   memsize file::write(const void* pBuffer, memsize itemSize, memsize itemCount)
   {

      if (m_file.is_null())
      {

         return 0;

      }

      m_file->write({ pBuffer, itemSize * itemCount });

      return itemCount;

   }


   memsize file::Read(void* pBuffer, memsize itemSize, memsize itemCount)
   {

      if (m_file.is_null())
      {

         return 0;

      }

      memsize uRead = m_file->read({ pBuffer, itemSize * itemCount });

      return (memsize)(uRead / itemSize);

   }


   string file::GetLocalStreamName() const
   {
      return m_strFileName;
   }


   ::u32 file::GetLocalStreamSize() const
   {

      if (m_file.is_null())
      {

         return 0;

      }

      return (::u32) m_file->size();

   }


   void file::SetLocalStreamOffset(::u32 dwOffsetFromBeginOfStream)
   {
      Seek(dwOffsetFromBeginOfStream, ::e_seek_set);
   }

   void file::OnBytesReceived(const memory& vBuffer, long lReceivedBytes)
   {
      write(vBuffer.data(), sizeof(memory::value_type), lReceivedBytes);
   }

   void file::OnPreBytesSend(unsigned char* pszBuffer, memsize bufferSize, memsize& bytesToSend)
   {
      bytesToSend = Read(pszBuffer, sizeof(char), bufferSize);
   }



} // namespace ftp




