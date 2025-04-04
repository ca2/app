#include "framework.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/operating_system/environment.h"
//#include "acme/operating_system/posix/file.h"
#include "acme/operating_system/path.h"

#include <sys/types.h>
#include <sys/sysctl.h>
//#include <sys/user.h>
#include <sys/stat.h>
//#include <libutil.h>
#include <kvm.h>
#include <unistd.h>

//class kvm_type
//{
//public:

   //char m_errbuf[_POSIX2_LINE_MAX];

   //kvm_t * m_pkvm;
   
   //kvm_type()
   //{
   
      //m_pkvm = nullptr;
   
   //}
   
   //~kvm_type()
   //{
   
      //if(m_pkvm)
      //{

         //kvm_close(m_pkvm);

         //m_pkvm = nullptr;
         
      //}
   
   //}
   
   
   //bool kvm_openfiles()
   //{
   
      //m_pkvm = ::kvm_openfiles(nullptr, 0, 0, KVM_NO_FILES, m_errbuf);
      
      //if(!m_pkvm)
      //{
      
         //return false;
      
      //}
      
      //return true;
   
   //}
   

   //kinfo_file * kvm_getfiles_by_pid(pid_t pid, int * piCount)
   //{

       //auto pinfofile = kvm_getfiles(m_pkvm, KERN_FILE_BYPID, pid, sizeof(struct kinfo_file), piCount); 
       
       //return pinfofile;

   //}

//};


//bool process_contains_module(pid_t pid, const ::file::path & path)
//{
   
   //struct stat st;

   //if(stat(path.c_str(), &st))
   //{
   
      //return false;
   
   //}
   
   //kvm_type kvm;
   
   //if (kvm.kvm_openfiles()) 
   //{
   
      //int iCount = 0;
   
      //auto pfile = kvm.kvm_getfiles_by_pid(getpid(), &iCount);
	
      //for (int i = 0; i < iCount; i++) 
      //{
      
         //if (pfile[i].fd_fd == KERN_FILE_TEXT) 
         //{

            //if (st.st_dev == (dev_t)pfile[i].va_fsid 
             //|| st.st_ino == (ino_t)pfile[i].va_fileid)
            //{

               //return true;

            //}

         //}

      //}
      
   //}
   
   //return false;

//}


::pointer < ::operating_system::environment > operating_system_get_environment();


::file::path get_module_path()
{

   auto strArg0 = ::platform::get()->_get_args(0);
   
   auto penvironment = ::operating_system_get_environment();
   
   printf("\n\nnetbsd arg0 : %s\n", strArg0.c_str());
   
   auto path = path_get_path(strArg0, penvironment);
   
   printf("\n\nnetbsd path : %s\n", path.c_str());
   
   if ((path.m_etype & ::file::e_type_existent_file) != ::file::e_type_existent_file)
   {
   
      printf("\n\nnetbsd file exists\n");
      
      //if (process_contains_module(getpid(), path)) 
      {
      
         printf("\n\nnetbsd process_contains_module\n");
         
         return path;
      	
      }
      //else
      {
      
//         printf("\n\nnetbsd process doesn't contain module\n");
      
      }
      
   }
	
   return strArg0;

}



