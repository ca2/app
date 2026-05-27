#include "framework.h"
//#include <fcntl.h>
//#include <sys/file.h>
//#include <errno.h>
//#undef USE_MISC
//
//
//
//#ifdef __APPLE__
//#include <unistd.h>
//
///* lock operations for flock(2) */
//#define	LOCK_SH		0x01		/* shared file lock */
//#define	LOCK_EX		0x02		/* exclusive file lock */
//#define	LOCK_NB		0x04		/* don't block when locking */
//#define	LOCK_UN		0x08		/* unlock file */
//
//
//
//::i32 flock(::i32, ::i32);
//
//
//
//#endif
//
//
//
//::i32 _c_lock_is_active(const_char_pointer pszName)
//{
//
//   ::i32 * pfd;
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
////::i32 _c_lock(const_char_pointer pszName, void ** pdata)
////{
////
////   ::i32 fd;
////
////   _ca_get_file_name(file::path("/var/lib/ca2/")/ pszName, true, &fd);
////
////   if(fd == -1)
////      return 0;
////
////
////   if(flock(fd, LOCK_EX | LOCK_NB) == -1)
////   {
////      if(errno == EWOULDBLOCK)
////      {
////         close(fd);
////         errno = EWOULDBLOCK;
////         return 0;
////      }
////      else
////      {
////         close(fd);
////         return 0;
////      }
////   }
////
////   ::i32 * pi = ___new ::i32();
////   *pi = fd;
////   *pdata = pi;
////
////   return 1;
////
////}
////
////
////::i32 _c_unlock(void ** pdata)
////{
////
////   ::i32 * pfd = (::i32 *) *pdata;
////
////   if(flock(*pfd, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
////   {
////   }
////
////   close(*pfd);
////
////
////   *pfd = 0;
////
////   delete pfd;
////
////   *pdata = nullptr;
////
////   return 1;
////
////}
////
////
////
////string _lock_get_file_name(const_char_pointer pszName, bool bCreate, ::i32 * pfd)
////{
////
////   string str(pszName);
////
////   str.replace("\\", "-");
////
////   str.replace("::", "_");
////
//////   auto psystem = system();
//////
//////   auto pdirectorysystem = psystem->m_pdirectorysystem;
//////
//////   pdirectorysystem->create(::file_path_folder(str));
////
////   if(bCreate)
////   {
////
////      ::i32 fd = open(str, O_CREAT | O_RDWR);
////
////      if(fd == -1)
////      {
////
////         return "";
////
////      }
////
////      if(pfd != nullptr)
////      {
////
////         *pfd = fd;
////
////      }
////
////   }
////
////   return str;
////
////}
////
////
////
