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

      MESSAGE_LINK(e_message_create, pchannel, this, &edit_window::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &edit_window::on_message_destroy);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit_window::_001OnSetFocus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit_window::_001OnKillFocus);

   }


   void edit_window::on_message_create(::message::message * pmessage)
   {
      
      _OnCreate();

   }


   void edit_window::on_message_destroy(::message::message * pmessage)
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
   
   //LRESULT _OnCommand(::u16, ::u16, HWND);

   LRESULT edit_window::_OnSetFocus(VOID)
   {

      return 0;

   }
   
   
   LRESULT edit_window::_OnKillFocus(VOID)
   {

      return 0;

   }


   void edit_window::get_text_composition_area(::rectangle & r)
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



