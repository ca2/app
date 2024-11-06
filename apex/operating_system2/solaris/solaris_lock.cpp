#include "ca/ca.h"


#include <fcntl.h>
#include <sys/file.h>
#undef USE_MISC



int _c_lock_is_active(const ::scoped_string & scopedstrName)
{

   int * pfd;

   if(_c_lock(pszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


int _c_lock(const ::scoped_string & scopedstrName, void ** pdata)
{

   int fd;

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

   int * pi = ___new int();
   *pi = fd;
   *pdata = pi;

   return 1;

}


int _c_unlock(void ** pdata)
{

   int * pfd = (int *) *pdata;

   if(flock(*pfd, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
   {
   }

   close(*pfd);


   *pfd = 0;

   delete pfd;

   *pdata = nullptr;

   return 1;

}



vsstring _ca_get_file_name(const ::scoped_string & scopedstrName, bool bCreate, int * pfd)
{

   vsstring str(pszName);

   str.replace("\\", "/");
   str.replace("::", "_");

            auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(::file_path_folder(str));

   if(bCreate)
   {
      int fd = open(str, O_CREAT | O_RDWR);
      if(fd == -1)
         return "";
      if(pfd != nullptr)
      {
         *pfd = fd;
      }
   }

   return str;
}
