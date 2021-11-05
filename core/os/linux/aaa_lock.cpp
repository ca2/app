#include "framework.h"


#include <fcntl.h>
#include <sys/file.h>
#undef USE_MISC
#include <unistd.h>


i32 _c_lock_is_active(const ::string & lpszName)
{

   i32 * pfd;

   if(_c_lock(lpszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


i32 _c_lock(const ::string & lpszName, void ** pdata)
{

   i32 fd;

   _ca_get_file_name(file::path("/var/lib/ca2/")/ lpszName, true, &fd);

   if(fd == -1)
      return 0;


   if(flock(fd, LOCK_EX | LOCK_NB) == -1)
   {
      if(errno == EWOULDBLOCK)
      {
         close(fd);
         errno = EWOULDBLOCK;
         return 0;
      }
      else
      {
         close(fd);
         return 0;
      }
   }

   i32 * pi = new i32;
   *pi = fd;
   *pdata = pi;

   return 1;

}


i32 _c_unlock(void ** pdata)
{

   i32 * pfd = (i32 *) *pdata;

   if(flock(*pfd, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
   {
   }

   close(*pfd);


   *pfd = 0;

   delete pfd;

   *pdata = nullptr;

   return 1;

}



string _ca_get_file_name(const ::string & lpszName, bool bCreate, i32 * pfd)
{

   string str(lpszName);

   str.replace("\\", "/");
   str.replace("::", "_");

            auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create(::file_path_folder(str));

   if(bCreate)
   {
      i32 fd = open(str, O_CREAT | O_RDWR, 0777);
      if(fd == -1)
         return "";
      if(pfd != nullptr)
      {
         *pfd = fd;
      }
   }

   return str;
}
