#include "framework.h"
#include "acme/operating_system.h"
// #include "file_lock.h"
// #include <fcntl.h>
// #include <sys/file.h>
// #undef USE_MISC
// #include <unistd.h>


namespace file_lock
{


   // file_lock::file_lock()
   // {

   //    m_iFileDescriptor = -1;

   // }


   // file_lock::file_lock(const char * pszName)
   // {

   //    m_iFileDescriptor = -1;

   //    set_name(pszName);

   // }


   // file_lock::~file_lock()
   // {

   //    close_file();

   // }


   // bool file_lock::set_name(const char * pszName)
   // {

   //    close_file();

   //    m_strName = pszName;

   //    m_strPath = _get_file_name(pszName);

   //    return true;

   // }


   // bool file_lock::is_active()
   // {

   //    if(lock())
   //    {

   //       unlock();

   //       return false;

   //    }

   //    return true;

   // }


   // bool file_lock::lock()
   // {

   //    if(!create_file())
   //    {

   //       return false;

   //    }

   //    if(flock(m_iFileDescriptor, LOCK_EX | LOCK_NB) == -1)
   //    {

   //       if(errno == EWOULDBLOCK)
   //       {

   //          close();

   //          errno = EWOULDBLOCK;

   //          return 0;

   //       }
   //       else
   //       {

   //          close(fd);

   //          return 0;

   //       }

   //    }

   //    i32 * pi = new i32;

   //    *pi = fd;

   //    *pdata = pi;

   //    return 1;

   // }


   // bool file_lock::unlock()
   // {

   //    if(m_iFileDescriptor < 0)
   //    {

   //       return false;

   //    }


   //    if(flock(m_iFileDescriptor, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
   //    {

   //       close_file();

   //       return false;

   //    }

   //    close_file();

   //    return 1;

   // }


   // bool file_lock::create_file()
   // {

   //    if(m_iFileDescriptor >= 0)
   //    {

   //       return true;

   //    }

   //    m_iFileDescriptor = open(m_strPath, O_CREAT | O_RDWR, 0777);

   //    if(m_iFileDescriptor < 0)
   //    {

   //       return false;

   //    }

   //    return true;

   // }


   // bool file_lock::close_file()
   // {

   //    if(m_iFileDescriptor < 0)
   //    {

   //       return true;

   //    }

   //    close(m_iFileDescriptor);

   //    m_iFileDescriptor = -1;

   //    return true;

   // }

//   string file_lock::_get_file_name(const char * lpszName)
//   {
//
//      string str;
//
//      str.replace("\\", "-");
//
//      str.replace("::", "_");
//
//      str = "/var/lib/ca2/" + str;
//
//      return str;
//
//   }

} // namespace file_lock



