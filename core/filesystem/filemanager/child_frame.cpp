#include "framework.h"
//#include "_filemanager.h"


namespace filemanager
{


   child_frame::child_frame()
   {

   }


   child_frame::~child_frame()
   {
   }


   void child_frame::install_message_routing(::channel * pchannel)
   {

      simple_child_frame::install_message_routing(pchannel);

      MSG_TYPE_LINK(::message::type_language, pchannel, this, &child_frame::_001OnAppLanguage);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &child_frame::_001OnShowWindow);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &child_frame::_001OnCreate);

   }


   bool child_frame::on_create_bars()
   {

      //auto pdocument = GetActiveDocument();

      //return pdocument->on_create_bars(this);

      return ::simple_frame_window::on_create_bars();

   }


   bool child_frame::DestroyBars()
   {

      return true;

   }


   void child_frame::route_command_message(::user::command * pcommand)
   {

      simple_child_frame::route_command_message(pcommand);

   }





   __pointer(document) child_frame::filemanager_document()
   {

      return  GetActiveDocument();

   }


   void child_frame::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->m_bRet)
      {

         return;

      }

      m_hMenuDefault = nullptr;

   }


   void child_frame::_001OnAppLanguage(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   ::file::item_array child_frame::get_selected_items()
   {

      __pointer(file_list) plist = GetActiveView();

      if (plist.is_null())
      {

         return ::file::item_array();

      }

      return plist->get_selected_items();

   }


   void child_frame::_001OnShowWindow(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);

   }



//   void child_frame::OnChangeEditSearch()
//   {
//
////      __pointer(::user::document) pdocument = GetActiveDocument();
////
////      if (pdocument != nullptr)
////      {
////
////         auto pupdate = new_update();
////
////         pupdate->m_id = id_filter;
////
////         string str;
////
////      }
//
//   }


//   void child_frame::OnChangeEditSearch()
//   {
//
//      __pointer(::user::document) pdocument = GetActiveDocument();
//
//      if (pdocument != nullptr)
//      {
//
//         auto pupdate = new_update();
//
//         pupdate->m_id = id_filter;
//
//         string str;
//
//      }
//
//   }


} // namespace filemanager



