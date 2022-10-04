#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "core/filesystem/filemanager/_filemanager.h"
//#endif
#include "main_frame.h"
#include "document.h"


namespace filemanager
{



   main_frame::main_frame()
   {



   }


   main_frame::~main_frame()
   {

   }


   void main_frame::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);


   }


   void main_frame::on_create_bars()
   {

      return ::simple_frame_window::on_create_bars();

   }


   ::filemanager::document * main_frame::filemanager_document()
   {


      return dynamic_cast <document *> (get_active_document());

   }



} // namespace filemanager



