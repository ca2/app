//
// Created by camilo on 2026-01-02 <3ThomasBorregaardSørensen!!
// At FreeBSd 15.0!!
//
#include "framework.h"
#include "acme/operating_system/file.h"


CLASS_DECL_ACME ::file::path get_home_config_folder_path()
{

   auto pathHomeConfigFolder = get_home_folder_path() / ".config";

   return pathHomeConfigFolder;

}




