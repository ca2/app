#include "platform.h"
#include "frame.h"
#include "tab_impact.h"
#include "document.h"
#include "berg/user/user/toolbar.h"
#include "acme/constant/user_message.h"


namespace filemanager
{


   frame::frame()
   {



   }


   frame::~frame()
   {

   }


   void  frame::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void frame::on_create_bars()
   {

      ensure_filemanager_toolbar();

   }


   void frame::ensure_filemanager_toolbar()
   {
      ::cast < ::filemanager::document > pdocument = m_pimpactMain
         ? m_pimpactMain->get_document() : get_active_document();
      if (!pdocument || !pdocument->m_pfilemanagerdata) return;
      if (!pdocument->has_toolbar())
      {
         if (m_ptoolbarFileManager) ::simple_frame_window::hide_control_bar(m_ptoolbarFileManager);
         m_ptoolbarFileManager.release();
         return;
      }
      auto ptoolbar = pdocument->get_toolbar(this, true);
      if (m_ptoolbarFileManager && m_ptoolbarFileManager != ptoolbar)
         ::simple_frame_window::hide_control_bar(m_ptoolbarFileManager);
      m_ptoolbarFileManager = ptoolbar;
      if (ptoolbar && !ptoolbar->is_this_visible()) show_control_bar(ptoolbar);
   }

   void frame::hide_control_bar(::user::control_bar * pcontrolbar)
   {
      // Child focus changes must not remove the frame's file-manager toolbar.
      if (m_ptoolbarFileManager && pcontrolbar == m_ptoolbarFileManager) return;
      ::simple_frame_window::hide_control_bar(pcontrolbar);
   }

   void frame::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {
      ensure_filemanager_toolbar();
      ::simple_frame_window::on_perform_top_down_layout(pgraphics);
   }


   void frame::install_message_routing(::channel * pchannel)
   {

      simple_frame_window::install_message_routing(pchannel);

//#ifdef WINDOWS_DESKTOP
//      USER_MESSAGE_LINK(WM_SETTEXT, pchannel, this, &frame::_001OnSetText);
//#endif

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &frame::on_message_create);

   }


   void  frame::_001OnSetText(::message::message * pmessage)
   {
      //   ::pointer<::user::message>pusermessage(pmessage);

      pmessage->previous();

      ::filemanager::tab_impact * ptabimpact = get_typed_parent < ::filemanager::tab_impact >();
      
      if (ptabimpact != nullptr)
      {
         
         auto strWindowText = get_window_text();

         ptabimpact->set_title_by_id(m_atomTab, strWindowText);

      }

   }


   ::pointer < ::experience::frame > frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "022", "LightBlue");

      //on_select_user_style();

//      create_point_font(::user::font_list_item, "Arial", 14.0, e_font_weight_bold);
//
//      create_f64(::user::f64_width_rate, 1.2);
//
//      create_f64(::user::f64_list_item_height_rate, 2.0);

      //set_need_layout();

      return pframe;

   }



} // namespace filemanager




