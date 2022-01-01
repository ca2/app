

#include <sys/ptrace.h>
#define wait darwin_wait
#include <sys/wait.h>
#undef wait


#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>


#include <fcntl.h>
#include <sys/file.h>
#undef USE_MISC


#include <dirent.h>


platform_char *** process_get_pargv();
platform_char ** process_get_argv();


//#include "_user.h"

//#include "desktop_file.h"
//#include "x11.h"
#include "acme/exception/engine.h"

#include "exception_engine.h"



