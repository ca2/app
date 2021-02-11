#include "framework.h"
#include "core/user/simple_ui/_simple_ui.h"

namespace simple_ui
{


   top::top()
   {

      m_bDrag = false;

   }


   top::~top()
   {

   }


   void top::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &top::_001OnCreate);
      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&top::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&top::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&top::_001OnMouseMove);

      MESSAGE_LINK(e_message_activate, pchannel, this, &top::_001OnActivate);
      MESSAGE_LINK(e_message_ncactivate, pchannel, this, &top::_001OnNcActivate);

//#ifdef WINDOWS_DESKTOP
//
//      MESSAGE_LINK(WM_SYSCOMMAND, pchannel, this, &top::_001OnSysCommand);
//
//#endif


   }


   void top::_001OnActivate(::message::message * pmessage)
   {

      //__pointer(::message::activate) pactivate(pmessage);

      pmessage->previous();

      set_need_redraw();

   }


   void top::_001OnNcActivate(::message::message * pmessage)
   {

      ///__pointer(::message::nc_activate) pncactivate(pmessage);

//#ifdef WINDOWS_DESKTOP
//
//      if (::IsIconic(get_handle()))
//      {
//
//         pncactivate->m_bRet = false;
//
//      }
//      else
//      {
//
//         pncactivate->m_lresult = false;
//
//         pncactivate->m_bRet = true;
//
//
//      }
//
//#else
//
//      pncactivate->m_lresult = true;
//
//      pncactivate->m_bRet = true;
//
//#endif

   }


   void top::_001OnSysCommand(::message::message * pmessage)
   {

   }


   void top::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      if(pcreate->previous())
         return;

   }


   void top::_001OnLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (pmessage->previous())
         return;

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;
      m_bDrag = false;

      m_pointLButtonDown = pmouse->m_point;
      
      m_sizeLButtonDownOffset = m_pointLButtonDown - layout().origin();

      set_mouse_capture();

      pmouse->m_bRet = true;

   }


   void top::_001OnLButtonUp(::message::message * pmessage)
   {

      m_bLButtonDown = false;

      __pointer(::message::mouse) pmouse(pmessage);

      if (pmouse->previous())
      {

         return;

      }

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_capture();

      m_bDrag = false;

      pmessage->m_bRet = true;

   }


   void top::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (m_bLButtonDown)
      {
         
         if (!m_bDrag)
         {

            m_bDrag = true;

            auto point = pmouse->m_point - m_sizeLButtonDownOffset;

            move_to(point);

            m_bDrag = false;

         }

         pmessage->m_bRet = true;

      }
      else
      {
         if(pmessage->previous())
            return;

         pmessage->m_bRet = true;
      }

   }


} // namespace account


