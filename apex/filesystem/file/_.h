#pragma once


#include "_constant.h"


using transfer_progress_function =
::function < void(double, filesize, filesize) >;


namespace file
{

   
   class insert_item;
   class edit_file;
   class set;


   /// Actions to listen for. Rename will send two events, one for
   /// the deletion of the old file, and one for the creation of the
   /// memory_new file.
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



//#include "_constant.h"