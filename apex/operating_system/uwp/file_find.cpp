#include "framework.h"
//#include "universal_windows.h"


#ifdef WINDOWS_DESKTOP

namespace universal_windows
{


   file_find::file_find()
   {
      m_pFoundInfo = nullptr;
      m_pNextInfo = nullptr;
      m_hContext = nullptr;
      m_chDirSeparator = '\\';
   }

   file_find::~file_find()
   {
      close();
   }

   void file_find::close()
   {
      if (m_pFoundInfo != nullptr)
      {
         delete m_pFoundInfo;
         m_pFoundInfo = nullptr;
      }

      if (m_pNextInfo != nullptr)
      {
         delete m_pNextInfo;
         m_pNextInfo = nullptr;
      }

      if (m_hContext != nullptr && m_hContext != INVALID_HANDLE_VALUE)
      {
         CloseContext();
         m_hContext = nullptr;
      }
   }

   void file_find::CloseContext()
   {
      ::FindClose(m_hContext);
      return;
   }

   bool file_find::FindFile(const char * pstrName /* = nullptr */, ::u32 dwUnused /* = 0 */)
   {
      UNUSED_ALWAYS(dwUnused);
      close();
      m_pNextInfo = new WIN32_FIND_DATAW;
      m_bGotLast = false;

      if (pstrName == nullptr)
         pstrName = "*.*";
      multibyte_to_unicode(CP_UTF8, ((WIN32_FIND_DATAW*) m_pNextInfo)->cFileName, MAX_PATH, pstrName);

      wstring wstrName = utf8_to_unicode(pstrName);

      m_hContext = shell::FindFirstFile(wstrName, (WIN32_FIND_DATAW*) m_pNextInfo);

      if (m_hContext == INVALID_HANDLE_VALUE)
      {
         ::u32 dwTemp = ::get_last_error();
         close();
         ::set_last_error(dwTemp);
         return false;
      }
      wstring wstrRoot;

      unichar * pstrRoot = wstrRoot.alloc(_MAX_PATH);
      const unichar * pstr = shell::_fullpath(pstrRoot, wstrName, _MAX_PATH);

      // passed name isn't a valid path but was found by the API
      ASSERT(pstr != nullptr);
      if (pstr == nullptr)
      {
         m_strRoot.Empty();
         close();
         ::set_last_error(ERROR_INVALID_NAME);
         return false;
      }
      else
      {
         // find the last forward or backward whack
         unichar * pstrBack  = wcsrchr(pstrRoot, '\\');
         unichar * pstrFront = wcsrchr(pstrRoot, '/');

         if (pstrFront != nullptr || pstrBack != nullptr)
         {
            if (pstrFront == nullptr)
               pstrFront = pstrRoot;
            if (pstrBack == nullptr)
               pstrBack = pstrRoot;

            // from the start to the last whack is the root

            if (pstrFront >= pstrBack)
               *pstrFront = '\0';
            else
               *pstrBack = '\0';
         }
         wstrRoot.release_string_buffer();
      }
      m_strRoot = unicode_to_utf8(wstrRoot);
      return true;
   }

   bool file_find::MatchesMask(::u32 dwMask) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
         return (!!(((LPWIN32_FIND_DATAW) m_pFoundInfo)->dwFileAttributes & dwMask));
      else
         return false;
   }

   bool file_find::GetLastAccessTime(FILETIME* pTimeStamp) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT(pTimeStamp != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastAccessTime;
         return true;
      }
      else
         return false;
   }

   bool file_find::GetLastWriteTime(FILETIME* pTimeStamp) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT(pTimeStamp != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastWriteTime;
         return true;
      }
      else
         return false;
   }

   bool file_find::GetCreationTime(FILETIME* pTimeStamp) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr && pTimeStamp != nullptr)
      {
         *pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftCreationTime;
         return true;
      }
      else
         return false;
   }

   bool file_find::GetLastAccessTime(::earth::time& refTime) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
      {
         refTime = ::earth::time(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastAccessTime);
         return true;
      }
      else
         return false;
   }

   bool file_find::GetLastWriteTime(::earth::time& refTime) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
      {
         refTime = ::earth::time(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastWriteTime);
         return true;
      }
      else
         return false;
   }

   bool file_find::GetCreationTime(::earth::time& refTime) const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
      {
         refTime = ::earth::time(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftCreationTime);
         return true;
      }
      else
         return false;
   }

   bool file_find::IsDots() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      // return true if the file name is "." or ".." and
      // the file is a directory

      bool bResult = false;
      if (m_pFoundInfo != nullptr && IsDirectory())
      {
         LPWIN32_FIND_DATAW pFindData = (LPWIN32_FIND_DATAW) m_pFoundInfo;
         if (pFindData->cFileName[0] == '.')
         {
            if (pFindData->cFileName[1] == '\0' ||
                  (pFindData->cFileName[1] == '.' &&
                   pFindData->cFileName[2] == '\0'))
            {
               bResult = true;
            }
         }
      }

      return bResult;
   }

   bool file_find::FindNextFile()
   {
      ASSERT(m_hContext != nullptr);

      if (m_hContext == nullptr)
         return false;
      if (m_pFoundInfo == nullptr)
         m_pFoundInfo = new WIN32_FIND_DATAW;

      ASSERT_VALID(this);

      WIN32_FIND_DATAW * pTemp = m_pFoundInfo;
      m_pFoundInfo = m_pNextInfo;
      m_pNextInfo = pTemp;

      return shell::FindNextFile(m_hContext, (LPWIN32_FIND_DATAW) m_pNextInfo);
   }

   string file_find::GetFileURL() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strResult(L"file://");
      strResult += GetFilePath();
      return strResult;
   }

   string file_find::GetRoot() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);
      return m_strRoot;
   }

   string file_find::GetFilePath() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strResult = GetRoot();
      if (strResult[strResult.get_length()-1] != '\\' &&
            strResult[strResult.get_length()-1] != '/')
         strResult += m_chDirSeparator;
      strResult += GetFileName();
      return strResult;
   }

   string file_find::GetFileTitle() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string strFullName = GetFileName();
      string strResult;

      _splitpath(strFullName, nullptr, nullptr, strResult.GetBuffer(_MAX_PATH), nullptr);
      strResult.ReleaseBuffer();
      return strResult;
   }

   string file_find::GetFileName() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      string ret;

      if (m_pFoundInfo != nullptr)
      {
         unicode_to_utf8(ret, ((LPWIN32_FIND_DATAW) m_pFoundInfo)->cFileName);
      }
      return ret;
   }

   i64 file_find::get_length() const
   {
      ASSERT(m_hContext != nullptr);
      ASSERT_VALID(this);

      if (m_pFoundInfo != nullptr)
         return ((LPWIN32_FIND_DATAW) m_pFoundInfo)->nFileSizeLow +
                ((i64)(((LPWIN32_FIND_DATAW) m_pFoundInfo)->nFileSizeHigh) << 32);
      else
         return 0;
   }


   void file_find::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);
      dumpcontext << "\nm_hContext = " << (::u32) m_hContext;
   }

   void file_find::assert_ok() const
   {
      // if you trip the ASSERT in the else side, you've called
      // a get() function without having done at least one
      // FindNext() call

      if (m_hContext == nullptr)
         ASSERT(m_pFoundInfo == nullptr && m_pNextInfo == nullptr);
      else
         ASSERT(m_pFoundInfo != nullptr && m_pNextInfo != nullptr);

   }



} // namespace universal_windows



#endif // defined(WINDOWS_DESKTOP)

