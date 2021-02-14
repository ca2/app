#include "framework.h"
#include "acme/operating_system.h"


#if defined(LINUX) || defined(ANDROID)
#include <sys/stat.h>
#include <fcntl.h>
#endif


namespace acme
{


#ifdef WINDOWS


   exclusive::exclusive(string strId ARG_SEC_ATTRS)
   {

      m_strId = strId;

      m_bResourceException = false;

      try
      {

         m_pmutex = __new(::mutex(e_create_new, false, strId ADD_PARAM_SEC_ATTRS));

         m_dwLastError = ::GetLastError();

      }
      catch (resource_exception &)
      {

         try
         {

            m_pmutex = __new(::mutex(e_create_new, false, strId));

            m_dwLastError = ::GetLastError();

         }
         catch (resource_exception &)
         {

            m_bResourceException = true;

         }

      }

   }


#else


   exclusive::exclusive(string strId ARG_SEC_ATTRS)
   {

      m_strId = strId;

      ::file::path path;

      path = "/var/tmp";

      path /= strId;

      ::dir::mk(path.folder());

      m_iFile = open(path, O_WRONLY | O_CREAT, 0777);

      m_iLock = lockf(m_iFile, F_TLOCK, 0);

   }


#endif


   exclusive::~exclusive()
   {

   }


   bool exclusive::exclusive_fails() const
   {

#ifdef WINDOWS

      return m_dwLastError == ERROR_ALREADY_EXISTS || m_bResourceException;

#else

      return m_iLock < 0;

#endif

   }


} // namespace acme



