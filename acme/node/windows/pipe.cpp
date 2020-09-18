#include "framework.h"
#include "acme/node/windows/_windows.h"


namespace windows
{


   pipe::pipe()
   {


      m_hRead = nullptr;
      m_hWrite = nullptr;
      m_pchBuf = nullptr;


   }


   pipe::~pipe()
   {

      if(m_pchBuf != nullptr)
      {
         free(m_pchBuf);
      }

      ::CloseHandle(m_hRead);

      ::CloseHandle(m_hWrite);

   }


   bool pipe::create(bool bBlock, bool bInherit)
   {

      if (!::process::pipe::create(bBlock, bInherit))
      {

         return false;

      }

      xxf_zero(m_sa);
      m_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_sa.bInheritHandle = bInherit ? TRUE : FALSE;
      m_sa.lpSecurityDescriptor = nullptr;


      if(!CreatePipe(&m_hRead,&m_hWrite,&m_sa,0))
         return false;

      if(!bBlock)
      {

         DWORD dwMode = PIPE_NOWAIT;
         VERIFY(SetNamedPipeHandleState(m_hRead,&dwMode,nullptr,nullptr));
         //VERIFY(SetNamedPipeHandleState(m_hWrite,&dwMode,nullptr,nullptr));

      }

      return true;

   }


   bool pipe::not_inherit_read()
   {

      if(!SetHandleInformation(m_hRead,HANDLE_FLAG_INHERIT,0))
         return false;

      return true;

   }


   bool pipe::not_inherit_write()
   {

      if(!SetHandleInformation(m_hWrite,HANDLE_FLAG_INHERIT,0))
         return false;

      return true;

   }


   bool pipe::write(const char * psz)
   {

      u32 dwLen = (u32)strlen(psz);

      bool bSuccess = false;

      DWORD dwWritten;

      bSuccess = WriteFile(m_hWrite,(const char *)psz,dwLen,&dwWritten,nullptr) != FALSE;

      return bSuccess != FALSE && dwWritten == dwLen;

   }


   string pipe::read()
   {

      string str;

      const i32 BUFSIZE = 1024 * 8;

      DWORD dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      for(;;)
      {

         __memset(chBuf,0,BUFSIZE);

         try
         {

            bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,nullptr) != FALSE;

         }
         catch(...)
         {

            bSuccess = false;

         }

         if(!bSuccess || dwRead == 0)
            break;

         str += chBuf;

         if(dwRead < BUFSIZE)
            break;

      }

      return str;

   }

   string pipe::one_pass_read()
   {

      string str;

      const i32 BUFSIZE = 1024 * 8;

      DWORD dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      __memset(chBuf,0,BUFSIZE);

      try
      {

         bSuccess = ReadFile(m_hRead,chBuf,BUFSIZE,&dwRead,nullptr) != FALSE;

      }
      catch(...)
      {

         bSuccess = false;

      }

      if(!bSuccess || dwRead == 0)
         return str;

      str += chBuf;

      return str;

   }


   void pipe::readex()
   {

      if(m_pchBuf == nullptr)
      {

         m_pchBuf = (char *)malloc(1025);

         if(m_pchBuf == nullptr)
            __throw(memory_exception());

      }

      __memset(&m_overlapped,0,sizeof(m_overlapped));

      m_overlapped.m_ppipe = this;

      ReadFileEx(m_hRead,m_pchBuf,1024,&m_overlapped.m_overlapped,(LPOVERLAPPED_COMPLETION_ROUTINE)&pipe::read_complete);

   }


   void WINAPI pipe::read_complete(
   u32 dwErrorCode,
   u32 dwNumberOfBytesTransfered,
   LPOVERLAPPED pOverlapped

   )
   {

      UNREFERENCED_PARAMETER(dwErrorCode);

      overlapped * plap = nullptr;

      plap = plap->from(pOverlapped);


      i32 iLimit = min(dwNumberOfBytesTransfered,1024);

      plap->m_ppipe->m_pchBuf[iLimit] = '\0';

      plap->m_ppipe->m_strRead += plap->m_ppipe->m_pchBuf;

   }


} // namespace acme
























