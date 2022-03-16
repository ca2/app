#include "framework.h"
//#include <fcntl.h>
//#include <sys/file.h>
//#include <errno.h>
//
//
//
//#ifdef __APPLE__
//
//
///* lock operations for flock(2) */
//#define	LOCK_SH		0x01		/* shared file lock */
//#define	LOCK_EX		0x02		/* exclusive file lock */
//#define	LOCK_NB		0x04		/* don't block when locking */
//#define	LOCK_UN		0x08		/* unlock file */
//
//
//
//int flock(int, int);
//
//
//
//#endif
//
//
//
//int _c_lock_is_active(const char * pszName)
//{
//
//   int * pfd;
//
//   if(_c_lock(pszName, (void **) &pfd))
//   {
//      _c_unlock((void **) &pfd);
//      return false;
//   }
//
//   return true;
//
//}
//
//
//int _c_lock(const char * pszName, void ** pdata)
//{
//
//   int fd;
//
//   _ca_get_file_name(file::path("/var/lib/ca2/") / pszName, true, &fd);
//
//   if(fd == -1)
//      return 0;
//
//
//   if(flock(fd, LOCK_EX | LOCK_NB) == -1)
//   {
//      if(errno == EWOULDBLOCK)
//      {
//         close(fd);
//         errno = EWOULDBLOCK;
//         return 0;
//      }
//      else
//      {
//         close(fd);
//         return 0;
//      }
//   }
//
//   int * pi = new int;
//   *pi = fd;
//   *pdata = pi;
//
//   return 1;
//
//}
//
//
//int _c_unlock(void ** pdata)
//{
//
//   int * pfd = (int *) *pdata;
//
//   if(flock(*pfd, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
//   {
//   }
//
//   close(*pfd);
//
//
//   *pfd = 0;
//
//   delete pfd;
//
//   *pdata = nullptr;
//
//   return 1;
//
//}
//
//
//
//string _ca_get_file_name(const char * pszName, bool bCreate, int * pfd)
//{
//
//   string str(pszName);
//
//   str.replace("\\", "/");
//   str.replace("::", "_");
//
//            auto psystem = m_psystem;
//
//         auto pacmedir = psystem->m_pacmedirectory;
//
//pacmedir->create(::file_path_folder(str));
//
//   if(bCreate)
//   {
//      int fd = open(str, O_CREAT | O_RDWR);
//      if(fd == -1)
//         return "";
//      if(pfd != nullptr)
//      {
//         *pfd = fd;
//      }
//   }
//
//   return str;
//}
