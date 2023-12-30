#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"


#include <fcntl.h>
#include <sys/file.h>

i32 _c_lock(const ::scoped_string & scopedstrName, void ** pdata);
i32 _c_unlock(void ** pdata);
string _ca_get_file_name(const ::scoped_string & scopedstrName, bool bCreate, i32 * pfd);

i32 _c_lock_is_active(const ::scoped_string & scopedstrName)
{

   i32 * pfd;

   if(_c_lock(pszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


i32 _c_lock(const ::scoped_string & scopedstrName, void ** pdata)
{

   i32 fd;

   _ca_get_file_name(::file::path("/var/lib/apex/") / pszName, true, &fd);

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

   i32 * pi = __new< i32 >();
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


string _ca_get_file_name(const ::scoped_string & scopedstrName, bool bCreate, i32 * pfd)
{

   string str(pszName);

   str.find_replace("\\", "/");
   str.find_replace("::", "_");

   auto psystem = system();

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
