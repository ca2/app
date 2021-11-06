//
// Created by camilo on 04/03/2021. 06:40 BRT ThomasBS_, I love you!!
//
#include "framework.h"
#include <unistd.h>


string get_current_directory_name()
{

    string strCurrentDirName;

#ifdef __APPLE__

   strCurrentDirName = ::string_from_strdup(getcwd(nullptr, 0));

#else

    strCurrentDirName = ::string_from_strdup(get_current_dir_name());

#endif

   return strCurrentDirName;

}


