#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"


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

      UNREFERENCED_PARAMETER(pmessage);


   }


   bool main_frame::on_create_bars()
   {

      return ::simple_frame_window::on_create_bars();

   }


   ::filemanager::document * main_frame::filemanager_document()
   {


      return dynamic_cast <document *> (get_active_document());

   }



} // namespace filemanager



