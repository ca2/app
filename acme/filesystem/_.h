// Created by camilo on 2022-09-03 22:47 
// <3ThomasBorregaardSorensen
#pragma once


#include "file/_.h"
#include "filesystem/_.h"
#include "watcher/_.h"


namespace file
{


   class file_dialog;

   class folder_dialog;

   class link;


} // namespace file


namespace file
{


   enum enum_link
   {

      e_link_none = 0,
      e_link_target = 1,
      e_link_folder = 2,
      e_link_icon = 4,
      e_link_arguments = 8,

      e_link_all = e_link_target | e_link_folder | e_link_icon | e_link_arguments,

   };


   DECLARE_ENUMERATION(e_link, enum_link);


} // namespace file
