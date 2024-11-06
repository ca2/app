#include "framework.h"


#include <fcntl.h>
#include <sys/file.h>
#undef USE_MISC
#include <unistd.h>


int _c_lock_is_active(const char * lpszName)
{

   int * pfd;

   if(_c_lock(lpszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


int _c_lock(const char * lpszName, void ** pdata)
{

   int fd;

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

   int * pi = aaa_primitive_new int;
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



string _ca_get_file_name(const char * lpszName, bool bCreate, int * pfd)
{

   string str(lpszName);

   str.replace("\\", "/");
   str.replace("::", "_");

            auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(::file_path_folder(str));

   if(bCreate)
   {
      int fd = open(str, O_CREAT | O_RDWR, 0777);
      if(fd == -1)
         return "";
      if(pfd != nullptr)
      {
         *pfd = fd;
      }
   }

   return str;
}
