#include "framework.h"
#include "acid/filesystem/filesystem/ace_path.h"
#include "acid/platform/platform.h"
#include "acid/platform/system.h"
#include "acid/operating_system/environment.h"

#include <sys/types.h>
//#include <sys/user.h>
#include <sys/stat.h>
#include <libutil.h>
#include <kvm.h>


::file::path get_module_path_openbsd()
{
/*
   int mib[4];
   mib[0] = CTL_KERN;
   mib[1] = KERN_PROC;
   mib[2] = KERN_PROC_PATHNAME;
   mib[3] = -1;
   char pathbuf[4096];
   size_t cb = sizeof(pathbuf);
   sysctl(mib, 4, pathbuf, &cb, NULL, 0);
   */



   ::string str;
   static kvm_t *kd = nullptr;
   str=  ::platform::get()->_get_argv(0);
   // not sure if I am doing this right??
   auto penvironment = ::platform::get()->system()->__create<::operating_system::environment>();
   auto path = ::platform::get()->system()->acepath()->path_get_path(str, penvironment);
   if (path.m_etype & (::file::e_type_existent_file))
   {
      int cntp = 0;
      struct stat st;
      kinfo_file *kif = nullptr;
      char errbuf[_POSIX2_LINE_MAX];
      kd = kvm_openfiles(nullptr, nullptr, nullptr, KVM_NO_FILES, errbuf);
      if (kd) {
         if ((kif = kvm_getfiles(kd, KERN_FILE_BYPID, getpid(), sizeof(struct kinfo_file), &cntp))) {
            for (int i = 0; i < cntp; i++) {
               if (kif[i].fd_fd == KERN_FILE_TEXT) {
                  if (!stat(path.c_str(), &st)) {
                     if (st.st_dev == (dev_t)kif[i].va_fsid || st.st_ino == (ino_t)kif[i].va_fileid) {
                        ok = true;
                        break;
                     }
                  }
               }
            }
         }
         kvm_close(kd);
      }
   }
   narrow[buff_size] = '\0';
   strcpy(buff, narrow.substr(0, buff_size).c_str());
   return ((ok) ? std::string(buff)  : "fish");

}
