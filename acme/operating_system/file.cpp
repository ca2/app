//
//  file.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 09/06/22 07:42.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#include "framework.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/file.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"


void file_put_contents(const ::scoped_string & scopedstrFilePath, const ::scoped_string & scopedstr)
{
   
   auto ptask = ::get_task();
   
   ptask->file_system()->put_contents(scopedstrFilePath, scopedstr);
   
}


CLASS_DECL_ACME ::file::path get_appconfig_folder_path()
{

   auto pathHomeConfigFolder = get_home_config_folder_path();

   auto papplication = ::system()->m_papplication;

   auto pathConfig = get_home_config_folder_path();

   auto pathAppConfig = pathConfig / papplication->m_strAppId;

   return pathAppConfig;


}


CLASS_DECL_ACME ::string get_appconfig(const ::scoped_string & scopedstr)
{

   auto pathAppConfig = get_appconfig_folder_path();

   ::string strFilename = scopedstr + ".txt";

   auto pathAppConfigFile = pathAppConfig / strFilename;

   if (!file_exists(pathAppConfigFile))
   {

      return {};

   }

   return file_as_string(pathAppConfigFile);


}




