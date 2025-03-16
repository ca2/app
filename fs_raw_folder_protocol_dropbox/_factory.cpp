// Created by camilo on 2024-04-28 00:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "fs_raw_folder_protocol.h"


IMPLEMENT_FACTORY(fs_raw_folder_protocol_dropbox)
{

   pfactory->add_factory_item < ::fs_raw_folder_protocol_dropbox::folder, ::fs::raw_folder_protocol >();
   pfactory->add_factory_item < ::fs_raw_folder_protocol_dropbox::folder, ::component_implementation >();
   
}



