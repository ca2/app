#include "framework.h"
#include "edit_window.h"


namespace user
{


   edit_window::edit_window()
   {


   }


   edit_window::~edit_window()
   {

   }


   void edit_window::install_edit_window_message_routing(channel * pchannel)
   {

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &edit_window::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &edit_window::_001OnDestroy);
      IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &edit_window::_001OnSetFocus);
      IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &edit_window::_001OnKillFocus);

   }


   void edit_window::_001OnCreate(::message::message * pmessage)
   {
      
      _OnCreate();

   }


   void edit_window::_001OnDestroy(::message::message * pmessage)
   {

      _OnDestroy();

   }


   void edit_window::_001OnSetFocus(::message::message * pmessage)
   {

      _OnSetFocus();

   }


   void edit_window::_001OnKillFocus(::message::message * pmessage)
   {

      _OnKillFocus();

   }




   LRESULT edit_window::_OnCreate(VOID)
   {

      return 0;

   }
   
   LRESULT edit_window::_OnDestroy(VOID)
   {

      return 0;

   }
   
   //LRESULT _OnCommand(WORD, WORD, HWND);

   LRESULT edit_window::_OnSetFocus(VOID)
   {

      return 0;

   }
   
   
   LRESULT edit_window::_OnKillFocus(VOID)
   {

      return 0;

   }


   void edit_window::get_text_composition_area(::rect & r)
   {


   }


   void edit_window::on_text_composition_done(string str)
   {


   }

   
   bool edit_window::edit_undo()
   {

      return false;

   }


   bool edit_window::is_text_composition_active()
   {

      return get_wnd()->is_text_composition_active();

   }

} // namespace user



