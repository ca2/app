#pragma once


//#include "apex/_file_watcher.h"
//#include "apex/_file_watcher_listener_thread.h"
//#include "apex/filesystem/filesystem.h"
//#include "apex/filesystem/filesystem/filesystem_application.h"
//#include "apex/filesystem/filesystem/filesystem_dir_application.h"
//#include "apex/filesystem/filesystem/filesystem_system.h"
//#include "apex/filesystem/filesystem/filesystem_dir_system.h"


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


class dir_context;
class file_context;
class dir_system;
class file_system;


namespace file
{


   class link;


} // namespace file



