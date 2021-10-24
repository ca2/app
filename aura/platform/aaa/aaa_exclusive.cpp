#include "framework.h"


#if defined(LINUX) || defined(ANDROID)
#include <sys/stat.h>
#include <fcntl.h>
#endif


namespace aura
{


#ifdef WINDOWS


   exclusive::exclusive(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      m_strId = strId;

      m_bResourceException = false;

      try
      {

         set_mutex(__new(::mutex(e_create_new, false, strId, psa)));

         m_dwLastError = ::GetLastError();

      }
      catch (resource_exception &)
      {

         try
         {

            set_mutex(__new(::mutex(e_create_new, false, strId)));

            m_dwLastError = ::GetLastError();

         }
         catch (resource_exception &)
         {

            m_bResourceException = true;

         }

      }

   }


#else


   exclusive::exclusive(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      __UNREFERENCED_PARAMETER(psa);

      m_strId = strId;

      ::file::path path;

      path = "/::payload/tmp";

      path /= strId;

               auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create(path.folder());

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


} // namespace aura



