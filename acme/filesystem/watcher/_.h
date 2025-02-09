// From apex/filesystem/file/_.h by camilo on 2023-0-17 08:36 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_constant.h"


using transfer_progress_function =
::function < void(double, filesize, filesize) >;


namespace file
{

   class action;


   class watch;
   class watcher;
   class listener;


   //using watch_id = long long;



   /// Actions to listen for. Rename will send two happenings, one for
   /// the deletion of the old file, and one for the creation of the
   /// ___new file.
   enum enum_action
   {


      e_action_none = 0,
      /// Sent when a file is created or renamed
      e_action_add = 1,
      /// Sent when a file is deleted or renamed
      e_action_delete = 2,
      /// Sent when a file is modified
      e_action_modify = 4


   };



};



