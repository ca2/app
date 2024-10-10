#include "framework.h"
#include "_netbsd.h"
#include "acme/operating_system/ansi/binreloc.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>

//#if defined(__OpenBSD__)
#include <kvm.h>
//#include <sys/types.h>
//#include <sys/sysctl.h>
//#else

string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}


bool __node_further_file_is_equal(const ::file::path &,  const ::file::path &)
{

   return false;

}



//bool context::_os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pprimitive, bool bNoUI, bool bNoMount)
//{
//
//    if(::is_null(psz))
//    {
//
//        return false;
//
//    }
//
//
//
//
//   char * pszRealPath = ::realpath(psz, NULL);
//
//   if(pszRealPath == NULL)
//   {
//
//      return false;
//
//   }
//
//   if(strcmp(psz, pszRealPath) == 0)
//   {
//
//    ::free(pszRealPath);
//
//    return false;
//
//   }
//
//   try
//   {
//
//      path = pszRealPath;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   ::free(pszRealPath);
//
//   return true;
//
//}
//


// CLASS_DECL_ACME bool context::os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



CLASS_DECL_ACME bool _os_may_have_alias(const ::scoped_string & scopedstr)
{

   return true;

}


namespace path
{


   ::file::path module()
   {

      // https://arstechnica.com/civis/viewtopic.php?t=433790

      char exepath[PATH_MAX];

      char temp[PATH_MAX];

      ::snprintf(temp, sizeof(temp),"/proc/%d/file", ::getpid());

      ::realpath(temp, exepath);
      // end https://arstechnica.com/civis/viewtopic.php?t=433790

      return exepath;

   }


} // namespace path


char * get_current_dir_name()
{

    return getcwd(nullptr, 0);

}





//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <errno.h>


//
//static get_path_result_t path_get_path_core(const wcstring &cmd, const wcstring_list_t &pathsv,
//                                            const environment_t &vars) {
//    const get_path_result_t noent_res{ENOENT, wcstring{}};
//    get_path_result_t result{};
//
//    /// Test if the given path can be executed.
//    /// \return 0 on success, an errno value on failure.
//    auto test_path = [](const wcstring &path) -> int {
//        std::string narrow = wcs2string(path);
//        struct stat buff;
//        if (access(narrow.c_str(), X_OK) != 0 || stat(narrow.c_str(), &buff) != 0) {
//            return errno;
//        }
//        return S_ISREG(buff.st_mode) ? 0 : EACCES;
//    };
//
//    // Commands cannot contain NUL byte.
//    if (cmd.find(L'\0') != wcstring::npos) {
//        return noent_res;
//    }
//
//    // If the command has a slash, it must be an absolute or relative path and thus we don't bother
//    // looking for a matching command.
//    if (cmd.find(L'/') != wcstring::npos) {
//        wcstring abs_cmd = path_apply_working_directory(cmd, vars.get_pwd_slash());
//        int merr = test_path(abs_cmd);
//        return get_path_result_t{merr, std::move(abs_cmd)};
//    }
//
//    get_path_result_t best = noent_res;
//    wcstring proposed_path;
//    for (const auto &next_path : pathsv) {
//        if (next_path.empty()) continue;
//        proposed_path = next_path;
//        append_path_component(proposed_path, cmd);
//        int merr = test_path(proposed_path);
//        if (merr == 0) {
//            // We found one.
//            best = get_path_result_t{merr, std::move(proposed_path)};
//            break;
//        } else if (merr != ENOENT && best.err == ENOENT) {
//            // Keep the first *interesting* error and path around.
//            // ENOENT isn't interesting because not having a file is the normal case.
//            // Ignore if the parent directory is already inaccessible.
//            if (waccess(wdirname(proposed_path), X_OK) == 0) {
//                best = get_path_result_t{merr, std::move(proposed_path)};
//            }
//        }
//    }
//    return best;
//}
//
//maybe_t<wcstring> path_get_path(const wcstring &cmd, const environment_t &vars) {
//    auto result = path_try_get_path(cmd, vars);
//    if (result.err != 0) {
//        return none();
//    }
//    wcstring path = std::move(result.path);
//    return path;
//}
//
//get_path_result_t path_try_get_path(const wcstring &cmd, const environment_t &vars) {
//    auto pathvar = vars.get(L"PATH");
//    return path_get_path_core(cmd, pathvar ? pathvar->as_list() : kDefaultPath, vars);
//}


//::file::path get_module_path()
//{
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
   
      
/*
    ::string narrow;
    static kvm_t *kd = nullptr;
	narrow=  ::platform()->get()->m_argv[0]
    // not sure if I am doing this right??
    null_environment_t vars = null_environment_t();
    auto path = path_get_path(wargv0, vars);
    if (path) {
        int cntp = 0;
        struct stat st;
        kinfo_file *kif = nullptr;
        char errbuf[_POSIX2_LINE_MAX];
        narrow = wcs2string(*path); 
        kd = kvm_openfiles(nullptr, nullptr, nullptr, KVM_NO_FILES, errbuf); 
        if (kd) {
            if ((kif = kvm_getfiles(kd, KERN_FILE_BYPID, getpid(), sizeof(struct kinfo_file), &cntp))) {
                for (int i = 0; i < cntp; i++) {
                    if (kif[i].fd_fd == KERN_FILE_TEXT) {
                        if (!stat(narrow.c_str(), &st)) {
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

*/


