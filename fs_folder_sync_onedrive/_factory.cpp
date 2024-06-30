// Created by camilo on 2024-04-28 00:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "fs_folder_sync.h"


IMPLEMENT_FACTORY(fs_folder_sync_onedrive)
{

   pfactory->add_factory_item < ::fs_folder_sync_onedrive::folder_sync, ::fs::folder_sync >();
   
}



