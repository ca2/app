#include "ca/ca.h"


#include <fcntl.h>
#include <sys/file.h>
#undef USE_MISC



i32 _c_lock_is_active(const char * pszName)
{

   i32 * pfd;

   if(_c_lock(pszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


i32 _c_lock(const char * pszName, void ** pdata)
{

   i32 fd;

   _ca_get_file_name(dir::path("/var/lib/ca2/", pszName), true, &fd);

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



vsstring _ca_get_file_name(const char * pszName, bool bCreate, i32 * pfd)
{

   vsstring str(pszName);

   str.replace("\\", "/");
   str.replace("::", "_");

            auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(::file_path_folder(str));

   if(bCreate)
   {
      i32 fd = open(str, O_CREAT | O_RDWR);
      if(fd == -1)
         return "";
      if(pfd != nullptr)
      {
         *pfd = fd;
      }
   }

   return str;
}
