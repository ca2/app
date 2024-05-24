#include "framework.h"
#include "exclusive.h"
#include "acid/filesystem/filesystem/ace_directory.h"
#include "acid/platform/node.h"
#include "acid/platform/system.h"
////#include "acid/primitive/primitive/object.h"
#include "acid/_operating_system.h"


//#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <unistd.h>
//#endif


namespace acid
{


//#ifdef WINDOWS
//

   //exclusive::exclusive(::particle * pparticle, string strId ARG_SEC_ATTRS)
   exclusive::exclusive()
   {

      //m_strId = strId;

      //m_bResourceException = false;

      //try
      //{

      //   m_pmutex = pparticle->node()->create_global_named_mutex(pparticle, false, strId);

      //   //m_pmutex = //__allocate< ::pointer < ::mutex > >(pparticle, false, strId ADD_PARAM_SEC_ATTRS);

      //   //m_dwLastError = ::GetLastError();

      //}
      //catch (const ::exception &)
      //{

      //   m_bResourceException = true;

      //   //try
      //   //{

      //   //   m_pmutex = __allocate< ::pointer < ::mutex > >(pparticle, false, strId);

      //   //   m_dwLastError = ::GetLastError();

      //   //}
      //   //catch (const ::exception &)
      //   //{

      //   //   m_bResourceException = true;

      //   //}

      //}

   }


//#else
//
//
//   exclusive::exclusive(::particle * pparticle, string strId ARG_SEC_ATTRS)
//   {
//
//      initialize(pparticle);
//
//      m_strId = strId;
//
//      ::file::path path;
//
//      if(strId.case_insensitive_begins("Local\\"))
//      {
//
//         path = pparticle->acedirectory()->home() / ".config/acid";
//
//      }
//      else
//      {
//
//         path = "/var/tmp/acid";
//
//      }
//
//      path /= strId;
//
//      acedirectory()->create(path.folder());
//
//      m_iFile = open(path, O_WRONLY | O_CREAT, 0777);
//
//      m_iLock = lockf(m_iFile, F_TLOCK, 0);
//
//   }
//
//
//#endif
//

   exclusive::~exclusive()
   {

   }


   bool exclusive::exclusive_fails() const
   {

      //return m_pmutex->already_exists();

      return false;

//#ifdef WINDOWS
//
//      return m_dwLastError == ERROR_ALREADY_EXISTS || m_bResourceException;
//
//#else
//
//      return m_iLock < 0;
//
//#endif

   }


} // namespace acid



