#include "framework.h"
#include "_uwp.h"


CLASS_DECL_APEX::winrt::Windows::Storage::StorageFolder ^ winrt_folder1(string & strPath, string & strPrefix)
{

   if (::str().begins_eat_ci(strPath, "image://"))
   {

      strPrefix = "image://";

      return ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;

   }
   else if (::str().begins_eat_ci(strPath, "music://"))
   {

      strPrefix = "music://";

      return ::winrt::Windows::Storage::KnownFolders::MusicLibrary;

   }
   else if (::str().begins_eat_ci(strPath, "video://"))
   {

      strPrefix = "video://";

      return ::winrt::Windows::Storage::KnownFolders::VideosLibrary;

   }
   else if (::str().begins_eat_ci(strPath, "document://"))
   {

      strPrefix = "document://";

      return ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;

   }
   else if (::str().begins_eat_ci(strPath, ::dir::sys_temp()))
   {

      strPrefix = ::dir::sys_temp();

      return ::winrt::Windows::Storage::ApplicationData::Current->TemporaryFolder;

   }
   else if (::str().begins_eat_ci(strPath, string(begin(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path))))
   {

      strPrefix = begin(::winrt::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

      return ::winrt::Windows::Storage::ApplicationData::Current->LocalFolder;

   }
   else
   {

      return nullptr;

   }

}



CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_folder(string & strPath, string & strPrefix)
{

   ::winrt::Windows::Storage::StorageFolder ^ folder = winrt_folder1(strPath, strPrefix);

   if (folder != nullptr)
   {

      return folder;

   }


   ::file::path_array patha;

   ::file::path path(strPath);

   patha = path.ascendants_path();

   for (auto & pathFolder : patha)
   {

      ::winrt::Windows::Storage::StorageFolder ^ folder = ::wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(pathFolder));

      if (folder != nullptr)
      {

         strPrefix = pathFolder;

         return folder;

      }

   }

   return nullptr;

}


CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder, string & strPrefix)
{

   string strPath = strFolder;

   ::winrt::Windows::Storage::StorageFolder ^ folder = winrt_folder(strPath, strPrefix);

   if (folder == nullptr)
   {

      return nullptr;

   }

   if (strPath.is_empty())
   {

      return folder;

   }
   else
   {

      strPath.replace("/", "\\");

      return wait(folder->GetFolderAsync(strPath));

   }

}


CLASS_DECL_APEX::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder)
{

   string strPrefix;

   return winrt_get_folder(strFolder, strPrefix);

}


CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder, string & strPrefix, string & strRelative)
{

   string strPath = strFolder;

   ::winrt::Windows::Storage::StorageFolder ^ folder = winrt_folder(strPath, strPrefix);

   if (folder == nullptr)
   {

      return nullptr;

   }

   strRelative = strFolder;

   strPrefix.replace("/", "\\");

   strRelative.replace("/", "\\");

   strPrefix.trim_right("/\\");

   strRelative.trim_right("/\\");

   ::str().begins_eat_ci(strRelative, strPrefix);

   strRelative.trim_left("/\\");

   return folder;

}

namespace universal_windows
{


   bool get_status(::file::file_status & status, const ::file::path & path)
   {

#ifdef WINDOWS_DESKTOP
      // attempt to fully qualify path first
      wstring wstrFullName;
      wstring wstrnative_bufferName;
      wstrnative_bufferName = utf8_to_unicode(pszfileName);

      if (!windows_full_path(wstrFullName, wstrnative_bufferName))
      {
         rStatus.m_strFullName.Empty();
         return false;
      }
      unicode_to_utf8(rStatus.m_strFullName, wstrFullName);

      WIN32_FIND_DATA findnative_bufferData;
      HANDLE hFind = FindFirstnative_buffer((char *)pszfileName, &findnative_bufferData);

      if (hFind == INVALID_HANDLE_VALUE)
         return false;
      VERIFY(FindClose(hFind));

      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      rStatus.m_attribute = (byte)(findnative_bufferData.dwnative_bufferAttributes & ~native_buffer_ATTRIBUTE_NORMAL);

      // get just the low ::u32 of the native_buffer size_i32
      ASSERT(findnative_bufferData.nnative_bufferSizeHigh == 0);
      rStatus.m_size = (::i32)findnative_bufferData.nnative_bufferSizeLow;

      // convert times as appropriate
      rStatus.m_ctime = ::earth::time(findnative_bufferData.ftCreationTime);
      rStatus.m_atime = ::earth::time(findnative_bufferData.ftLastAccessTime);
      rStatus.m_mtime = ::earth::time(findnative_bufferData.ftLastWriteTime);

      if (rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;

      if (rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;
#endif
      return true;
   }


   native_buffer::native_buffer()
   {

      m_bCloseOnDelete = true;

   }


   native_buffer::native_buffer(StorageFile ^ file)
   {

      m_file = file;

      m_bCloseOnDelete = true;

   }


   native_buffer::~native_buffer()
   {

      close();

   }


   ::extended::status native_buffer::open(const ::file::path & path, const::file::e_open & efileopenParam)
   {

      ::file::e_open eopen(efileopenParam);

      m_efileopen = efileopen;
      m_file = nullptr;
      m_folder = nullptr;

      ASSERT_VALID(this);
      ASSERT(__is_valid_string(path));
      ASSERT(!(eopen & ::file::e_open_text));   // text mode not supported

      // native_buffer objects are always binary and Createnative_buffer does not need flag
      eopen -= ::file::e_open_binary;


      string strPath = path;

      string strPrefix;

      ::winrt::Windows::Storage::StorageFolder ^ folder = winrt_folder(strPath, strPrefix);

      if (folder == nullptr)
      {

         return error_failed;

      }

      return open(folder, strPath, eopen);

   }


   ::extended::status native_buffer::open(::winrt::Windows::Storage::StorageFolder ^ folder, const ::file::path & pathFileArgument, const ::file::e_open & efileopenParam)
   {

      ::file::e_open eopen(efileopenParam);

      ::file::path pathFile(pathFileArgument);

      pathFile.trim("\\/");

      string strPrefix = folder->Path->Begin();

      ::file::path path(strPrefix);

      path /= pathFile;

      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {

         pcontext->m_papexcontext->dir().create(path.folder());

      }

      string strName = path.name();

      ::file::path pathFolder = path.folder();

      string strRelative = pathFolder;

      ::str().begins_eat_ci(strRelative, strPrefix);

      if (strRelative.is_empty())
      {

         m_folder = folder;

      }
      else
      {

         strRelative.trim("\\/");

         m_folder = wait(folder->GetFolderAsync(strRelative));

      }

      if (m_folder == nullptr)
      {

         return error_failed;

      }

      m_bCloseOnDelete = false;
      //m_hnative_buffer = (::u32)hnative_bufferNull;
      m_strFileName.Empty();

      m_strFileName  = path;
      //      m_wstrnative_bufferName    = utf8_to_unicode(m_strFileName);

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      ASSERT((::file::e_open_read | ::file::e_open_write | ::file::e_open_read_write) == 3);
      ::u32 dwAccess = 0;
      switch(eopen & 3)
      {
      case ::file::e_open_read:
         dwAccess = GENERIC_READ;
         break;
      case ::file::e_open_write:
         dwAccess = GENERIC_WRITE;
         break;
      case ::file::e_open_read_write:
         dwAccess = GENERIC_READ | GENERIC_WRITE;
         break;
      default:
         dwAccess = GENERIC_READ;
         break;
      }

      SECURITY_ATTRIBUTES sa;
      sa.nLength = sizeof(sa);
      sa.lpSecurityDescriptor = nullptr;

      sa.bInheritHandle = !(eopen & ::file::e_open_no_inherit);

      folder = m_folder;

      if(eopen & ::file::e_open_create)
      {

         if (eopen & ::file::e_open_no_truncate)
         {

            m_file = ::wait(folder->CreateFileAsync(strName, ::winrt::Windows::Storage::CreationCollisionOption::OpenIfExists));

         }
         else
         {

            m_file = ::wait(folder->CreateFileAsync(strName, ::winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting));

         }

      }
      else
      {

         try
         {

            m_file = ::wait(folder->GetFileAsync(strName));

         }
         catch (...)
         {

            m_file = nullptr;

         }

      }

      if(m_file == nullptr)
      {

         m_folder = nullptr;

         return error_failed;

      }

      ASSERT((::file::e_open_read | ::file::e_open_write | ::file::e_open_read_write) == 3);

      switch (eopen & 3)
      {
      case ::file::e_open_read:
         m_stream = ::wait(m_file->OpenAsync(::winrt::Windows::Storage::FileAccessMode::Read));
         break;
      case ::file::e_open_write:
         m_stream = ::wait(m_file->OpenAsync(::winrt::Windows::Storage::FileAccessMode::ReadWrite));
         break;
      case ::file::e_open_read_write:
         m_stream = ::wait(m_file->OpenAsync(::winrt::Windows::Storage::FileAccessMode::ReadWrite));
         break;
      default:
         m_stream = ::wait(m_file->OpenAsync(::winrt::Windows::Storage::FileAccessMode::Read));
         break;
      }

      if(m_stream == nullptr)
      {

         m_file = nullptr;

         m_folder = nullptr;

         return error_failed;

      }

      m_bCloseOnDelete = true;

      m_efileopen = efileopen;

      return ::success;

   }


   memsize native_buffer::read(void *  pdata,memsize nCount)
   {

      ::winrt::Windows::Storage::Streams::IBuffer ^ buffer = ref new ::winrt::Windows::Storage::Streams::Buffer(nCount);

      ::winrt::Windows::Storage::Streams::IBuffer ^ buffer2 = ::wait(m_stream->ReadAsync(buffer,nCount,::winrt::Windows::Storage::Streams::InputStreamOptions::None));

      auto read = minimum(nCount, (memsize) buffer->Length);

      read_buffer(pdata, buffer, read);

      return read;

   }


   void native_buffer::write(const void * pdata,memsize nCount)
   {

      memory memory(pdata, nCount);

      ::winrt::Windows::Storage::Streams::IBuffer ^ buffer = memory.get_os_buffer();

      unsigned int u = ::wait(m_stream->WriteAsync(buffer));

      if (u != nCount)
      {

         throw ::exception(error_io);

      }

   }

   filesize native_buffer::seek(filesize lOff,::enum_seek eseek)
   {
      if(nFrom == ::e_seek_set)
      {
         m_stream->Seek(lOff);
      }
      else if(nFrom == ::e_seek_current)
      {
         m_stream->Seek(m_stream->Position+lOff);
      }
      else
      {
         m_stream->Seek(m_stream->Size + lOff);
      }

      return m_stream->Position;
   }

   filesize native_buffer::get_position() const
   {

      return m_stream->Position;
   }


   void native_buffer::flush()
   {

      ::wait(m_stream->FlushAsync());

   }


   void native_buffer::close()
   {

      if (m_efileopen & ::file::e_open_write)
      {

         flush();

      }

      m_stream       = nullptr;

      m_file         = nullptr;

      m_folder       = nullptr;

      m_efileopen    = 0;

   }


   //void native_buffer::Abort()
   //{
   //   //ASSERT_VALID(this);
   //   //if(m_hnative_buffer != (::u32)hnative_bufferNull)
   //   //{
   //   //   // close but ignore errors
   //   //   ::CloseHandle((HANDLE)m_hnative_buffer);
   //   //   m_hnative_buffer = (::u32)hnative_bufferNull;
   //   //}
   //   //m_strFileName.Empty();
   //}

   void native_buffer::lock(filesize dwPos,filesize dwCount)
   {
      //ASSERT_VALID(this);
      //ASSERT(m_hnative_buffer != (::u32)hnative_bufferNull);

      ////      if (!::Locknative_buffer((HANDLE)m_hnative_buffer, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
      ////       WinFileException::ThrowOsError(get_app(), (::i32)::get_last_error());
   }

   void native_buffer::unlock(filesize dwPos,filesize dwCount)
   {
      //ASSERT_VALID(this);
      //ASSERT(m_hnative_buffer != (::u32)hnative_bufferNull);

      ////  if (!::Unlocknative_buffer((HANDLE)m_hnative_buffer,  LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
      ////   WinFileException::ThrowOsError(get_app(), (::i32)::get_last_error());
   }

   void native_buffer::set_size(filesize dwNewLen)
   {
      //ASSERT_VALID(this);
      //ASSERT(m_hnative_buffer != (::u32)hnative_bufferNull);

      //seek((::i32)dwNewLen,(::enum_seek)::e_seek_set);

      //if(!::SetEndOfnative_buffer((HANDLE)m_hnative_buffer))
      //   WinFileException::ThrowOsError(get_app(),(::i32)::get_last_error());
   }


   filesize native_buffer::get_size() const
   {

      ASSERT_VALID(this);

      filesize dwLen,dwCur;

      // seek is a non const operation
      native_buffer* pnative_buffer = (native_buffer*)this;
      dwCur = pnative_buffer->seek(0L,::e_seek_current);
      dwLen = pnative_buffer->seek_to_end();
      VERIFY(dwCur == (u64)pnative_buffer->seek((filesize)dwCur,::e_seek_set));

      return (filesize)dwLen;
   }

   //// native_buffer does not support direct buffering (CMemnative_buffer does)
   //u64 native_buffer::GetBufferPtr(::u32 nCommand,u64 /*nCount*/,
   //                                     void ** /*ppBufStart*/,void ** /*ppBufMax*/)
   //{
   //   ASSERT(nCommand == bufferCheck);
   //   UNUSED(nCommand);    // not used in retail build

   //   return 0;   // no support
   //}

   /*
   void native_buffer::Rename(const char * pszOldName, const char * pszNewName)

   {
   if (!::Movenative_buffer((char *)pszOldName, (char *)pszNewName))

   WinFileException::ThrowOsError(get_app(), (::i32)::get_last_error());
   }

   void native_buffer::erase(const char * pszfileName)

   {
   if (!::Deletenative_buffer((char *)pszfileName))

   WinFileException::ThrowOsError(get_app(), (::i32)::get_last_error());
   }
   */



   void native_buffer::assert_ok() const
   {

      ::file::file::assert_ok();
      
   }


   void native_buffer::dump(dump_context & dumpcontext) const
   {
      
      ::file::file::dump(dumpcontext);

   }


   //string native_buffer::GetFileName() const
   //{

   //   ASSERT_VALID(this);

   //   ::file::file_status status;

   //   GetStatus(status);

   //   string wstrResult;

   //   wstrResult = status.m_strFullName.name();

   //   return wstrResult;

   //}


   //string native_buffer::GetFileTitle() const
   //{

   //   ASSERT_VALID(this);

   //   ::file::file_status status;

   //   GetStatus(status);

   //   string wstrResult;

   //   wstrResult = status.m_strFullName.title();

   //   return wstrResult;

   //}


   ::file::path native_buffer::get_file_path() const
   {

      return m_path;

   }


   bool native_buffer::get_status(::file::file_status& rStatus) const
   {

      ASSERT_VALID(this);

      rStatus.m_strFullName = m_path;

      return true;

   }


   bool native_buffer::is_opened() const
   { 

      return m_file != nullptr;

   }


   void native_buffer::set_file_path(const ::file::path & path)
   {

      ASSERT_VALID(this);

      ASSERT(__is_valid_string(path));

      m_strFileName = path;

   }


} // namespace universal_windows




