#include "framework.h"
#include "child_frame.h"
#include "file_list.h"
#include "document.h"
#include "acme/constant/message.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/handler/item.h"
#include "aura/graphics/image/icon.h"


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

      MESSAGE_LINK(e_message_language, pchannel, this, &child_frame::_001OnAppLanguage);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &child_frame::on_message_show_window);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &child_frame::on_message_create);

   }


   void child_frame::on_create_bars()
   {

      return ::simple_frame_window::on_create_bars();

   }


   bool child_frame::DestroyBars()
   {

      return true;

   }


   void child_frame::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      simple_child_frame::route_command(pcommand);

   }


   ::pointer<document>child_frame::filemanager_document()
   {

      return  get_active_document();

   }


   void child_frame::on_message_create(::message::message * pmessage)
   {

      if (pmessage->m_bRet)
      {

         return;

      }

//#ifdef WINDOWS_DESKTOP
//
//      m_hMenuDefault = nullptr;
//
//#endif


   }


   void child_frame::_001OnAppLanguage(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   ::file::item_array child_frame::get_selected_items()
   {

      ::pointer<file_list>plist = get_active_impact();

      if (plist.is_null())
      {

         return ::file::item_array();

      }

      return plist->get_selected_items();

   }


   void child_frame::on_message_show_window(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


} // namespace filemanager



