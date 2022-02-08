//
//  ns_exe_path.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 8/3/15.
//
//
#include "framework.h"
#include <mach-o/dyld.h>

string get_exe_path()
{
char path[8192];
u32 size = sizeof(path);
if (_NSGetExecutablePath(path, &size) == 0)
printf("executable path is %s\n", path);
else
printf("buffer too small; need size_i32 %u\n", size);
//                     strPath += ".app/Contents/MacOS/app";

   return path;

}
